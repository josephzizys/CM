project.name = "CM"
project.bindir = "bin"
project.configs = {"Release", "Debug"}

amalgamated = true

addoption("sndlib", "Location of SNDLIB source directory or install prefix")
addoption("liblo", "Optional LIBLO directory or install prefix")
addoption("fomus", "Optional FOMUS install prefix")
addoption("svnversion", "Optional SVN version number")
addoption("sdif", "Optional SDIF install prefix")

if options["juce"] then
   amalgamated = false
end

sndlib = nil
fomus = nil
liblo = nil
sdif = nil
svnvers = nil
juce_config = {"JUCE_OPENGL=0", "JUCE_CHECK_MEMORY_LEAKS=0"}
if linux then
   table.insert(juce_config, "JUCE_JACK=1")
end

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

   if (options["svnversion"]) then
      svnvers = "SVNVERSION=" .. options["svnversion"]
   elseif (options["target"] == "gnu") then
      if (fileexists( "/usr/bin/svnversion")) then
	 svnvers = "SVNVERSION=\\\"`/usr/bin/svnversion`\\\""
      elseif (fileexists( "/usr/local/bin/svnversion")) then
	 svnvers = "SVNVERSION=\\\"`/usr/local/bin/svnversion`\\\""
      end
   end

------------------------------------------
--           JUCE Amalgamated
------------------------------------------

if amalgamated then
   juce_library = newpackage() 
   juce_library.includepaths = { "src" }
   add( juce_library.config["Debug"].defines, "DEBUG=1")
   add( juce_library.config["Release"].defines, "NDEBUG=1")

   juce_library.name = "juce"
   juce_library.target = "obj/juce/juce"
   juce_library.language = "c++"
   juce_library.kind = "lib"
   juce_library.objdir = "obj/juce"
   juce_library.buildflags = {"static-runtime"}
   juce_library.files = {"src/juce.h", "src/juce_amalgamated.cpp", "src/juce_amalgamated.h"}
   --juce_library.defines = juce_config
   add(juce_library.defines, juce_config)
   if macosx then
      juce_library.buildoptions = {"-x objective-c++", "-w"}
   elseif linux then
      add(juce_library.includepaths, "/usr/include/freetype2")
   elseif windows then
      fh = io.open("src/loadlibrary.h", "w+")
      fh:write("void* dlopen();\n")
      fh:write("void* dlsym(void* ha, const char* name);\n")
      fh:close()
      fcpp = io.open("src/loadlibrary.cpp", "w+")
      fcpp:write("#ifndef STRICT\n")
      fcpp:write("#define STRICT 1\n")
      fcpp:write("#endif\n")
      fcpp:write("#define WIN32_LEAN_AND_MEAN\n")
      fcpp:write("#ifdef _MSC_VER\n")
      fcpp:write("#pragma warning (push)\n")
      fcpp:write("#pragma warning (disable : 4100 4201)\n")
      fcpp:write("#endif\n")
      fcpp:write("#ifndef DISABLE_TRANSPARENT_WINDOWS\n")
      fcpp:write("#define _WIN32_WINNT 0x0500\n")
      fcpp:write("#endif\n")
      fcpp:write("#define _UNICODE 1\n")
      fcpp:write("#define UNICODE 1\n")
      fcpp:write("#include <windows.h>\n")
      fcpp:write("#include \"loadlibrary.h\"\n")
      fcpp:write("void* dlopen() {return LoadLibrary(L\"libfomus.dll\");}\n")
      fcpp:write("void* dlsym(void* ha, const char* name) {return GetProcAddress((HINSTANCE)ha, name);}\n")
      fcpp:close()    
      add(juce_library.files, "src/loadlibrary.h")
      add(juce_library.files, "src/loadlibrary.cpp")
   end
end

numtargets=2

for i = 1,numtargets do   
   cm = i == 1
   grace = i == 2

------------------------------------------
--           Global
------------------------------------------


   mypackage = newpackage() -- premake sets 'package' to default package
   mypackage.includepaths = { "src" }
   mypackage.buildflags = {"static-runtime", "no-main"}
   mypackage.language = "c++"
   add(mypackage.defines, juce_config)
   add(mypackage.defines, "COMMONMUSIC=1")

   if amalgamated then 
      add(mypackage.libpaths, "obj/juce")
      add(mypackage.links, "juce")
   end

   mypackage.files = {

      "src/Syntax.cpp", "src/Syntax.h",
      "src/CmSupport.cpp", "src/CmSupport.h",
      "src/Console.cpp", "src/Console.h",
      "src/Scheme.cpp", "src/Scheme.h",
      "src/Preferences.cpp", "src/Preferences.h",
      "src/SchemeSources.cpp", "src/SchemeSources.h",
      "src/Midi.cpp", "src/Midi.h",
      "src/Csound.cpp", "src/Csound.h",
      "src/Main.cpp", "src/Main.h",
      "src/Resources.cpp", "src/Resources.h",
      "src/SndLib.cpp", "src/SndLib.h",
      "src/SndLibBridge.cpp", "src/SndLibBridge.h",
      "src/Instruments.cpp", "src/Instruments.h"
   }

   if options["liblo"] then
      add(mypackage.files,"src/Osc.cpp")
      add(mypackage.files,"src/Osc.h")
   end

   if  options["fomus"] then
      add(mypackage.files,"src/Fomus.cpp")
      add(mypackage.files,"src/Fomus.h")
   end

   add( mypackage.config["Debug"].defines, "DEBUG=1")
   add( mypackage.config["Release"].defines, "NDEBUG=1")

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
      add(mypackage.files, "src/Fonts.h")
      add(mypackage.files, "src/Help.cpp")
      add(mypackage.files, "src/Help.h")
      add(mypackage.files, "src/Commands.cpp")
      add(mypackage.files, "src/Commands.h")
      add(mypackage.files, "src/Menus.cpp")
      add(mypackage.files, "src/Menus.h")
      add(mypackage.files, "src/CodeEditor.cpp")
      add(mypackage.files, "src/CodeEditor.h")
      add(mypackage.files, "src/Documentation.cpp")
      add(mypackage.files, "src/Documentation.h")
      add(mypackage.files, "src/Images.cpp")
      add(mypackage.files, "src/Images.h")
      add(mypackage.files, "src/Audio.cpp")
      add(mypackage.files, "src/Audio.h")
      add(mypackage.files, "src/Cells.h")
      add(mypackage.files, "src/Cells.cpp")
      add(mypackage.files, "src/Plot.h")
      add(mypackage.files, "src/Plot.cpp")
      add(mypackage.files, "src/PlotEditor.h")
      add(mypackage.files, "src/PlotEditor.cpp")
      add(mypackage.files, "src/PlotWindow.h")
      add(mypackage.files, "src/PlotWindow.cpp")
      add(mypackage.files, "src/Alerts.h")
      add(mypackage.files, "src/Alerts.cpp")
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
      add(mypackage.defines, "WITH_SNDLIB=1")
      if os.fileexists(sndlib .. "mus-config.h") then
         add(mypackage.includepaths, sndlib)
         add(mypackage.libpaths, sndlib )
	 if (options["target"] == "vs2005" or options["target"] == "vs2008") then
	    add(mypackage.config["Debug"].links, "sndlib_debug")
	    add(mypackage.config["Release"].links, "sndlib")
	 else
	    sndlib_config = sndlib .. "sndlib-config"
            if os.fileexists(sndlib .. "libsndlib.a") then
               add(mypackage.linkoptions, sndlib .. "libsndlib.a")
            else
               error("--sndlib: can't find static sndlib library " .. sndlib .. "libsndlib.a")
            end
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

   else
      error("you must provide a --sndlib installation")
   end

------------------------------------------
--           FOMUS
------------------------------------------

   if options["fomus"] then
      fomus = insure_slash(options["fomus"])
      add(mypackage.defines, "WITH_FOMUS=1")
      add(mypackage.defines, "FOMUSLIBPATH=\\\"" .. fomus .. "lib\\\"")
      if os.fileexists(fomus .. "include/fomus.h") then
         add(mypackage.includepaths, fomus .. "include")
         --add(mypackage.libpaths, fomus .. "lib")
         --add(mypackage.links, "fomus")
      else
         error("--fomus must point to the FOMUS install prefix (eg. /usr or /usr/local)")
      end
   end

------------------------------------------
--           SDIF
------------------------------------------

   if options["sdif"] then
      if (windows) then
	 sdiflibname="sdif.lib";
      else
	 sdiflibname="libsdif.a";
      end

      sdif = insure_slash(options["sdif"])
      add(mypackage.defines, "WITH_SDIF=1")
      if os.fileexists(sdif .. "include/sdif.h") then
         add(mypackage.includepaths, sdif .. "include")
      else
         error("--sdif: can't find sdif.h in " .. sdif .. "include/")
      end
      if os.fileexists(sdif .. "lib/" .. sdiflibname) then
         add(mypackage.linkoptions, sdif .. "lib/" .. sdiflibname)
      else
         error("--sdif: can't find " .. sdiflibname .. " in " .. sdif .. "lib/")
      end
   end

-----------------------------------------
--           LIBLO
------------------------------------------

   if options["liblo"] then
      liblo = insure_slash(options["liblo"])
      add(mypackage.defines, "WITH_LIBLO")
      if os.fileexists(liblo .. "include/lo/lo.h") then
         add(mypackage.includepaths, liblo .. "include")
         add(mypackage.libpaths, liblo .. "lib")
         add(mypackage.links, "lo")
      else
         if os.fileexists(liblo .. "lo/lo.h") then
            add(mypackage.includepaths, liblo )
            if os.fileexists(liblo .. "src/.libs/liblo.a") then
               add(mypackage.linkoptions, liblo .. "src/.libs/liblo.a")
            else
               error("--liblo: can't find static liblo library " .. liblo .. "src/.libs/liblo.a")
            end
         else
            error("--liblo: can't find include file lo/lo.h")
         end
      end
      
      if windows then
	 add(mypackage.defines, "WIN32")
	 add(mypackage.defines, "_CRT_SECURE_NO_DEPRECATE")
	 add(mypackage.defines, "HAVE_CONFIG_H")
	 add(mypackage.defines, "LIBLO_LIB")
	 add(mypackage.links, "lo")
	 add(mypackage.links, "user32")
	 add(mypackage.links, "wsock32")
	 add(mypackage.links, "ws2_32")
	 add(mypackage.links, "pthreadVC2")
      end

   end
   
   if (svnvers) then
      add(mypackage.defines, svnvers)
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
      add(mypackage.linkoptions, "-framework QTKit")
      add(mypackage.linkoptions, "-framework DiscRecording")
      add(mypackage.linkoptions, "-framework WebKit")
      add(mypackage.linkoptions, "-framework IOKIT")
      if (grace) then
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
