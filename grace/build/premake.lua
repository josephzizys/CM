addoption("release", "optional release number nnn (printed n.n.n)")
addoption("revision", "optional source revision number")
addoption("juce", "required location of juce directory")
addoption("csound", "build with csound support")
addoption("fomus", "build with fomus support")
addoption("debug", "build against debug libs")

juce_dir = ""

if options["juce"] then
   juce_dir = options["juce"]
elseif (not options["clean"]) and (not options["help"]) then
   error("Use --juce and provide the location of the JUCE directory")
end

source_dir = "../../src/"

gracecl_files = {"Buffer", "Console", "Editor", "Grace", 
		 "Layer", "Lisp", "Help", "Resources",
		 "Plotter", "Points", "Syntab", "Syntax"}

grace_files = {"Buffer", "ChickenBridge", "Console", 
	       "Csound", "Fomus",
	       "Editor", "Grace", 
	       "Help", "Layer", "Midi", "MidiReceiveComponent", "Resources",
	       "Plotter", "Points", "Scheme", "Syntab", "Syntax", "Toolbox"
	    }

function source_files(files)
   local relative = {}
   for i,f in files do
      table.insert(relative, source_dir .. f .. ".h")
      table.insert(relative, source_dir .. f .. ".cpp")
   end
   return relative
end

function add_release_options()
   if (options["release"]) then
      table.insert(package.defines, "RELEASE=" .. options["release"] )
   end
   if (options["revision"]) then
      table.insert(package.defines, "REVISION=" .. options["revision"] )
   end
end

project.name = "GRACE"
project.bindir = "build"
-- hack: reorder configurations to make Release the default
project.configs = {"Release", "Debug"}

------------------------------------------------------------------------------
------------------------------- GraceCL Package ------------------------------
------------------------------------------------------------------------------

package = newpackage()
package.name = "GraceCL"
package.language = "c++"
package.kind = "exe"
package.files = { source_files( gracecl_files ) }
package.includepaths = {juce_dir, "/usr/local/include", "/usr/include" }
package.libpaths = {juce_dir .. "/bin", "/usr/local/lib", "/usr/lib" }
package.objdir = "build/gracecl.obj"

if (macosx) then
   package.config["Release"].target = "Release/GraceCL.app/Contents/MacOS/GraceCL"
   package.config["Debug"].target = "Debug/GraceCL.app/Contents/MacOS/GraceCL"
   package.defines = { "MACOSX=1" }
   package.links = {"juce -framework Carbon -framework CoreServices -framework CoreAudio -framework CoreMidi -framework ApplicationServices -framework OpenGL -framework AGL -framework QuickTime -framework IOKIT"}
elseif ( linux ) then
   package.config["Release"].target = "Release/GraceCL/bin/gracecl"
   package.config["Debug"].target = "Debug/GraceCL/bin/gracecl"
   package.defines = { "LINUX=1" }
   package.links = {"juce", "freetype", "GLU", "GL", "asound"}
elseif ( windows ) then
   package.config["Release"].target = "Release/GraceCL/GraceCL"
   package.config["Debug"].target = "Debug/GraceCL/GraceCL"
   package.defines = { "WINDOWS=1" }
end

add_release_options()

------------------------------------------------------------------------------
-------------------------------  Grace Package  ------------------------------
------------------------------------------------------------------------------

package = newpackage()
package.name = "Grace"
package.language = "c++"
package.kind = "exe"

package.files = { source_files( grace_files ) }
package.includepaths = { juce_dir, "/usr/local/include", "/usr/include" }
package.libpaths = { juce_dir .. "/bin", "/usr/local/lib" }
package.objdir = "build/grace.obj"

if (macosx) then
   package.config["Release"].target = "Release/Grace.app/Contents/MacOS/Grace"
   package.config["Debug"].target = "Debug/Grace.app/Contents/MacOS/Grace"
   package.defines = { "MACOSX=1", "SCHEME=1" }
   frameworks = " -framework Carbon -framework CoreServices -framework CoreAudio -framework CoreMidi -framework ApplicationServices -framework OpenGL -framework AGL -framework QuickTime -framework IOKIT"
   if ( options["csound"] ) then
      frameworks = frameworks .. " -framework CsoundLib"
   end
-- Hack: add static lib as fullpathname to .linkoptions and NOT as 
-- library in the .links else the static lib will be ignored by gcc
   package.config["Release"].linkoptions = { "/usr/local/lib/libchicken.a" }
   package.config["Debug"].linkoptions = { "/usr/local/lib/libchickendebug.a" }
   package.config["Release"].links = { "juce" .. frameworks}
   package.config["Debug"].links = { "jucedebug" .. frameworks}
elseif ( linux ) then
   package.defines = { "LINUX=1", "SCHEME=1"}
   package.config["Release"].target = "Release/Grace/bin/grace"
   package.config["Debug"].target = "Debug/Grace/bin/grace"
   package.config["Release"].linkoptions = { "/usr/local/lib/libchicken.a" }
   package.config["Debug"].linkoptions = { "/usr/local/lib/libchickendebug.a" }
   package.config["Release"].links = { "juce", "freetype", "GLU", "GL", "asound"}
   package.config["Debug"].links = { "jucedebug", "freetype", "GLU", "GL", "asound"}
   if ( options["csound"] ) then
      table.insert(package.links, "csound")
      table.insert(package.links, "sndfile")
   end
elseif ( windows ) then
   package.config["Release"].target = "Release/Grace/Grace"
   package.config["Debug"].target = "Debug/Grace/Grace"
   package.defines = { "WINDOWS=1", "SCHEME=1" }
end

if ( options["csound"] ) then
   table.insert(package.defines, "PORTCSOUND=1")
end

if ( options["fomus"] ) then
   table.insert(package.defines, "FOMUS=1")
end

add_release_options()

-- EOF










