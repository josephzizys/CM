project.name = "CM"
project.bindir = "bin"
project.configs = {"Release", "Debug"}

addoption("juce", "Location of JUCE source directory or install prefix")
addoption("sndlib", "Optional location of SNDLIB source directory or install prefix")
addoption("chicken", "Optional location of CHICKEN source directory or install prefix")

sndlib = nil
chicken = nil

function insure_slash(path) 
  --insure slash at end of directory so concatenation works
  if not (string.sub(path, string.len(path)) == "/")  then
     path = path .. "/"
  end
  return path
end

function add(t, element)
   table.insert(t, element)
end

if not (options["clean"] or options["help"] or options["version"]) then

for i = 1,2 do   
   cm = i == 1
   grace = i == 2

------------------------------------------
--           Global
------------------------------------------

   mypackage = newpackage() -- premake sets 'package' to default package
   mypackage.includepaths = { "src" }
   mypackage.linkflags = {"static-runtime"}
   mypackage.language = "c++"
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
   mypackage.config["Debug"].defines = {"DEBUG=1"}

------------------------------------------
--           CM
------------------------------------------
  
   if (cm) then
      mypackage.name = "cm"
      mypackage.target = "cm"
      mypackage.kind = "exe"
      mypackage.objdir = "obj/cm"
   end

------------------------------------------
--           Grace
------------------------------------------

   if (grace) then
      mypackage.name = "grace"
      mypackage.target = "Grace"
      mypackage.kind = "winexe"
      mypackage.objdir = "obj/grace"
      add(mypackage.defines, "GRACE=1")
      add(mypackage.files, "src/Fonts.cpp")
      add(mypackage.files, "src/Help.cpp")
      add(mypackage.files, "src/Commands.cpp")
      add(mypackage.files, "src/Menus.cpp")
      add(mypackage.files, "src/TextEditor.cpp")
      add(mypackage.files, "src/Documentation.cpp")
      add(mypackage.files, "src/Images.cpp")
      add(mypackage.files, "src/Audio.cpp")
   end

------------------------------------------
--           Juce
------------------------------------------

   if options["juce"] then
      juce = insure_slash(options["juce"])
      juce_lib = "juce"
      if os.fileexists(juce .. "juce.h") then
         add(mypackage.includepaths, juce)
         add(mypackage.libpaths, juce .. "bin")
         if os.fileexists(juce .. "bin/libjuce_debug.a") then
            juce_debug_lib = "juce_debug"
         elseif os.fileexists(juce .. "bin/libjucedebug.a") then
            juce_debug_lib = "jucedebug"
         else
            juce_debug_lib = "juce"
            print("WARNING: no juce debug lib found for CONFIG=Debug")
         end
      elseif os.fileexists(juce .. "include/juce/juce.h") then
         add(mypackage.includepaths, juce .. "include/juce")
         add(mypackage.libpaths, juce .. "lib")
         juce_debug_lib = "juce"
         print("WARNING: no juce debug lib when linking against installed juce")
      else
         error("--juce must point to either juce source directory or juce install prefix (eg. /usr or /usr/local)")
      end
      mypackage.config["Release"].links = { juce_lib }
      mypackage.config["Debug"].links = { juce_debug_lib }
   else
      error("CM requires juce, add --juce to your premake options")
   end
   
------------------------------------------
--           Sndlib
------------------------------------------
   
   if options["sndlib"] then
      sndlib = insure_slash(options["sndlib"])
      add(mypackage.defines, "SNDLIB=1")
      add(mypackage.files, "src/SndLib.cpp")
      add(mypackage.files, "src/SndLibBridge.cpp")
      add(mypackage.files, "src/Instruments.cpp")
      if os.fileexists(sndlib .. "mus-config.h") then
         add(mypackage.includepaths, sndlib)
         add(mypackage.linkoptions, sndlib .. "sndlib.a")
         sndlib_config = sndlib .. "sndlib-config"
      elseif os.fileexists(sndlib .. "include/mus-config.h") then
         add(mypackage.includepaths, sndlib .. "include")
         add(mypackage.libpaths, sndlin .. "lib")
         add(mypackage.links, "sndlib")
         sndlib_config = sndlib .. "bin/sndlib-config"
      else
	 error("--sndlib must point to either sndlib source directory or sndlib install prefix (eg. /usr or /usr/local)")
      end
      if linux then
         -- run the snd-config command to get the libs we need to
         -- include and add them to the linking set
         os.execute(sndlib_config .. " --libs > /tmp/sndlibs")
         for line in io.lines("/tmp/sndlibs") do 
            add(mypackage.linkoptions, line)
         end
      end

------------------------------------------
--           Chicken
------------------------------------------
   
   elseif options["chicken"] then
      chicken = insure_slash(options["chicken"])
      add(mypackage.defines, "CHICKEN=1")
      add(mypackage.files, "src/Chicken.cpp")
      add(mypackage.files, "src/ChickenBridge.cpp")
      if os.fileexists(chicken .. "chicken.h") then
         add(mypackage.includepaths, chicken)
         add(mypackage.linkoptions, chicken .. "libchicken.a")
      elseif os.fileexists(chicken .. "include/chicken.h") then
         add(mypackage.includepaths, chicken .. "include")
         add(mypackage.libpaths, chicken .. "lib")
         add(mypackage.links, "chicken")
      else
         error("--chicken must point to either chicken source directory or chicken install prefix (eg. /usr or /usr/local)")
      end
   else
      error("CM requires a Scheme implementation, add either --sndlib or --chicken to your premake options")
   end
   
------------------------------------------
--           OS Specific 
------------------------------------------
         
   if macosx then
      add(mypackage.defines, "MACOSX=1")
      add(mypackage.linkoptions, "-framework Carbon")
      add(mypackage.linkoptions, "-framework Cocoa")
      add(mypackage.linkoptions, "-framework CoreServices")
      add(mypackage.linkoptions, "-framework CoreAudio")
      add(mypackage.linkoptions, "-framework CoreMidi")
      add(mypackage.linkoptions, "-framework ApplicationServices")
      add(mypackage.linkoptions, "-framework OpenGL")
      add(mypackage.linkoptions, "-framework AGL")
      add(mypackage.linkoptions, "-framework QuickTime")
      add(mypackage.linkoptions, "-framework IOKIT")
   elseif linux then
      add(mypackage.defines, "LINUX=1")
      add(mypackage.links, "pthread")
      add(mypackage.links, "rt")
      add(mypackage.links, "X11")
      add(mypackage.links, "GL")
      add(mypackage.links, "GLU")
      add(mypackage.links, "Xinerama")
      add(mypackage.links, "asound")
      add(mypackage.links, "freetype")
      add(mypackage.libpaths, "/usr/X11R6/lib/")
   elseif windows then
   
      -- premake outputs libs defined at the config level BEFORE slibs
      -- defined at the package level. on windows this causes linking
      -- to fail because -ljuce appears after the libs listed below (i
      -- dont know why this should be the case but it is). this means
      -- that to ensure -ljuce appears BEFORE these libs we add them
      -- to the configs rather than to the package as on linux an
      -- macos. 
      for c in {"Release", "Debug"} do
         add(mypackage.defines, "WINDOWS=1")
         add(mypackage.config[c].links, "gdi32")
         add(mypackage.config[c].links, "comdlg32")
         add(mypackage.config[c].links, "shell32")
         add(mypackage.config[c].links, "ole32")
         add(mypackage.config[c].links, "vfw32")
         add(mypackage.config[c].links, "winmm")
         add(mypackage.config[c].links, "wininet")
         add(mypackage.config[c].links, "dsound")
         add(mypackage.config[c].links, "wsock32")
         add(mypackage.config[c].links, "opengl32")
         add(mypackage.config[c].links, "glu32")
         add(mypackage.config[c].links, "uuid")
         add(mypackage.config[c].links, "rpcrt4")
      end
   end
end

end
