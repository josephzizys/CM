addoption("juce", "Location of JUCE  directory")
addoption("sndlib", "Optional location of SNDLIB directory")
addoption("chicken", "Optional location of CHICKEN directory")

juce = ""
juce_debug = ""
sndlib = ""
chicken = ""

if not (options["clean"] or options["help"] or options["version"]) then
   if not options["juce"] then
      error("CM requires JUCE, add '--juce /path/to/juce' to your premake options.")
   end
   juce = options["juce"]
   if not (string.sub(juce,string.len(juce)) == "/")  then
      --insure slash at end of directory so concatenation works
      juce = juce .. "/"
   end
   -- sanity check: dont build if juce.h is not found
   if not os.fileexists(juce .. "juce.h") then
      error("--juce directory does not contain juce.h")
   end
   -- arrg! juce debug lib can be either "libjuce_debug" or "jucedebug"
   if os.fileexists(juce .. "bin/libjuce_debug.a") then
      juce_debug="juce_debug"
   elseif os.fileexists(juce .. "bin/libjucedebug.a") then
      juce_debug="jucedebug"
   else
      print("WARNING: no JUCE debug lib found for CONFIG=Debug")
   end
   if options["sndlib"] then
      sndlib = options["sndlib"]
      -- insure slash at end directory so that concatenation works.
      if not (string.sub(sndlib, string.len(sndlib)) == "/") then
	 sndlib = sndlib .. "/"
      end
      -- sanity check: dont build if mus-config.h is not found
      if not os.fileexists(sndlib .. "mus-config.h") then
	 error("--sndlib directory does not contain mus-config.h")
      end
   elseif options["chicken"] then
      chicken = options["chicken"]
      --insure slash at end of directory so that concatenation works.
      if not (string.sub(chicken, string.len(chicken)) == "/")  then
	 chicken = chicken .. "/"
      end
      -- sanity check: dont attempt to build if chicken.h is not found
      if not os.fileexists(chicken .. "chicken.h") then
	 error("--chicken directory does not contain chicken.h")
      end
   else 
      error("CM requires a Scheme implementation, add either '--sndlib /path/to/sndlib' or '--chicken /path/to/chicken' to your premake options.")
   end
end

------------------------------------------
--           Global settings
------------------------------------------

project.name = "CM"
project.bindir = "bin"
project.configs = {"Release", "Debug"}
mypackage = package -- premake sets 'package' to default package

for i = 1,2 do   
   mypackage.language = "c++"
   -- the core set of files for all builds
   mypackage.files = {
      "src/Scanner.cpp",
      "src/Syntax.cpp",
      "src/CmSupport.cpp",
      "src/Console.cpp",
      "src/Scheme.cpp", 
      "src/Preferences.cpp", 
      "src/SchemeSources.cpp", 
      "src/Midi.cpp", 
      "src/Main.cpp"
   }
   
   if (i == 1) then
      mypackage.name = "cm"
      mypackage.target = "cm"
      mypackage.kind = "exe"
      mypackage.objdir = "obj/cm"
   else
      mypackage.name = "grace"
      mypackage.target = "Grace"
      mypackage.kind = "winexe"
      mypackage.objdir = "obj/grace"
      mypackage.defines = {"GRACE=1"}
      --if options["texteditor-can-colorize"] then
      --  table.insert(mypackage.defines, "TEXTEDITOR_CAN_COLORIZE")
      --end
      --table.insert(mypackage.files, "src/Preferences.cpp")
      table.insert(mypackage.files, "src/Fonts.cpp")
      table.insert(mypackage.files, "src/Help.cpp")
      table.insert(mypackage.files, "src/Commands.cpp")
      table.insert(mypackage.files, "src/Menus.cpp")
      table.insert(mypackage.files, "src/TextEditor.cpp")
      table.insert(mypackage.files, "src/Documentation.cpp")
      table.insert(mypackage.files, "src/Images.cpp")
      table.insert(mypackage.files, "src/Audio.cpp")
   end   
   
   if options["juce"] then  -- not cleaning etc
      -- scheme specific files
      if options["chicken"] then
	 table.insert(mypackage.files, "src/Chicken.cpp")
	 table.insert(mypackage.files, "src/ChickenBridge.cpp")
      elseif options["sndlib"] then
	 table.insert(mypackage.files, "src/SndLib.cpp")
	 table.insert(mypackage.files, "src/SndLibBridge.cpp")
	 table.insert(mypackage.files, "src/Instruments.cpp")
      end
      
      mypackage.includepaths = { juce, "src" }
      mypackage.libpaths = {juce .. "bin"}
      mypackage.linkflags = {"static-runtime"}
      
      if options["sndlib"] then
	 table.insert(mypackage.defines, "SNDLIB=1")
	 table.insert(mypackage.includepaths, sndlib)
      elseif options["chicken"] then
	 table.insert(mypackage.defines, "CHICKEN=1")
	 table.insert(mypackage.includepaths, chicken)
      end
      
      table.insert(mypackage.config["Debug"].defines, "DEBUG=1")
      
      ------------------------------------------
      --           OS Specific 
      ------------------------------------------
      
      mac_links = ""
      linux_links = ""
      
      if macosx then
	 table.insert(mypackage.defines, "MACOSX=1")
	 mac_links =             " -framework Carbon "
	 mac_links = mac_links .. "-framework Cocoa "
	 mac_links = mac_links .. "-framework CoreServices "
	 mac_links = mac_links .. "-framework CoreAudio "
	 mac_links = mac_links .. "-framework CoreMidi "
	 mac_links = mac_links .. "-framework ApplicationServices "
	 mac_links = mac_links .. "-framework OpenGL "
	 mac_links = mac_links .. "-framework AGL "
	 mac_links = mac_links .. "-framework QuickTime "
	 mac_links = mac_links .. "-framework IOKIT"
	 
	 if options["sndlib"] then
	    mac_links = mac_links .. " " .. sndlib .. "sndlib.a"
	 elseif options["chicken"] then
	    mac_links = mac_links .. " " .. chicken .. "libchicken.a"
	 end
	 mypackage.config["Release"].links = {"juce" .. mac_links}
	 mypackage.config["Debug"].links = {juce_debug .. mac_links}
      elseif linux then
	 table.insert(mypackage.defines, "LINUX=1")
	 linux_links = " -l freetype"
	 linux_links = linux_links .. " -l pthread"
	 linux_links = linux_links .. " -l rt"
	 linux_links = linux_links .. " -l X11"
	 linux_links = linux_links .. " -l GL"
	 linux_links = linux_links .. " -l GLU"
	 linux_links = linux_links .. " -l Xinerama"
	 linux_links = linux_links .. " -l asound"
	 if options["sndlib"] then
	    -- run the snd-config command to get the libs we need to
	    -- include and add them to the linking set
	    os.execute(sndlib .. "sndlib-config --libs > /tmp/sndlibs")
	    for line in io.lines("/tmp/sndlibs") do 
	       linux_links = linux_links .. " " .. line
	    end
	    --linux_links = linux_links .. " -l gsl"
	    --linux_links = linux_links .. " -l gslcblas"
	    --linux_links = linux_links .. " -l m"
	    linux_links = linux_links .. " " .. sndlib .. "sndlib.a"
	 elseif options["chicken"] then
	    mac_links = mac_links .. " " .. chicken .. "libchicken.a"
	 end
	 table.insert(mypackage.libpaths, "/usr/X11R6/lib/")
	 mypackage.config["Release"].links = {"juce" .. linux_links}
	 mypackage.config["Debug"].links = {juce_debug .. linux_links}
      end
   end
   if (i == 1) then
      mypackage = newpackage()
   end
end

-- eof
