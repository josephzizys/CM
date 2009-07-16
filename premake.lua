project.name = "CM"
project.bindir = "bin"
project.configs = {"Release", "Debug"}

amalgamated = true

addoption("juce", "Location of JUCE source directory or install prefix")
addoption("sndlib", "Optional location of SNDLIB source directory or install prefix")
addoption("chicken", "Optional location of CHICKEN source directory or install prefix")
addoption("fomus", "Optional FOMUS install prefix")

if options["juce"] then
   amalgamated = false
end

sndlib = nil
chicken = nil
fomus = nil

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

------------------------------------------
--           JUCE Amalgamated
------------------------------------------

if amalgamated then
   juce_library = newpackage() 
   juce_library.includepaths = { "src" }
   juce_library.name = "juce"
   juce_library.target = "obj/juce/juce"
   juce_library.language = "c++"
   juce_library.kind = "lib"
   juce_library.objdir = "obj/juce"
   juce_library.buildflags = {"static-runtime"}
   juce_library.files = {"src/juce.h", "src/juce_amalgamated.cpp", "src/juce_amalgamated.h"}
   if macosx then
      juce_library.buildoptions = {"-x objective-c++", "-w"}
      add(juce_library.defines, "MACOSX")
   elseif linux then
      add(juce_library.defines, "LINUX")
      add(juce_library.includepaths, "/usr/include/freetype2")
   elseif windows then
      add(juce_library.defines, "WINDOWS")
   end
end


for i = 1,3 do   
   cm = i == 1
   grace = i == 2
   gracecl = i == 3

------------------------------------------
--           Global
------------------------------------------

   mypackage = newpackage() -- premake sets 'package' to default package
   mypackage.includepaths = { "src" }
   mypackage.buildflags = {"static-runtime", "no-main"}
   mypackage.language = "c++"

   if amalgamated then 
      add(mypackage.libpaths, "obj/juce")
      add(mypackage.links, "juce")
   end

   mypackage.files = {

      "src/Scanner.cpp", "src/Scanner.h",
      "src/Syntax.cpp", "src/Syntax.h",
      "src/CmSupport.cpp", "src/CmSupport.h",
      "src/Console.cpp", "src/Console.h",
      "src/Scheme.cpp", "src/Scheme.h",
      "src/Preferences.cpp", "src/Preferences.h",
      "src/SchemeSources.cpp", "src/SchemeSources.h",
      "src/Midi.cpp", "src/Midi.h",
      "src/Csound.cpp", "src/Csound.h",
      "src/Main.cpp", "src/Main.h"
   }
   if  options["fomus"] then
      add(mypackage.files,"src/Fomus.cpp")
      add(mypackage.files,"src/Fomus.h")
   end
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
--           Grace and GraceCL
------------------------------------------

   if (grace or gracecl) then
      if (grace) then
	 mypackage.name = "grace"
	 mypackage.target = "Grace"
	 mypackage.kind = "winexe"
	 mypackage.objdir = "obj/grace"
	 add(mypackage.defines, "GRACE=1")
      else
	 mypackage.name = "gracecl"
	 mypackage.target = "GraceCL"
	 mypackage.kind = "winexe"
	 mypackage.objdir = "obj/gracecl"
	 add(mypackage.defines, "GRACE=1")
	 add(mypackage.defines, "GRACECL=1")
      end
      add(mypackage.files, "src/Fonts.cpp") 
      add(mypackage.files, "src/Fonts.h")
      add(mypackage.files, "src/Help.cpp")
      add(mypackage.files, "src/Help.h")
      add(mypackage.files, "src/Commands.cpp")
      add(mypackage.files, "src/Commands.h")
      add(mypackage.files, "src/Menus.cpp")
      add(mypackage.files, "src/Menus.h")
      add(mypackage.files, "src/TextEditor.cpp")
      add(mypackage.files, "src/TextEditor.h")
      add(mypackage.files, "src/Documentation.cpp")
      add(mypackage.files, "src/Documentation.h")
      add(mypackage.files, "src/Images.cpp")
      add(mypackage.files, "src/Images.h")
      add(mypackage.files, "src/Audio.cpp")
      add(mypackage.files, "src/Audio.h")
      add(mypackage.files, "src/CommonLisp.cpp")
      add(mypackage.files, "src/CommonLisp.h")
      add(mypackage.files, "src/Triggers.cpp")
      add(mypackage.files, "src/Triggers.h")
      add(mypackage.files, "src/Plot.h")
      add(mypackage.files, "src/Plot.cpp")
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

	 -- windows nonsense
         if os.fileexists(juce .. "bin/jucelib_static_Win32.lib") then
            juce_lib = "jucelib_static_Win32"
         else
            juce_lib = "juce"
         end
         if os.fileexists(juce .. "bin/libjuce_debug.a") then
            juce_debug_lib = "juce_debug"
         elseif os.fileexists(juce .. "bin/libjucedebug.a") then
            juce_debug_lib = "jucedebug"
         elseif os.fileexists(juce .. "bin/jucelib_static_Win32_debug.lib") then
            juce_debug_lib = "jucelib_static_Win32_debug"
         else
            juce_debug_lib = juce_lib
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

   elseif not amalgamated then
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
         add(mypackage.libpaths, sndlib )
	 if options["target"] == "vs2005" then
	    add(mypackage.config["Debug"].links, "sndlib_debug")
	    add(mypackage.config["Release"].links, "sndlib")
	 else
	    add(mypackage.links, "sndlib" )
	    sndlib_config = sndlib .. "sndlib-config"
	 end

      elseif os.fileexists(sndlib .. "include/mus-config.h") then
         add(mypackage.includepaths, sndlib .. "include")
         add(mypackage.libpaths, sndlib .. "lib")
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
--           FOMUS
------------------------------------------

   if options["fomus"] then
      fomus = insure_slash(options["fomus"])
      add(mypackage.defines, "WITHFOMUS=1")
      if os.fileexists(fomus .. "include/fomus.h") then
         add(mypackage.includepaths, fomus .. "include")
         add(mypackage.libpaths, fomus .. "lib")
         add(mypackage.links, "fomus")
      else
         error("--fomus must point to the FOMUS install prefix (eg. /usr or /usr/local)")
      end

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
      add(mypackage.linkoptions, "-framework WebKit")
      add(mypackage.linkoptions, "-framework IOKIT")
      if (grace or gracecl) then
	 mypackage.postbuildcommands = 
	    {"cp res/etc/" .. mypackage.target .. ".plist bin/" .. mypackage.target .. ".app/Contents/Info.plist",
	     "mkdir -p bin/" .. mypackage.target ..  ".app/Contents/Resources",
	     "cp res/etc/icons.icns bin/"  .. mypackage.target .. ".app/Contents/Resources"}
      end
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
      add(mypackage.defines, "WINDOWS=1")
      if (options["target"] == "vs2005" or options["target"] == "vs2008" ) then
	 add(mypackage.config["Debug"].links, "comsuppwd")
	 add(mypackage.config["Release"].links, "comsuppw")
	 table.insert(mypackage.files, matchfiles("res/etc/*.rc"))
      elseif options["target"] == "gnu" then
	 -- premake outputs libs defined at the config level BEFORE slibs
	 -- defined at the package level. on windows this causes linking
	 -- to fail because -ljuce appears after the libs listed below (i
	 -- dont know why this should be the case but it is). this means
	 -- that to ensure -ljuce appears BEFORE these libs we add them
	 -- to the configs rather than to the package as on linux an
	 -- macos. 
	 for j = 1,2 do   
	    if j == 1 then
	       cfg = "Release"
	    else
	       cfg = "Debug"
	    end
	    add(mypackage.config[cfg].links, "gdi32")
	    add(mypackage.config[cfg].links, "comdlg32")
	    add(mypackage.config[cfg].links, "shell32")
	    add(mypackage.config[cfg].links, "ole32")
	    add(mypackage.config[cfg].links, "vfw32")
	    add(mypackage.config[cfg].links, "winmm")
	    add(mypackage.config[cfg].links, "wininet")
	    add(mypackage.config[cfg].links, "dsound")
	    add(mypackage.config[cfg].links, "wsock32")
	    add(mypackage.config[cfg].links, "opengl32")
	    add(mypackage.config[cfg].links, "glu32")
	    add(mypackage.config[cfg].links, "uuid")
	    add(mypackage.config[cfg].links, "rpcrt4")
	 end
      end
   end
end

end
