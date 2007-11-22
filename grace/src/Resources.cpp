/*************************************************************************
 * Copyright (C) 2007 Todd Ingalls, Rick Taube.                          *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the Lisp Lesser Gnu Public License. The text of *
 * this agreement is available at http://www.cliki.net/LLGPL             *
 *************************************************************************/

// $Revision$
// $Date$ 

#include "Resources.h"
#include "Editor.h"
#include "Grace.h"

File getGraceResourceDirectory() {
  // returns the "site wide" resource directory for grace determined
  // relative to the directory that contains the running executable:
  //   MacOSX:   {exedir}/../Resources/
  //   Windows:  {exedir}/Resources/
  //   Linux:    {exedir}/../lib/grace
  File exe = File::getSpecialLocation(File::currentExecutableFile);

  if ( isHostWindows() )     // win32: "{exe}/Resources/"
    return exe.getSiblingFile(T("Resources"));
  else if ( isHostLinux() ) {  // Linux: "{exe}../lib/grace/"
    //    return
    // exe.getParentDirectory().getParentDirectory().getChildFile(T("lib/grace"));
    // goddam it, currentExecutableFile is nonsense on linux. for now
    // i simply return a hardwired path.
    return File(T("/usr/local/lib/grace"));
  }
  else if ( isHostMacOSX() ) // OSX:   "{exe}../Resources/"
    return exe.getParentDirectory().getParentDirectory().getChildFile(T("Resources"));
  else
    return File::nonexistent;
}

int getHostOS() {
  SystemStats::OperatingSystemType sys = SystemStats::getOperatingSystemType();
  return (int)sys;
}

bool isHostWindows () {
  return ((getHostOS() & SystemStats::Windows) != 0);
}

bool isHostLinux() {
  return ((getHostOS() & SystemStats::Linux) != 0);
}

bool isHostMacOSX() {
  return ((getHostOS() & SystemStats::MacOSX) != 0);
}

String getPlotterHelp () {
  // REMOVE!
  return String::empty;
}

String getEditorHelp () {
  // REMOVE!
  return String::empty;
}

void addCommonHelpItems(PopupMenu* menu, GraceWindowType w) {
  PopupMenu sub1;
  if (w==winConsole)
    menu->addItem(cmdHelpWindow+w, T("Console Help"));
  else if (w==winEditor)
    menu->addItem(cmdHelpWindow+w, T("Editor Help"));
  else if (w==winPlotter)
    menu->addItem(cmdHelpWindow+w, T("Plotter Help"));
  menu->addSeparator();
#ifdef SCHEME
  menu->addItem(cmdHelpWindow+12, T("Scheme")); 
#endif 
  sub1.addItem(cmdHelpSalTutorial+0, T("Hello World"));
  sub1.addItem(cmdHelpSalTutorial+1, T("Symbolic Expressions"));
  sub1.addItem(cmdHelpSalTutorial+2, T("Function Calls"));
  sub1.addItem(cmdHelpSalTutorial+3, T("Working with Lists"));
  sub1.addItem(cmdHelpSalTutorial+4, T("Making Sound"));
  sub1.addItem(cmdHelpSalTutorial+5, T("Defining Variables"));
  sub1.addItem(cmdHelpSalTutorial+6, T("Defining Functions"));
  sub1.addItem(cmdHelpSalTutorial+7, T("Iteration"));
  sub1.addItem(cmdHelpSalTutorial+8, T("Musical Processes"));
  menu->addSubMenu(T("SAL Tutorials"), sub1, true);
  menu->addSeparator();
  //  menu->addItem(cmdHelpURL+0, T("SAL Dictionary"));
  menu->addItem(cmdHelpWindow+11, T("SAL Dictionary"));
  menu->addItem(cmdHelpURL+1, T("CM Dictionary"));
  menu->addItem(cmdHelpURL+2, T("CM Homepage"));
  menu->addItem(cmdHelpURL+3, T("Juce Homepage"));
  menu->addSeparator();
  menu->addItem(cmdHelpAboutGrace, T("About Grace"), false);
}

void commonHelpItemSelected (int cmd, int arg) {
  File res=File::nonexistent;
  URL url;
  String err;

  switch (cmd) {
  case cmdHelpWindow :
    res=getGraceResourceDirectory();
    if (arg == winConsole)
      res=res.getChildFile(T("doc/console.html"));
    else if (arg == winEditor)
      res=res.getChildFile(T("doc/editor.html"));
    if (arg == winPlotter)
      res=res.getChildFile(T("doc/plotter.html"));
    else if (arg==11)
      res=res.getChildFile(T("doc/sal/sal.html"));
    else if (arg==12)
      res=res.getChildFile(T("doc/scheme.html"));

    if ( res.existsAsFile() )
#ifdef LINUX
      // launchInDefaultBrowser on Linux does not for local files so I
      // have to hardwire a browser. At some point this could be a
      // Preference setting...
      {
	String u=T("file://") + res.getFullPathName();
        File foxy=File(T("/usr/bin/firefox"));
        if ( foxy.existsAsFile() ) {
          foxy.startAsProcess(u.quoted());
        }
        else
	  err=T(">>> Can't open ") + u + T(" because ") +
	      foxy.getFullPathName() + T(" does not exist.");
      }
#endif
#ifndef LINUX
      URL(res.getFullPathName()).launchInDefaultBrowser();
#endif
    else err=T(">>> Help file ") + res.getFullPathName() +
	   T(" does not exist.");
    break;

  case cmdHelpSalTutorial :
    res=getGraceResourceDirectory().getChildFile(T("doc/sal/tutorials/"));
    if (arg == 0) res=res.getChildFile(T("hello.sal"));
    else if (arg == 1) res=res.getChildFile(T("sexpr.sal"));
    else if (arg == 2) res=res.getChildFile(T("funcall.sal"));
    else if (arg == 3) res=res.getChildFile(T("lists.sal"));
    else if (arg == 4) res=res.getChildFile(T("sound.sal"));
    else if (arg == 5) res=res.getChildFile(T("variables.sal"));
    else if (arg == 6) res=res.getChildFile(T("functions.sal"));
    else if (arg == 7) res=res.getChildFile(T("loop.sal"));
    else if (arg == 8) res=res.getChildFile(T("processes.sal"));
    if ( res.existsAsFile() )
	new EditorWindow(0, (TextBuffer::load | TextBuffer::nosave), 
			 res.getFullPathName());
    else err=T(">>> Help file ") + res.getFullPathName() +
	   T(" does not exist.");
    break;

  case cmdHelpURL :
    if (arg == 0) {
      res=getGraceResourceDirectory().getChildFile(T("doc/sal/sal.html"));
      if ( res.existsAsFile() )
	url=URL(res.getFullPathName());
      else err=T(">>> Help file ") + res.getFullPathName() + 
	     T(" does not exist.");
    }
    else if (arg == 1 )
      url=URL(T("http://commonmusic.sf.net/doc/dict/index.html"));
    else if (arg == 2)
      url=URL(T("http://commonmusic.sf.net/doc/cm.html"));
    else if (arg == 3)
      url=URL(T("http://www.rawmaterialsoftware.com/juce"));
    if (err==String::empty)
      url.launchInDefaultBrowser();
    break;  
  case cmdHelpAboutGrace :
    break;
  default :
    break;
  }

  if (err != String::empty ) {
    GraceApp* app = (GraceApp*)JUCEApplication::getInstance();
    app->getConsole()->printError(err);
  }
  return;
}

void addCommonWindowItems(PopupMenu* menu, GraceWindowType w) {
  // window type is ignored for now but could be used to organize the
  // window list according to the type of window that is filling the
  // menu. of course each window would have to record its 'type'...
  bool n=TopLevelWindow::getTopLevelWindow(0)->isUsingNativeTitleBar();
  for (int i=0; i<  TopLevelWindow::getNumTopLevelWindows(); i++) {
    TopLevelWindow* w = TopLevelWindow::getTopLevelWindow(i);
    menu->addItem(cmdWindowSelect+i, w->getName() );
  }
  menu->addSeparator();
  menu->addItem(cmdWindowNative, T("Native Titlebars"), true,
		n);
}

void commonWindowItemSelected (int cmd, int arg) {
  TopLevelWindow* w;
  switch (cmd) {
  case cmdWindowSelect :
    w= TopLevelWindow::getTopLevelWindow(arg);
    if (w != (TopLevelWindow *)NULL) {
      w->grabKeyboardFocus();
      w->toFront(true);
    }
    break;
  case cmdWindowNative :
    {
      bool n=TopLevelWindow::getTopLevelWindow(0)->isUsingNativeTitleBar();
      for (int i=0; i<TopLevelWindow::getNumTopLevelWindows(); i++) {
	w = TopLevelWindow::getTopLevelWindow(i);
	w->setUsingNativeTitleBar(!n);
      }
    }
    break;
  default :
    break;
  }
}

//
// Preferences
//

juce_ImplementSingleton (GracePreferences);

GracePreferences::GracePreferences()
  : lisps ((XmlElement *)NULL),
    asdfs ((XmlElement *)NULL)
{
  initPropertiesFile();
}

// Property File

void GracePreferences::initPropertiesFile () {
  
  propfile=PropertiesFile::createDefaultAppPropertiesFile
    (T("Grace"), T("prefs"), String::empty, false, -1, 
     PropertiesFile::storeAsXML);

  // initialize any undefined properties
  if (!propfile->containsKey(T("NativeTitleBars")))
    setNativeTitleBars(true);
  if (!propfile->containsKey(T("ConsoleTheme")))
    setConsoleTheme(T("Clarity and Beauty"));
  if (!propfile->containsKey(T("ConsoleFontSize")))
    setConsoleFontSize(17.0);
  if (!propfile->containsKey(T("EditorFontSize")))
    setEditorFontSize(17.0);

  // default to 4x Chicken's minimum heap size
  if (!propfile->containsKey(T("SchemeHeapSize")))
    setSchemeHeapSize(2000000);
  // default to Chicken's default stack size
  if (!propfile->containsKey(T("SchemeStackSize")))
    setSchemeStackSize(64000);

  if (!propfile->containsKey(T("LispSystemsDirectory")))
    propfile->setValue(T("LispSystemsDirectory"), 
		       getGraceResourceDirectory().getFullPathName());

  if (!propfile->containsKey(T("LispLaunchAtStartup")) )
    propfile->setValue(T("LispLaunchAtStartup"), false);

  if (!propfile->containsKey(T("LispImplementations")) ) {
    XmlElement* top=new XmlElement(T("list"));

    // look for <ResDir>/bin/clisp if it exists set exe to that and
    // the -B arg to <ResDir>/lib/clisp
#ifndef WINDOWS
    String clispexe=T("clisp");
#else
    String clispexe=T("clisp.exe");
#endif
    File clispdir=getGraceResourceDirectory().getChildFile(T("clisp"));
    File clispcom=clispdir.getChildFile(clispexe);
    if ( clispcom.existsAsFile() )
      top->addChildElement( new Lisp( T("CLISP"), T("cltl"), T("-x"), 
				      clispcom.getFullPathName(), 
#ifndef WINDOWS
				      (T("-B ") + clispdir.getFullPathName())
#else
				      T("")
#endif
				      ));
    else
      top->addChildElement( new Lisp( T("CLISP"), T("cltl"), T("-x"), 
				      clispexe, T("")));
    // OPENMCL
    top->addChildElement( new Lisp( T("OpenMCL"), T("cltl"), T("--eval"), 
				      T("openmcl"), T("")));
#ifdef WINDOWS
    String sbclexe=T("sbcl.exe");
#else
    String sbclexe=T("sbcl");
#endif
    File sbcldir=getGraceResourceDirectory().getChildFile(T("sbcl"));
    File sbclcom=sbcldir.getChildFile(sbclexe);
    // I dont think this will work as is because SBCL_HOME probably
    // has to be set too or (require ...) won't work
    if ( sbclcom.existsAsFile() )
      top->addChildElement(new Lisp( T("SBCL"), T("cltl"), T("--eval"), 
				     sbclcom.getFullPathName(), 
				     (T("--core ") + 
				      sbcldir.getChildFile(T("sbcl.core")).getFullPathName())));
    else
      top->addChildElement( new Lisp( T("SBCL"), T("cltl"), T("--eval"), 
				      sbclexe, T("")));
    propfile->setValue(T("LispImplementations"), top);
  }

  // initialize lisps to Xml list from file
  lisps=propfile->getXmlValue( T("LispImplementations") );

  if (!propfile->containsKey(T("LispToLaunch")) )
    setLispToLaunch(getLisp(0));

  if (!propfile->containsKey(T("LispSystems")) ){
    XmlElement* top=new XmlElement(T("list"));
    top->addChildElement( new ASDF( T("Grace")));
    top->addChildElement( new ASDF( T("CM"), String::empty,
				    T("asdf:load-op"),
				    String::empty,
				    T("(cl-user::cm)")));
    propfile->setValue(T("LispSystems"), top);
  }

  // initialize asdfs to Xml values from file
  asdfs=propfile->getXmlValue( T("LispSystems") );

  recentlyloaded.clear();
  recentlyloaded.setMaxNumberOfItems(10);
  recentlyloaded.restoreFromString
    (propfile->getValue(T("RecentlyLoadedFiles")));
  recentlyloaded.removeNonExistentFiles();

  recentlyopened.clear();
  recentlyopened.setMaxNumberOfItems(10);
  recentlyopened.restoreFromString
    (propfile->getValue(T("RecentlyOpenedFiles")));
  recentlyopened.removeNonExistentFiles();
} 

GracePreferences::~GracePreferences() {
  save();
  delete propfile;
  delete lisps;
  delete asdfs;
  clearSingletonInstance();
}

bool GracePreferences::save() {
  propfile->setValue(T("LispImplementations"), lisps);
  propfile->setValue(T("LispSystems"), asdfs);
  propfile->setValue (T("RecentlyLoadedFiles"), recentlyloaded.toString());
  propfile->setValue (T("RecentlyOpenedFiles"), recentlyopened.toString());
  propfile->save();
  return true;
}

//
// General Preferences
//

bool GracePreferences::isNativeTitleBars() {
  return propfile->getBoolValue(T("NativeTitleBars"));
}

void GracePreferences::setNativeTitleBars(bool b) {
  propfile->setValue(T("NativeTitleBars"), b);
}

String GracePreferences::getConsoleTheme() {
  return propfile->getValue(T("ConsoleTheme"));
}

void GracePreferences::setConsoleTheme(String t) {
  propfile->setValue(T("ConsoleTheme"), t);
}

float GracePreferences::getConsoleFontSize() {
  return (float)(propfile->getDoubleValue(T("ConsoleFontSize")));
}

void GracePreferences::setConsoleFontSize(float f) {
  propfile->setValue(T("ConsoleFontSize"), (double)f);
}

float GracePreferences::getEditorFontSize() {
  return (float)(propfile->getDoubleValue(T("EditorFontSize")));
}

void GracePreferences::setEditorFontSize(float f) {
  propfile->setValue(T("EditorFontSize"), (double)f);
}

void GracePreferences::addRecentlyLoadedFile(File f) {
  recentlyloaded.addFile(f);
}

void GracePreferences::addRecentlyLoadedItems(PopupMenu* m, int i) {
  recentlyloaded.createPopupMenuItems(*m, i, false, true);
}

File GracePreferences::getRecentlyLoadedFile(int i) {
  return recentlyloaded.getFile(i);
}

void GracePreferences::clearRecentlyLoadedFiles() {
  recentlyloaded.clear();
}

bool GracePreferences::areRecentlyLoadedFiles() {
  return (recentlyloaded.getNumFiles()>0);
}

void GracePreferences::addRecentlyOpenedFile(File f) {
  recentlyopened.addFile(f);
}

void GracePreferences::addRecentlyOpenedItems(PopupMenu* m, int i) {
  recentlyopened.createPopupMenuItems(*m, i, false, true);
}


File GracePreferences::getRecentlyOpenedFile(int i) {
  return recentlyopened.getFile(i);
}

void GracePreferences::clearRecentlyOpenedFiles() {
  recentlyopened.clear();
}

bool GracePreferences::areRecentlyOpenedFiles() {
  return (recentlyopened.getNumFiles()>0);
}

//
// Scheme
//

int GracePreferences::getSchemeHeapSize() {
  return propfile->getIntValue(T("SchemeHeapSize"));
}
void GracePreferences::setSchemeHeapSize(int size) {
  propfile->setValue(T("SchemeHeapSize"), size);
}

int GracePreferences::getSchemeStackSize() {
  return propfile->getIntValue(T("SchemeStackSize")); 
}

void GracePreferences::setSchemeStackSize(int size) {
  propfile->setValue(T("SchemeStackSize"), size);
}

//
// Lisp 
//

Lisp::Lisp (String n, String t, String o, String e, String a)
  : XmlElement(T("lisp"))
{ 
  //  if ( isHostWindows() )
  //    e+=T(".exe");
  //  else
  //    e=T("/usr/local/bin/") + e;
  setAttribute(T("name"), n);
  setAttribute(T("type"), t);
  setAttribute(T("optn"), o);
  setAttribute(T("exec"), e);
  setAttribute(T("args"), a);
}

String Lisp::getLispName () {
  return getStringAttribute(T("name"));
}

String Lisp::getLispEvalArg () {
  return getStringAttribute(T("optn"));
}

String Lisp::getLispProgram () {
  return getStringAttribute(T("exec"));
}

void Lisp::setLispProgram (String e) {
  setAttribute(T("exec"), e);
}

String Lisp::getLispProgramArgs () {
  return getStringAttribute(T("args"));
}

void Lisp::setLispProgramArgs (String a) {
  setAttribute(T("args"), a);
}

// Lisp Preferences

XmlElement* GracePreferences::getLispImplementations() {
  //return propfile->getXmlValue(T("LispImplementations"));
  return lisps;
}

Lisp* GracePreferences::getLispToLaunch() {
  String name=propfile->getValue(T("LispToLaunch"));
  return findLisp(name);
}

void GracePreferences::setLispToLaunch(Lisp* l) {
  if (l==(Lisp *)NULL)
    propfile->setValue(T("LispToLaunch"), String::empty);
  else
    propfile->setValue(T("LispToLaunch"), l->getLispName());
}

int GracePreferences::numLisps () {
  return getLispImplementations()->getNumChildElements();
}

Lisp* GracePreferences::getLisp (int i) {
  XmlElement* lisps=getLispImplementations();
  return (Lisp *)(lisps->getChildElement(i));
}

int GracePreferences::getLispIndex(Lisp* lisp) {
  if (lisp == (Lisp *)NULL) return -1;
  XmlElement* lisps=getLispImplementations();
  int i=0;
  forEachXmlChildElement(*lisps, c)
    if ( c->compareAttribute(T("name"), lisp->getLispName()) )
      return i;
    else i++;
  return -1;
}

Lisp* GracePreferences::findLisp(String name) {
  XmlElement* lisps=getLispImplementations();
  forEachXmlChildElement(*lisps, c)
    if ( c->compareAttribute(T("name"), name) )
      return (Lisp *) c;
  return (Lisp *)NULL;
}

File GracePreferences::getLispSystemsDirectory () {
  return File(propfile->getValue(T("LispSystemsDirectory")));
}

void GracePreferences::setLispSystemsDirectory (File dir) {
  propfile->setValue(T("LispSystemsDirectory"),
		     dir.getFullPathName());
}

bool GracePreferences::isLispLaunchAtStartup() {
  return propfile->getBoolValue(T("LispLaunchAtStartup"),false);
}

void GracePreferences::setLispLaunchAtStartup(bool b) {
  propfile->setValue(T("LispLaunchAtStartup"), b);
}

/// ASDFs

ASDF::ASDF (String n, String p, String o, String b, String a) 
  : XmlElement(T("asdf"))
{
  setAttribute(T("name"), n);
  setAttribute(T("path"), p);
  setAttribute(T("oper"), o);
  setAttribute(T("before"), b);
  setAttribute(T("after"), a);
}

String ASDF::getPathName() {
  return getStringAttribute(T("path"));
}

void ASDF::setPathName(String p) {
  setAttribute(T("path"), p);
}

String ASDF::getASDFName (bool lower) {
  String name=getStringAttribute(T("name"));
  if (lower) return name.toLowerCase();
  return name;
}

String ASDF::getASDFFileName () {
  return getASDFName(true) + T(".asd");
}

String ASDF::findASDFFile(File root) {
  if ( root.isDirectory() ) {
    String file=getASDFFileName();
    if ( root.getChildFile(file).existsAsFile() )
      return root.getChildFile(file).getFullPathName();
    else {
      // search for subdir whose name starts with the ASDF's name, if
      // it exists then look inside for the .asd file.
      OwnedArray<File> dirs;
      OwnedArray<File> asds;
      int d=root.findChildFiles(dirs, File::findDirectories, false,
				( getASDFName(true) + T("*")));
      for (int i=0; i<d; i++) {
	int b=dirs[i]->findChildFiles(asds, File::findFiles, false, file);
	if (b==1)
	  return asds[0]->getFullPathName();
	asds.clear();
      }
    }
  }
  return String::empty;
}

File ASDF::getDefinitionFile(File dir) {
  String path=getPathName();
  // if a hardwired path, use it
  if (path != String::empty) return File(path);
  // else look under Lisp Systems Directory
  path=findASDFFile(dir);
  if (path != String::empty) return File(path);
  return File::nonexistent;
}

String ASDF::getLoadForm(String path) {
  String before=getStringAttribute(T("before"));
  String after=getStringAttribute(T("after"));
  String oper=getStringAttribute(T("oper"));
  String form=T("(progn ");
  if (before != String::empty)
    form += before + T(" ");
  form += T("(load ") + path.quoted() + T(") (asdf:oos (quote ") + 
    oper + T(") ") + getASDFName(true).quoted() + T(")");
  if (after != String::empty)
    form += T(" ") + after;
  form += T("(values))");
  return form;
}

// ASDF Preferences

XmlElement* GracePreferences::getLispSystems() {
  //return propfile->getXmlValue(T("LispSystems"));
  return asdfs;
}

void GracePreferences::clearLispSystems() {
  // process asdfs in reverse order so indexes remain valid after
  // removal. Grace and CM systems [0 and 1] remain
  for (int i=numASDFs()-1; i>1; i--)
    asdfs->removeChildElement(asdfs->getChildElement(i), true);
}

int GracePreferences::numASDFs () {
  return getLispSystems()->getNumChildElements();
}

ASDF* GracePreferences::getASDF(int i) {
  XmlElement* all=getLispSystems();
  return (ASDF *)(all->getChildElement(i));
}

void GracePreferences::addASDF (ASDF* s) {
  XmlElement* all=getLispSystems();
  ASDF* old=findASDF(s->getASDFName());
  if (old==(ASDF *)NULL)
    all->addChildElement(s);
  else
    all->replaceChildElement(old,s);
}

ASDF* GracePreferences::findASDF(String name) {
  XmlElement* all=getLispSystems();
  forEachXmlChildElement(*all, c) {
    if ( c->compareAttribute(T("name"), name, true) ) {
      return (ASDF *) c;
    }
  }
  return (ASDF *)NULL;
}

// JUCER_RESOURCE: grace_png, 58074, "/Lisp/grace/grace.png"

static const unsigned char resource_grace_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,193,0,0,1,82,8,2,0,0,0,5,43,243,82,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,
0,154,156,24,0,0,0,7,116,73,77,69,7,215,2,9,15,14,12,88,78,188,69,0,0,0,29,116,69,88,116,67,111,109,109,101,110,116,0,67,114,101,97,116,101,100,32,119,105,116,104,32,84,104,101,32,71,73,77,80,239,100,
37,110,0,0,32,0,73,68,65,84,120,218,236,189,89,151,236,56,146,38,102,6,128,155,175,17,113,111,230,205,165,178,214,238,154,25,169,71,103,116,244,164,103,253,122,157,163,7,189,104,90,221,163,234,238,218,
114,139,205,247,141,4,160,7,16,112,35,0,210,233,17,113,179,178,50,201,202,115,139,78,167,123,184,211,201,143,159,153,125,246,25,192,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,
12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,
203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,176,12,203,199,93,112,56,4,127,103,63,24,14,63,217,207,
122,209,90,15,7,97,192,208,97,25,208,115,88,6,36,29,48,116,88,6,244,28,150,1,73,135,203,115,56,4,3,128,14,203,0,163,195,50,96,232,0,160,195,50,192,232,176,12,24,58,44,3,128,14,203,0,163,3,134,14,203,155,
224,230,15,137,161,195,69,56,192,232,176,252,157,97,232,64,178,94,118,28,126,128,227,54,92,141,3,92,14,7,237,199,142,161,63,103,0,125,49,104,190,237,65,187,234,148,26,46,218,1,73,135,35,246,35,194,208,
159,33,128,246,255,202,209,61,63,246,17,235,127,110,13,215,237,128,164,195,225,250,27,99,232,207,7,64,251,124,211,126,251,176,143,113,46,189,254,84,27,174,222,1,70,135,195,245,246,24,250,182,16,249,119,
7,184,23,63,240,165,29,62,34,164,246,56,117,244,203,94,59,92,195,63,60,14,12,135,224,227,157,129,215,190,219,143,23,242,254,190,0,180,251,211,182,63,139,215,236,143,215,30,162,215,209,73,125,213,27,14,
72,58,32,233,207,19,70,223,12,167,126,134,0,250,34,220,188,34,221,73,182,95,253,135,94,140,158,177,141,87,128,233,128,164,3,146,254,220,96,20,63,6,124,124,100,124,252,219,195,107,199,87,136,61,213,11,
55,123,86,147,122,190,240,226,25,208,7,64,131,125,244,128,164,63,49,164,248,89,221,51,94,121,232,218,94,142,111,139,32,31,255,229,127,75,0,125,37,116,122,251,116,63,12,55,246,68,231,254,231,92,55,98,118,
62,236,5,166,3,146,14,72,250,83,130,209,31,11,134,254,157,2,104,143,112,59,254,33,59,128,242,18,134,70,246,124,229,221,235,98,156,78,119,232,179,222,241,242,225,106,31,144,244,103,2,163,248,26,4,121,211,
87,253,13,24,241,139,255,196,85,208,217,103,189,27,121,47,194,104,184,177,127,241,231,34,62,70,119,184,10,73,7,24,29,160,243,7,255,178,31,189,133,196,189,234,239,24,67,63,54,128,246,67,171,203,208,217,
130,155,125,128,53,250,212,139,191,245,117,148,147,108,212,109,79,181,33,233,64,72,7,36,253,249,192,232,203,20,57,175,220,255,163,0,247,27,66,234,181,232,121,17,58,221,206,225,179,125,152,105,184,207,
85,95,246,18,49,188,0,145,109,96,250,2,36,29,96,116,64,207,143,244,29,123,239,175,223,252,175,227,91,65,210,79,3,64,95,140,158,49,76,188,128,155,221,156,244,18,110,94,245,125,91,177,172,141,117,70,97,
212,110,28,144,116,64,210,1,70,219,47,197,171,192,168,223,206,175,108,221,249,129,240,180,7,122,190,4,58,47,226,102,116,183,54,20,54,235,47,251,130,45,193,251,117,88,25,238,208,142,164,3,140,14,232,249,
113,191,218,27,117,36,191,182,239,249,99,99,232,27,224,227,71,128,245,143,129,158,125,160,243,10,84,141,237,217,231,11,98,31,49,147,59,43,2,236,139,194,165,190,10,73,7,24,29,144,244,199,3,163,175,199,
208,139,111,242,18,199,223,215,64,231,75,123,34,63,10,152,190,33,122,70,145,49,220,161,7,164,66,39,177,125,201,239,117,45,3,13,3,121,7,151,45,59,247,34,164,3,140,190,33,206,252,156,161,243,149,184,217,
249,236,75,222,249,138,2,197,139,253,50,174,148,166,191,45,152,94,241,167,123,162,167,135,110,33,56,122,16,25,102,51,187,95,210,29,224,135,158,35,29,71,163,173,209,168,61,221,169,91,160,179,11,79,95,67,
72,7,24,253,217,211,207,183,129,206,23,56,57,188,24,76,189,23,226,219,209,207,171,209,240,101,79,193,171,235,87,61,218,37,187,171,64,47,129,78,111,207,75,20,53,194,82,219,37,162,216,243,84,104,41,184,
55,160,176,29,37,235,205,218,46,64,30,209,119,107,33,164,3,140,14,72,250,211,132,81,124,117,70,242,58,232,124,171,237,151,176,163,245,29,122,210,207,171,208,211,29,70,2,157,254,206,225,158,47,0,211,54,
74,123,109,32,223,7,61,91,30,210,157,27,212,181,7,33,29,96,116,0,208,151,125,145,151,64,231,85,219,175,114,47,243,94,133,175,96,124,87,160,222,139,45,54,94,147,40,240,249,246,219,163,167,195,65,8,129,
50,182,91,199,150,198,118,104,175,89,49,198,200,231,239,121,166,250,191,122,27,134,198,184,167,14,215,67,48,13,8,233,117,48,58,96,232,207,13,67,123,126,133,23,240,196,254,16,249,86,96,138,111,69,0,223,
214,118,232,42,143,56,232,45,144,234,217,50,212,27,61,91,113,211,3,202,54,36,189,136,161,65,137,169,53,162,191,216,238,25,146,208,128,126,66,55,98,94,90,247,114,166,23,96,116,160,162,3,128,190,105,96,
222,11,16,123,226,230,85,72,138,189,65,237,10,104,123,41,116,190,146,171,246,218,63,32,164,125,235,233,33,63,141,2,165,247,108,8,172,209,55,236,200,168,6,84,20,95,48,63,249,98,20,31,67,70,8,192,84,245,
67,213,11,165,252,1,70,127,152,236,225,79,15,64,175,97,142,87,123,56,188,248,205,177,143,3,219,27,162,231,197,122,200,43,163,254,126,217,79,236,19,188,19,176,131,88,210,19,67,82,217,13,157,134,183,6,176,
11,49,96,189,156,120,237,31,209,7,106,208,8,103,108,4,228,1,86,42,69,129,82,133,168,58,192,232,192,67,223,4,253,175,162,159,253,112,240,58,48,237,205,73,91,106,74,253,1,244,90,172,124,141,71,220,149,73,
0,136,182,247,64,139,66,168,71,97,189,21,61,59,136,167,93,191,252,146,238,132,41,4,210,122,239,147,195,53,101,165,182,2,122,19,64,29,110,170,150,21,8,159,106,97,169,112,45,140,14,24,250,83,197,208,126,
31,251,229,244,179,7,246,189,216,45,247,2,146,226,37,15,139,94,209,241,139,137,231,235,222,170,245,19,210,194,75,91,246,211,237,211,134,92,109,161,122,231,58,244,216,39,228,176,151,203,247,238,147,123,
31,187,227,32,132,103,79,155,26,52,10,157,90,131,129,69,15,49,149,82,22,49,253,29,218,144,52,252,115,193,121,57,192,232,207,29,67,251,167,32,175,229,146,29,96,250,22,72,170,177,179,255,250,58,50,248,2,
83,225,215,188,73,247,75,250,116,160,91,60,242,203,235,23,137,103,52,66,103,140,245,223,185,131,201,194,5,229,83,196,4,175,155,138,70,253,68,194,82,146,195,199,112,37,4,80,242,16,44,110,118,196,248,0,
65,221,191,13,67,7,24,253,233,97,232,139,1,244,218,216,188,183,55,238,203,145,52,252,72,24,82,182,158,0,218,31,7,251,120,101,118,190,249,21,80,30,188,103,119,119,16,123,5,241,52,16,140,100,97,225,158,
125,222,10,46,149,152,162,15,175,234,251,12,97,52,90,77,50,216,7,0,49,172,52,148,211,225,163,34,27,21,125,73,27,140,118,198,245,3,21,125,203,172,226,79,21,64,251,135,231,29,232,217,211,96,172,59,197,212,
208,216,183,96,232,21,0,218,19,254,222,214,218,61,10,163,33,118,247,112,0,97,30,253,244,2,106,15,40,205,214,230,70,214,132,209,86,90,74,64,54,34,138,106,209,150,66,192,76,161,195,157,228,226,153,26,214,
229,155,185,208,51,14,90,244,116,112,121,198,77,183,209,193,43,217,89,135,180,180,169,193,191,44,29,29,96,244,39,68,69,63,22,128,246,156,164,112,237,72,155,222,224,75,124,236,3,12,125,43,250,121,133,69,
113,159,23,246,249,211,45,97,59,139,2,168,163,159,6,16,59,232,39,99,204,33,24,65,79,230,225,102,115,75,4,85,47,229,70,35,154,211,78,226,124,245,144,165,48,31,26,77,134,154,42,188,3,71,139,158,148,123,
250,96,234,96,55,196,226,14,24,29,168,232,79,30,67,47,125,212,55,0,208,107,209,240,170,225,55,125,80,213,195,208,23,166,59,175,181,19,134,126,70,153,61,19,5,177,15,22,213,114,250,242,120,183,197,112,70,
15,209,108,250,50,68,70,214,124,138,81,108,101,12,99,32,27,41,57,121,127,43,72,137,182,170,5,250,216,229,181,157,130,209,162,124,51,149,233,71,235,20,40,155,91,36,125,72,96,84,17,20,118,232,169,66,41,
254,16,209,255,132,1,244,77,166,115,247,204,126,190,126,38,216,197,51,176,3,73,41,134,190,132,111,246,135,194,107,135,100,244,231,170,222,83,209,200,189,89,62,138,134,210,44,154,196,180,240,202,236,67,
186,51,197,208,232,206,53,129,245,226,250,104,29,31,122,55,47,245,156,44,210,1,163,161,99,72,179,136,68,73,101,141,155,82,202,182,135,22,76,253,168,223,75,146,6,109,248,3,21,253,41,167,68,95,224,15,210,
115,104,77,79,0,237,118,95,236,57,28,172,15,140,34,5,151,171,0,244,218,121,65,61,217,83,199,254,208,233,232,238,209,207,168,73,135,139,133,163,136,230,40,164,23,176,59,124,164,40,217,177,177,147,156,198,
139,245,81,0,109,83,56,145,210,252,107,169,104,83,18,239,225,160,35,149,210,49,77,41,165,197,205,198,83,30,39,117,64,220,209,224,52,80,209,159,42,15,125,153,237,241,181,17,116,219,169,114,113,206,205,
69,0,237,9,190,94,44,255,55,3,208,158,195,47,219,62,67,135,108,222,203,30,146,90,16,180,81,66,198,120,192,61,207,1,187,139,247,201,195,112,75,152,12,197,102,137,41,26,203,123,108,20,218,184,103,16,203,
95,200,5,183,157,187,109,186,122,11,127,224,146,158,30,74,18,232,108,172,107,173,163,48,74,19,172,158,146,212,157,132,3,134,254,196,96,244,69,14,117,47,145,40,93,5,142,111,181,115,184,142,140,241,171,
98,246,171,208,179,63,116,246,31,137,17,160,103,220,214,168,25,194,55,82,141,52,251,73,25,162,37,143,220,21,154,40,205,36,235,140,68,238,103,6,106,223,129,81,176,14,179,168,237,194,166,86,17,104,243,160,
49,8,188,72,186,239,58,209,115,174,105,97,231,5,242,224,0,212,134,235,82,107,37,101,3,64,149,146,102,7,75,78,61,78,218,8,237,137,140,84,123,20,24,122,91,228,13,203,143,63,144,127,125,8,127,85,141,232,
34,234,93,59,126,241,5,72,42,222,10,64,47,194,98,27,188,118,239,6,173,245,247,56,3,237,236,255,57,51,70,26,238,187,100,37,69,201,16,25,9,15,101,22,73,153,69,100,102,95,139,65,161,9,90,212,163,81,106,25,
149,214,123,223,157,181,167,71,187,115,199,141,159,159,230,36,29,61,100,204,177,200,250,123,42,165,16,37,99,40,165,2,144,186,110,202,144,238,115,42,37,1,64,41,243,121,76,22,20,16,81,41,165,53,2,160,5,
80,173,53,115,98,82,242,219,65,168,89,118,31,21,17,7,24,13,150,31,245,49,185,118,158,153,214,154,158,174,193,195,200,59,187,125,162,43,246,132,143,191,173,89,177,7,16,221,110,116,123,184,226,206,73,122,
66,158,119,115,60,244,26,0,189,192,58,175,25,211,118,29,194,130,111,160,25,105,54,167,114,117,71,6,3,185,18,134,197,31,194,34,57,69,67,199,67,45,152,182,61,213,136,235,59,50,161,205,86,122,47,239,217,
49,100,41,210,91,213,60,189,122,105,158,130,174,121,160,194,120,151,250,164,17,186,37,164,82,41,41,165,163,162,103,30,74,2,121,26,230,251,106,252,88,86,116,160,162,63,157,64,254,122,18,122,93,204,30,82,
212,54,242,216,103,214,55,244,30,247,221,157,7,16,61,89,103,79,182,216,129,158,215,143,114,139,128,117,208,45,30,173,104,215,228,52,84,47,17,240,98,94,210,211,171,14,113,206,29,175,116,16,233,40,103,147,
141,122,101,250,51,164,6,185,130,56,9,13,203,71,157,191,72,196,145,164,211,188,185,11,70,45,138,113,87,249,113,84,148,49,165,148,66,100,136,210,16,82,0,4,96,0,210,16,80,243,93,13,15,53,228,84,74,96,12,
205,14,82,34,99,104,40,45,99,168,20,34,26,126,91,91,150,152,255,180,214,134,7,56,250,16,92,90,3,134,122,68,79,255,104,1,180,251,148,243,158,37,156,49,220,225,188,222,66,54,107,62,142,24,97,136,244,161,
217,230,118,139,126,36,135,135,230,85,29,204,52,36,164,136,136,156,199,195,249,107,233,103,239,73,109,215,237,0,113,141,39,184,204,160,3,86,155,0,13,155,127,26,252,48,16,51,49,47,233,105,182,115,206,41,
235,108,193,205,40,15,101,49,13,169,87,65,234,139,158,208,46,45,104,217,161,235,86,212,82,89,210,158,56,212,49,80,67,75,13,223,116,26,38,250,208,49,80,186,133,188,86,133,2,82,23,218,123,10,127,115,42,
15,149,165,191,83,30,122,173,150,190,79,213,168,67,108,212,135,117,118,79,15,235,230,164,151,8,105,227,225,11,1,244,202,113,67,215,77,115,107,7,80,108,11,225,45,140,158,25,168,171,192,196,0,148,185,170,
17,231,220,171,179,59,178,25,176,78,78,160,51,242,146,176,28,223,22,194,119,79,75,134,206,9,201,65,42,3,250,228,82,233,91,53,167,204,251,193,181,82,134,129,106,198,152,82,146,49,173,20,42,133,74,41,41,
207,244,19,177,170,51,163,18,17,165,101,247,38,19,42,93,158,20,209,48,80,165,53,42,101,114,163,232,160,19,209,199,208,33,156,255,123,196,208,139,12,212,187,139,7,251,119,177,78,247,14,142,247,133,73,76,
202,19,29,57,141,38,211,45,45,141,127,5,251,81,35,185,212,38,33,69,202,91,123,198,242,125,227,238,171,166,93,246,71,222,192,212,61,154,253,60,23,112,92,210,144,10,146,12,98,90,24,194,104,150,211,254,31,
183,91,184,17,60,57,250,105,158,162,184,73,1,148,84,243,33,168,35,117,171,62,161,89,37,131,142,44,138,5,120,134,12,1,25,171,111,9,156,33,50,206,65,1,48,48,10,119,173,181,214,82,107,116,25,201,182,196,
168,107,126,103,140,91,24,85,54,84,55,160,175,12,36,34,34,128,4,0,0,69,62,182,217,72,255,5,0,84,74,50,134,230,3,52,35,250,90,240,100,255,163,160,57,132,243,112,21,167,251,49,167,23,162,33,188,135,80,238,
204,39,79,53,194,118,47,196,14,241,180,9,163,93,88,217,255,89,239,157,59,74,82,34,56,28,47,0,208,43,216,229,203,94,72,163,117,130,65,53,247,140,138,150,40,253,36,101,119,112,32,232,232,103,27,223,100,
204,172,55,80,149,66,42,13,234,155,73,213,72,207,104,168,159,135,11,118,244,245,103,226,130,115,46,56,79,132,16,169,200,152,224,130,39,156,113,228,128,200,193,144,105,102,238,33,156,1,104,206,13,130,162,
214,202,116,10,161,2,19,86,75,172,170,242,84,29,165,172,78,167,147,148,149,148,210,158,46,12,64,51,166,181,86,136,76,107,101,211,160,168,148,162,255,74,9,136,104,254,69,4,67,66,165,148,174,94,79,146,21,
96,178,159,166,154,111,138,253,90,187,127,161,163,184,20,205,223,15,203,143,240,104,132,52,179,155,159,82,192,245,200,166,87,91,143,66,234,69,226,217,220,1,109,194,253,50,146,134,175,109,203,144,122,48,
42,224,165,178,164,14,28,188,246,169,238,55,108,2,104,35,7,26,102,63,93,41,137,166,62,141,228,51,80,203,59,238,201,131,248,253,204,55,57,23,180,82,223,196,80,63,19,26,99,160,208,93,115,167,11,99,140,115,
158,138,68,164,121,90,140,82,68,150,38,12,24,3,94,169,82,41,165,43,9,168,43,121,42,79,80,169,10,64,115,158,112,14,76,8,86,223,30,120,202,51,150,112,33,146,52,77,152,72,5,227,74,1,232,74,131,174,42,80,
234,168,53,168,170,58,41,165,202,82,170,242,176,223,237,15,135,211,233,40,101,101,20,72,136,74,107,134,181,82,41,74,48,221,191,117,74,158,49,208,218,24,184,212,156,84,169,154,122,51,102,226,122,211,246,
170,0,184,161,180,246,223,51,27,53,168,138,136,142,8,184,187,203,0,163,63,218,154,210,245,211,59,240,98,17,41,136,147,40,164,182,17,195,14,184,108,125,42,26,188,71,65,214,3,80,10,163,162,39,128,118,39,
64,47,78,254,105,235,254,190,248,146,166,148,135,53,115,160,222,70,95,78,68,89,97,179,206,30,102,54,121,192,73,235,221,40,194,210,125,98,0,234,185,141,64,135,104,137,150,212,133,16,105,154,229,69,158,
165,35,38,146,84,8,165,212,233,116,148,101,181,89,44,74,121,148,165,19,12,233,182,14,87,247,33,56,231,105,154,164,105,145,101,41,99,73,154,23,69,54,18,34,205,178,108,58,207,160,146,21,40,45,85,85,85,82,
150,101,169,244,252,116,58,148,167,234,120,44,247,251,237,102,183,219,85,85,101,216,162,71,69,13,217,164,231,8,34,154,75,154,90,243,121,255,25,233,168,165,159,104,250,242,205,185,75,199,52,185,42,23,13,
166,134,148,232,143,156,135,118,102,66,251,68,241,145,58,18,229,158,237,88,137,45,57,141,142,124,104,7,146,94,65,72,67,24,21,175,1,208,43,81,242,10,244,108,209,147,99,160,162,63,135,240,84,66,79,18,160,
46,65,73,139,233,46,36,63,135,234,38,114,119,148,211,161,170,209,57,209,138,188,217,237,82,115,103,180,255,189,17,168,39,66,20,121,145,23,227,36,201,210,52,3,128,227,233,88,149,135,197,230,184,219,109,
170,170,84,74,135,153,22,234,17,67,27,237,221,99,41,213,225,112,60,30,79,235,53,34,98,146,166,147,241,52,75,139,52,203,178,172,200,178,209,120,60,203,166,57,168,170,42,43,169,100,85,85,178,60,30,78,199,
170,170,78,147,221,225,112,216,31,183,235,229,242,120,60,162,19,205,159,71,138,74,59,252,192,125,40,151,14,18,136,85,236,28,149,136,220,164,68,149,2,206,181,41,46,1,208,154,146,231,114,63,96,232,223,13,
134,94,243,148,238,89,71,162,117,155,104,106,210,3,211,240,89,7,139,253,243,164,230,212,107,169,38,117,193,168,232,9,160,253,83,156,29,232,121,113,106,80,212,150,152,226,41,237,235,49,91,28,144,65,208,
91,233,24,168,203,135,82,46,233,16,147,224,166,32,59,120,207,118,240,80,243,73,194,52,104,244,112,129,16,73,94,140,71,197,40,77,179,52,205,56,23,187,195,102,187,93,29,78,251,221,102,99,19,148,96,223,48,
26,205,209,118,79,239,160,129,247,25,100,85,45,151,11,198,86,105,146,20,163,73,62,154,156,170,99,113,200,71,197,116,54,127,199,64,85,178,60,158,170,81,117,148,242,116,58,156,14,167,253,225,116,156,140,
230,187,221,102,177,120,60,157,142,134,144,210,116,39,162,34,56,46,173,220,181,14,240,109,186,95,186,23,186,158,37,147,105,5,80,0,166,3,74,183,140,23,253,49,98,232,53,195,2,126,22,24,218,145,106,236,22,
51,249,253,230,232,189,91,92,153,100,83,61,208,50,210,198,156,118,154,192,232,25,103,91,182,183,34,108,172,20,6,109,48,42,222,14,64,253,237,175,65,85,234,208,65,107,238,52,13,74,72,95,189,209,113,195,
166,90,158,66,158,163,144,231,68,39,229,161,30,188,82,72,13,121,104,187,146,41,172,32,1,99,44,207,138,209,120,154,101,73,158,22,60,41,180,174,214,235,229,113,127,56,156,118,219,237,38,188,80,195,139,165,
197,142,4,90,234,87,13,61,127,89,85,229,106,185,221,110,202,227,254,144,143,142,199,163,132,106,148,143,39,147,155,241,68,84,167,83,41,85,89,238,15,135,253,233,116,56,100,69,81,76,139,116,180,220,60,47,
151,79,158,108,0,0,0,120,120,133,16,73,22,208,150,78,171,112,66,87,95,178,167,160,81,14,128,3,211,14,24,253,97,224,3,175,237,85,252,193,241,238,71,133,161,61,171,76,87,234,231,175,96,160,180,106,111,207,
165,136,234,222,36,235,123,86,231,233,206,205,63,29,255,60,226,101,0,218,193,40,163,64,25,13,111,59,54,82,111,249,96,60,145,249,24,232,89,135,24,212,179,4,144,187,202,186,39,140,247,32,210,43,40,89,42,
234,71,247,78,117,79,10,241,84,56,197,98,64,86,31,79,206,249,100,58,45,242,113,154,102,89,82,164,121,118,56,236,181,150,223,221,127,115,220,239,78,167,147,214,154,49,30,222,126,219,46,231,230,97,7,239,
24,82,13,108,8,166,90,235,229,114,177,219,109,143,199,131,214,234,84,28,164,84,179,217,205,252,238,19,85,85,229,113,127,28,29,170,83,185,45,54,197,97,159,101,105,49,25,103,89,246,248,248,93,89,86,30,146,
218,50,186,147,229,74,251,208,157,42,117,207,146,169,77,217,246,121,77,36,162,44,176,194,243,48,244,163,195,232,219,130,230,15,128,125,63,18,12,237,79,66,59,140,147,95,204,64,131,167,34,83,194,28,45,165,
12,148,114,79,2,187,151,225,149,86,59,61,132,21,31,15,64,219,56,105,116,140,101,115,123,196,229,179,249,110,225,176,13,230,2,106,218,62,68,68,72,110,163,176,79,25,100,20,142,123,218,125,226,108,148,168,
241,253,230,206,104,27,18,0,112,206,198,179,155,34,29,143,199,227,36,73,211,52,219,109,215,251,253,254,233,241,155,221,97,95,158,78,221,134,11,209,59,121,83,58,234,126,53,90,228,9,143,182,127,252,164,
148,171,213,178,170,202,201,228,166,170,42,169,42,0,152,223,190,187,25,223,30,143,85,85,86,105,81,28,246,199,44,205,15,251,157,81,86,125,247,221,95,237,31,229,112,110,103,0,0,80,234,44,215,7,208,74,129,
214,156,104,155,144,220,222,235,238,207,152,135,19,184,179,156,74,238,223,28,70,95,4,154,61,95,162,127,0,40,252,241,96,104,79,18,218,145,6,141,214,223,251,48,80,26,155,211,122,81,20,31,155,1,123,164,178,
20,214,223,221,231,161,113,189,151,30,117,127,69,120,39,74,7,128,118,231,46,187,97,49,186,91,20,100,155,62,155,140,102,6,61,165,167,23,77,55,219,49,141,60,30,155,181,32,193,234,54,78,70,37,77,156,115,
10,163,22,67,105,57,190,65,69,195,65,117,33,134,10,33,38,147,105,150,21,163,209,36,203,242,162,152,173,215,143,235,245,122,177,248,126,191,223,29,143,71,47,18,167,97,72,120,175,131,70,151,81,228,119,105,
114,255,182,153,204,204,155,31,186,223,239,79,167,147,169,194,215,249,144,249,39,55,119,162,170,68,182,207,143,197,33,203,210,195,97,207,147,4,164,46,203,234,225,225,107,173,181,82,70,192,116,230,161,
228,223,243,189,86,41,52,154,39,251,17,165,82,204,182,207,215,249,80,207,217,222,35,17,29,48,218,31,80,174,68,204,143,193,73,245,219,34,227,143,1,67,219,73,232,219,164,65,175,98,160,97,98,212,203,126,
82,120,117,81,14,173,236,119,19,210,54,24,117,219,69,56,104,183,77,195,244,2,0,13,107,68,237,85,35,244,204,226,28,22,120,0,106,242,162,94,41,220,225,166,181,82,166,196,179,81,23,34,15,41,116,70,214,99,
106,167,134,176,212,230,13,24,69,67,206,216,116,50,205,71,163,34,155,36,89,62,30,79,143,251,237,114,241,189,6,249,253,247,95,31,143,123,173,129,49,119,55,67,226,187,129,246,55,211,81,247,132,118,80,208,
228,55,210,65,187,125,180,12,229,144,78,45,151,247,74,85,10,192,234,14,223,221,188,79,239,10,56,30,114,0,56,28,246,178,44,43,93,85,234,72,36,1,46,232,110,252,11,160,155,121,82,109,196,254,74,73,198,56,
128,178,84,20,149,210,156,163,215,59,31,150,8,250,192,232,43,67,249,75,16,124,21,178,188,25,75,109,195,202,151,153,1,190,57,236,122,247,245,142,63,68,49,209,41,91,219,210,160,36,216,10,171,70,173,12,212,
138,139,91,33,50,164,159,30,104,82,243,145,104,252,222,13,163,34,10,145,205,203,53,26,194,95,65,54,163,251,68,241,212,169,65,105,68,31,157,242,102,208,204,180,195,123,162,37,35,105,114,122,120,42,78,114,
43,94,17,201,68,244,142,156,134,170,123,42,132,162,181,120,58,179,19,0,166,211,113,62,154,140,242,105,158,23,69,49,6,198,148,42,183,251,221,211,195,183,251,195,81,170,202,50,235,115,143,163,253,133,26,
74,242,80,103,222,121,229,99,187,245,178,47,59,243,138,78,102,167,245,122,201,0,181,6,101,250,62,225,221,221,93,186,221,193,126,191,218,239,55,251,253,122,191,95,237,54,27,123,139,170,241,130,178,209,
0,71,26,13,160,174,73,201,181,204,219,19,158,25,24,37,88,76,47,69,253,3,211,174,31,127,65,233,199,192,67,59,63,192,117,94,118,86,57,23,49,7,9,115,157,52,219,227,229,64,61,6,74,3,26,186,197,74,148,116,
179,214,132,222,22,136,104,69,187,96,84,68,137,103,155,43,240,139,201,102,31,60,165,105,80,231,29,103,123,93,104,20,95,59,134,120,94,115,140,213,144,106,18,151,77,52,52,85,248,179,120,158,115,202,61,41,
253,60,111,52,65,189,99,178,180,42,5,190,183,30,228,249,168,200,138,241,116,150,143,70,147,124,156,20,197,97,191,213,149,124,124,124,188,191,255,107,89,30,73,12,238,59,203,58,224,176,17,7,146,83,36,122,
109,155,219,114,212,107,25,105,29,41,186,189,73,75,235,103,87,155,37,50,20,12,25,3,68,38,216,59,5,234,88,86,101,121,58,85,229,233,84,217,194,151,207,185,156,123,8,99,90,107,205,121,4,154,140,253,157,173,
41,177,166,151,40,163,36,52,10,163,31,15,56,218,65,243,53,96,170,63,50,240,253,72,49,52,172,29,53,145,200,255,252,90,107,198,88,12,28,123,213,142,60,220,36,251,159,183,88,164,243,176,21,104,104,31,141,
226,47,110,161,48,42,250,116,100,94,2,208,200,150,254,120,26,27,55,196,98,81,188,51,54,110,88,199,147,233,29,94,133,189,174,38,25,238,105,64,179,89,68,114,208,233,74,240,172,89,95,226,161,103,168,55,50,
30,64,11,198,139,241,100,62,191,203,178,116,60,158,231,249,88,150,199,195,110,255,252,252,40,101,245,253,247,223,40,37,67,250,233,20,103,228,56,83,179,3,99,4,7,212,212,61,96,151,97,125,9,157,17,167,171,
249,208,195,76,187,137,104,68,95,195,232,122,193,208,244,230,11,38,196,108,50,183,79,41,0,224,92,104,173,1,152,13,228,25,13,222,221,135,177,134,246,103,27,39,219,238,137,90,35,99,38,37,202,154,211,146,
195,64,62,2,163,31,179,160,132,111,66,75,251,76,10,122,253,87,248,219,242,208,142,166,201,48,178,143,214,226,195,124,168,23,115,24,114,234,112,51,196,83,131,137,77,48,109,84,225,47,34,41,169,94,250,16,
73,141,71,195,72,63,20,102,53,52,246,109,62,76,175,6,208,43,30,218,45,46,66,119,228,212,31,9,231,210,160,212,19,196,109,48,15,57,175,185,36,97,166,20,52,207,33,60,165,165,129,32,52,156,237,81,147,98,13,
106,60,154,20,197,164,24,79,110,38,115,158,21,211,241,124,189,126,146,229,105,177,120,124,124,252,238,116,42,181,174,237,60,16,181,82,103,160,36,241,187,3,77,244,148,61,246,89,63,5,134,72,211,55,231,90,
147,237,85,143,196,248,129,46,170,33,98,181,224,203,87,155,103,158,48,68,38,132,72,80,108,215,171,237,118,181,94,175,183,219,181,245,115,2,203,58,35,41,75,11,250,244,175,43,68,169,212,153,129,42,133,198,
217,196,150,149,160,7,140,94,205,239,46,193,31,254,0,10,167,238,81,233,47,6,196,191,117,44,223,151,132,182,17,210,139,193,59,231,44,86,108,212,54,140,142,132,234,33,9,13,145,52,198,37,193,203,144,82,138,
211,31,70,69,52,144,239,15,160,109,179,42,175,122,216,108,214,108,72,214,13,144,1,49,172,115,93,240,140,113,67,82,157,19,40,237,115,167,229,117,146,15,21,14,61,45,86,82,90,42,40,135,165,201,208,80,72,
15,160,39,147,219,233,244,118,60,30,141,242,241,108,118,139,140,73,165,100,89,61,45,30,239,31,191,149,149,113,216,100,238,39,52,198,28,20,242,92,28,161,181,129,27,36,39,147,243,227,240,195,138,102,144,
174,155,238,253,103,250,217,196,205,48,187,77,49,244,92,209,218,110,55,34,45,178,237,40,21,121,85,157,78,167,147,177,35,225,60,49,50,38,198,116,208,6,173,169,63,136,61,221,93,191,60,216,209,76,178,73,
69,149,89,15,192,179,163,172,244,226,72,22,123,212,139,94,5,172,221,136,25,214,90,250,191,85,204,254,253,111,67,96,105,190,190,79,41,137,126,89,239,7,238,160,162,30,176,106,173,40,229,244,236,190,188,
2,125,55,146,190,18,103,189,240,209,93,173,226,226,32,163,208,125,189,63,128,70,205,232,46,122,203,123,243,142,98,243,224,234,49,80,84,108,228,41,231,107,17,83,35,209,217,64,213,32,150,143,26,56,133,6,
245,168,181,202,211,180,24,207,166,211,217,100,114,59,26,21,69,49,49,78,238,207,203,199,199,197,253,211,195,119,90,213,244,147,220,202,128,170,222,232,5,82,23,114,130,176,157,198,242,209,225,92,238,157,
233,138,167,4,110,31,67,16,245,45,197,195,97,47,182,235,44,73,210,52,5,37,1,52,48,224,60,181,227,163,235,106,187,73,100,33,214,153,80,167,40,48,247,9,165,144,115,99,215,100,10,74,181,127,168,117,179,175,
173,161,72,62,180,17,181,5,215,161,238,93,251,190,170,194,142,63,84,65,169,251,243,235,31,24,10,63,66,26,225,10,83,122,79,193,22,165,162,77,60,173,101,112,97,252,30,221,210,241,208,58,222,94,0,202,232,
67,42,69,240,74,76,209,126,249,46,121,124,55,128,122,246,31,45,1,59,11,35,119,215,181,217,140,226,207,209,122,96,91,231,233,231,77,195,123,67,221,73,73,168,139,214,13,3,109,22,232,121,80,175,103,109,174,
34,74,201,241,120,50,157,222,142,70,163,241,244,118,54,153,21,197,120,191,223,42,165,158,159,239,159,158,30,158,159,190,39,55,36,151,214,164,181,32,77,117,160,228,200,107,18,221,55,32,18,252,150,9,154,
13,160,69,121,23,107,176,0,23,204,223,101,180,142,228,117,142,218,151,136,242,184,63,28,14,199,227,238,176,219,110,183,235,237,122,37,68,106,2,121,41,205,155,104,155,216,208,238,99,155,106,146,85,143,
34,89,169,133,19,166,209,211,214,148,152,27,200,76,228,77,145,90,252,197,112,254,197,108,180,3,52,99,79,225,139,19,157,215,224,233,15,86,83,186,246,77,176,103,41,9,186,70,192,71,64,51,104,172,240,75,76,
46,210,50,190,101,253,227,119,251,144,206,145,101,175,68,85,146,96,61,3,171,232,24,3,71,55,6,53,34,240,0,180,155,114,70,177,149,18,76,10,166,86,204,196,194,193,238,182,249,253,108,249,65,100,76,54,76,
39,117,121,27,188,59,24,61,99,168,197,77,10,160,140,148,224,121,208,205,169,185,16,69,58,159,206,167,211,233,221,184,24,141,38,243,233,248,230,121,249,160,64,45,159,239,159,30,31,22,203,7,90,210,9,180,
141,148,105,162,23,174,82,177,58,217,71,119,80,42,26,191,211,32,221,253,23,100,66,195,88,222,135,81,198,216,241,120,58,157,14,167,195,126,119,58,30,14,71,165,65,144,95,153,148,194,128,186,208,187,196,
174,251,12,70,207,103,10,74,214,128,217,1,168,225,23,58,90,148,39,225,252,199,174,38,133,79,97,39,117,141,130,200,133,66,202,85,247,131,104,192,241,166,37,169,87,145,208,232,20,141,62,165,36,42,62,33,
60,180,81,74,234,232,221,212,218,8,138,181,203,161,95,140,223,45,62,178,62,168,170,148,234,79,78,157,82,202,108,17,208,106,96,1,16,168,62,91,32,181,21,64,195,110,72,10,166,46,185,25,38,28,105,201,200,
1,168,81,47,81,33,103,96,170,196,109,86,148,19,250,201,154,65,189,201,123,210,60,169,235,92,58,215,241,61,245,62,104,205,184,184,189,121,95,228,163,201,108,50,155,220,166,249,36,31,141,204,40,182,197,
226,225,241,233,251,229,106,1,192,16,149,181,144,247,1,46,232,102,107,0,37,41,55,33,97,100,109,23,60,182,111,196,160,160,116,97,197,55,36,213,170,170,202,83,85,49,208,90,203,68,164,54,161,9,132,138,26,
152,54,160,9,140,153,188,39,16,175,169,134,164,201,56,54,153,224,61,74,40,154,60,20,188,90,237,199,148,52,97,12,176,122,33,105,91,150,51,236,11,232,119,75,208,125,24,244,43,14,200,43,143,164,142,82,242,
30,211,229,180,151,150,49,166,142,36,126,215,174,148,212,132,72,8,187,129,201,137,212,69,66,149,82,1,235,116,208,233,106,188,202,129,163,81,89,153,185,179,189,99,252,154,147,138,104,20,15,193,24,56,136,
201,230,3,213,39,182,205,101,243,192,52,32,152,72,186,221,145,86,216,173,134,137,118,192,211,112,158,214,211,207,77,156,14,58,17,235,74,145,133,84,65,32,245,252,114,10,157,68,75,143,22,59,84,146,136,249,
237,187,249,236,147,60,207,39,147,217,116,122,3,12,64,85,139,229,98,181,184,127,122,186,95,175,87,212,7,68,107,52,212,210,122,128,58,175,108,221,36,161,232,93,120,182,59,152,146,80,244,174,154,166,225,
200,121,34,180,253,15,169,174,168,185,238,171,142,232,173,243,252,254,140,157,78,101,85,149,235,197,98,183,89,101,197,216,158,94,148,138,158,47,9,250,167,13,146,186,51,193,140,162,179,231,61,179,227,151,
89,180,67,137,0,104,43,122,190,0,65,218,24,104,44,246,234,27,248,119,146,175,46,244,140,38,121,47,50,196,48,147,243,3,151,149,218,58,229,58,0,52,24,31,11,84,209,25,11,234,149,17,189,180,25,41,208,208,
223,25,39,182,197,239,6,19,221,83,6,82,61,232,116,184,233,192,209,92,236,87,165,74,1,72,77,201,139,226,59,234,72,61,226,116,118,113,221,70,205,104,123,52,209,101,66,1,156,26,201,100,72,253,58,79,24,119,
59,220,164,145,187,11,219,29,110,58,169,19,201,141,122,22,77,94,45,30,148,146,105,154,206,110,110,111,231,119,243,249,93,150,143,198,147,25,40,37,149,90,46,158,158,159,31,158,158,30,214,235,149,197,50,
55,48,11,189,226,29,17,111,54,174,55,173,93,155,57,16,133,185,39,21,210,45,215,118,56,119,62,154,200,195,96,61,254,38,246,214,202,20,40,41,229,177,220,1,49,208,50,84,20,81,155,54,7,68,109,114,162,102,
163,107,97,178,5,37,244,44,239,72,99,18,45,37,169,22,0,189,192,227,222,148,123,94,164,162,216,51,203,25,124,236,46,66,221,71,252,116,145,247,253,48,108,148,244,249,188,190,154,164,194,117,173,193,41,142,
189,197,155,161,109,174,39,3,118,109,72,106,64,210,61,165,181,52,190,193,0,0,32,0,73,68,65,84,212,25,82,189,245,144,129,190,0,70,69,91,20,223,86,71,186,146,129,178,176,248,78,180,241,94,92,143,141,177,
149,141,42,60,179,118,118,156,12,59,58,151,215,93,116,239,248,38,13,234,73,45,158,55,37,247,94,99,146,175,165,151,178,76,211,252,118,126,59,157,191,159,223,222,206,231,239,243,52,171,78,71,169,244,114,
253,176,88,60,61,62,222,239,118,107,83,102,177,64,224,14,160,241,27,214,65,122,20,155,74,160,104,2,20,201,91,233,150,235,63,46,68,107,130,105,116,75,36,216,167,69,124,134,76,203,10,64,131,134,44,27,217,
219,0,237,128,48,229,120,102,227,119,23,188,55,10,74,74,129,141,229,105,252,197,168,90,5,128,145,94,79,232,214,216,191,12,61,162,200,24,184,10,116,151,155,176,27,140,250,196,179,237,8,219,1,112,173,127,
247,69,185,218,215,136,1,122,189,79,123,53,201,181,117,26,172,4,210,165,6,102,0,173,137,241,109,8,175,46,130,169,177,81,179,240,215,120,202,170,6,235,172,168,237,134,162,235,202,131,203,182,117,79,207,
20,93,68,71,20,223,83,218,217,189,30,152,34,159,81,146,116,25,121,228,148,185,65,70,36,25,234,11,224,93,252,238,229,58,29,74,146,248,189,81,77,10,251,229,67,87,17,68,148,178,204,243,124,62,127,63,159,
221,206,111,238,230,243,187,217,77,182,90,28,21,192,114,249,184,88,60,61,63,127,119,56,108,13,93,181,9,80,70,139,125,214,31,90,25,16,65,100,193,60,97,191,212,110,114,169,78,129,31,150,68,219,166,132,6,
11,235,206,168,180,249,245,105,173,1,1,65,175,86,143,219,237,118,50,187,113,14,140,46,234,81,74,27,83,59,171,85,64,210,143,164,16,205,24,100,197,152,114,253,72,38,7,26,132,105,154,2,104,183,176,233,42,
137,101,16,137,119,97,104,59,128,98,127,90,215,73,193,186,1,180,63,156,33,180,122,145,244,188,205,244,173,173,119,4,236,116,168,92,15,98,174,108,173,210,239,68,114,162,14,210,152,228,110,174,172,9,154,
42,10,166,102,118,119,179,107,83,17,131,90,183,174,44,241,4,74,84,67,72,141,194,43,201,162,198,139,248,162,35,138,111,143,137,46,176,81,15,64,61,137,37,29,206,209,236,121,247,136,39,53,251,112,190,159,
103,9,103,179,185,136,59,154,233,9,63,105,14,212,21,145,168,26,148,24,131,114,215,140,84,201,50,77,179,219,219,247,211,233,205,252,246,253,124,122,115,51,203,22,139,227,242,249,73,129,90,44,30,22,139,
199,221,110,239,68,160,68,233,169,173,27,147,127,150,19,189,39,54,25,171,211,141,158,87,154,173,159,254,5,223,236,53,2,27,92,135,160,9,49,167,43,170,78,139,220,65,181,214,200,217,161,60,38,89,102,171,
100,238,254,108,246,209,0,180,142,84,127,84,67,60,141,221,178,117,24,169,137,167,203,115,121,170,233,88,69,158,94,132,250,98,1,231,69,24,138,225,198,32,174,199,222,28,45,14,148,132,188,120,15,175,24,118,
210,226,141,116,173,148,245,138,220,107,244,11,246,57,24,205,187,72,131,117,154,155,174,161,156,112,158,235,83,71,208,120,238,64,58,199,40,86,179,161,186,19,160,198,12,151,132,237,224,213,148,92,38,148,
34,166,129,200,230,14,238,3,99,148,141,6,86,191,231,243,71,92,27,197,71,57,143,167,87,234,0,208,216,70,176,168,218,48,172,35,85,36,30,227,161,158,96,190,33,167,55,139,183,133,160,170,23,197,115,207,151,
190,170,202,52,73,239,238,222,207,110,238,110,166,239,103,243,155,217,44,89,44,142,207,203,135,213,234,9,148,90,46,159,118,187,173,1,80,55,230,215,30,86,135,74,14,76,207,54,178,228,232,99,80,235,164,215,
134,118,151,79,128,197,204,3,211,192,97,164,241,159,167,81,163,219,163,60,20,0,148,146,169,72,149,44,147,98,98,19,85,13,102,205,152,182,96,90,35,169,27,39,165,117,109,89,223,12,225,177,201,35,24,17,213,
123,65,188,238,159,9,189,182,209,51,48,114,140,3,104,88,100,235,54,21,110,131,206,176,56,214,17,234,94,163,108,213,47,130,248,215,86,162,90,84,77,24,99,223,202,206,48,215,182,122,227,178,159,76,41,205,
57,184,10,146,217,238,238,172,74,25,82,162,24,51,161,125,3,245,28,128,82,105,135,129,209,102,169,234,28,206,155,149,16,49,237,27,130,195,211,144,129,122,142,77,209,186,188,193,208,43,42,239,23,211,160,
81,0,165,245,247,166,238,146,53,103,181,115,58,238,205,27,97,20,56,42,57,112,244,72,232,153,126,58,78,74,64,147,55,83,168,13,104,54,159,188,170,202,36,17,183,183,239,103,179,187,155,217,221,124,126,51,
155,37,207,207,199,229,226,97,181,124,94,44,30,1,96,183,221,48,38,136,198,141,134,240,206,20,11,237,109,237,236,139,232,126,36,2,136,231,87,153,202,12,69,91,240,231,137,199,135,81,247,76,182,68,99,249,
200,5,169,20,99,236,40,203,140,113,75,18,93,112,132,110,68,179,157,140,100,189,195,234,21,198,152,50,2,38,179,18,205,103,69,219,84,60,0,141,70,187,87,1,66,152,9,109,199,205,238,10,18,94,162,117,58,80,
243,180,66,106,91,182,183,39,140,182,121,119,246,198,80,221,39,221,121,49,57,208,57,232,88,53,139,72,154,214,231,25,171,175,26,171,112,82,74,49,251,42,26,206,43,196,122,55,23,202,16,244,68,119,58,41,165,
132,48,83,99,21,99,104,247,65,155,68,2,147,60,53,47,180,144,10,14,103,77,149,41,10,163,1,206,122,98,251,166,62,180,79,8,223,167,142,212,13,160,33,21,109,182,84,50,146,42,13,7,31,133,14,117,62,9,165,153,
80,219,17,127,6,214,166,95,189,55,27,185,198,238,170,42,133,224,243,249,221,108,250,110,126,115,59,159,191,191,153,241,199,231,227,98,241,176,90,61,46,86,207,171,197,51,23,9,23,41,173,32,217,68,248,249,
80,53,231,169,250,74,38,39,96,114,149,119,114,202,214,79,18,244,196,128,75,133,16,122,246,9,36,182,129,78,216,16,89,188,23,210,63,84,105,117,56,238,38,227,155,192,152,150,153,51,207,196,89,80,59,0,212,
244,147,174,216,175,239,180,35,58,234,34,209,70,65,187,97,180,15,146,182,212,145,122,165,68,219,92,201,219,98,228,238,100,110,7,45,237,79,18,3,180,106,109,255,111,107,38,186,10,70,163,108,235,210,1,161,
223,157,7,131,9,252,114,188,233,12,6,208,182,78,174,172,229,163,27,248,234,76,64,26,105,77,211,49,108,135,116,213,60,212,162,167,199,61,91,129,50,92,247,96,212,177,78,207,43,218,187,135,153,125,68,71,
174,51,8,247,218,140,232,177,45,90,247,0,52,24,44,124,150,121,186,33,198,196,114,201,249,126,98,88,121,247,82,159,30,15,13,86,26,36,52,152,76,87,43,82,165,172,16,245,116,122,59,159,223,205,231,183,243,
249,221,164,6,208,199,229,234,121,185,92,46,158,158,78,167,253,205,104,98,79,172,58,125,195,152,209,69,158,171,234,84,231,228,214,137,239,167,57,21,128,164,32,21,117,192,11,171,73,94,207,88,36,154,143,
37,61,195,95,39,24,16,18,241,111,230,76,112,38,132,72,201,199,118,255,41,155,124,55,213,0,119,154,186,142,120,12,166,128,177,246,82,82,3,101,218,203,20,47,225,161,49,18,138,109,133,35,210,175,5,177,132,
105,71,169,186,79,252,174,47,177,209,171,244,173,250,82,225,254,114,202,248,170,209,35,45,210,174,110,38,14,97,27,146,87,142,55,196,147,49,112,118,136,54,138,111,220,122,205,25,104,72,36,128,50,28,83,
41,229,168,165,3,74,211,138,29,160,103,205,69,58,96,212,34,166,11,28,193,243,69,163,199,192,59,30,181,231,72,59,15,13,202,19,45,169,207,104,81,56,112,90,10,39,106,120,46,159,224,230,193,5,45,237,158,175,
18,119,77,156,182,254,30,214,148,252,88,158,232,153,152,39,8,5,64,13,90,169,114,118,243,254,102,254,110,62,191,155,207,238,166,147,68,75,203,191,52,160,86,66,224,120,252,105,120,136,108,2,5,157,158,169,
54,199,211,116,182,179,241,111,55,220,205,153,111,106,231,64,66,124,13,128,90,220,199,146,119,225,205,44,122,87,99,237,120,234,79,78,166,191,254,108,118,27,132,96,181,150,211,25,244,89,209,253,185,119,
147,49,229,214,109,6,74,199,106,241,209,248,61,26,197,191,74,99,223,114,62,183,225,102,55,39,237,250,12,65,77,201,191,55,180,240,211,23,54,11,188,178,166,116,165,9,150,167,9,185,144,9,165,197,64,171,113,
86,36,37,106,226,247,134,15,147,37,137,46,203,201,40,109,116,247,96,196,250,236,2,80,4,1,105,228,110,194,127,148,82,90,120,69,71,126,25,3,75,87,27,20,213,192,168,91,9,104,105,35,255,22,38,70,157,7,115,
23,104,118,71,241,221,249,80,226,172,28,7,80,90,13,39,67,59,206,172,51,58,48,46,172,191,135,249,208,176,166,228,229,79,233,180,100,147,216,46,79,187,217,236,253,237,252,246,102,118,51,155,221,78,231,9,
104,88,45,142,139,213,227,106,245,184,92,62,107,173,242,124,74,7,179,144,72,188,161,171,143,21,223,181,235,119,140,5,95,154,148,167,128,208,213,86,0,165,165,249,88,209,143,93,114,104,141,11,164,162,162,
113,203,163,27,140,210,168,85,154,218,145,134,71,61,41,196,211,42,188,142,53,174,64,139,192,254,85,48,218,50,22,37,130,155,97,85,173,79,194,177,61,132,143,99,104,16,224,119,11,69,91,211,17,237,114,247,
55,7,208,174,24,191,247,161,112,6,11,38,202,214,90,115,203,43,149,221,136,38,59,100,207,25,101,49,139,17,109,156,145,208,153,141,53,15,117,81,188,75,125,18,202,121,198,71,11,154,202,10,75,206,16,28,172,
196,105,41,129,206,72,68,47,162,36,52,90,180,109,147,34,82,54,234,225,102,104,182,228,249,215,133,67,140,189,113,196,22,236,4,145,127,178,32,96,175,91,224,155,72,202,194,88,158,218,226,17,99,61,60,28,
183,211,233,236,230,230,102,54,187,155,221,220,206,102,153,214,176,90,29,23,171,231,213,234,121,177,120,94,44,158,70,163,49,231,73,211,35,217,117,37,57,160,105,140,0,48,49,126,179,61,201,243,88,162,83,
198,52,145,70,65,39,135,106,132,225,47,117,110,109,188,67,172,130,225,188,193,129,244,182,187,246,15,12,228,120,231,172,86,51,1,202,90,154,226,123,34,203,117,1,105,135,83,125,111,0,197,168,164,52,166,
87,213,45,197,147,14,12,109,187,91,92,204,72,92,76,47,224,43,67,248,48,108,111,115,50,109,31,25,223,136,226,161,57,183,195,54,248,42,11,166,174,80,99,202,71,134,119,186,196,40,218,136,190,70,76,198,152,
173,191,43,47,7,234,208,211,81,78,41,161,29,61,27,43,78,196,77,71,11,91,146,11,30,116,82,227,11,71,69,69,148,132,6,114,209,139,69,9,12,101,76,33,92,210,160,222,165,35,105,229,221,162,155,201,123,158,173,
67,154,45,240,62,205,52,42,122,175,118,228,164,245,225,191,158,162,126,183,91,102,105,86,20,147,172,40,242,124,148,231,69,81,192,119,223,156,25,232,98,241,12,160,133,200,236,249,161,154,103,173,110,10,
233,145,28,107,58,111,195,139,223,29,24,157,127,254,142,43,132,252,192,97,50,20,47,22,253,218,134,89,69,65,164,157,88,133,177,57,163,218,102,83,68,10,246,1,175,124,20,22,175,47,9,182,175,174,206,71,17,
48,10,151,23,9,105,111,30,218,0,205,110,60,237,207,167,195,47,18,122,33,246,104,193,188,34,67,218,161,174,39,201,132,11,184,76,43,72,14,40,13,3,133,26,44,77,189,187,86,53,113,110,200,163,75,132,42,7,181,
74,73,26,215,43,37,181,102,74,153,128,93,187,113,135,118,246,167,195,92,176,174,181,46,89,15,36,132,63,195,104,52,162,119,192,74,241,52,204,150,154,172,157,8,25,104,83,111,232,69,124,93,168,74,37,150,
158,123,113,24,212,55,205,235,26,115,225,77,152,238,114,163,52,31,234,202,238,22,46,5,229,155,156,11,135,188,22,109,93,188,239,205,245,172,63,195,225,176,101,44,153,76,111,166,211,155,233,244,102,50,153,
143,38,112,216,3,48,147,5,101,0,32,4,155,76,222,5,60,81,187,113,234,36,167,137,214,127,222,153,140,184,112,160,161,23,113,26,38,18,157,93,80,59,6,88,9,77,153,39,116,131,102,75,145,48,66,112,154,46,206,
154,140,107,110,56,59,152,79,78,233,167,67,15,111,108,114,179,25,201,155,58,215,149,3,125,177,237,72,119,235,81,136,155,29,41,209,254,210,250,144,104,71,225,181,15,197,110,145,100,133,77,50,23,63,231,
171,70,76,55,15,181,59,98,58,32,101,141,87,216,185,91,245,83,38,215,217,28,100,228,220,99,153,69,76,109,197,197,140,49,37,37,210,20,167,137,235,77,189,200,20,142,204,191,70,167,204,57,74,233,162,248,243,
10,231,198,117,52,132,75,244,72,168,217,110,134,44,152,21,175,190,20,141,232,67,15,230,14,111,208,136,32,209,67,219,54,17,98,180,136,68,244,79,220,155,28,103,37,246,156,168,235,27,169,76,163,88,66,228,
100,180,156,163,165,162,105,168,28,23,213,211,86,168,170,170,148,146,243,219,187,233,244,102,60,158,78,199,243,241,4,101,9,235,205,113,181,122,94,47,151,235,213,19,0,140,199,55,180,137,168,89,158,163,
35,54,93,80,223,200,132,154,18,188,107,230,105,78,73,194,230,136,237,46,244,108,242,71,140,150,147,250,48,83,232,156,160,101,59,163,104,233,192,221,18,252,161,11,52,174,111,1,80,104,195,145,62,117,164,
87,79,1,9,205,68,48,140,232,59,16,246,18,188,180,134,240,49,19,0,221,230,168,114,205,231,191,2,229,251,144,250,182,251,81,115,74,7,118,202,167,220,160,99,29,148,149,206,231,131,243,138,165,34,121,19,197,
147,78,182,58,245,201,185,155,190,197,8,140,162,131,81,41,165,161,174,6,121,45,141,5,23,206,219,21,29,131,209,8,122,58,135,54,103,6,79,19,163,33,116,58,60,5,208,34,246,219,196,221,151,163,73,207,232,150,
38,116,70,27,222,67,7,166,176,147,221,201,63,157,121,93,163,154,68,179,159,70,16,106,95,43,108,220,207,61,50,235,225,248,225,180,157,77,111,102,227,219,201,100,62,155,220,78,38,9,0,172,215,199,197,226,
121,181,124,90,172,158,87,203,167,162,152,102,217,136,184,186,34,128,81,183,49,251,208,157,238,230,247,6,210,164,161,201,10,141,226,207,51,96,219,237,12,226,215,185,107,238,242,70,9,116,140,158,14,64,
214,123,207,208,254,46,34,211,241,116,157,81,83,178,230,22,232,244,181,235,232,68,234,111,201,17,54,113,197,35,220,22,101,40,118,74,154,176,79,28,15,181,249,22,213,241,80,162,221,54,243,217,215,137,246,
249,216,205,236,121,95,24,125,1,128,6,159,170,21,67,233,155,115,238,103,135,233,125,148,115,237,12,15,181,54,97,123,45,222,48,161,189,219,98,44,153,200,58,83,74,58,80,51,59,91,125,168,52,232,218,28,190,
173,172,217,141,34,159,19,109,31,148,115,195,57,115,79,135,179,14,202,12,58,7,94,34,241,12,169,8,47,191,144,132,246,209,57,133,74,123,18,161,179,192,31,175,225,60,239,77,33,182,173,241,142,135,50,87,124,
167,72,218,76,131,54,80,213,50,92,175,43,9,105,91,231,122,245,148,103,249,104,52,201,139,209,104,52,201,199,89,158,195,247,15,229,106,177,88,46,159,86,171,167,213,226,169,60,149,119,119,99,114,193,32,
73,39,155,88,190,33,164,183,199,74,91,211,79,29,59,213,233,56,16,71,102,47,160,103,40,167,239,152,103,21,13,249,99,153,208,120,0,75,37,86,54,114,172,175,4,115,9,187,208,62,244,0,165,15,99,241,236,117,
50,201,158,3,124,186,219,138,90,226,122,47,19,10,87,117,202,135,95,42,118,167,9,233,170,38,67,9,175,83,23,116,74,134,175,197,208,235,84,98,205,15,211,26,40,52,123,61,67,119,59,7,154,134,63,214,78,178,
54,78,87,182,125,254,108,56,107,38,32,0,152,150,33,45,101,237,141,169,20,42,37,57,103,54,28,84,22,37,193,161,164,169,38,89,71,49,143,108,158,97,212,60,213,140,210,28,3,165,17,189,47,29,165,197,37,17,213,
132,198,50,161,16,40,237,227,3,230,162,238,162,52,150,39,101,247,80,240,228,49,71,46,4,157,134,196,17,153,16,46,19,234,107,236,221,62,77,231,145,136,156,126,191,95,163,192,201,100,54,30,79,199,227,233,
104,52,29,143,224,120,4,102,187,48,65,33,99,236,253,39,95,90,51,17,221,36,41,154,116,196,71,132,244,174,135,199,221,0,221,240,85,27,194,119,3,65,36,11,26,171,5,69,137,167,255,27,133,217,152,54,10,70,46,
87,221,76,137,186,174,42,159,102,134,124,179,197,138,41,110,108,212,191,100,124,125,32,223,149,21,109,97,160,87,251,140,116,98,40,85,140,182,29,13,125,41,132,15,111,114,186,79,11,64,91,59,192,43,14,105,
196,202,182,69,157,198,73,21,190,145,12,101,172,174,47,41,165,172,158,73,25,49,146,101,151,104,189,65,209,4,245,38,19,106,26,58,165,60,3,153,82,210,22,142,128,115,80,74,19,88,60,103,69,29,140,122,100,
211,161,36,69,79,26,218,55,85,43,103,9,99,208,133,168,69,167,38,20,186,43,72,94,189,40,228,158,94,17,156,60,108,248,45,69,81,207,68,241,246,41,97,146,161,78,105,111,200,166,16,194,153,218,9,33,40,9,13,
70,198,59,119,122,38,85,85,150,167,249,124,62,25,207,199,227,233,116,58,31,143,177,170,96,189,60,46,215,139,229,242,113,185,124,90,44,159,103,179,219,36,73,44,255,170,13,11,168,99,136,13,231,25,157,220,
210,12,222,205,93,148,121,36,174,251,12,14,67,236,0,7,89,135,182,169,131,132,94,202,6,246,130,9,138,149,237,160,233,27,239,182,197,236,157,114,250,87,38,67,35,42,165,22,84,194,118,51,102,108,171,204,196,
242,161,241,233,190,205,103,161,143,157,74,96,0,228,107,206,250,169,157,250,120,14,232,110,117,125,52,207,19,179,191,139,140,237,116,145,187,35,164,182,34,207,93,192,110,170,56,136,202,186,38,214,15,17,
21,231,90,74,105,52,161,136,210,218,217,40,43,20,53,131,99,181,93,169,33,24,64,58,57,125,20,70,155,36,212,15,237,105,114,210,97,174,87,92,242,66,251,72,62,52,156,238,25,187,80,177,187,11,187,109,34,8,
25,245,222,40,239,52,157,68,152,231,57,207,249,121,176,135,115,164,55,132,212,179,101,178,244,150,135,14,161,46,138,95,45,23,69,29,191,143,242,98,146,101,73,150,193,247,223,31,215,203,197,114,253,180,
90,61,173,86,207,0,42,207,71,54,137,137,22,4,177,41,173,135,102,116,31,109,140,99,110,198,86,179,62,131,177,92,94,60,97,23,251,9,26,245,37,79,105,15,190,57,158,23,76,224,197,142,70,23,194,71,19,163,36,
162,135,118,235,144,174,224,189,93,29,169,223,14,67,163,142,118,208,28,107,10,45,113,125,95,12,37,2,242,72,41,201,187,175,192,165,73,39,215,96,232,133,25,165,109,105,208,254,198,207,68,108,23,159,46,213,
140,44,66,62,174,155,154,56,165,148,230,220,201,230,235,26,184,129,78,173,141,249,172,97,163,102,122,182,116,18,37,68,229,252,106,149,170,205,21,237,247,150,70,10,74,63,79,20,40,93,173,201,61,107,122,
237,219,56,41,141,232,155,197,37,159,138,122,222,119,109,50,154,72,72,216,214,139,77,189,65,91,6,181,35,153,225,193,40,246,81,75,58,126,150,132,114,146,15,173,119,176,17,125,163,16,223,84,212,251,154,
80,243,39,183,219,21,23,98,100,226,247,98,60,42,198,163,17,28,143,0,192,84,253,75,0,231,248,238,221,47,154,48,167,131,83,185,222,72,125,152,204,164,32,15,25,93,127,36,4,13,224,180,53,222,59,242,29,129,
124,172,215,200,67,213,144,138,70,106,83,29,229,2,167,95,161,131,24,105,17,172,27,61,33,98,151,217,191,73,188,191,14,244,130,235,123,180,38,211,165,22,109,173,41,249,95,164,179,224,22,215,195,54,97,180,
87,74,183,5,229,245,85,69,249,254,170,219,30,36,212,115,223,240,222,155,138,189,220,236,185,115,46,148,54,116,90,210,87,15,215,34,131,61,148,65,79,19,111,89,25,83,125,98,75,137,84,66,143,168,164,4,206,
65,74,83,68,146,70,0,3,160,67,24,229,28,170,74,123,205,208,61,57,169,131,206,38,39,181,177,124,84,210,212,34,127,233,154,53,31,115,131,247,77,216,28,216,121,250,39,82,154,247,109,234,29,63,181,232,41,
136,168,94,208,204,169,35,182,116,116,18,117,183,51,63,201,233,180,155,205,110,39,163,201,104,52,43,198,211,241,24,165,132,245,186,220,172,159,54,171,231,229,250,121,181,90,206,231,239,56,23,205,240,132,
234,126,206,183,65,122,78,219,4,98,195,7,143,76,96,175,173,152,162,205,115,49,197,34,182,8,233,89,243,118,198,90,208,19,90,58,226,123,9,201,91,12,53,186,84,229,45,202,243,190,18,197,107,88,231,21,5,165,
22,48,130,126,150,119,23,165,245,173,117,164,48,192,143,181,21,52,238,208,81,93,125,152,124,184,214,251,238,101,9,208,22,201,125,92,104,21,61,38,90,131,173,246,52,164,160,166,131,211,170,230,165,82,218,
230,61,235,38,119,0,52,65,189,148,18,0,181,150,214,149,194,232,61,205,150,58,19,106,80,79,8,148,210,240,92,112,180,52,228,155,156,115,243,172,99,166,81,18,218,246,208,163,162,110,139,8,171,73,94,11,96,
91,21,254,98,55,97,208,199,121,134,127,71,39,25,227,198,156,141,154,207,123,57,77,19,200,211,6,164,96,206,71,99,104,18,205,9,216,105,119,245,103,88,44,190,79,211,162,24,141,243,98,156,23,69,145,101,89,
6,143,15,229,114,245,180,90,46,150,171,231,213,114,33,101,153,231,227,64,204,220,8,166,72,5,201,85,232,26,84,206,34,169,110,158,249,154,216,221,67,172,224,17,9,186,3,124,100,237,145,123,188,161,62,252,
53,47,105,86,116,52,100,187,68,54,47,90,216,93,116,83,127,251,49,200,221,97,251,85,48,218,49,245,183,69,254,5,157,93,173,250,154,20,4,246,168,153,93,87,83,234,41,206,239,211,152,31,252,244,202,25,142,
208,102,54,67,51,137,99,141,137,232,165,82,166,58,111,182,40,91,121,71,33,80,74,105,28,209,12,128,2,128,17,51,1,72,122,20,12,205,116,124,147,192,168,246,248,166,113,200,55,200,232,102,44,94,68,207,144,
138,186,130,82,221,167,20,53,51,143,86,225,219,72,104,244,97,8,157,100,24,39,18,195,80,244,180,77,6,100,105,229,157,150,230,169,212,137,180,213,135,219,185,55,222,110,191,223,32,194,120,50,45,242,73,81,
140,139,98,92,20,176,63,130,84,74,105,208,160,148,146,10,212,167,159,126,101,103,6,208,216,246,28,202,4,5,83,108,70,238,245,127,196,252,237,98,33,190,129,116,61,120,104,107,147,82,19,118,219,208,243,58,
99,55,232,114,198,188,24,185,119,75,17,175,182,189,232,25,200,183,251,135,134,179,64,240,82,223,100,148,146,119,165,65,59,229,77,208,221,41,31,132,207,254,21,73,71,111,181,127,229,214,188,103,127,211,
187,232,185,221,13,184,182,124,228,230,20,48,18,206,159,155,229,173,159,136,178,5,34,141,40,181,102,136,74,41,233,172,111,165,52,252,84,186,88,222,172,35,42,50,213,17,165,148,97,216,110,58,151,16,27,57,
80,41,77,234,64,83,18,106,16,86,74,221,143,138,158,119,59,199,242,221,213,164,232,74,31,18,202,57,167,81,60,197,50,231,13,218,236,191,228,136,108,179,121,122,126,254,147,73,44,34,48,100,134,178,114,206,
92,7,167,41,193,39,140,49,198,5,231,92,48,193,152,224,66,216,242,189,176,210,209,134,248,137,33,43,38,243,187,155,15,147,241,100,60,158,22,227,241,168,224,82,194,122,121,92,175,23,235,229,211,106,249,
180,92,47,54,171,199,237,250,65,107,173,148,212,90,154,72,67,201,74,106,165,148,84,82,42,41,165,170,148,84,82,73,165,42,165,42,169,180,146,82,169,234,188,191,82,214,249,205,116,99,40,80,90,131,54,178,
209,51,117,53,113,184,155,247,206,0,0,25,227,232,126,90,110,14,66,51,167,204,24,2,114,119,215,49,247,36,102,27,102,145,1,99,204,226,44,34,55,33,1,66,253,63,26,221,83,248,208,218,85,43,204,21,175,65,59,
162,165,141,239,184,51,51,211,160,206,85,87,195,199,181,38,236,35,40,34,105,13,216,118,5,107,47,156,61,239,161,64,163,57,85,1,53,106,115,25,219,15,22,142,81,33,125,99,128,204,188,31,189,225,217,35,97,
254,12,2,2,163,169,14,162,127,100,228,195,41,212,104,18,218,231,97,206,6,11,106,154,195,180,6,165,142,182,243,70,41,173,76,34,176,182,18,50,62,171,46,188,183,181,106,29,220,6,16,80,35,48,247,235,212,159,
181,14,11,181,118,35,179,234,28,142,6,205,144,133,119,99,29,77,139,184,132,148,57,158,103,145,29,45,83,213,209,148,241,82,2,141,230,135,101,172,81,41,177,193,20,144,12,109,125,26,184,198,36,75,57,161,
62,36,181,15,178,178,87,86,189,166,149,84,102,93,86,170,110,149,87,245,158,202,172,72,115,204,149,57,254,74,41,173,204,155,154,19,214,245,63,153,207,145,103,183,159,127,241,123,203,46,235,161,53,14,49,
173,56,84,27,48,165,36,212,61,188,24,215,187,108,158,19,141,138,224,94,141,94,137,201,91,233,57,236,211,43,205,55,39,208,249,19,137,93,42,243,112,216,78,38,227,233,116,218,156,41,239,21,235,121,211,187,
158,134,243,78,252,212,80,74,33,178,170,82,121,58,205,178,60,77,71,105,154,229,105,145,102,112,58,89,1,174,185,116,148,156,205,38,246,158,89,67,161,214,82,41,165,148,180,255,53,214,205,207,76,214,207,
255,58,79,217,88,53,41,140,217,163,142,45,188,105,86,205,61,251,43,111,221,123,19,162,130,98,94,121,10,122,56,99,122,165,228,75,50,166,11,147,141,223,106,170,79,127,53,104,44,143,79,79,230,182,163,129,
49,238,118,254,22,74,201,170,82,74,106,100,9,231,66,107,37,229,150,177,9,113,177,82,205,246,173,154,127,121,213,106,104,119,69,138,9,99,218,134,185,246,9,183,117,119,108,209,161,174,187,86,63,27,104,135,
207,199,193,180,105,210,139,203,161,170,221,34,109,148,111,54,74,50,14,54,122,96,67,83,90,253,63,254,191,255,241,229,47,254,179,75,163,81,250,73,170,243,204,69,244,30,9,181,1,232,133,184,222,22,214,154,
177,124,88,20,14,77,125,46,186,228,181,131,102,232,131,231,181,48,213,24,57,26,205,158,158,23,219,221,142,161,213,223,91,87,17,134,156,11,81,71,249,220,216,139,136,26,64,205,58,115,27,185,181,194,99,140,
9,195,102,39,147,187,201,104,84,20,227,60,175,163,248,242,4,219,77,185,217,172,86,155,213,102,181,88,175,158,247,199,109,85,157,204,239,173,28,241,212,74,73,89,179,78,41,149,146,178,254,183,50,59,72,45,
149,52,119,84,41,149,2,243,106,144,118,232,171,214,129,207,68,179,94,110,186,47,204,248,19,180,164,210,206,158,50,169,14,218,38,128,102,3,71,68,115,148,144,12,170,34,166,168,232,230,196,213,15,17,17,240,
82,36,175,9,101,81,77,43,141,102,160,170,235,164,5,58,194,10,160,213,217,224,82,107,13,104,152,204,153,58,246,71,75,188,8,11,8,53,179,63,167,166,155,181,23,71,56,207,236,19,237,118,47,121,2,225,180,106,
128,70,170,194,16,44,4,49,26,205,242,92,36,89,154,37,249,226,233,97,119,88,30,79,7,226,219,166,149,174,169,149,189,125,26,85,113,205,162,28,215,215,160,161,97,55,171,153,19,198,212,117,67,115,189,159,
231,112,97,3,79,205,46,231,17,133,221,24,218,200,61,144,35,104,63,128,54,172,147,100,252,153,151,0,65,160,59,56,88,165,21,87,218,189,230,168,131,180,7,67,73,37,117,173,175,151,103,196,148,74,42,233,96,
212,18,23,165,164,82,160,180,84,26,12,181,215,90,75,165,141,243,168,210,96,252,192,21,161,245,90,105,253,201,251,95,25,41,55,162,182,25,82,237,216,40,1,83,109,199,151,57,18,234,143,8,235,142,235,93,101,
207,143,229,99,20,41,58,109,9,99,142,36,225,56,144,182,122,125,35,150,183,74,38,198,24,187,187,251,236,253,251,95,120,45,240,66,156,131,116,175,203,211,115,176,15,205,234,205,223,120,124,252,150,49,204,
138,81,158,231,185,169,36,101,240,240,80,174,150,79,203,213,211,114,185,88,46,159,149,210,255,248,143,255,91,147,115,209,59,234,57,155,19,140,87,83,205,93,61,214,230,231,161,218,197,76,61,237,236,128,
244,212,66,167,157,157,127,31,108,17,144,183,101,45,117,75,141,190,191,80,233,35,213,136,122,86,228,59,40,42,190,192,250,232,175,127,253,131,148,229,104,52,226,60,73,146,244,47,95,255,81,129,254,111,255,
235,255,209,94,86,130,78,77,168,238,248,252,49,13,22,116,183,210,191,160,94,212,233,54,16,21,201,118,235,189,206,37,199,112,4,225,249,118,98,83,162,132,117,42,27,222,209,248,79,73,83,107,215,82,41,37,
165,172,209,87,74,173,165,148,202,252,235,66,67,186,191,201,120,18,226,169,45,152,50,66,63,235,201,75,134,132,210,24,58,164,162,77,45,141,31,215,139,152,44,209,99,239,17,255,145,118,75,11,79,251,237,179,
212,179,53,19,111,20,151,0,206,93,237,38,163,76,68,163,156,2,98,83,121,202,189,217,156,100,44,104,189,94,150,167,83,117,184,153,189,203,178,34,207,167,69,94,100,25,28,14,160,148,185,49,155,86,4,253,249,
231,191,118,217,36,98,254,118,214,120,196,172,148,117,103,137,230,124,187,130,96,192,92,208,47,228,233,228,33,218,206,64,168,37,70,103,35,7,202,10,232,231,69,20,149,151,55,218,61,155,214,250,58,148,226,
255,152,150,214,187,69,39,30,117,53,249,60,62,126,167,148,188,189,125,63,26,77,16,217,211,226,129,115,241,171,175,254,19,99,172,179,172,20,213,51,233,43,85,4,224,89,119,7,191,102,171,189,211,203,44,239,
90,14,169,142,246,29,132,61,105,97,238,194,182,201,35,99,245,224,3,162,100,162,173,68,78,53,104,54,106,68,83,29,106,84,219,157,38,148,115,32,174,81,96,154,151,0,24,231,218,133,231,102,214,172,205,226,
162,101,169,94,169,156,210,76,160,233,78,10,124,148,129,186,171,172,214,135,182,168,175,219,2,121,140,205,215,141,250,135,122,1,62,179,137,185,218,57,201,245,44,121,17,189,85,128,50,98,188,116,182,85,
166,174,160,84,17,213,116,26,173,129,24,145,173,86,143,121,86,228,121,49,202,71,89,150,37,73,146,230,240,240,125,185,94,63,45,151,207,203,229,114,181,122,78,211,60,203,114,234,7,17,140,180,60,247,29,1,
40,139,167,174,153,193,13,186,104,54,50,16,145,80,240,86,29,94,130,208,97,165,220,142,161,208,110,171,220,215,142,200,124,247,195,97,119,56,236,202,242,248,201,39,95,54,197,213,126,200,253,82,173,247,
71,87,48,93,228,161,61,200,215,153,116,87,85,185,218,60,207,199,55,227,241,140,115,177,88,220,111,86,139,233,100,62,26,77,59,138,242,208,28,175,212,39,171,219,206,151,233,141,80,191,136,144,246,237,92,
104,209,243,117,147,89,95,171,96,38,134,121,134,161,214,154,30,181,70,165,234,121,197,86,156,100,32,194,149,224,149,109,217,52,101,122,35,11,5,55,34,151,202,60,1,92,150,147,59,240,85,74,91,92,214,52,162,
55,181,38,87,113,50,80,107,116,78,22,118,25,85,59,245,9,231,69,20,55,163,4,51,252,189,67,250,73,114,225,145,208,222,225,42,225,149,220,178,78,90,39,137,212,244,155,101,253,179,241,40,157,171,28,62,44,
203,211,233,116,188,185,121,151,230,163,52,47,242,188,40,50,168,14,192,160,30,141,5,32,25,99,159,188,255,146,220,228,61,11,184,198,148,36,219,223,9,193,58,54,239,213,254,221,59,234,174,214,210,134,20,
234,113,25,196,253,153,34,63,215,149,81,60,84,213,233,112,216,159,78,251,227,241,80,150,39,89,30,129,33,50,161,202,163,126,255,5,231,60,28,115,239,89,169,182,37,53,15,135,109,81,76,222,2,30,53,249,93,
240,218,107,190,35,108,15,238,106,245,119,60,157,142,167,211,177,170,78,82,86,74,169,178,60,205,167,55,243,249,221,205,236,29,114,67,105,88,150,141,15,135,141,16,169,16,9,0,35,54,8,181,0,174,217,217,5,
45,61,175,93,25,134,232,4,189,88,176,163,214,235,197,225,176,147,74,114,134,156,103,69,49,46,138,201,139,239,112,65,222,9,98,231,118,132,133,106,173,182,219,205,241,184,59,157,78,134,138,38,73,58,30,207,
132,72,154,158,202,181,119,157,243,97,178,6,204,103,82,105,185,36,99,231,238,65,45,37,216,129,157,244,239,187,140,167,203,167,49,206,117,85,153,172,174,178,192,162,58,92,63,66,91,94,74,72,155,225,120,
131,153,214,254,161,129,114,48,90,186,245,255,100,184,177,133,129,186,98,49,171,181,59,100,139,169,62,211,209,199,212,19,143,206,245,116,21,121,175,1,201,91,236,251,212,112,188,92,62,230,249,56,207,71,
163,116,148,101,69,150,37,34,131,135,199,227,122,189,92,175,23,203,229,243,122,189,72,146,92,36,41,253,73,130,201,239,230,151,48,194,55,69,3,117,203,65,25,113,171,213,22,139,117,199,25,25,131,81,55,32,
62,210,211,25,148,239,161,195,10,47,252,3,90,235,170,42,165,172,170,170,44,171,83,85,158,170,170,172,170,178,170,42,68,237,210,38,105,158,151,156,85,167,99,154,100,197,236,157,16,9,248,211,28,35,33,127,
148,224,124,255,253,159,54,155,133,16,201,135,15,191,52,61,11,237,168,23,185,214,143,199,253,106,245,188,63,108,202,242,160,164,2,0,33,68,81,76,223,191,255,194,126,42,124,17,51,109,109,253,222,237,214,
251,253,250,112,216,151,85,9,160,24,114,169,21,42,37,146,52,207,243,217,244,118,58,187,3,208,203,229,131,146,170,170,228,98,241,103,165,164,150,85,165,20,34,10,145,164,105,241,225,195,47,133,72,60,103,
216,158,3,229,187,147,182,4,79,207,60,116,179,89,62,63,127,179,223,111,16,121,194,19,96,160,0,160,90,61,62,125,35,56,27,141,110,63,251,236,43,198,248,235,216,189,139,178,27,65,21,253,70,74,201,231,231,
239,55,155,231,195,105,135,200,80,11,142,168,81,73,169,183,219,213,253,253,95,138,209,236,23,95,254,214,217,117,59,226,73,26,147,192,81,82,68,105,186,57,137,56,212,113,79,52,209,61,231,238,220,11,167,
103,27,63,80,109,48,215,96,176,214,26,145,83,18,234,168,168,189,138,209,35,164,244,250,34,151,252,89,40,234,120,143,104,235,212,238,206,129,118,116,200,180,217,59,69,161,182,201,76,125,163,188,166,146,
212,177,90,12,73,104,179,102,101,170,46,172,170,78,151,119,192,196,0,0,32,0,73,68,65,84,167,234,120,51,187,205,211,44,205,179,52,47,178,4,78,71,96,192,64,105,5,26,24,67,132,79,63,253,170,153,230,168,167,
116,120,73,207,112,158,34,85,29,99,173,164,243,204,234,35,144,17,163,138,93,69,36,165,36,16,163,19,90,221,170,213,134,36,79,15,90,43,173,104,242,222,238,47,173,58,202,14,160,70,158,166,69,81,32,55,229,
125,20,149,44,183,219,213,124,118,55,153,220,24,156,242,130,181,150,129,101,17,84,58,28,118,251,253,242,230,230,147,170,58,126,243,205,191,191,127,255,229,124,254,174,39,204,173,150,79,139,213,67,121,
58,164,105,154,136,164,200,11,67,195,181,210,85,117,250,250,235,127,251,240,225,171,209,104,218,179,178,116,81,63,191,221,174,54,155,231,211,97,15,182,177,98,84,140,211,52,79,147,76,36,169,16,201,110,
183,78,211,116,54,155,3,192,106,185,92,46,150,34,73,38,147,219,44,27,85,85,85,85,39,89,158,202,170,60,158,118,155,205,115,37,203,223,252,250,127,106,100,131,116,56,236,90,95,106,79,186,204,67,23,139,135,
199,199,175,165,44,243,180,152,207,63,17,130,187,159,76,41,101,138,45,135,195,246,79,255,241,47,191,248,229,239,211,52,125,105,234,19,154,35,64,252,113,32,85,117,186,191,255,102,187,126,214,90,33,79,210,
36,87,82,78,166,243,44,43,16,77,209,71,150,229,97,179,219,125,243,237,31,191,248,252,55,110,114,140,37,158,224,76,63,17,145,115,101,184,39,34,112,110,162,126,23,173,187,70,248,48,238,54,167,116,237,4,
202,24,183,70,107,42,76,128,94,92,108,196,19,207,144,70,195,121,209,118,203,107,11,225,61,100,37,235,44,154,163,37,196,19,104,57,158,218,48,123,229,32,55,15,153,24,48,179,230,92,120,111,197,20,169,26,
51,65,17,113,241,124,159,166,89,150,231,105,62,202,210,44,75,18,145,194,195,211,113,189,92,46,215,139,245,122,177,92,62,142,242,81,146,36,225,57,68,123,55,73,87,59,54,231,20,158,7,99,0,177,46,246,198,
196,199,78,71,108,75,156,120,15,183,219,229,191,254,243,255,165,19,145,104,206,18,198,24,175,155,96,81,8,198,128,51,100,130,163,113,255,67,142,66,115,141,74,91,81,189,214,160,25,227,105,154,165,34,99,
140,153,132,59,131,186,105,1,236,48,106,64,88,47,87,66,164,95,125,245,123,206,69,160,91,140,183,184,116,84,147,158,158,190,205,242,73,49,202,17,70,137,200,158,159,191,153,207,239,154,132,40,114,106,173,
215,79,79,207,223,105,165,211,52,27,143,38,169,72,48,73,57,114,198,1,53,83,90,87,213,113,179,94,63,60,124,253,171,95,253,151,30,84,180,75,196,165,148,90,46,31,183,219,53,64,197,24,103,130,143,199,55,69,
49,41,138,49,189,115,28,143,251,197,226,126,50,154,26,103,153,229,250,105,187,93,124,249,139,223,167,105,30,246,113,150,229,209,156,144,196,225,48,226,222,210,155,56,99,180,38,182,94,47,190,251,238,79,
82,86,163,188,200,138,219,44,43,18,158,48,145,102,153,0,168,7,6,41,89,73,169,14,199,98,189,222,126,253,245,31,126,251,219,127,122,37,9,245,62,191,185,117,223,223,255,117,189,126,22,130,127,246,197,111,
198,227,153,33,117,82,86,223,126,251,199,170,58,205,231,183,105,154,86,149,174,170,157,214,15,79,79,247,53,235,211,110,84,156,43,34,213,8,98,242,155,118,221,52,116,106,165,32,232,3,146,246,232,84,142,
135,74,169,77,59,188,137,171,0,64,107,206,57,216,25,162,230,231,8,169,168,225,162,42,64,82,164,182,24,209,112,222,49,83,209,169,242,109,157,187,235,181,54,117,240,80,10,178,14,46,9,94,208,45,97,90,147,
250,63,241,192,129,20,233,110,78,8,105,127,3,121,40,15,243,249,93,150,22,105,94,228,69,145,165,112,58,1,40,99,7,162,65,1,71,230,72,168,189,225,80,40,244,187,235,188,217,197,180,243,221,131,90,135,168,
193,25,233,77,70,138,135,243,238,152,45,22,15,217,104,108,51,110,192,76,11,141,245,192,103,192,4,112,145,36,66,36,70,112,35,132,89,23,156,39,198,92,181,44,79,155,205,82,8,62,25,79,161,22,237,35,34,175,
91,157,144,237,246,235,205,122,197,5,183,78,43,209,17,184,30,30,57,92,136,160,194,225,176,45,203,227,108,114,155,103,99,68,118,58,29,17,249,110,191,157,78,110,218,178,147,187,221,250,254,254,175,90,171,
60,27,101,89,158,166,89,34,178,36,229,130,101,40,152,201,112,84,85,121,127,191,62,86,123,115,63,184,132,146,216,134,8,74,169,197,226,97,187,91,9,206,211,52,169,42,61,157,222,77,167,183,182,194,14,148,
118,61,63,125,151,101,69,94,140,211,52,127,120,248,118,187,89,165,217,216,152,34,122,77,211,90,107,3,172,212,249,159,182,249,246,118,9,137,102,69,209,96,244,215,127,253,183,195,113,51,26,77,1,184,2,117,
60,30,143,199,35,99,44,201,178,236,88,76,167,179,155,249,59,0,38,229,73,106,216,108,82,37,213,98,185,219,110,87,211,233,205,235,120,168,166,23,254,110,183,188,191,255,139,214,250,246,246,195,221,221,7,
114,194,107,33,210,79,62,249,197,127,252,199,127,215,136,55,55,183,183,243,247,79,15,39,93,15,133,175,189,239,204,53,101,117,154,224,149,230,237,186,27,108,119,46,28,153,198,48,68,109,99,112,151,45,85,
46,48,183,233,184,134,145,29,98,237,138,127,177,46,31,141,170,163,225,188,139,77,69,84,25,26,168,154,34,36,52,172,32,153,30,205,150,143,117,33,121,218,196,71,108,70,232,180,91,148,211,120,63,192,217,51,
23,94,174,158,210,36,205,146,52,73,243,84,164,66,100,105,10,15,143,229,114,185,220,108,158,214,235,197,243,250,113,148,207,56,79,232,101,67,38,79,57,60,69,66,72,117,83,228,132,52,246,119,61,242,52,15,
217,46,253,139,70,241,254,77,43,77,179,44,155,100,89,150,38,105,146,100,105,150,39,73,150,36,121,154,166,73,146,209,220,104,204,230,14,0,48,77,11,198,248,253,253,95,24,99,227,241,124,50,153,113,206,16,
5,50,40,79,167,245,250,121,187,217,108,54,171,207,63,255,181,16,105,160,91,194,22,61,99,23,28,60,62,124,147,231,163,124,52,202,139,98,191,221,25,185,159,168,135,9,250,59,75,89,125,127,255,151,195,126,
155,231,69,154,22,89,150,153,81,5,66,164,163,124,148,230,5,103,28,25,219,174,23,135,227,1,145,23,217,248,243,207,127,75,49,244,170,124,232,122,253,188,94,61,49,206,39,163,233,238,176,155,20,227,217,252,
151,142,32,147,25,171,0,128,155,205,82,42,57,153,76,178,188,56,29,143,0,128,200,191,248,226,55,205,177,131,209,127,161,121,134,232,232,205,166,5,229,227,84,244,241,241,155,135,135,191,38,201,136,243,116,
187,221,216,59,37,215,26,142,199,195,225,176,63,165,59,165,42,212,108,118,115,59,191,125,191,219,109,143,167,93,146,230,73,146,111,119,171,217,236,14,174,176,190,199,152,56,180,62,43,238,239,255,178,221,
46,16,241,195,135,95,141,70,19,82,99,172,143,94,158,143,24,227,160,20,84,218,120,200,113,68,33,32,73,18,131,113,132,132,42,203,61,193,218,217,129,115,174,51,215,160,43,46,153,28,168,45,46,105,98,32,98,
96,65,75,105,154,59,149,109,138,55,228,212,20,151,28,246,249,197,37,170,177,167,193,123,136,135,158,224,201,109,23,151,242,238,216,50,86,55,234,146,215,150,24,141,38,67,25,145,233,56,52,244,166,210,71,
109,159,48,36,170,180,78,101,94,113,220,109,70,227,105,81,140,139,188,40,138,81,158,193,169,4,128,58,136,80,0,2,248,135,15,95,210,25,30,14,4,201,160,77,154,24,133,102,38,20,93,245,137,22,244,201,192,134,
14,17,95,84,87,31,209,132,126,241,197,111,191,252,178,67,85,6,23,109,234,13,78,213,237,176,140,51,198,198,227,41,67,254,188,120,220,110,214,155,237,118,187,91,165,105,78,202,62,142,119,120,213,3,12,193,
52,60,119,214,235,69,37,171,233,232,38,203,10,193,83,100,123,68,150,103,197,100,50,15,79,179,229,242,225,105,113,159,112,49,153,204,43,37,79,167,211,233,116,100,140,113,158,100,217,169,170,202,41,194,
120,124,179,217,60,111,182,171,221,118,179,223,111,190,248,242,119,66,136,107,116,77,245,14,101,121,124,122,252,78,169,178,24,77,42,89,86,178,250,236,195,87,73,146,123,95,138,216,24,170,245,234,113,52,
154,140,70,19,165,212,102,183,220,108,151,211,233,77,154,102,142,87,210,185,167,22,40,181,55,2,150,222,134,95,36,210,194,170,42,255,252,167,127,41,171,19,0,50,6,183,55,95,76,103,183,105,154,211,211,233,
120,220,223,63,252,117,189,89,32,50,228,104,10,226,2,57,231,60,73,82,3,43,175,23,135,150,229,241,254,251,63,75,37,57,79,62,251,236,215,89,86,120,249,43,155,55,215,204,120,53,112,212,90,85,213,190,44,79,
230,12,180,137,123,0,64,198,92,35,28,58,208,108,58,215,25,191,81,102,101,161,38,244,70,11,146,218,213,139,24,51,19,33,141,141,30,167,226,80,151,81,60,119,194,199,116,75,64,134,205,53,235,242,62,122,134,
41,209,184,198,190,243,55,239,154,153,236,133,240,142,51,198,84,247,44,44,46,17,93,61,186,33,201,198,28,175,217,101,207,73,13,138,53,155,74,17,17,215,235,149,68,45,82,193,185,16,34,21,92,112,1,207,203,
114,189,94,174,87,11,99,50,50,26,205,76,232,26,106,238,188,18,74,211,63,212,143,220,155,181,120,160,245,159,54,150,209,35,31,122,65,37,26,122,53,181,204,249,0,0,60,28,118,73,146,114,145,114,33,132,72,
56,231,229,177,50,105,80,6,200,65,124,246,217,175,76,79,97,128,152,58,54,14,23,59,132,135,207,203,251,241,120,58,25,77,199,227,233,106,181,220,108,150,155,237,234,246,230,83,108,186,99,72,89,125,247,221,
159,78,229,33,225,137,148,167,253,94,38,73,130,136,74,171,178,172,202,227,161,44,211,188,168,204,247,220,109,54,187,221,118,183,91,207,102,239,178,52,111,63,61,227,210,37,173,97,181,122,218,109,23,92,
228,163,108,44,101,149,96,126,123,251,137,131,149,230,239,85,131,194,98,241,12,136,105,146,137,36,171,202,19,2,75,68,246,225,195,87,230,200,91,197,27,82,48,117,124,51,26,194,183,27,208,97,155,86,1,17,
214,235,229,215,127,253,3,112,16,34,251,242,203,95,143,70,211,208,183,219,80,191,175,126,241,143,139,197,253,227,211,119,230,130,154,78,239,20,160,115,25,187,70,162,16,213,234,227,110,191,121,184,255,
115,158,143,171,253,254,243,47,126,157,165,5,52,189,186,157,180,75,74,5,92,112,206,144,241,253,126,87,86,85,85,29,139,98,230,124,61,108,96,14,0,96,107,65,212,158,206,41,150,184,251,60,46,78,183,209,253,
121,58,183,245,22,49,10,167,218,38,141,82,81,51,176,222,128,131,214,53,21,141,117,168,107,170,112,242,34,236,142,208,92,180,106,40,218,107,241,228,15,64,52,251,25,6,242,222,216,15,251,58,238,168,168,249,
218,0,240,151,63,255,191,155,237,35,231,66,36,25,103,156,243,68,112,211,17,239,58,62,157,57,83,210,156,238,41,108,49,74,128,214,179,249,251,44,41,178,44,79,210,36,205,184,148,192,92,30,20,20,130,94,175,
31,214,235,7,83,200,38,173,102,103,99,17,83,85,52,255,217,30,121,215,234,171,26,30,51,141,10,184,242,36,44,161,11,125,44,5,225,119,13,16,135,105,17,140,222,107,24,254,59,81,3,52,237,8,206,191,166,198,
241,100,158,38,137,65,210,178,44,55,187,245,118,187,217,109,55,155,221,170,42,15,95,127,253,7,167,235,34,151,68,215,236,10,219,195,68,219,202,177,170,170,172,24,167,105,150,100,25,66,173,254,99,200,86,
171,251,213,234,222,29,13,41,37,99,34,21,153,84,82,215,115,113,161,170,142,238,188,210,168,79,199,157,212,10,129,33,114,100,128,192,56,227,187,221,114,191,95,133,147,166,58,187,9,52,0,227,34,41,70,83,
68,80,74,29,14,123,68,248,238,187,63,66,100,120,137,19,24,42,173,112,60,25,231,69,81,149,229,118,187,217,108,86,85,117,252,143,255,248,127,168,3,166,91,55,103,66,180,27,56,56,152,126,151,207,57,18,66,
103,52,85,95,53,85,85,101,233,88,51,212,101,169,177,252,227,31,255,123,84,83,12,196,66,165,44,171,221,46,17,140,51,38,148,210,32,65,107,181,222,172,254,240,135,255,187,179,163,20,160,101,180,129,121,40,
101,37,146,108,50,158,43,85,105,93,126,243,245,31,162,71,207,28,10,41,171,132,167,9,79,184,224,168,53,3,4,38,118,187,197,63,255,243,255,73,61,122,220,245,229,93,104,90,25,123,10,169,149,146,170,146,82,
41,85,89,55,52,73,154,59,245,185,61,84,43,173,148,16,201,237,237,151,183,183,31,60,42,74,174,136,232,64,58,8,235,242,33,21,109,75,137,54,60,152,251,145,80,175,94,143,225,191,109,42,253,24,34,159,93,222,
92,68,255,180,248,203,187,187,119,156,113,13,192,5,99,12,24,2,231,200,184,17,158,1,114,197,153,226,130,115,166,25,83,140,75,206,144,49,228,92,50,102,212,74,21,79,198,89,146,38,105,42,210,36,77,50,33,96,
187,149,235,237,114,189,94,109,54,155,205,102,181,219,111,178,148,43,208,90,75,173,140,73,140,116,157,185,245,79,37,43,99,53,98,90,116,149,116,191,95,85,195,168,148,82,27,47,46,89,95,62,160,172,41,215,
57,156,71,48,86,108,12,141,251,156,249,78,136,160,57,32,106,224,26,56,67,6,192,1,56,128,64,228,90,51,165,56,160,0,197,17,165,214,92,3,7,16,90,75,173,185,214,220,156,16,26,24,128,0,80,0,92,163,198,243,
32,60,6,160,160,150,70,233,44,155,8,145,38,73,146,36,34,17,162,170,42,109,174,91,134,156,33,166,28,160,114,26,112,160,182,108,214,172,205,213,99,73,198,207,55,111,83,90,11,145,21,217,184,40,38,69,54,218,
236,87,251,253,122,191,95,35,74,235,234,95,55,234,165,233,72,41,89,202,61,3,101,28,232,0,170,58,92,178,200,192,19,4,117,220,237,193,220,39,142,199,29,50,69,172,215,124,193,141,75,85,19,32,208,90,107,206,
211,60,31,113,158,40,93,41,169,143,199,141,25,45,73,4,143,58,156,249,172,148,206,178,145,201,59,159,78,39,0,228,28,16,80,233,10,44,98,218,105,5,14,64,149,155,193,118,198,80,208,112,54,156,81,231,162,182,
223,116,132,231,163,91,19,118,44,75,61,30,207,170,170,210,178,162,164,214,134,144,80,255,132,54,27,110,222,57,73,240,116,58,156,100,81,150,71,0,148,74,26,123,205,186,150,13,160,227,229,126,140,106,82,
1,0,1,165,212,121,62,25,143,39,171,197,147,70,133,40,235,163,199,234,166,36,107,255,98,206,64,5,160,68,154,240,36,17,60,89,60,63,44,55,171,221,230,57,203,132,86,149,212,18,81,35,86,128,10,177,98,76,105,
45,25,151,128,18,160,254,79,161,4,212,12,165,68,133,204,24,51,215,174,119,82,154,17,202,160,21,83,186,110,106,82,138,129,70,165,153,148,167,175,191,254,215,219,219,207,41,21,69,84,38,91,106,71,201,107,
90,89,10,195,249,168,239,18,13,234,227,60,180,63,140,70,37,80,238,95,91,210,137,24,143,134,240,234,44,133,12,253,180,109,160,136,218,56,100,162,173,64,215,151,22,154,178,59,67,6,188,222,195,108,2,134,
13,143,40,144,10,242,36,229,73,154,36,105,42,114,33,50,91,129,48,127,95,106,192,36,97,231,243,155,204,92,180,215,134,49,40,212,103,255,204,243,245,97,172,64,65,43,123,77,160,2,165,1,52,104,133,8,214,107,
18,117,205,45,234,249,43,54,99,202,106,219,32,100,26,129,213,247,136,90,208,90,251,55,57,155,72,43,6,99,104,44,65,235,221,208,169,98,27,230,120,200,98,221,23,140,177,52,205,210,52,73,146,140,243,148,33,
238,247,155,253,118,189,223,109,247,187,77,89,30,133,176,83,79,80,131,174,29,123,106,234,100,179,20,214,249,20,53,106,212,160,153,245,65,37,128,170,37,230,227,34,207,211,52,207,54,187,245,118,187,94,109,
214,135,253,54,207,211,218,54,85,3,162,72,211,84,202,19,64,85,127,213,179,31,16,186,95,26,108,162,1,180,220,239,55,73,82,156,202,67,154,38,109,3,162,201,121,120,198,5,165,33,75,243,52,203,179,180,56,30,
247,90,235,211,105,203,24,154,201,189,103,26,165,181,198,179,76,205,32,99,146,164,89,150,167,89,86,85,114,183,223,30,14,91,173,237,208,222,218,224,168,6,93,171,222,96,22,30,21,2,2,170,154,89,186,179,1,
53,0,115,130,218,38,211,211,230,171,214,223,11,80,131,70,72,102,179,249,241,180,3,40,207,167,127,131,113,250,97,166,187,121,84,178,42,79,101,89,158,210,52,3,208,12,88,34,132,243,0,173,113,209,162,184,
187,43,185,96,130,254,17,208,80,41,53,26,205,71,163,201,106,241,116,170,142,89,150,106,224,231,50,60,106,116,23,17,232,250,198,196,120,194,211,36,73,17,208,216,240,102,105,198,24,72,208,12,204,136,36,
198,25,128,230,117,210,83,153,251,190,62,15,206,97,18,52,103,76,43,137,140,49,37,21,48,134,182,191,19,80,1,42,52,122,120,5,0,202,248,204,2,224,225,176,55,245,119,198,152,148,42,232,162,244,65,201,115,
55,7,80,77,77,40,16,195,17,140,85,212,27,53,37,236,108,230,140,255,96,177,118,111,104,11,234,59,244,4,180,195,253,238,221,87,235,245,147,81,53,50,134,156,35,231,200,21,211,188,238,175,215,140,129,228,
8,28,81,32,114,5,2,129,107,37,52,114,173,185,201,47,39,73,154,166,153,209,250,36,9,236,118,176,217,172,54,235,213,122,187,220,109,214,219,237,58,207,50,165,53,128,2,173,16,20,34,55,42,116,68,142,40,1,
36,89,17,200,36,42,129,168,24,171,0,20,160,2,41,53,87,224,162,57,99,178,203,64,107,133,141,180,87,125,66,214,134,191,224,28,11,107,28,244,20,175,156,135,97,59,247,162,120,103,235,87,11,108,25,227,53,170,
218,210,28,195,218,93,24,65,41,157,212,252,51,21,34,77,211,228,84,150,181,121,45,2,34,164,105,129,136,238,46,65,167,201,59,1,44,88,135,230,70,211,119,243,124,145,74,102,89,146,231,163,60,27,229,105,81,
30,15,90,43,148,58,203,70,6,219,149,146,200,132,145,161,48,198,1,120,212,202,51,108,187,210,90,151,229,33,203,10,227,78,13,158,26,140,128,238,57,21,160,21,2,203,146,52,77,179,52,205,141,99,116,85,150,
156,167,158,237,135,237,83,112,78,91,74,131,174,170,42,73,178,52,77,179,36,123,94,62,238,119,235,195,225,144,101,169,214,90,129,100,181,165,134,229,71,245,196,236,136,91,168,189,17,105,240,103,129,24,
16,211,36,135,77,112,12,0,53,206,110,110,87,171,53,3,4,158,219,251,76,252,248,156,205,181,45,177,209,186,50,41,166,211,169,92,175,215,101,117,200,243,162,65,53,227,61,115,17,145,127,37,171,241,104,54,
25,77,78,85,137,156,153,254,81,237,155,2,214,233,77,48,81,152,150,73,42,178,172,72,178,252,249,249,97,179,126,222,239,54,121,81,40,165,24,114,133,138,161,2,166,148,170,73,40,98,253,31,32,135,250,138,83,
160,42,141,82,43,166,64,42,85,73,133,198,173,217,140,6,81,170,158,170,36,165,52,245,40,195,83,57,207,255,225,31,126,235,196,76,84,198,100,140,38,140,22,213,138,156,48,26,194,123,109,235,33,249,35,189,
51,164,215,179,135,191,0,116,116,41,182,16,216,232,77,210,157,4,44,20,234,155,91,229,111,126,243,95,77,54,80,8,206,88,98,230,119,10,145,52,147,158,231,241,74,222,240,78,165,228,159,255,248,47,105,146,
39,73,42,68,150,36,137,72,96,127,60,158,170,178,170,142,166,244,251,217,135,175,62,253,244,23,16,115,165,117,182,93,13,223,200,184,33,49,68,199,10,117,31,51,122,143,111,3,142,238,161,170,33,11,243,10,
74,244,239,125,251,237,31,17,33,77,242,52,201,146,36,97,92,108,214,139,253,126,189,219,237,246,251,237,120,124,243,238,221,231,45,159,92,247,159,169,169,1,254,242,231,255,145,36,105,49,154,20,163,233,
122,189,216,108,55,155,205,122,52,158,124,254,197,111,17,97,181,122,126,122,250,54,203,138,79,63,253,138,215,109,122,120,149,178,39,250,48,170,54,61,158,246,235,213,115,146,164,34,17,137,72,181,210,101,
89,205,102,239,109,253,240,66,207,247,241,120,120,120,252,58,205,242,36,201,203,178,50,161,206,175,127,253,159,179,172,8,186,195,227,78,34,237,227,164,46,123,124,40,165,254,244,199,127,97,156,33,23,255,
233,247,191,75,210,252,98,129,55,236,197,122,120,248,235,118,187,96,136,167,211,110,60,157,127,241,217,255,18,182,123,246,25,127,242,248,248,237,225,176,53,0,186,219,237,190,252,242,119,86,12,224,187,
32,210,70,131,175,191,254,55,41,171,44,203,235,104,75,36,255,243,63,253,239,73,146,54,115,199,58,106,127,231,92,238,141,181,157,179,188,107,102,78,235,90,133,214,178,170,42,251,176,82,74,25,75,95,41,171,
96,118,142,34,53,121,36,19,207,84,20,160,236,14,113,219,233,112,139,232,95,148,143,14,79,134,192,111,45,166,3,13,93,214,193,213,208,61,189,189,9,63,77,81,222,160,42,169,65,209,222,208,184,107,192,122,
253,44,210,68,36,60,73,210,84,8,145,166,0,192,20,88,97,61,34,103,239,222,125,238,157,124,22,58,27,74,38,111,88,188,85,174,156,103,37,49,6,65,29,182,213,2,195,187,245,64,171,115,104,188,97,41,134,179,145,
31,129,254,141,221,110,83,201,106,60,26,39,38,173,145,230,229,169,172,25,15,67,193,197,221,221,135,22,39,11,239,171,71,209,147,244,29,62,223,43,37,133,16,137,72,234,56,85,107,193,216,135,207,126,133,136,
79,79,223,174,86,207,211,233,237,187,119,159,247,51,1,193,158,237,143,225,75,246,251,205,118,187,202,178,60,205,114,4,212,90,149,85,57,153,204,59,123,198,27,95,118,181,122,204,210,60,79,179,36,201,150,
139,199,253,110,39,146,172,40,198,253,125,248,155,115,135,208,179,107,233,160,44,90,171,63,253,249,95,185,224,203,229,243,239,126,247,79,89,94,92,34,52,241,130,190,82,138,161,216,108,215,89,62,250,197,
135,95,98,100,94,200,101,194,180,92,62,29,246,219,209,120,92,202,106,183,219,76,167,115,123,23,1,207,17,145,42,91,182,219,101,89,30,198,227,89,145,141,43,121,210,26,190,248,226,55,89,150,155,217,74,54,
131,92,131,151,65,55,165,76,65,156,185,2,189,209,42,73,105,180,244,204,137,156,220,128,120,51,96,217,152,111,216,159,175,110,61,2,112,98,123,36,110,161,30,200,168,88,59,124,29,34,42,203,81,189,112,62,
90,86,138,228,67,91,10,71,97,223,39,182,252,27,207,53,4,169,1,128,246,81,148,181,113,247,153,168,178,230,183,69,111,78,137,247,182,251,253,218,116,236,240,68,136,36,73,56,238,54,114,181,89,237,182,139,
205,106,181,217,44,146,36,179,157,197,46,7,234,85,33,207,128,216,60,38,231,129,116,86,107,118,46,73,187,64,184,77,68,210,19,67,219,140,68,131,25,159,190,81,83,120,155,92,46,239,179,52,75,147,44,205,242,
44,203,17,217,126,191,220,239,55,187,221,246,112,216,142,199,55,77,100,209,225,189,182,197,125,18,155,42,37,185,92,62,228,249,168,40,198,89,94,172,215,139,237,118,189,221,44,111,239,62,227,60,249,254,
251,63,239,182,171,247,239,63,159,76,239,218,36,165,109,124,10,90,204,174,218,24,193,102,179,60,30,119,121,94,212,116,73,235,178,42,137,130,13,66,7,0,56,199,191,218,180,75,105,45,211,116,148,164,89,89,
29,77,174,224,211,247,191,8,4,112,13,37,83,83,24,215,24,221,26,60,219,133,134,127,250,211,191,106,85,46,183,187,119,239,62,140,199,179,126,14,0,145,163,119,58,29,164,146,55,55,239,239,238,62,131,94,182,
85,254,246,237,102,185,217,60,143,39,227,52,43,246,187,109,81,140,223,191,255,34,156,110,79,162,90,173,53,74,89,62,63,127,87,20,211,209,120,90,41,185,217,46,39,147,219,209,104,74,238,81,110,21,105,50,
185,46,144,106,122,37,27,99,186,136,252,200,149,94,164,212,196,21,212,245,248,212,46,80,38,156,167,207,154,191,72,133,244,209,34,121,148,135,134,44,149,210,74,1,23,98,167,232,240,143,11,253,245,225,199,
10,158,101,94,27,104,48,233,247,92,37,232,168,236,219,60,241,249,78,114,56,28,231,243,121,154,228,169,200,146,52,19,9,156,78,53,99,87,12,0,128,120,98,122,90,232,120,60,78,124,107,124,31,101,170,64,36,
183,101,236,164,27,209,219,79,56,202,152,130,163,63,84,181,207,116,157,245,102,161,181,78,210,44,73,179,52,73,133,72,77,140,99,94,197,185,184,189,253,196,251,97,67,196,244,46,191,168,203,253,227,227,215,
156,241,52,205,146,36,3,141,147,201,13,34,38,73,118,119,247,225,219,111,254,253,112,220,125,248,236,151,23,45,66,218,99,246,136,221,70,204,41,28,214,235,231,83,121,202,243,81,154,102,6,16,79,229,169,40,
166,212,60,165,249,189,232,55,50,78,66,106,189,94,165,89,145,102,185,148,242,176,219,237,15,219,60,31,37,105,74,186,54,157,225,161,38,150,88,180,39,13,155,52,13,160,159,213,252,215,223,252,187,73,251,
206,68,254,229,151,191,235,48,246,142,130,50,249,70,186,170,202,247,239,191,152,205,222,93,68,219,232,179,167,211,126,177,188,47,138,81,94,76,247,219,205,225,176,255,240,225,151,158,20,167,41,125,173,
109,149,239,239,255,146,101,69,150,21,219,205,90,43,61,153,188,27,143,103,196,5,237,124,119,161,96,224,14,41,173,55,107,45,45,44,184,174,191,218,94,132,172,83,96,53,110,35,76,74,197,88,3,4,155,134,30,
170,145,18,38,91,66,76,11,121,168,87,92,242,235,242,61,27,41,218,18,84,30,252,145,195,29,238,207,200,53,207,90,236,71,25,105,116,101,116,123,72,72,41,200,238,118,27,68,205,81,160,25,67,207,216,241,0,187,
221,110,183,219,236,119,235,195,102,163,148,166,215,115,96,188,228,179,9,18,185,232,166,249,2,186,142,105,111,82,66,79,30,122,177,91,169,101,184,60,118,206,61,174,255,144,148,114,189,122,204,178,60,207,
138,60,27,165,89,161,148,220,237,54,251,253,102,191,223,237,118,187,217,236,54,8,241,168,35,6,70,39,191,135,60,241,120,220,239,182,235,98,52,205,178,34,207,178,124,52,51,199,105,52,210,203,229,195,241,
116,248,252,243,223,228,249,232,122,226,217,11,61,221,163,205,122,81,85,101,158,21,105,154,105,173,78,167,19,32,228,249,56,73,210,240,143,210,91,5,189,146,55,155,5,231,152,176,36,17,73,89,150,26,0,25,
154,252,131,19,213,55,123,144,136,255,25,156,187,57,73,228,238,243,181,54,58,249,240,240,205,106,245,56,25,207,215,171,231,127,252,253,127,107,211,114,219,19,178,203,81,155,49,246,187,223,253,215,158,
26,254,112,187,82,234,233,233,187,44,27,141,70,147,221,110,179,63,108,179,188,200,178,220,163,240,212,57,215,88,139,221,223,255,69,8,193,185,48,6,222,159,126,250,139,60,31,187,178,129,215,236,71,146,39,
52,166,108,120,127,132,211,56,236,20,41,77,174,19,8,156,33,235,183,98,76,25,227,59,173,85,180,241,50,12,187,9,242,98,247,205,207,123,185,232,206,219,191,160,154,228,157,1,97,223,62,68,102,135,64,83,97,
64,165,42,20,90,232,107,35,52,121,187,91,153,40,62,73,82,158,36,92,36,85,37,75,99,77,86,202,82,30,102,179,119,244,146,32,10,103,74,73,206,237,155,244,196,69,12,27,150,176,79,143,118,139,27,121,159,124,
40,92,242,87,142,243,208,199,167,111,25,227,105,154,39,73,154,164,105,146,136,178,60,185,95,32,77,196,205,205,123,175,53,37,108,212,241,218,84,162,81,255,253,253,95,147,52,205,178,44,77,179,52,43,4,99,
171,213,2,64,239,247,171,227,113,247,249,231,191,118,73,180,75,103,23,118,231,61,163,109,32,182,171,253,185,172,202,44,43,210,52,83,74,158,78,199,170,60,142,198,51,215,13,25,230,100,188,64,196,104,200,
143,135,109,146,230,34,203,170,170,58,28,182,199,227,174,200,167,66,8,210,12,78,77,184,41,15,245,236,17,124,206,222,205,79,214,235,167,199,135,111,102,211,219,229,242,105,126,243,190,237,99,119,12,252,
128,184,67,51,70,11,71,221,213,164,135,135,175,25,195,44,203,109,188,194,63,121,255,101,96,37,142,132,88,96,89,30,191,191,255,139,224,137,6,45,101,165,181,254,242,203,127,16,66,16,247,50,138,251,154,60,
212,77,123,36,207,160,179,174,164,91,153,103,68,180,39,165,73,176,122,129,218,217,119,217,105,149,154,88,225,215,108,105,92,31,214,198,195,140,165,23,212,139,126,40,208,85,113,138,62,21,245,191,111,235,
119,178,18,209,80,150,207,130,89,205,81,223,163,250,88,28,246,91,33,68,146,164,156,115,206,132,224,80,73,117,158,91,174,217,237,237,39,158,144,80,235,70,57,40,60,245,181,134,96,110,18,254,255,204,189,
71,155,35,73,146,37,40,162,196,24,136,147,32,201,73,79,145,38,243,245,238,97,246,182,255,255,176,151,254,190,153,158,158,174,222,98,73,131,186,195,193,141,170,200,30,212,84,161,198,0,68,100,86,239,160,
162,60,13,230,112,16,131,217,211,39,34,79,158,12,51,59,231,49,20,198,70,27,157,153,124,59,17,176,219,149,3,206,207,252,56,30,119,85,89,100,179,121,20,197,81,156,68,81,92,215,205,241,120,44,138,125,126,
60,22,199,195,242,246,217,96,225,228,41,48,157,186,240,152,97,191,123,170,235,106,54,155,71,113,28,197,73,164,163,221,126,189,219,111,0,249,112,216,223,223,189,156,96,160,23,218,195,161,111,112,53,142,
164,246,222,110,183,169,235,42,142,211,56,78,140,49,117,93,213,85,37,149,246,22,118,99,153,80,236,242,80,100,134,221,110,45,108,27,130,212,21,149,8,136,82,221,223,191,236,54,194,123,244,28,55,151,9,87,
154,179,117,164,211,173,174,171,215,175,191,203,230,75,38,2,134,207,63,255,205,180,209,15,12,178,144,163,41,78,188,134,239,143,126,173,155,205,131,161,38,75,178,36,73,119,187,77,81,28,103,179,27,55,200,
0,123,33,139,221,185,219,173,54,235,135,40,78,152,169,44,139,251,187,151,179,217,50,52,156,237,81,147,224,253,120,187,171,30,151,234,55,61,7,248,217,17,198,251,218,242,16,96,7,181,147,51,248,211,249,205,
24,39,61,39,144,31,241,190,155,56,208,56,245,85,93,28,207,61,212,150,142,190,239,33,112,76,136,179,122,4,182,127,134,213,117,158,36,119,110,114,178,68,132,252,152,231,199,99,81,28,138,242,72,204,83,87,
117,143,117,134,133,248,192,156,137,123,175,219,245,130,195,43,78,226,33,134,226,25,169,211,52,146,246,142,15,132,246,34,235,245,251,36,73,147,36,141,237,207,72,228,5,185,230,37,148,58,182,100,124,236,
235,230,97,77,121,162,232,4,204,252,184,122,155,36,89,146,102,73,156,165,201,108,179,93,31,14,219,195,97,199,192,183,55,207,123,222,245,103,78,179,177,6,112,156,78,37,159,14,227,241,184,175,235,34,138,
147,40,74,148,84,68,13,0,42,29,45,151,119,83,35,128,6,31,144,109,70,194,152,90,71,177,82,81,213,84,54,26,157,205,150,190,101,104,152,177,9,227,250,240,45,245,220,2,47,222,126,252,241,79,74,71,105,28,191,
123,255,122,54,191,25,58,131,140,93,198,112,29,239,185,200,67,177,135,230,187,253,38,77,178,56,78,27,99,16,81,8,117,123,251,60,244,141,8,131,146,60,223,109,54,15,198,52,128,80,148,249,205,242,217,243,
231,95,58,206,120,170,182,13,82,207,157,130,190,55,59,15,46,46,244,172,51,108,187,156,72,106,141,150,166,251,32,233,11,238,221,69,14,166,135,189,159,19,57,245,202,74,29,30,138,191,210,128,177,107,122,
156,206,174,180,56,61,33,103,136,236,167,194,75,89,30,1,132,237,166,215,82,105,165,138,210,152,186,110,76,93,215,117,93,213,31,98,161,56,130,26,151,176,224,162,57,249,40,9,29,167,90,67,137,207,117,245,
89,120,92,189,209,81,156,102,179,52,153,165,105,150,196,42,47,154,252,184,47,138,227,241,120,200,243,253,237,237,203,95,254,21,51,195,106,245,6,153,117,164,149,142,35,29,239,15,155,195,97,187,223,111,
119,187,237,167,159,124,233,203,202,87,79,223,29,30,249,243,13,199,214,42,127,111,67,120,173,117,85,149,117,93,35,218,162,150,56,91,191,10,83,55,200,76,135,195,70,235,40,210,81,20,39,69,126,64,68,33,213,
148,241,254,53,39,255,149,66,168,247,15,175,140,169,22,139,187,162,44,64,224,55,223,252,3,254,106,67,254,206,3,232,200,171,172,86,111,210,36,75,211,44,78,102,69,113,0,198,249,105,21,241,170,41,83,150,
121,145,31,142,249,158,168,97,6,165,116,150,45,230,243,91,225,173,64,251,151,67,127,164,152,99,163,60,113,237,96,32,150,192,49,161,91,47,160,158,204,14,159,63,150,56,57,137,247,131,143,181,58,243,26,103,
64,122,108,207,25,45,84,47,186,239,252,126,44,72,63,243,179,127,45,57,126,10,199,227,94,74,37,149,29,54,175,133,80,77,83,213,166,54,166,49,166,49,198,99,232,168,207,35,4,101,162,94,173,105,68,44,233,116,
18,163,48,58,41,111,28,51,166,59,173,1,97,227,243,25,21,253,96,207,233,57,87,171,183,166,169,210,108,174,85,164,181,86,50,106,207,218,182,149,16,34,29,47,22,183,211,215,121,47,105,53,206,85,1,192,152,
122,187,125,76,146,121,28,37,105,156,84,117,121,56,108,246,135,221,110,183,77,147,236,230,246,249,7,129,230,216,224,188,209,150,141,211,70,85,149,135,195,38,138,146,40,138,34,29,87,85,89,215,101,93,87,
89,182,116,26,254,139,178,202,246,51,238,247,107,4,180,222,213,101,145,23,69,158,231,71,15,196,65,178,243,20,196,3,116,114,163,67,81,199,53,80,88,20,199,167,213,155,217,108,217,52,213,225,176,123,126,
255,217,71,217,211,225,165,20,39,158,205,153,182,111,117,179,121,100,102,165,148,82,170,29,186,35,177,110,170,87,175,254,130,66,218,147,200,24,102,54,0,64,76,74,233,89,122,155,101,11,55,13,151,123,33,
93,144,6,229,97,253,54,188,12,189,62,41,60,164,174,6,229,67,207,182,40,31,50,83,232,219,208,249,52,104,71,7,58,53,156,120,176,186,224,104,169,99,208,152,52,86,83,130,191,249,237,154,217,97,35,23,219,40,
104,158,57,65,203,178,16,202,78,202,136,80,10,41,176,1,16,162,125,121,235,64,252,129,236,242,220,27,238,77,82,26,146,229,169,213,103,180,164,30,98,226,55,1,92,50,0,0,32,0,73,68,65,84,216,178,132,231,203,
2,118,9,217,31,182,179,217,60,137,210,36,78,227,56,141,19,40,114,46,203,162,170,242,170,42,202,178,184,187,123,249,171,48,157,247,239,126,150,74,197,81,164,227,84,235,164,44,11,107,185,146,198,201,87,
95,255,238,3,153,62,118,149,97,231,113,214,230,43,204,110,247,164,117,28,69,73,20,197,85,85,84,117,213,212,149,16,50,44,97,141,14,80,235,93,195,77,83,213,85,169,117,164,180,150,82,55,77,141,8,74,169,229,
242,238,131,130,143,64,212,113,237,217,245,230,213,95,179,108,49,155,221,28,246,91,33,68,56,134,250,163,34,158,11,124,243,12,128,26,211,236,247,79,105,50,183,2,181,162,40,171,50,7,230,178,204,1,0,152,
64,8,41,148,214,82,169,40,142,147,40,74,28,63,229,49,112,252,200,235,40,252,8,68,252,167,191,252,247,121,118,251,226,197,231,195,164,226,212,180,218,191,221,164,238,243,252,84,93,159,187,153,74,134,158,
161,177,31,248,0,60,30,119,239,222,253,181,44,247,66,40,173,99,33,164,82,182,61,188,181,188,115,77,159,170,181,188,83,82,186,238,79,98,190,189,121,33,68,36,37,10,41,132,130,114,159,23,197,177,44,243,178,
42,171,170,248,227,31,255,197,59,116,121,227,50,111,165,21,56,107,25,111,180,101,27,206,252,158,83,95,26,19,211,201,34,33,116,141,27,148,188,68,215,179,95,6,22,128,39,167,187,96,163,189,219,246,206,75,
41,48,124,64,219,35,47,130,231,113,173,29,42,203,230,54,28,75,210,44,78,68,145,83,158,31,138,34,207,139,67,126,60,150,69,190,90,189,89,61,189,241,77,206,208,237,210,235,222,27,157,150,110,73,168,17,66,
206,102,243,40,137,19,21,87,101,113,56,108,246,187,29,51,21,213,241,143,127,252,151,1,47,227,1,73,31,159,255,60,28,79,32,80,0,98,215,111,27,153,69,146,36,81,20,187,81,107,232,76,64,104,179,121,223,205,
23,247,91,48,93,99,59,180,14,150,196,90,69,90,199,145,142,203,34,47,139,188,40,138,166,169,94,191,254,107,96,108,200,163,126,119,225,252,244,238,0,100,190,132,116,208,52,38,138,146,36,154,23,197,254,152,
239,203,178,248,243,159,255,251,88,54,131,167,242,194,131,149,88,92,97,56,59,94,177,100,67,73,54,79,146,52,73,178,178,44,138,50,47,138,156,217,10,45,25,128,201,52,100,26,0,40,138,195,126,127,234,135,230,
158,73,213,201,1,146,237,5,226,143,97,231,218,33,178,237,155,161,15,94,207,4,175,40,171,101,118,251,151,55,255,227,251,239,255,103,184,223,182,120,58,35,202,254,53,171,84,116,127,255,133,111,135,251,32,
26,247,75,110,31,196,67,63,120,244,194,176,52,54,246,39,167,223,110,54,239,243,124,53,203,50,33,36,10,22,146,164,32,33,81,32,41,69,2,141,16,40,37,91,220,64,65,136,236,26,200,72,112,100,49,71,162,144,66,
146,1,170,137,136,13,81,211,52,204,198,1,31,16,89,171,58,34,54,20,116,230,218,187,68,245,233,123,53,100,216,144,253,190,217,48,145,245,62,240,221,190,8,192,64,237,89,117,42,54,184,147,187,53,255,16,78,
57,44,17,133,53,149,97,144,76,130,132,148,210,90,165,40,102,1,32,153,37,128,2,144,8,77,235,134,39,90,67,60,107,120,67,172,4,33,9,9,36,4,10,2,1,136,82,232,52,155,103,217,60,73,231,73,58,79,18,233,45,129,
200,218,18,1,8,9,68,117,128,134,157,193,224,67,172,244,215,10,120,227,12,102,6,32,2,219,11,164,163,20,4,238,183,235,253,110,179,221,111,145,107,235,217,225,93,54,78,10,218,177,200,28,65,128,119,223,2,
63,183,245,228,172,202,44,236,55,109,101,194,118,131,25,147,56,179,243,163,132,144,101,153,219,108,183,127,231,142,50,140,20,196,66,123,80,0,48,134,164,210,118,117,110,207,67,68,4,146,246,64,49,81,7,67,
79,95,58,180,70,51,14,65,194,35,213,27,213,219,157,26,227,15,55,98,148,36,179,52,201,118,187,13,179,145,18,136,170,224,189,158,82,134,54,168,13,40,58,246,137,140,245,49,236,12,83,11,87,110,175,90,111,
77,192,78,27,214,215,174,225,56,201,180,86,74,235,170,46,203,50,47,139,99,85,21,74,157,152,215,201,224,170,253,63,193,105,3,130,70,120,110,205,120,129,219,193,178,220,129,78,123,5,17,51,147,97,187,221,
101,48,12,6,216,212,85,189,152,223,191,121,251,221,108,150,48,85,140,36,132,181,197,35,0,67,100,0,140,16,140,130,172,33,158,253,114,136,161,49,135,159,127,254,95,207,158,125,30,68,226,167,206,206,243,
25,203,94,247,209,84,93,126,244,38,224,127,167,27,51,1,182,54,132,216,90,135,185,83,137,189,11,8,176,179,43,180,103,102,75,8,209,202,116,17,164,0,20,198,176,97,67,13,145,105,128,168,53,202,241,86,100,
237,249,232,172,111,108,246,133,161,237,186,61,89,207,129,0,55,37,243,148,126,241,142,115,2,176,53,222,19,104,93,65,173,187,62,88,151,62,137,210,121,50,217,13,20,216,82,75,180,27,150,117,182,148,75,34,
74,217,62,151,51,184,107,199,161,56,30,219,206,61,60,185,221,1,162,0,157,101,203,44,205,210,116,158,165,179,36,145,66,64,145,83,126,60,30,139,67,153,31,14,199,67,89,28,172,121,98,136,149,231,1,212,90,
252,185,139,186,237,137,53,134,180,178,99,157,210,88,199,219,237,227,110,191,217,109,183,101,190,99,54,12,196,76,158,235,7,150,196,173,5,164,189,198,218,251,224,8,29,119,46,208,16,144,250,113,31,177,178,
182,176,42,214,90,23,101,94,85,85,93,149,198,84,221,209,3,254,251,243,105,34,28,132,102,172,164,245,83,141,180,142,138,50,47,171,188,40,243,198,212,224,39,19,12,71,133,91,19,251,94,146,225,36,169,241,
9,109,129,1,138,129,16,128,194,139,109,136,69,154,102,105,154,182,235,7,131,82,18,49,144,98,56,102,125,178,107,114,113,179,199,209,145,133,226,244,125,33,158,204,172,112,108,78,154,173,166,89,91,175,36,
142,18,173,211,40,74,91,215,92,99,132,56,249,243,117,199,106,97,47,155,201,189,73,243,167,139,21,188,31,109,40,139,176,201,129,147,151,34,98,248,148,8,80,55,38,155,221,151,249,97,49,207,160,175,232,97,
119,84,188,137,24,99,251,74,237,87,125,60,22,255,249,168,165,254,183,194,208,187,187,79,202,234,152,31,247,82,130,82,66,74,20,132,74,10,201,18,164,144,32,13,74,64,137,40,25,21,131,36,82,2,20,160,4,22,
66,72,16,54,1,106,173,8,26,102,50,220,48,179,161,90,10,141,40,17,152,5,11,102,102,178,227,171,80,24,193,220,250,191,34,1,27,0,66,48,6,8,192,8,32,18,36,200,180,158,50,68,12,45,10,132,22,79,192,52,66,199,
253,5,212,38,198,195,17,123,202,15,62,241,65,186,205,78,156,188,239,132,64,209,143,226,67,163,60,223,143,144,101,203,52,157,167,233,60,203,210,36,85,73,12,117,221,54,224,33,147,97,6,64,173,35,63,124,38,
240,181,131,208,126,120,184,211,35,172,221,201,200,18,40,78,178,36,206,210,52,163,166,38,6,32,36,164,36,201,92,202,159,253,147,192,136,76,242,228,211,230,194,207,94,174,67,116,199,101,99,103,22,172,16,
145,142,181,142,116,164,45,221,177,134,7,82,70,195,126,226,33,15,117,239,202,46,191,66,181,86,44,17,19,123,164,84,42,182,222,176,130,137,219,90,179,253,186,21,51,33,83,119,32,118,63,147,115,166,34,111,
223,18,145,137,35,149,196,89,20,165,199,227,174,42,14,13,53,81,148,12,221,158,38,50,185,12,99,246,245,48,54,130,23,208,15,44,19,97,188,111,79,72,102,86,82,38,105,22,39,89,154,102,68,198,131,84,59,157,
176,181,64,101,6,22,22,0,153,218,61,167,195,104,183,9,128,65,176,96,178,87,151,96,34,34,0,70,150,128,108,29,237,132,96,34,131,72,2,136,208,180,134,147,32,81,24,1,196,198,52,166,74,146,155,166,41,24,9,
49,98,99,152,36,81,67,36,136,132,49,118,134,157,49,6,136,192,16,177,17,134,152,8,137,0,128,81,164,191,255,253,111,255,255,194,80,190,46,101,48,154,68,235,172,67,93,125,101,103,34,194,240,193,124,250,50,
218,125,105,186,248,221,111,255,155,19,120,182,73,79,155,18,117,137,209,147,241,29,98,59,137,222,18,195,255,247,79,255,98,231,69,131,176,147,231,90,179,38,38,3,128,127,255,251,255,75,142,204,50,155,24,
113,113,202,9,134,43,45,247,30,216,29,63,7,211,245,159,209,177,242,48,214,181,57,37,23,237,3,179,221,126,120,120,69,166,206,178,89,150,205,179,108,150,166,81,28,67,93,67,126,164,99,126,44,138,253,241,
120,44,138,3,34,126,253,245,63,156,189,194,167,46,218,206,172,164,247,239,126,60,30,183,74,233,72,105,41,197,122,179,62,236,55,219,221,234,235,111,254,33,75,23,231,15,236,57,221,77,191,248,62,146,239,
3,192,199,199,215,8,160,172,110,77,168,188,56,84,85,89,85,85,154,206,188,148,106,194,134,170,255,166,246,251,13,81,163,148,146,74,9,33,243,252,80,20,69,89,20,179,217,141,157,157,55,234,107,55,60,19,38,
60,89,206,189,252,127,252,199,191,100,217,98,54,155,89,243,33,67,244,249,231,191,185,187,123,241,33,177,26,79,20,24,207,20,148,250,7,188,170,202,213,227,235,40,78,146,36,75,146,25,0,86,101,81,85,101,85,
150,105,50,187,191,255,228,138,107,164,151,58,135,110,121,224,116,249,247,160,32,12,252,137,218,37,138,136,142,199,237,159,254,252,175,76,230,247,191,255,111,90,71,109,118,141,77,56,5,36,72,140,122,167,
187,118,210,68,176,209,116,178,84,125,144,153,66,161,145,15,120,165,70,237,111,21,203,243,135,212,234,188,121,210,224,25,134,48,221,217,232,152,175,48,2,19,179,129,6,0,168,174,155,186,110,234,166,105,
76,195,224,38,171,126,172,112,100,84,169,21,60,108,248,175,31,69,142,141,68,238,143,164,30,98,230,132,171,8,0,224,187,119,63,150,229,49,142,211,40,74,172,202,199,218,107,120,107,83,102,96,100,102,126,
246,236,179,169,149,44,200,21,94,0,208,186,46,182,187,149,142,210,56,201,162,52,221,108,30,119,219,245,118,253,152,166,203,16,64,71,79,202,209,19,119,250,84,25,249,219,195,97,211,52,149,210,90,233,40,
82,145,49,181,125,148,82,242,172,161,201,200,211,90,69,125,20,37,82,42,173,180,49,237,144,12,33,189,114,227,178,54,224,227,170,22,63,252,240,199,229,242,110,190,88,206,230,183,46,80,21,139,197,29,252,
231,222,234,186,122,92,189,214,81,156,164,105,146,164,105,154,18,27,178,85,1,106,174,62,158,31,164,190,224,137,179,171,61,247,202,50,255,238,251,255,133,4,255,229,191,252,179,214,241,25,252,152,30,237,
119,230,75,231,191,41,154,137,95,239,217,249,252,254,222,101,211,67,195,105,244,231,179,87,26,135,11,96,91,49,18,12,100,39,208,17,48,1,145,58,7,160,120,137,42,245,234,161,120,81,101,21,160,231,208,225,
31,166,28,67,38,44,65,71,175,97,124,247,238,167,186,46,179,108,46,149,82,42,82,74,41,5,82,64,85,65,145,155,99,190,207,143,7,59,237,67,74,213,107,90,31,5,208,225,73,223,59,107,223,190,253,81,42,21,69,81,
18,199,96,236,84,91,146,81,242,213,87,191,29,69,198,139,176,216,61,31,250,251,194,130,134,49,205,118,187,178,74,166,72,71,214,85,164,114,130,208,174,199,235,185,11,134,25,140,105,138,226,144,36,153,16,
104,135,6,215,117,89,149,101,81,21,113,156,14,191,208,137,79,52,37,50,27,106,51,79,255,222,188,254,30,192,36,73,26,71,169,169,235,166,174,235,186,20,82,42,165,255,214,133,227,174,36,160,126,120,124,149,
68,233,108,182,76,147,89,154,206,136,124,17,11,164,84,151,58,116,207,144,208,206,136,128,51,4,168,119,214,85,85,254,221,95,255,141,12,125,251,155,255,58,108,111,227,17,128,56,199,171,62,14,7,63,144,243,
241,56,134,14,9,237,144,83,76,189,210,0,31,121,138,51,143,157,229,83,37,14,255,147,66,87,249,1,63,111,239,73,41,8,140,49,0,212,48,19,1,17,9,176,243,87,64,4,127,14,83,24,61,186,30,12,44,235,47,28,141,49,
224,227,161,138,205,103,198,187,63,121,236,25,250,23,216,219,119,63,84,85,158,101,243,166,105,6,158,41,16,156,207,12,140,207,158,125,58,29,193,244,142,198,73,173,21,252,99,0,222,239,215,121,126,72,162,
36,142,226,40,142,183,251,205,110,183,217,110,215,159,127,246,173,85,86,5,57,144,209,219,200,47,122,161,22,243,184,178,10,0,158,158,222,11,33,148,213,182,41,93,148,69,89,229,85,85,48,179,229,44,131,43,
138,123,255,220,123,160,195,97,27,199,169,148,74,235,88,183,210,40,96,96,129,56,159,223,158,153,74,16,234,193,194,67,212,59,116,99,39,54,3,240,219,183,63,84,213,49,155,47,178,116,62,155,45,26,38,99,12,
48,37,113,58,5,55,189,111,97,112,49,14,95,177,183,103,100,187,105,170,135,199,159,153,121,177,188,99,38,91,180,170,155,170,174,203,170,46,171,170,234,89,5,14,95,49,56,188,48,58,249,53,60,50,62,101,28,
16,157,240,172,99,0,174,170,226,175,127,253,183,198,212,223,124,243,143,89,58,239,189,138,123,30,10,79,176,233,159,16,156,78,52,26,164,135,231,219,88,130,238,28,161,155,66,63,53,189,218,252,103,172,141,
204,228,103,132,157,161,45,211,73,213,147,119,167,214,154,26,178,147,85,169,177,68,212,202,144,24,5,142,126,180,129,168,19,198,172,151,189,141,19,14,84,123,253,49,183,83,52,118,202,170,110,212,184,10,
96,132,138,250,230,162,119,239,127,108,234,106,54,91,212,117,45,132,136,162,89,93,215,121,126,64,156,3,170,178,48,182,167,243,120,60,230,197,193,218,215,95,177,226,142,174,240,167,157,15,15,175,146,52,
139,211,44,203,150,155,245,106,187,221,236,118,143,113,60,15,226,62,62,147,10,24,37,113,99,94,249,28,248,185,180,201,232,170,42,242,98,159,101,115,165,90,23,84,127,233,90,37,252,152,181,90,103,49,243,
151,195,254,176,209,90,71,81,2,192,90,71,117,85,218,214,131,170,42,180,142,3,183,74,190,68,66,121,162,235,102,252,195,62,60,252,124,44,246,203,197,77,154,45,102,179,133,33,195,100,8,168,49,102,54,207,
70,255,246,151,8,215,167,25,104,245,254,253,43,0,126,241,226,139,170,174,202,34,183,246,146,12,237,208,76,34,147,36,203,41,78,213,59,61,206,196,230,131,224,157,199,158,141,153,185,44,243,191,252,229,223,
154,166,254,230,155,127,202,178,57,17,13,132,203,60,204,248,117,69,87,60,13,26,231,105,223,71,50,211,225,254,241,50,203,104,89,51,44,28,13,127,14,51,152,83,9,221,193,82,0,68,36,68,63,253,220,21,241,194,
144,129,186,121,179,109,31,158,148,9,53,21,53,53,17,17,52,118,246,0,35,0,129,16,50,116,40,27,30,135,224,187,9,77,236,249,140,5,100,96,201,220,59,74,157,158,209,169,239,111,248,43,111,184,55,245,87,198,
152,119,111,127,16,82,206,102,243,186,174,148,138,150,203,103,90,235,167,213,186,49,49,0,0,204,67,171,49,96,118,36,244,114,13,100,42,10,102,230,213,234,109,211,148,73,146,106,21,129,29,196,198,70,8,245,
245,215,191,27,142,214,57,155,183,10,13,226,58,199,193,109,248,190,218,147,174,114,181,122,171,149,86,50,82,90,107,169,15,199,93,89,229,117,89,161,16,81,20,159,89,245,123,95,217,225,176,37,67,201,108,
102,76,45,165,66,171,137,115,127,50,159,223,12,226,12,30,13,96,175,91,39,78,15,120,120,120,117,216,111,63,121,249,5,2,103,217,44,77,103,251,253,198,13,175,195,36,206,166,159,228,218,58,85,111,221,246,
14,141,161,161,84,93,151,15,15,63,3,192,139,23,95,41,21,61,173,222,50,128,117,252,212,90,251,225,70,3,133,192,240,106,225,254,76,191,126,212,216,43,49,157,88,103,47,46,57,30,247,223,253,240,111,100,232,
219,111,255,41,73,102,78,118,218,206,166,30,52,50,208,24,44,180,111,128,136,67,186,218,139,119,195,217,77,19,228,236,244,1,137,104,244,227,159,201,83,169,43,0,116,156,211,246,158,186,91,148,15,167,182,
77,214,232,237,54,17,73,41,96,48,0,46,44,145,7,199,81,132,7,17,209,9,45,128,146,36,219,110,243,134,106,83,55,166,110,116,156,180,3,118,133,32,83,135,69,246,211,68,91,247,182,253,178,63,128,146,83,129,
126,16,191,92,159,80,199,1,88,92,155,153,245,143,175,170,242,237,187,31,35,29,41,231,16,124,119,247,66,8,185,221,62,29,243,125,10,172,164,148,82,18,81,158,239,243,252,144,231,7,59,217,116,84,52,115,38,
55,223,59,87,140,105,30,87,111,83,91,124,136,103,187,221,122,119,216,238,247,155,79,63,253,86,74,125,49,210,233,94,225,195,102,174,208,73,206,155,28,179,251,5,30,14,155,170,46,23,243,101,20,105,173,180,
161,198,166,40,136,233,182,29,46,210,235,22,29,63,140,199,124,223,52,245,124,126,99,76,83,150,185,214,17,0,86,117,85,85,69,85,149,86,1,210,91,99,186,51,215,134,235,208,85,103,128,5,208,197,242,30,24,246,
135,29,32,2,163,105,251,53,152,141,209,58,254,208,172,92,112,72,251,188,190,183,80,249,133,188,44,143,15,15,175,133,192,151,47,191,82,74,19,81,85,151,73,146,9,33,149,84,158,253,33,64,215,181,122,56,123,
110,52,106,233,51,208,30,2,132,172,200,255,219,237,158,126,252,241,15,192,248,119,127,247,79,113,156,117,187,191,194,132,73,191,160,63,200,9,80,87,228,223,163,89,35,152,51,85,139,239,85,243,97,66,122,
52,252,19,21,218,248,93,252,242,166,137,21,79,4,221,195,183,75,108,37,100,76,0,34,204,95,0,8,215,13,98,149,121,76,68,214,15,38,204,126,18,121,129,30,217,235,135,153,16,229,124,126,243,244,248,170,41,155,
138,202,218,52,177,112,58,103,193,166,54,67,255,237,97,81,107,192,181,195,62,238,222,213,223,25,252,208,139,28,71,183,207,203,18,206,63,236,112,216,62,62,190,78,210,153,16,194,152,58,210,233,237,221,75,
68,36,226,253,254,41,138,226,40,142,163,40,137,226,180,200,15,254,122,191,191,255,172,183,36,140,242,208,9,6,202,190,148,36,4,198,81,28,69,241,238,176,222,110,215,219,205,138,152,111,111,159,15,194,142,
241,231,153,34,242,161,223,96,184,225,141,38,17,249,233,233,93,164,34,165,236,140,107,189,223,111,139,178,40,203,2,1,28,99,10,77,64,194,175,230,20,98,231,249,161,174,138,44,91,8,161,118,187,21,51,11,33,
133,104,218,111,150,57,203,150,99,146,157,81,36,133,233,82,9,143,132,240,135,205,98,249,252,254,254,229,207,63,255,153,217,200,220,242,190,8,25,16,64,8,208,58,186,52,20,118,114,205,14,95,55,184,120,251,
158,208,135,195,126,181,122,163,148,126,249,242,43,41,21,51,228,249,222,77,126,20,40,208,212,13,81,99,200,112,171,21,25,79,203,12,7,154,142,117,12,247,167,225,142,134,149,79,79,239,223,188,250,179,148,
209,55,223,252,163,148,42,104,165,13,53,79,220,29,255,201,33,86,6,207,217,123,51,225,75,83,183,115,164,159,3,237,69,195,19,69,17,30,173,239,135,127,165,174,33,161,163,88,57,140,232,7,172,132,167,36,47,
195,213,96,172,79,166,175,97,182,71,89,74,238,178,90,2,144,109,121,65,200,186,41,155,170,169,155,186,189,158,16,17,176,54,85,176,50,51,98,127,245,238,94,198,167,9,48,195,225,201,33,159,26,181,74,25,205,
208,93,186,157,123,228,227,227,155,253,254,41,203,230,0,0,4,179,217,173,213,48,2,240,118,243,200,214,115,72,70,74,69,185,43,199,31,243,93,146,204,148,82,83,69,146,169,178,73,111,71,81,228,219,221,227,
98,118,107,7,181,151,197,209,80,67,134,254,238,55,255,212,43,181,77,211,168,9,195,143,192,195,184,59,226,141,125,194,113,183,223,24,83,167,73,162,164,210,74,23,69,97,26,99,45,184,110,110,94,248,21,110,
116,156,81,240,17,142,85,85,36,73,166,84,212,52,85,211,52,90,107,33,4,145,157,147,157,27,54,97,0,59,138,164,99,159,244,60,27,229,119,239,126,202,243,221,114,249,252,238,238,5,51,87,69,158,100,115,27,59,
27,99,44,52,184,185,56,252,129,101,226,17,186,221,37,161,167,243,122,187,93,109,183,15,145,78,95,126,242,5,162,180,127,123,60,238,133,20,173,212,90,74,170,43,34,102,67,178,227,95,119,70,21,115,193,99,
97,64,39,59,0,250,230,205,247,171,213,27,29,37,223,124,243,15,118,254,199,160,180,120,106,192,31,146,80,162,161,202,148,67,54,234,99,247,209,180,225,104,130,113,200,252,206,4,220,67,115,12,117,6,46,195,
150,140,128,91,113,215,147,149,71,169,104,152,33,237,97,171,165,153,67,108,181,4,19,145,186,133,54,98,22,163,5,95,187,211,55,159,32,242,124,126,91,150,135,178,44,235,234,88,215,11,137,237,84,101,106,76,
152,104,11,56,105,31,83,186,67,47,58,105,202,43,163,248,9,183,208,126,81,126,248,219,225,79,34,243,238,221,143,117,83,205,103,75,67,166,105,170,151,47,191,210,58,182,111,137,136,246,251,117,146,164,81,
20,199,81,164,181,54,77,9,192,118,64,226,253,253,39,23,47,251,81,141,68,248,1,95,191,249,94,171,56,138,227,56,206,182,219,245,102,187,90,111,158,102,217,50,73,230,191,16,67,167,138,39,225,232,233,245,
211,91,173,149,212,145,142,148,84,145,169,11,219,30,42,132,74,211,89,208,230,192,129,65,122,167,190,87,20,135,178,204,227,36,179,117,164,34,63,8,97,177,67,153,166,50,212,24,99,210,100,62,134,20,60,248,
198,249,26,249,148,173,242,191,125,243,67,89,30,239,110,95,46,111,158,1,64,158,239,25,65,74,235,145,35,235,166,102,43,6,16,226,122,80,30,68,45,163,214,133,236,51,203,0,240,248,248,250,120,220,198,241,
236,229,203,47,188,181,35,34,212,117,33,164,106,91,230,16,91,168,2,18,66,157,73,248,76,208,79,30,195,154,126,9,3,218,97,121,205,15,63,252,161,42,142,89,182,252,226,139,223,140,202,56,60,74,134,88,25,134,
246,253,246,252,83,158,212,166,50,237,31,194,88,178,145,130,55,211,223,211,163,125,215,23,148,90,12,237,133,243,62,213,56,6,169,83,56,125,34,210,158,147,118,183,137,89,4,177,121,95,103,224,71,75,59,254,
110,103,79,147,91,169,208,58,110,216,231,177,15,151,18,221,31,90,196,129,219,187,23,63,124,255,80,86,121,85,206,203,50,151,42,82,66,219,94,166,253,126,99,233,91,152,250,28,133,209,9,97,211,104,78,253,
12,175,228,46,183,237,39,251,194,233,102,254,110,24,204,230,249,254,241,225,181,144,42,77,102,134,72,72,245,217,139,47,253,52,99,102,88,175,223,75,41,165,138,148,142,148,214,121,177,207,243,195,225,184,
207,243,93,150,45,221,232,237,145,218,200,148,76,175,119,241,108,183,171,178,56,44,150,55,81,148,72,29,153,227,150,137,21,224,87,95,253,198,229,230,47,228,203,38,80,0,123,245,183,238,156,225,246,193,101,
153,23,101,121,179,188,209,74,43,21,87,85,145,231,135,188,56,150,69,110,187,146,130,180,105,111,40,86,11,166,199,124,95,85,69,28,37,73,156,218,132,79,85,151,74,69,182,101,182,1,180,31,194,18,252,179,189,
55,227,137,242,137,74,35,189,123,247,83,81,28,238,239,63,93,44,238,236,115,229,249,209,59,114,33,74,228,186,29,176,222,235,55,191,144,253,224,233,154,56,4,54,184,192,12,68,230,237,219,31,154,186,92,44,
238,111,239,94,250,66,19,34,19,65,93,215,169,210,214,169,158,25,240,36,98,131,177,10,240,136,246,115,218,223,11,134,74,35,187,231,120,220,255,240,211,31,155,170,188,187,125,241,242,147,175,78,14,79,39,
43,44,114,219,167,127,228,155,172,79,191,226,192,199,196,98,46,57,94,207,46,9,64,204,166,211,14,197,67,151,41,30,22,96,6,59,167,168,104,7,255,213,7,170,154,120,170,148,52,252,14,44,2,118,179,162,30,88,
219,172,168,175,154,185,210,57,127,255,221,191,238,246,43,33,68,20,165,82,218,230,78,111,127,39,133,84,214,236,46,216,31,248,197,9,73,204,69,126,200,211,44,45,211,197,226,94,235,200,218,235,254,245,47,
255,170,163,104,120,169,184,239,50,180,159,25,102,169,169,39,129,236,29,208,222,216,231,174,171,219,169,183,61,104,3,23,109,54,234,116,87,134,119,137,72,235,120,54,91,0,32,49,149,197,17,17,127,206,247,
129,62,159,1,68,150,206,163,40,178,163,143,171,166,178,75,50,17,28,14,155,195,97,19,70,85,97,88,228,86,224,222,65,24,208,7,162,249,226,46,77,23,89,54,219,61,173,182,219,167,167,167,135,166,41,255,253,
223,255,159,97,211,158,127,78,183,61,218,31,34,2,103,13,12,156,84,172,201,138,117,114,177,158,0,194,24,154,207,111,132,80,82,106,41,101,211,212,206,205,132,14,135,77,158,239,67,159,39,68,209,155,81,72,
68,90,71,198,152,220,236,243,124,111,207,49,41,149,61,198,214,54,180,174,139,170,170,30,30,94,117,191,122,30,108,143,126,58,30,34,172,69,112,41,36,177,121,120,248,233,225,225,39,123,78,52,117,147,164,
153,53,144,81,2,43,96,34,116,210,200,127,29,168,199,169,7,91,23,11,77,189,238,12,102,64,16,66,74,0,94,111,222,111,182,15,221,241,68,44,176,245,20,244,9,21,251,57,247,251,117,81,236,199,206,243,209,104,
186,123,208,192,155,221,113,136,125,246,106,170,234,74,201,136,136,141,169,223,190,251,238,205,219,191,184,86,78,10,172,38,155,176,173,211,155,57,89,151,60,107,171,102,255,27,218,229,57,251,74,195,204,
74,69,119,119,159,223,223,127,74,109,179,13,117,191,175,190,132,249,162,44,116,170,120,62,21,203,143,64,103,15,248,70,229,77,163,123,186,172,120,248,242,190,188,78,30,76,125,137,233,113,245,195,179,251,
103,136,2,16,132,96,33,88,180,246,119,70,74,16,2,165,117,189,3,66,4,20,4,72,128,166,181,137,3,131,136,69,126,204,243,67,158,207,146,184,80,90,42,165,149,138,17,145,168,132,238,41,111,253,159,200,218,136,
64,107,123,200,29,231,46,251,81,12,129,51,117,115,255,9,15,90,27,84,34,2,183,222,98,0,136,32,24,16,81,16,163,64,129,32,24,4,130,100,16,8,130,89,48,91,51,55,105,45,184,25,36,130,32,66,41,163,52,157,69,
113,214,166,174,132,233,117,145,2,32,17,39,201,92,107,165,117,172,84,212,106,66,243,195,241,184,111,154,92,74,225,107,150,222,131,137,79,75,116,87,171,28,26,168,184,253,117,77,73,178,144,90,107,173,216,
30,34,38,102,35,4,53,77,222,189,126,192,133,84,224,28,58,32,180,99,105,179,159,192,8,2,1,64,180,70,24,214,200,170,93,78,80,144,144,66,8,34,33,165,100,86,66,68,82,233,72,199,86,121,83,20,69,81,228,69,113,
172,202,92,71,26,192,88,235,114,20,214,186,74,180,62,122,109,32,133,90,199,117,93,246,184,155,112,175,85,55,85,99,234,166,105,0,76,200,131,206,195,40,49,133,101,102,119,222,159,210,128,66,68,8,216,152,
188,93,227,184,181,88,1,0,1,2,17,185,117,240,107,145,142,129,141,169,78,229,236,224,127,182,63,194,59,102,157,174,50,103,138,212,6,46,206,177,8,157,250,152,8,180,78,153,217,152,210,91,196,135,227,114,
153,89,232,25,180,105,16,105,109,148,60,153,48,166,28,169,207,180,230,142,189,196,37,5,9,201,19,128,58,99,73,102,54,76,76,108,154,154,162,120,94,213,71,166,138,200,56,195,186,214,63,212,61,79,195,96,201,
35,1,146,119,186,67,100,33,12,19,177,48,72,68,194,26,223,157,124,8,201,94,185,132,204,108,154,227,207,63,255,225,238,238,147,97,8,31,230,106,45,194,6,185,90,24,171,131,77,2,232,72,44,31,134,237,97,56,
63,168,138,240,32,209,9,83,157,39,65,137,201,87,207,71,50,193,214,253,51,8,240,173,189,49,48,216,95,145,45,155,2,19,19,130,173,37,49,89,111,32,66,70,54,214,27,147,9,90,47,38,98,33,69,81,108,14,199,52,
142,183,145,142,102,243,133,82,81,164,148,210,113,221,236,165,245,46,178,71,176,245,211,99,116,101,12,123,202,51,121,121,157,157,173,202,140,18,173,123,30,218,140,105,39,238,108,221,187,124,3,188,144,
216,122,228,88,122,36,157,91,19,34,74,209,82,167,246,98,22,178,117,198,179,120,192,132,81,156,206,102,55,77,83,231,199,3,64,19,12,60,61,113,13,102,86,42,142,116,164,163,68,71,74,41,85,213,133,191,10,44,
128,6,7,223,195,41,135,58,177,19,128,66,63,168,33,34,41,227,52,77,179,36,75,210,249,118,251,184,217,172,182,235,71,230,218,133,72,192,64,208,241,220,181,29,97,96,189,35,221,137,70,126,244,24,0,48,26,4,
68,98,107,4,71,76,200,40,132,237,208,69,209,38,114,217,178,149,52,201,4,74,20,66,40,213,52,77,211,84,198,212,77,83,91,123,61,34,16,66,0,144,157,125,11,4,132,104,167,190,35,72,169,84,211,148,3,161,133,
178,134,132,40,208,175,229,46,36,10,17,97,172,29,206,17,121,143,157,94,116,103,55,13,145,146,49,51,16,148,24,14,208,118,89,35,110,145,52,152,98,41,156,53,104,200,66,17,2,247,85,226,211,165,222,66,53,1,
97,40,100,62,5,246,12,214,12,52,93,144,169,0,26,108,207,215,147,30,6,16,237,151,227,71,174,187,89,237,108,47,7,98,131,12,189,234,139,251,164,20,248,148,17,49,91,62,10,246,122,13,170,58,54,20,178,124,164,
49,70,138,56,138,85,93,29,218,147,199,2,40,27,26,198,242,214,212,60,92,204,128,92,40,78,220,21,197,179,55,132,128,224,204,6,200,143,7,171,95,238,45,135,228,156,96,135,53,174,169,238,199,225,207,177,10,
190,139,229,135,249,208,51,213,249,16,37,93,10,223,171,142,200,230,40,71,179,15,225,187,247,250,164,80,198,100,131,139,187,219,47,183,219,71,68,17,69,137,148,40,132,144,18,132,0,41,89,8,144,2,140,4,37,
81,72,100,129,130,128,37,8,129,22,1,89,8,54,136,66,30,143,155,36,78,210,56,141,147,44,77,211,170,202,226,50,47,171,66,4,118,144,222,156,141,91,246,104,63,8,9,193,12,32,59,177,155,53,71,155,142,170,90,
186,209,93,243,219,148,125,16,209,11,97,109,217,189,229,157,51,10,21,134,72,136,56,74,146,36,73,1,184,170,75,4,176,22,121,195,137,167,204,70,43,109,173,219,148,76,202,226,88,230,121,81,28,243,226,200,
0,150,92,184,232,65,4,196,223,246,69,115,167,90,10,189,206,72,96,166,166,129,108,22,69,81,22,199,209,110,179,90,63,61,174,183,171,195,126,147,101,25,128,118,164,137,194,124,63,2,217,229,12,129,25,121,
76,11,10,225,241,105,141,61,29,97,7,144,0,194,255,99,102,84,74,74,33,148,82,82,214,198,0,179,181,45,23,66,49,183,14,205,142,152,251,13,96,64,37,69,211,212,61,219,93,34,82,170,157,74,222,212,117,83,87,
117,93,213,117,45,165,244,166,151,173,129,219,73,202,70,224,249,36,178,5,64,56,97,12,219,5,151,25,140,49,74,37,246,84,65,80,48,24,55,203,64,158,197,2,131,16,82,72,68,0,129,178,29,16,212,177,218,100,235,
155,219,10,175,58,83,218,157,71,95,111,68,52,131,33,18,66,41,173,154,186,64,68,0,5,216,182,56,59,187,209,214,143,215,159,210,214,117,243,100,168,216,30,121,60,49,98,240,111,158,153,5,131,207,105,180,78,
136,192,204,32,92,249,7,109,161,194,62,146,200,52,53,233,120,110,154,170,170,115,102,96,150,68,64,140,204,72,36,136,140,45,114,24,131,192,198,16,50,163,49,204,4,196,64,4,198,216,196,46,25,195,204,108,
12,50,3,81,251,143,9,44,24,59,54,106,108,28,240,237,223,253,31,68,97,14,148,186,200,67,163,180,111,180,97,116,152,27,157,16,107,194,57,141,125,175,52,223,13,234,207,103,94,123,37,38,235,26,79,66,160,75,
146,182,193,187,221,25,38,34,191,254,250,31,173,247,157,205,117,186,13,127,87,14,29,240,156,171,166,61,33,16,81,22,197,225,245,155,239,132,16,40,213,253,253,139,162,170,146,178,40,203,252,249,243,47,130,
113,175,56,145,252,229,158,197,236,132,60,126,100,78,119,207,216,17,198,237,154,58,9,172,178,60,62,62,190,110,154,38,203,230,85,85,53,117,117,255,236,179,151,47,191,14,255,42,124,213,178,204,159,86,111,
116,20,41,173,149,210,141,169,243,252,112,56,110,143,199,131,105,234,175,191,254,253,68,29,0,206,202,119,78,143,207,243,253,15,63,252,33,77,210,36,73,210,120,150,231,57,179,225,198,252,243,63,255,223,
73,146,77,41,126,70,95,104,44,109,215,219,238,205,40,108,87,139,63,255,233,127,104,41,133,84,90,8,37,213,177,222,22,117,89,215,37,51,127,245,213,223,143,182,204,230,249,225,112,88,3,136,44,91,38,73,214,
59,104,235,245,123,0,70,33,81,8,106,106,67,198,26,20,217,225,157,211,101,147,203,197,165,135,135,87,199,195,70,71,233,39,159,124,61,53,84,238,245,235,239,136,27,0,98,0,70,178,230,176,118,228,194,205,237,
39,126,128,232,84,125,233,124,19,173,49,205,219,183,63,20,69,46,133,248,228,211,111,211,52,155,50,193,179,199,108,179,121,216,237,214,222,194,92,74,33,68,203,208,5,138,151,47,191,236,53,7,15,78,155,222,
181,222,239,74,34,162,119,239,126,90,175,223,9,161,146,100,241,233,167,95,41,165,7,85,7,10,53,73,65,242,212,16,113,144,229,164,137,159,225,56,16,59,132,194,250,224,53,118,187,91,176,234,84,149,124,209,
169,71,72,135,130,203,97,104,63,101,145,167,70,149,161,163,165,249,209,20,236,104,223,103,32,87,34,119,98,245,222,168,45,181,183,98,79,34,178,115,114,92,68,208,66,173,103,169,46,33,96,23,177,211,216,3,
34,116,16,220,74,244,137,132,16,148,36,179,231,207,62,123,124,124,109,251,79,110,111,239,76,93,54,85,249,248,254,231,249,252,86,41,229,163,33,63,223,177,219,103,217,158,46,110,1,24,215,54,7,139,205,208,
185,18,47,137,64,185,170,170,135,199,87,85,121,140,227,153,82,170,44,15,183,119,159,44,23,119,3,51,173,78,69,123,179,121,212,58,82,42,138,116,172,117,82,85,133,173,72,26,99,94,60,255,98,112,174,143,36,
202,135,88,16,158,28,175,94,253,69,235,72,199,89,146,166,143,79,239,55,79,171,213,234,253,124,121,151,36,105,119,117,188,44,162,28,211,133,32,244,71,63,246,53,246,198,52,117,85,194,124,166,164,227,137,
57,244,0,0,32,0,73,68,65,84,64,37,171,186,54,198,176,105,26,99,226,214,161,163,243,87,0,188,89,63,150,85,129,0,55,183,247,113,156,6,212,178,189,85,85,25,69,145,205,152,54,214,104,178,105,162,89,124,157,
174,126,92,35,105,140,121,255,246,199,162,206,23,179,219,251,103,159,193,56,245,6,0,144,82,53,165,157,75,211,48,145,142,35,93,70,90,71,82,203,205,246,97,185,188,191,84,124,159,84,143,173,86,111,215,235,
247,128,48,75,23,47,94,126,41,165,26,0,241,176,61,68,16,27,195,68,220,16,17,10,161,149,86,82,91,78,178,217,60,62,127,254,249,24,82,140,151,91,122,89,189,213,234,205,227,227,27,123,113,126,242,233,183,
206,140,181,19,71,119,1,148,187,213,167,126,85,106,128,128,158,122,158,246,186,103,96,223,244,105,251,53,7,209,48,13,172,73,58,72,117,190,9,115,180,79,157,157,59,247,48,31,218,113,229,8,24,232,184,36,
254,140,37,79,112,212,196,68,50,194,202,152,58,225,188,83,137,146,29,105,141,104,113,211,14,248,245,176,219,70,91,54,143,110,107,21,109,238,159,64,8,94,44,238,140,105,86,171,55,212,24,34,19,167,179,187,
155,123,102,248,241,231,63,126,245,197,111,45,182,134,107,71,207,206,96,170,161,104,244,238,132,35,137,87,146,163,91,93,218,132,73,93,87,143,143,111,138,226,16,69,177,212,113,83,215,55,55,247,139,229,
189,148,42,48,221,8,163,183,246,5,243,124,79,212,196,113,166,117,164,85,92,87,197,241,184,203,243,221,126,191,67,132,36,205,136,120,84,2,13,151,173,167,152,25,182,219,199,162,202,111,151,119,177,78,165,
142,153,183,13,144,80,248,229,87,191,245,231,101,239,210,154,122,230,51,69,228,160,145,6,187,210,46,68,196,227,113,199,136,54,13,34,64,0,219,217,59,134,76,227,226,152,211,161,174,235,106,179,126,100,32,
64,113,127,255,210,82,158,30,244,24,211,16,53,0,17,34,11,68,55,230,151,180,142,39,62,197,101,0,61,30,247,15,15,63,17,241,243,231,159,205,102,183,83,134,56,246,150,166,179,195,126,211,52,85,99,154,166,
169,23,233,172,142,211,168,42,117,148,148,219,245,110,187,154,47,238,174,20,240,251,23,218,237,214,171,213,155,198,52,128,252,233,243,175,102,243,91,167,176,238,181,27,116,6,56,35,178,148,202,152,134,
155,134,140,33,50,64,28,37,137,110,170,168,42,171,170,62,30,183,121,113,72,226,108,170,193,59,108,191,14,19,232,171,213,155,167,205,3,155,218,52,205,205,221,139,103,247,159,9,33,221,57,51,162,114,113,
82,164,83,36,30,78,175,115,109,8,45,205,244,211,235,152,201,27,51,247,228,80,0,100,12,1,80,240,204,212,14,0,35,238,245,65,13,147,141,65,55,234,120,26,244,140,181,163,26,116,118,159,41,43,117,100,243,163,
41,209,32,132,239,228,1,218,194,158,11,231,109,182,208,82,78,91,240,181,40,233,132,93,232,169,40,0,219,169,82,68,6,17,44,9,13,145,203,24,144,18,220,42,34,132,176,167,160,16,130,110,111,95,8,161,222,63,
190,106,136,230,217,33,157,45,238,238,158,61,61,61,252,248,211,31,191,12,96,244,227,28,170,194,14,19,231,51,52,228,155,28,200,33,17,128,203,178,88,173,222,149,229,62,138,98,37,165,105,234,155,219,23,203,
229,157,77,125,118,91,161,112,40,165,222,239,215,145,78,226,40,139,227,52,78,226,60,63,90,13,1,17,189,124,249,101,87,128,53,170,224,27,198,170,29,24,125,251,246,167,40,142,98,157,36,73,186,125,122,120,
122,122,124,90,191,249,242,243,223,90,177,238,7,130,242,185,246,36,15,154,246,99,218,82,139,253,204,101,149,219,210,148,37,77,204,130,9,141,13,241,92,113,18,17,137,104,179,121,204,243,189,16,34,142,211,
219,219,23,66,72,187,132,244,98,130,170,42,219,218,51,10,99,140,161,134,76,237,245,200,215,225,102,103,237,120,124,124,181,219,175,133,84,159,125,246,141,214,201,208,201,162,23,124,164,233,220,80,83,215,
117,221,52,77,211,24,99,230,179,165,157,92,68,141,121,120,124,45,117,148,196,233,116,255,88,103,231,126,191,126,120,124,93,87,53,35,221,46,238,159,61,255,60,160,159,220,83,224,6,171,123,123,162,198,113,
74,13,55,212,56,23,248,102,190,136,129,23,216,98,142,121,120,255,211,139,23,95,69,81,124,38,17,228,181,9,101,153,175,158,222,28,246,107,0,172,235,106,62,187,121,246,197,103,214,4,160,215,163,233,35,253,
46,217,228,96,188,46,135,82,167,147,42,148,67,25,83,56,228,206,132,15,235,42,73,185,203,112,185,55,141,245,124,2,116,52,97,58,214,96,25,232,67,71,21,245,93,114,122,33,37,26,178,74,68,28,219,35,172,96,
84,136,86,105,111,247,123,18,26,68,241,136,104,211,249,198,166,201,136,218,2,4,17,2,24,127,53,18,33,179,5,208,118,188,33,17,48,179,16,182,248,40,132,128,197,226,86,235,232,253,251,239,203,124,63,43,138,
116,150,221,221,221,175,86,143,223,127,255,135,207,62,251,214,218,205,246,168,232,64,185,141,87,40,103,217,97,129,239,242,236,88,141,0,192,225,184,125,90,189,109,154,42,142,83,41,53,27,88,222,62,91,46,
239,237,164,160,160,127,212,83,215,190,35,207,110,183,38,50,42,73,165,214,82,201,60,63,30,15,251,195,113,127,216,111,148,210,90,199,1,204,13,227,145,243,216,199,204,80,85,69,153,239,110,146,123,21,233,
227,113,187,90,189,123,122,122,107,12,220,220,60,39,162,169,152,238,202,100,232,68,26,20,122,227,128,152,177,169,107,32,195,8,136,44,0,211,56,169,170,36,170,243,168,74,202,252,104,213,130,187,253,250,
120,216,10,33,25,204,98,246,194,199,140,99,75,26,52,77,77,96,135,176,18,0,147,241,242,46,154,90,0,70,249,41,0,20,69,254,240,240,170,105,202,52,93,60,127,254,153,16,50,176,182,60,247,145,231,243,187,252,
176,85,74,71,90,239,247,168,148,142,147,100,206,75,219,32,244,234,213,159,238,239,62,11,130,250,145,222,7,34,90,175,31,54,155,7,106,42,16,34,138,146,231,207,63,79,211,121,24,135,118,155,190,58,121,249,
240,205,68,177,46,171,50,174,138,70,39,117,93,239,183,40,164,152,47,150,132,196,96,136,232,205,171,239,178,249,242,246,246,197,160,13,191,61,109,242,124,191,219,173,15,135,109,211,148,90,170,166,105,146,
100,254,242,197,87,73,58,31,45,221,12,165,99,93,105,125,103,138,114,192,55,201,67,103,152,15,117,115,149,67,109,169,9,248,169,127,18,182,9,86,207,124,3,8,238,128,44,17,241,21,183,169,60,85,39,31,58,44,
208,135,89,191,49,39,145,11,66,129,30,150,58,131,187,147,159,136,101,166,198,160,21,150,187,98,203,41,61,106,140,23,78,27,8,68,112,254,148,112,205,145,182,2,206,66,8,34,171,24,180,213,127,17,199,233,23,
95,252,253,155,55,223,63,60,189,203,138,89,150,205,178,249,12,25,127,248,254,63,102,139,219,79,63,249,90,8,17,90,213,157,153,159,51,234,151,209,99,154,189,159,117,93,174,215,15,135,195,26,89,168,72,35,
50,32,46,151,247,55,55,207,39,74,16,67,139,82,182,5,74,235,31,28,69,113,164,227,56,74,143,249,190,157,163,217,218,139,80,207,91,0,46,141,143,239,229,254,242,124,79,200,0,66,160,180,185,249,134,204,111,
127,243,127,118,163,120,190,232,61,241,17,24,234,207,58,251,141,26,70,50,13,51,55,92,31,242,157,82,106,49,191,7,22,251,253,250,47,127,249,87,129,82,39,17,50,10,33,95,60,255,82,169,200,235,231,96,204,32,
138,200,112,251,47,152,223,75,52,16,90,143,230,67,79,13,35,171,213,235,253,110,131,8,207,158,127,97,141,83,135,62,105,83,209,247,221,221,139,99,190,43,203,98,183,91,87,85,165,180,142,180,22,66,205,231,
55,150,132,61,62,252,252,244,244,102,185,124,62,159,223,72,169,253,27,168,170,242,112,216,238,118,79,85,117,4,33,193,144,210,201,253,253,11,59,65,164,71,129,187,19,125,121,24,33,217,55,115,123,251,242,
213,235,239,98,165,181,138,104,107,116,28,75,148,82,42,45,244,124,126,99,89,225,110,247,180,90,189,141,162,72,169,88,10,201,192,198,52,141,49,117,149,215,117,131,200,74,105,102,106,154,38,142,103,159,
63,255,50,77,179,94,43,71,0,61,212,109,108,15,145,212,132,221,238,22,28,3,0,109,119,186,160,158,135,157,75,100,199,44,115,27,197,251,167,237,42,156,104,80,160,191,252,115,88,251,153,104,115,98,21,8,197,
67,0,229,94,235,103,24,161,247,200,173,15,231,175,121,103,198,24,165,208,254,100,102,68,50,6,149,242,180,212,94,78,246,158,1,0,41,209,201,38,216,61,134,220,117,104,132,0,59,14,71,8,54,198,106,6,33,12,
231,221,105,132,159,125,246,109,81,28,223,189,251,241,88,236,179,104,30,167,241,242,230,238,120,220,253,249,175,255,243,118,249,236,238,238,165,181,180,129,145,1,94,157,11,43,100,172,195,156,189,103,145,
198,212,219,237,106,183,125,50,77,37,117,2,128,32,112,150,45,102,139,187,36,78,7,121,192,208,249,13,130,141,19,124,111,183,143,66,8,173,236,213,167,243,124,127,60,236,246,251,221,126,111,141,217,229,64,
171,113,13,33,237,192,198,108,118,19,201,168,174,171,195,113,99,140,121,124,255,118,190,188,77,146,44,164,90,103,89,45,140,206,131,233,214,42,49,40,22,99,160,188,105,181,10,204,152,165,217,219,38,175,
235,186,174,170,205,122,213,182,68,146,213,59,69,179,217,162,105,170,166,170,239,239,63,89,44,238,236,217,18,206,239,29,56,183,34,34,250,2,174,115,118,226,186,174,137,140,255,250,206,11,24,182,219,199,
167,205,123,54,148,36,217,253,253,167,206,81,240,195,76,146,63,121,249,245,155,87,127,46,138,67,18,207,116,100,103,50,75,4,9,66,44,151,55,66,64,113,204,31,87,175,223,189,251,17,64,8,41,136,153,154,6,129,
164,138,132,96,67,38,141,102,55,207,238,231,109,234,147,70,235,87,93,11,171,190,9,139,61,74,90,199,203,197,221,254,176,49,76,113,148,68,113,132,40,165,86,2,4,34,107,29,205,231,11,41,69,85,151,117,85,215,
117,81,146,69,70,20,200,90,71,18,69,89,151,85,85,220,222,60,255,244,211,111,149,138,92,254,241,68,237,135,253,93,158,247,249,52,104,64,4,59,113,122,88,160,15,218,150,90,56,237,69,241,33,199,236,209,204,
110,229,106,52,19,10,189,78,208,209,114,252,197,86,177,94,44,127,33,37,58,232,77,26,169,32,185,90,252,232,30,207,23,108,82,217,180,80,71,38,224,35,194,38,76,177,213,243,81,55,132,183,111,82,34,182,10,
50,41,153,8,216,25,56,216,55,98,73,168,197,40,47,74,140,227,228,235,175,127,191,223,111,215,235,183,135,167,173,146,81,26,101,73,162,158,54,15,239,31,127,202,146,197,205,242,249,242,230,222,245,167,142,
40,114,194,136,27,78,179,118,219,29,198,152,195,97,123,60,110,242,60,175,77,25,171,88,72,201,136,81,20,47,230,183,139,229,173,37,203,161,177,94,79,15,16,110,244,244,43,101,121,76,146,44,138,34,29,197,
58,142,170,170,36,38,38,18,136,119,119,47,187,109,157,61,12,157,20,161,13,195,249,47,190,250,253,247,127,253,247,227,113,175,148,18,145,252,234,171,223,217,145,109,61,183,221,137,64,158,167,61,158,241,
34,15,117,81,5,42,21,107,157,30,243,3,0,107,173,16,165,85,184,50,114,85,149,198,52,203,155,103,207,95,60,87,82,91,28,241,163,171,166,38,93,41,165,235,186,170,155,186,49,77,130,44,164,85,232,194,110,183,
246,3,65,71,185,57,51,236,247,235,245,250,189,49,4,72,207,159,125,110,233,167,49,116,198,229,111,74,140,33,132,248,244,243,223,60,188,255,105,179,126,208,177,150,58,81,66,74,233,20,178,8,81,162,163,56,
110,154,170,177,248,97,234,134,69,93,55,18,32,137,151,159,124,242,220,122,78,143,102,15,70,37,52,216,215,145,158,252,4,110,110,158,19,153,237,102,165,163,40,138,98,137,10,165,20,202,94,165,78,81,43,181,
136,209,202,114,155,166,172,235,166,170,106,102,74,103,139,251,249,237,124,113,107,87,32,139,128,19,109,55,227,125,95,68,228,242,165,97,32,31,166,68,237,211,82,112,243,48,26,2,171,13,227,71,2,252,0,112,
71,251,208,70,213,163,83,89,136,113,250,217,239,151,31,10,236,7,22,36,161,231,113,63,67,218,171,50,133,63,173,240,222,253,68,41,91,42,26,180,39,25,199,47,81,8,108,231,44,98,171,100,114,215,112,107,52,
231,239,1,160,148,109,77,201,242,80,71,50,172,157,179,16,130,93,149,31,241,164,117,199,44,91,204,102,75,23,98,111,204,177,214,42,74,227,25,0,189,123,255,227,171,215,223,73,169,147,36,78,226,44,73,103,
81,148,72,169,165,82,162,163,217,70,171,71,107,154,186,40,142,85,149,151,117,73,77,101,234,90,234,200,22,25,148,16,81,60,75,210,236,102,249,76,107,237,216,86,88,78,57,153,102,12,114,160,216,179,149,218,
110,31,173,239,164,142,34,173,227,195,97,119,60,236,14,135,221,254,176,158,207,61,23,235,227,230,96,56,45,12,44,23,251,62,102,66,200,175,191,253,135,239,191,255,195,126,187,253,252,203,223,244,174,216,
177,156,192,56,22,79,121,89,121,194,24,150,146,122,60,20,17,191,252,242,119,63,253,244,199,213,227,123,169,148,16,202,174,160,113,156,205,102,55,119,119,47,236,244,115,79,63,195,231,12,2,133,14,120,33,
98,213,212,81,93,53,141,73,163,25,197,77,85,215,219,237,99,28,39,46,254,232,72,190,154,166,217,237,86,187,237,202,150,117,151,203,59,155,123,113,9,19,184,122,60,114,31,218,158,191,248,242,238,254,147,
245,211,195,225,184,57,212,21,50,129,16,136,2,65,16,27,215,244,101,148,140,148,142,231,243,187,197,226,214,9,54,79,125,186,103,21,35,231,70,34,135,143,185,185,121,145,166,243,213,234,221,118,179,2,68,
41,149,213,190,144,16,109,203,25,25,34,106,154,154,25,146,36,211,58,94,46,159,205,102,75,167,239,118,125,189,220,55,69,238,209,207,145,230,250,32,21,233,195,109,11,121,97,117,190,219,62,223,3,80,159,7,
109,211,160,142,174,153,174,52,170,37,161,33,69,237,18,85,186,40,185,159,10,228,79,7,246,238,238,133,135,24,209,122,197,217,214,68,49,220,24,56,101,180,250,246,224,110,219,246,224,231,191,219,253,82,42,
33,132,16,202,255,214,239,180,250,121,191,17,234,231,165,84,86,3,236,247,4,127,222,121,33,239,85,225,61,62,220,59,183,219,182,155,197,247,106,159,70,19,215,117,185,223,175,243,252,88,85,71,99,42,68,165,
148,0,161,37,82,211,80,67,198,54,70,24,68,41,5,50,186,83,68,184,30,170,72,9,52,142,107,107,29,165,201,44,155,45,23,139,150,117,122,122,213,155,138,124,126,198,103,120,171,170,98,179,126,72,211,89,150,
45,178,217,60,73,210,227,225,176,63,174,119,187,93,85,21,47,158,127,49,152,233,198,3,1,28,79,240,208,115,26,210,233,116,39,95,250,213,148,37,224,212,40,211,78,15,147,63,56,117,85,230,197,17,128,148,138,
210,116,97,45,214,7,71,114,56,56,122,132,147,237,247,235,221,238,105,177,184,201,178,165,210,90,161,204,139,195,110,191,57,28,118,113,156,197,113,34,132,2,224,166,169,171,178,200,171,163,169,43,33,100,
67,245,124,118,115,179,124,110,39,181,13,205,100,225,151,222,184,44,11,171,121,98,34,123,234,42,21,185,9,163,103,96,250,42,188,30,28,8,28,27,61,111,107,68,135,162,56,54,141,205,111,48,0,10,41,5,138,40,
138,227,56,181,117,246,238,128,141,225,9,214,9,225,137,40,52,163,11,82,162,52,224,161,20,54,125,122,125,210,160,190,100,122,149,37,75,62,221,254,246,110,72,66,173,137,137,221,178,248,235,84,83,190,12,
101,186,234,253,83,150,192,63,172,11,229,157,183,234,127,170,174,119,70,88,65,234,233,114,70,180,77,61,13,105,143,202,119,229,77,100,103,27,57,49,83,39,191,233,50,161,97,74,52,36,161,150,153,182,36,20,
17,221,6,56,101,40,7,21,48,102,23,216,35,182,29,193,204,2,145,133,176,149,125,12,46,87,208,58,186,187,123,121,119,103,63,62,149,197,177,172,242,178,44,136,106,224,6,0,25,137,193,32,34,19,35,32,10,105,
13,232,164,20,74,197,90,71,90,199,113,148,88,210,26,160,243,201,204,177,103,240,20,120,60,159,146,162,142,165,142,56,242,110,183,79,58,138,117,20,235,72,235,40,62,30,143,199,124,119,216,239,15,251,237,
179,103,159,118,103,200,12,93,108,135,108,116,220,178,108,138,87,142,245,186,157,203,6,12,98,219,126,27,66,72,30,157,164,169,67,66,61,63,85,58,90,232,216,127,83,86,41,220,213,66,117,212,166,189,141,240,
173,100,217,114,187,91,31,14,251,166,105,148,210,118,225,77,211,89,67,166,204,143,199,227,150,216,0,3,128,148,18,200,16,51,39,201,108,185,188,11,57,239,148,85,224,37,42,10,103,228,28,90,71,221,241,27,
224,219,166,167,27,150,120,80,68,154,124,173,97,235,199,96,129,65,203,241,227,56,27,123,57,111,128,52,90,156,28,89,173,7,190,36,208,173,197,251,200,189,5,80,251,97,3,47,187,80,28,122,10,225,123,0,234,
254,182,159,12,181,236,216,81,90,238,138,243,251,119,175,239,248,28,180,57,116,168,168,26,164,255,79,41,209,238,204,162,83,56,63,90,157,31,32,230,9,37,237,97,178,149,119,33,208,153,129,182,181,35,104,
93,124,208,106,152,94,191,254,83,158,111,132,64,41,35,33,4,162,180,230,28,174,161,211,115,219,30,3,181,92,88,74,233,185,167,244,36,218,217,124,4,126,15,125,6,52,158,182,235,17,40,3,128,45,10,67,93,35,
226,209,37,109,195,116,129,127,69,116,29,168,246,215,2,79,78,69,136,40,187,143,239,55,197,123,215,25,173,98,173,173,209,114,82,21,249,225,184,217,239,118,187,221,186,40,246,111,223,22,189,37,241,148,110,
63,85,159,251,75,125,159,47,156,44,27,8,58,225,88,31,148,131,9,13,212,233,6,105,173,34,120,194,245,46,36,158,214,164,46,60,86,157,184,193,125,227,189,61,194,155,15,120,35,193,240,208,245,214,197,224,72,
182,95,32,187,218,122,20,37,74,107,37,85,235,90,196,36,148,0,161,160,6,162,166,110,242,162,48,77,83,9,129,69,113,120,124,252,121,216,151,50,62,114,18,24,57,252,204,108,155,224,174,226,162,227,29,132,157,
56,242,202,78,48,232,52,8,35,7,54,5,99,189,200,193,121,222,95,187,79,147,221,208,182,250,143,152,108,146,235,65,10,226,116,215,67,4,173,170,136,252,206,208,27,180,117,110,10,124,155,60,234,5,250,164,240,
116,61,69,235,150,87,57,88,111,97,215,178,94,33,244,114,249,98,185,124,225,33,216,189,61,19,26,54,247,68,248,67,72,157,82,28,13,3,249,83,159,18,4,163,119,7,62,193,29,24,29,86,231,195,187,30,49,61,241,
244,249,80,251,169,130,154,59,6,162,54,228,211,186,139,187,221,155,23,207,159,131,21,1,181,134,156,40,80,218,11,70,10,4,4,68,144,18,0,88,10,6,52,66,128,16,32,16,64,144,53,251,145,66,2,144,64,1,237,229,
231,173,46,0,236,101,108,159,165,253,220,34,184,214,133,231,221,65,83,61,6,127,226,158,192,98,39,120,44,160,96,195,230,97,5,34,11,191,45,172,144,192,118,13,72,68,227,30,207,93,44,128,208,21,69,162,142,
226,44,142,211,36,73,163,56,61,30,118,214,109,129,153,148,20,204,53,0,49,24,112,190,97,173,189,133,243,22,107,183,57,236,6,241,129,149,69,79,234,218,137,90,152,36,4,63,139,150,173,129,16,19,129,107,4,
59,217,220,129,115,24,226,214,179,41,240,252,15,52,94,237,167,18,110,121,16,192,0,40,1,16,16,153,37,130,0,70,64,105,29,237,236,30,102,4,16,68,82,8,4,18,100,29,4,73,88,45,90,7,142,1,89,136,214,233,13,130,
132,137,251,82,61,152,23,101,201,121,139,221,192,24,56,3,53,0,44,90,115,62,134,222,48,74,239,174,212,21,144,181,199,1,193,26,33,245,230,193,114,224,155,196,238,84,106,253,88,208,247,18,3,32,89,4,118,193,
96,187,118,66,91,177,13,103,37,50,118,231,60,158,132,75,33,185,97,228,78,179,124,107,224,36,16,236,23,11,206,121,12,5,182,142,82,61,55,114,4,182,111,10,152,169,93,33,91,130,236,239,159,60,229,90,51,21,
6,102,52,104,189,35,173,167,9,88,107,74,70,32,20,4,68,222,214,135,192,136,214,63,159,129,8,209,59,230,145,103,175,174,212,79,208,26,95,33,177,1,146,236,236,31,17,37,17,187,112,148,155,186,121,255,254,
251,249,252,89,192,91,189,230,169,223,66,58,108,1,240,48,125,177,154,212,171,215,247,253,67,123,10,39,199,73,79,27,231,193,52,64,76,95,91,183,185,66,176,81,60,17,72,41,66,0,181,219,182,215,72,8,100,2,
2,22,182,55,84,88,171,25,36,96,1,132,32,13,145,20,142,216,10,32,98,148,86,16,10,134,65,128,32,65,72,214,29,7,157,8,128,24,164,245,60,179,128,137,12,104,79,31,47,78,106,205,217,16,216,180,31,220,26,236,
129,112,218,249,214,107,12,17,173,11,146,117,203,69,129,206,131,11,128,241,116,197,162,247,236,9,125,208,172,255,207,184,40,20,186,49,62,0,24,195,58,209,90,43,173,35,173,244,241,176,221,31,118,187,253,
122,183,95,151,197,65,107,43,62,32,38,110,195,31,38,54,118,102,36,49,153,118,165,63,157,55,214,207,49,148,203,65,207,6,20,216,158,156,46,84,15,173,34,160,141,156,2,50,102,127,71,29,55,86,231,21,135,206,
238,18,17,209,26,99,9,6,118,247,17,145,172,1,28,34,2,11,6,18,8,140,40,25,88,32,51,10,43,181,65,36,6,41,128,0,133,96,1,130,152,91,220,68,33,0,90,77,177,104,173,11,221,98,23,144,175,147,175,22,3,183,51,
92,77,135,253,33,139,246,68,113,112,224,203,114,30,69,224,68,214,173,123,136,195,20,158,176,163,191,58,39,106,191,247,22,40,45,30,251,164,35,120,167,168,177,201,46,28,172,88,246,82,9,23,12,143,162,162,
93,219,90,54,224,175,108,4,2,151,72,106,79,94,14,87,0,239,239,119,242,249,99,119,52,78,65,58,64,199,76,196,88,167,186,214,14,143,56,136,129,92,235,188,139,232,201,184,240,134,160,245,118,110,125,124,193,
121,225,217,101,154,128,144,177,125,24,88,219,61,64,4,38,66,4,182,41,64,6,68,60,30,247,190,19,212,105,164,134,66,122,50,198,156,161,162,103,72,232,160,196,4,29,31,251,169,112,222,85,139,71,202,244,83,
96,26,204,137,62,185,225,89,254,41,4,18,25,155,174,244,177,188,179,102,64,99,40,155,61,123,90,109,17,80,72,237,125,152,92,108,231,238,162,16,74,34,96,235,96,47,25,129,131,154,146,20,72,40,78,20,79,8,240,
145,35,162,177,108,177,237,12,117,105,83,24,138,110,78,87,98,55,18,69,180,87,46,162,112,41,60,193,246,249,217,185,214,179,96,87,115,115,205,254,2,81,8,16,46,241,219,198,255,208,178,42,116,35,214,218,28,
31,17,41,21,71,113,18,197,73,20,37,74,199,69,89,180,186,57,195,66,202,166,177,162,46,32,98,34,36,242,119,3,139,48,246,27,173,7,164,21,101,51,33,117,206,15,228,16,10,25,92,16,215,118,10,50,163,59,99,208,
63,192,81,85,12,92,173,125,2,93,156,242,161,136,192,32,156,189,167,103,220,66,32,34,88,71,117,68,48,2,236,193,64,20,40,64,88,124,21,62,169,13,2,25,144,4,10,20,236,190,89,114,214,194,237,193,107,69,250,
46,200,232,121,23,117,3,214,190,247,10,119,208,211,94,201,196,167,238,240,241,150,89,226,147,67,93,144,249,181,171,69,75,34,69,216,53,213,123,19,45,128,181,161,183,227,181,192,231,157,13,90,239,61,96,
24,54,40,117,20,29,136,8,64,157,3,17,36,138,28,93,0,100,228,64,152,223,177,136,113,166,28,67,179,14,159,204,241,220,14,192,217,49,51,244,220,146,24,152,12,57,172,181,136,6,161,192,158,136,252,44,37,15,
181,129,164,212,180,62,165,157,168,156,1,193,186,227,1,128,16,234,243,207,127,23,164,71,195,33,34,225,4,17,26,196,239,212,3,205,160,5,99,196,6,164,55,72,74,245,132,208,225,152,154,64,174,132,129,7,51,
94,164,162,150,117,250,238,120,209,122,207,250,34,18,32,10,99,200,138,147,136,188,146,137,136,224,197,139,111,125,253,61,204,117,218,89,32,0,24,22,229,189,48,32,84,5,12,138,242,162,155,128,243,249,56,
159,30,194,161,5,219,72,90,45,168,255,122,87,240,240,97,254,105,253,208,139,94,182,110,58,109,55,82,145,95,175,223,71,58,78,227,52,77,178,52,157,237,247,155,253,97,179,223,109,119,251,167,44,155,47,22,
95,78,171,240,250,221,193,195,181,116,212,172,123,108,40,194,148,91,207,84,37,106,178,100,220,45,154,143,28,129,97,93,62,56,110,208,61,140,157,35,63,90,146,239,233,120,206,19,193,43,188,1,175,234,38,248,
85,110,163,3,38,97,108,52,241,249,164,104,175,209,96,104,133,119,70,88,10,103,39,8,245,74,43,99,62,73,20,166,44,61,158,250,242,209,201,81,190,107,218,100,19,250,254,97,65,95,60,135,29,156,97,89,201,63,
102,48,89,228,148,6,13,249,166,43,211,135,106,127,26,116,84,210,249,248,189,119,213,168,174,120,30,195,237,169,202,210,53,113,189,55,27,15,84,181,32,4,216,89,114,150,138,186,170,122,235,36,226,221,67,
2,57,33,3,72,87,148,55,204,44,165,52,198,190,123,219,97,213,246,231,216,113,76,118,211,122,73,32,218,57,34,104,12,133,226,45,171,129,11,7,30,13,49,212,95,153,221,86,110,127,202,9,230,83,141,56,104,185,
241,219,20,56,229,116,134,122,118,51,102,48,213,143,127,60,108,152,73,105,37,149,210,90,159,14,7,179,18,122,62,191,29,27,186,29,10,152,185,235,54,22,22,1,134,163,147,96,122,94,227,208,49,143,47,182,204,
95,232,243,28,105,150,15,229,95,216,93,147,70,145,116,74,216,52,58,75,245,42,12,61,215,52,63,217,207,122,217,220,243,67,160,115,242,25,70,231,21,159,7,237,97,165,190,135,167,231,1,116,122,69,25,159,129,
60,88,176,79,211,19,194,6,161,160,67,169,35,225,12,139,242,22,46,67,133,147,111,3,181,240,234,101,164,22,13,45,69,13,154,235,195,78,167,14,3,29,66,103,47,126,31,226,233,121,119,209,147,198,190,103,47,
50,85,95,234,77,248,232,138,156,38,193,212,24,99,97,113,16,209,67,16,197,183,24,36,37,120,24,117,217,3,233,223,140,148,45,98,74,105,103,91,54,204,210,89,181,75,171,103,98,182,227,137,136,217,86,30,218,
56,90,8,182,215,164,235,152,66,39,26,61,85,234,125,129,222,247,41,9,235,104,15,174,122,4,94,85,195,33,200,6,23,255,9,154,93,140,143,39,23,241,224,193,67,143,151,176,181,217,24,83,148,199,44,89,196,73,
18,37,89,148,164,251,221,246,112,220,110,247,219,253,246,233,230,238,229,0,64,105,152,35,63,19,167,12,219,153,166,250,235,97,48,22,237,76,215,252,25,70,22,178,194,41,183,145,177,182,37,154,194,217,49,
157,233,71,99,104,95,57,52,54,247,244,140,45,192,197,129,166,31,7,166,147,86,120,31,202,121,123,221,74,231,181,80,163,40,218,61,56,60,134,161,52,33,111,10,215,117,112,32,5,3,121,211,80,114,207,97,69,40,
20,63,13,129,50,104,24,181,61,75,61,243,145,78,26,116,8,157,3,187,210,241,25,159,195,193,118,254,224,168,110,51,120,56,36,99,88,89,250,48,42,26,222,181,17,61,17,184,14,119,112,85,38,239,199,108,21,78,
182,131,147,61,158,134,119,45,223,116,239,80,50,51,17,74,169,218,89,5,44,45,235,181,253,36,68,39,209,12,145,16,2,1,108,103,84,139,116,222,203,217,187,156,184,11,146,28,210,113,160,28,56,93,189,46,139,
218,1,71,63,51,46,216,35,92,102,112,180,131,147,125,243,146,111,180,181,15,216,237,158,180,138,116,172,35,149,196,58,62,236,182,135,253,122,187,221,236,247,107,64,33,165,28,109,95,27,24,58,244,210,61,
48,74,69,123,153,157,51,61,72,103,172,157,175,119,14,29,72,157,134,161,250,104,27,194,40,15,237,39,88,134,78,69,195,41,0,215,197,208,83,174,213,124,246,193,48,221,253,137,215,36,19,46,74,77,199,226,235,
15,2,208,115,18,209,137,195,49,157,53,238,200,57,166,102,127,118,234,221,93,207,208,48,162,239,217,56,25,207,73,189,152,196,155,219,135,214,36,93,101,232,20,128,142,244,209,247,244,243,231,187,57,71,83,
162,225,215,161,134,135,174,215,59,31,94,39,97,50,116,72,69,67,160,244,113,122,16,161,99,152,51,181,150,160,94,42,239,177,213,231,223,165,4,99,208,15,145,147,18,130,129,124,45,33,69,20,0,141,149,208,251,
64,222,161,39,185,187,22,58,109,175,58,249,121,71,14,10,133,149,172,118,217,104,135,31,217,7,120,105,55,81,56,46,177,29,228,217,75,14,48,123,181,83,152,55,16,238,40,182,79,24,172,70,237,121,92,150,185,
161,58,205,102,81,148,68,73,162,181,174,170,194,157,201,184,188,121,214,227,155,189,165,123,16,209,211,244,57,1,99,178,199,190,91,226,168,86,241,227,156,67,71,137,232,116,251,214,144,156,134,248,219,99,
178,48,149,24,189,30,67,167,209,241,242,32,128,95,55,37,122,62,81,208,29,164,124,77,44,127,85,252,222,27,99,113,38,89,220,27,50,60,221,10,201,225,252,247,209,188,211,64,102,207,131,214,207,126,36,238,
74,234,97,193,221,4,64,60,14,160,62,13,122,38,96,191,18,73,71,181,77,28,248,177,247,121,232,160,82,223,146,151,238,198,105,226,241,197,90,83,152,3,245,17,189,245,0,181,48,26,58,194,73,137,198,180,239,
161,105,216,185,19,73,71,72,195,64,222,30,122,41,132,125,233,182,25,223,181,48,9,215,54,125,170,41,89,3,20,215,39,133,109,5,19,135,173,135,246,207,123,251,69,55,133,215,118,145,218,17,105,65,114,217,15,
77,107,29,212,60,90,58,191,146,142,251,61,17,29,143,251,89,54,75,147,52,73,178,52,201,142,199,125,91,77,218,175,147,116,110,23,158,110,241,112,100,148,66,207,233,118,76,239,6,131,236,248,135,69,238,87,
231,7,187,149,241,174,216,123,130,141,142,98,235,84,37,10,38,6,88,141,135,177,151,104,32,143,18,177,255,124,12,157,206,129,242,88,64,115,6,49,47,239,185,238,109,48,0,244,218,222,0,122,70,77,39,160,9,170,
76,116,22,79,131,9,199,208,201,144,182,162,167,129,197,125,192,73,59,238,162,93,125,254,57,0,29,242,211,139,192,122,62,43,170,70,164,106,236,3,121,56,67,69,123,5,122,191,52,141,162,167,195,205,19,69,117,
57,199,246,174,211,135,6,131,117,1,0,26,33,164,11,231,165,49,182,118,228,223,188,116,51,65,219,41,95,118,219,22,142,152,109,103,20,6,84,20,93,135,18,57,151,188,14,33,29,45,16,91,67,147,48,115,106,39,56,
133,15,3,176,14,74,24,148,251,41,64,79,242,120,234,188,211,79,253,160,225,104,188,253,126,173,148,140,116,164,117,28,197,201,241,184,223,237,214,219,253,122,191,93,23,69,190,92,62,115,125,29,208,109,61,
10,155,64,134,204,116,52,37,58,82,92,58,239,110,119,198,169,100,250,170,198,233,150,121,12,90,101,70,115,157,147,59,167,77,6,112,16,200,159,43,67,95,170,213,240,135,76,244,155,10,201,63,134,126,94,4,211,
15,76,158,92,46,46,93,95,88,234,25,87,135,88,217,235,152,116,160,57,69,69,79,10,39,223,178,25,148,239,141,155,225,220,111,229,236,85,150,2,63,145,62,218,134,33,252,53,100,115,180,208,52,77,66,131,88,62,
196,205,161,86,244,12,21,245,196,211,113,76,17,114,210,94,68,239,4,134,29,54,106,117,78,246,174,13,108,153,165,148,194,185,49,181,239,196,82,78,251,59,151,238,148,150,96,182,89,79,33,152,79,134,35,46,
132,15,134,18,183,70,250,167,222,74,23,149,163,115,212,247,130,164,62,146,34,10,119,12,122,102,193,33,212,122,155,40,236,58,69,113,47,204,71,228,97,160,106,63,105,93,23,68,38,77,179,40,201,146,56,73,226,
116,83,20,214,119,172,49,230,246,246,197,80,8,50,40,110,118,170,156,83,137,209,33,152,78,231,61,167,188,53,135,169,185,201,0,115,56,93,178,171,73,26,175,50,77,41,153,70,49,244,124,129,126,58,194,29,77,
82,195,7,77,160,154,206,93,94,85,55,31,157,195,116,93,51,232,5,36,189,38,102,63,95,154,31,149,118,245,78,18,159,94,11,207,40,159,235,28,67,210,246,12,12,147,164,189,208,126,224,81,66,161,83,137,49,228,
253,149,221,54,117,237,154,66,7,147,73,163,144,179,56,123,217,217,62,12,227,212,240,128,141,138,156,186,84,52,24,206,238,202,55,93,244,20,61,18,234,89,167,139,247,169,75,63,209,24,43,146,63,213,142,122,
69,36,41,217,241,80,27,185,219,13,236,213,226,1,68,88,77,2,104,219,90,236,78,199,58,109,2,84,32,66,192,31,237,148,39,26,80,81,10,105,169,16,220,189,43,0,208,201,179,66,196,4,103,22,229,9,41,3,136,238,
232,80,12,60,128,57,47,142,89,58,203,178,44,73,102,73,54,223,109,158,246,187,167,237,238,105,183,89,51,128,16,210,165,210,135,194,186,206,221,1,170,246,97,20,198,198,19,94,195,64,39,252,153,174,41,76,
15,43,230,67,190,121,70,55,122,94,204,52,21,194,95,79,187,46,204,58,189,40,29,253,219,164,68,199,121,104,144,146,190,166,166,52,229,69,50,137,176,83,83,9,194,248,189,87,98,234,181,238,4,118,77,97,129,
222,147,86,234,186,58,209,112,114,242,64,70,218,1,77,87,172,231,32,180,31,57,255,207,3,232,32,90,239,35,233,197,13,255,241,213,249,111,174,71,69,253,60,63,231,181,222,201,176,134,238,203,65,8,47,130,119,
233,35,122,225,31,224,42,78,94,81,100,221,149,236,35,133,7,208,166,105,39,122,6,48,218,169,197,219,175,77,8,59,107,236,132,155,190,142,228,118,218,25,36,224,224,175,3,154,14,82,71,202,68,78,234,196,65,
129,200,54,237,218,103,11,141,217,91,236,14,162,248,182,47,171,171,118,242,197,36,60,28,54,90,137,40,142,180,142,227,36,66,0,66,215,95,39,112,49,187,241,43,109,47,126,31,93,81,195,208,62,108,187,24,40,
156,120,88,37,232,1,226,148,111,211,24,208,140,50,169,190,152,102,56,89,126,34,186,31,111,115,24,48,208,41,101,40,94,71,181,206,137,219,121,146,131,242,25,61,252,47,3,210,139,199,243,26,81,42,254,18,169,
221,63,0,0,0,32,0,73,68,65,84,24,61,147,12,29,170,68,195,73,133,189,78,69,63,98,54,16,44,83,87,14,21,50,211,48,114,26,78,72,110,125,73,156,241,124,103,4,83,40,221,247,27,83,0,26,170,5,70,5,246,211,184,
9,83,213,121,223,167,4,221,153,1,29,42,234,161,51,128,212,48,126,31,9,237,61,122,14,74,73,208,139,229,93,204,11,78,75,127,226,158,1,92,178,16,4,32,17,201,149,146,8,81,182,35,10,196,137,123,90,54,234,88,
167,113,13,160,86,195,127,162,162,214,60,223,53,98,158,80,18,128,28,128,18,246,130,240,147,122,191,37,164,1,51,181,187,67,227,103,251,200,19,29,14,173,75,123,97,105,85,149,68,164,227,121,28,165,73,146,
165,241,108,179,93,237,119,155,221,126,189,223,60,69,201,124,32,200,152,202,251,244,2,121,162,174,137,195,132,51,77,79,60,127,193,245,110,154,154,93,184,158,207,198,221,56,141,173,208,237,16,195,139,81,
252,160,144,117,109,89,233,162,68,244,188,74,244,87,4,208,51,58,167,33,219,29,204,181,199,51,209,0,76,250,73,225,244,155,233,103,54,194,112,100,74,37,26,44,201,158,132,142,200,150,39,146,78,126,156,28,
135,73,210,174,145,157,233,210,88,14,25,232,104,104,31,134,104,19,191,226,49,83,146,240,13,247,18,23,221,88,254,204,23,19,66,103,88,113,10,181,247,195,208,222,162,39,128,240,48,106,139,45,65,14,244,84,
139,183,123,152,89,74,225,54,36,145,65,100,0,22,130,141,17,65,57,222,246,116,2,128,45,28,181,117,121,247,186,44,132,13,237,145,232,36,20,117,106,39,116,67,237,125,73,94,56,148,36,95,68,26,116,103,90,7,
82,14,146,164,236,55,164,108,79,65,106,251,232,173,36,171,229,161,150,165,186,174,249,83,67,173,43,70,113,93,22,233,108,62,75,231,179,108,158,101,139,205,118,181,221,62,109,183,155,221,246,177,168,138,
116,118,19,8,226,56,8,222,59,146,227,1,170,242,116,86,148,7,230,143,215,99,232,133,104,247,74,109,211,213,24,58,154,253,236,103,69,199,34,122,60,91,149,62,215,35,52,245,49,199,120,217,245,22,162,191,60,
138,239,236,190,62,111,48,42,17,157,62,26,120,73,168,0,161,153,127,215,204,187,23,206,119,112,179,103,162,24,234,240,125,212,239,234,72,157,170,233,80,180,23,76,154,227,65,66,192,171,71,249,60,128,134,
146,213,41,233,213,176,148,212,245,190,227,142,247,221,40,21,13,181,162,61,232,244,192,234,227,119,119,68,189,194,105,100,195,24,144,82,122,24,245,240,234,154,235,1,64,24,3,66,176,199,86,43,23,181,108,
148,200,62,143,66,180,110,219,22,19,201,149,236,219,33,119,190,4,239,216,104,43,20,117,106,205,147,188,105,16,206,11,167,238,164,208,224,210,87,138,92,32,47,186,233,78,225,176,216,230,7,236,231,165,48,
174,119,0,218,11,237,17,0,242,124,167,180,138,162,40,210,90,71,169,181,95,67,100,2,98,224,229,226,126,116,81,29,144,80,211,3,80,162,209,147,236,114,56,127,54,13,122,85,139,78,32,149,155,76,137,78,149,
212,207,23,220,167,115,160,35,29,243,31,26,203,143,126,192,209,134,130,15,92,63,248,131,244,85,103,138,93,191,36,229,122,197,192,37,184,78,213,111,33,178,163,180,15,30,217,27,46,235,43,72,220,181,41,241,
137,209,48,240,239,160,100,48,160,158,92,211,35,5,176,75,99,253,205,161,33,19,79,87,92,121,52,252,239,65,234,148,15,30,12,124,167,213,149,167,84,48,127,237,148,10,177,41,66,15,148,30,79,221,134,175,47,
133,27,232,247,248,81,198,129,116,201,202,206,69,87,1,202,94,236,105,69,245,129,92,169,229,158,46,251,137,66,72,215,78,218,73,137,186,80,221,187,137,122,207,124,97,205,237,173,44,223,165,32,188,137,50,
251,48,220,189,7,108,13,217,156,55,190,119,206,15,54,78,129,103,80,104,10,125,66,219,211,183,174,43,0,176,174,34,73,58,203,210,108,187,123,220,110,158,54,219,245,126,243,168,116,108,91,63,195,14,223,222,
124,130,225,206,65,99,198,84,15,40,15,203,172,83,50,166,179,168,113,189,228,187,143,107,195,30,205,43,165,75,211,243,63,166,42,242,191,36,37,10,23,173,85,206,140,209,254,112,250,121,85,153,254,131,176,
116,162,89,30,46,129,59,15,179,28,161,74,20,70,166,96,118,64,179,23,249,14,156,188,67,81,17,247,120,107,96,89,18,78,229,156,114,135,232,197,230,60,164,162,163,184,25,110,244,102,142,14,116,214,147,252,
67,13,128,178,79,69,135,5,59,191,57,8,228,47,227,169,253,56,62,218,13,92,157,208,91,58,249,202,146,199,77,167,150,247,163,62,168,135,173,14,205,145,136,93,98,180,181,71,243,21,121,155,42,53,38,228,152,
22,37,237,53,38,124,131,166,39,158,78,6,219,62,161,55,160,178,64,233,59,5,0,192,47,18,110,44,98,175,52,127,18,138,250,150,39,102,174,155,106,185,88,100,217,34,77,23,179,217,205,122,243,184,219,174,55,
219,245,102,247,88,20,199,219,100,22,146,208,46,205,52,195,73,47,191,16,67,71,253,210,67,159,183,225,181,116,141,46,114,202,61,40,64,186,11,177,249,68,248,63,194,58,199,42,242,248,17,56,54,90,88,59,123,
16,206,100,51,127,29,161,168,191,93,51,212,254,163,165,78,99,47,199,195,46,169,49,53,113,159,163,117,41,167,135,87,234,142,174,107,209,13,66,218,25,84,228,45,128,14,134,110,246,55,122,244,243,122,36,29,
226,230,121,3,230,209,250,146,226,190,1,6,15,7,82,95,45,191,135,209,66,83,8,163,94,225,228,209,211,21,151,208,1,43,180,35,111,145,17,173,105,147,167,171,54,204,103,99,68,175,31,201,87,228,173,76,202,2,
178,147,142,178,23,183,58,159,65,225,147,158,62,108,119,152,203,173,197,111,11,148,39,60,13,171,249,190,29,192,139,246,221,101,35,124,82,34,40,205,135,81,252,41,150,47,138,125,18,167,81,148,70,73,150,
36,73,251,217,153,0,12,51,205,231,183,189,204,78,119,244,118,232,185,48,9,163,103,188,72,38,230,91,92,136,223,63,90,242,29,162,219,104,248,61,225,75,2,131,81,22,112,137,129,126,124,32,127,77,190,226,26,
0,253,219,100,66,59,218,166,95,11,67,225,146,123,211,168,194,169,183,220,122,160,12,21,163,189,156,251,104,197,105,8,88,30,121,199,208,115,188,134,30,214,154,206,35,233,16,64,207,227,102,239,26,129,177,
217,113,29,239,187,137,3,202,3,102,234,239,135,244,74,56,244,4,55,245,27,3,190,25,90,138,180,164,213,19,73,139,68,131,112,190,77,59,50,147,173,206,187,68,167,240,166,39,193,147,248,224,218,24,227,135,
143,158,106,71,198,88,123,209,54,222,183,45,76,246,139,15,70,45,181,47,225,59,62,153,237,52,36,159,12,181,111,172,133,218,96,3,218,204,170,251,92,221,141,78,137,223,35,66,93,151,82,234,52,91,164,233,108,
158,164,217,108,254,180,122,191,217,172,182,219,167,205,102,101,7,246,18,53,99,210,182,112,98,87,31,61,131,222,97,51,165,18,29,27,246,57,218,18,62,213,95,56,9,31,211,2,251,113,152,155,230,164,151,69,75,
83,148,115,40,233,191,186,45,7,166,66,215,169,79,61,85,246,249,181,195,249,190,10,245,35,80,244,124,228,62,133,162,221,172,69,231,224,132,184,57,22,212,119,148,79,99,34,124,152,0,83,234,201,137,206,36,
244,187,242,123,30,70,223,31,138,164,103,118,142,170,235,237,77,117,125,70,194,169,147,23,35,250,126,116,239,97,52,140,238,61,9,245,56,59,220,227,26,201,49,156,235,41,229,169,168,101,115,148,238,203,102,
175,242,116,141,73,182,82,68,66,72,196,246,168,250,44,164,149,219,19,181,89,83,79,51,91,45,18,27,68,130,118,236,132,27,146,224,88,103,48,19,52,108,153,247,76,9,164,148,254,100,10,154,11,236,234,210,158,
16,110,142,144,87,218,35,145,65,54,89,182,76,179,89,54,159,103,217,242,105,245,110,179,93,111,183,143,219,205,211,241,184,247,109,157,3,247,89,19,54,11,135,99,93,199,154,133,59,158,14,19,38,52,52,93,139,
255,0,218,117,165,225,200,89,48,61,103,26,114,177,29,126,74,99,127,241,253,76,191,243,203,52,124,244,111,127,37,165,61,79,0,235,7,75,250,71,15,254,199,210,98,238,226,248,25,3,239,147,236,169,215,203,52,
156,21,26,136,76,123,125,116,103,122,216,39,91,72,186,238,247,231,56,233,80,100,223,179,233,153,74,131,246,238,94,228,161,253,195,233,33,117,116,219,61,207,9,31,135,48,42,37,6,123,60,69,21,126,88,136,
175,89,123,14,235,132,68,237,240,9,59,70,130,217,115,73,116,105,1,182,222,34,174,208,36,132,96,34,91,79,7,43,59,117,250,164,83,157,29,192,134,255,28,68,244,232,115,8,174,191,8,157,158,244,244,174,156,
75,127,91,77,242,201,80,23,194,219,13,112,43,132,37,164,192,12,117,93,205,151,55,139,217,98,185,88,206,102,55,4,237,128,14,34,38,160,217,236,198,152,166,215,134,212,157,13,27,246,177,141,16,210,174,169,
87,175,220,121,222,189,9,96,124,54,231,85,240,241,161,151,244,152,181,37,78,60,236,28,223,28,144,77,188,186,108,114,158,135,246,89,216,52,25,135,143,232,248,252,40,60,229,143,59,248,103,20,78,87,131,232,
8,15,29,171,50,245,42,78,29,226,217,219,30,157,236,221,101,148,29,252,29,240,205,11,190,80,163,252,116,128,149,116,134,108,14,51,161,67,6,221,153,47,15,167,78,249,73,42,234,239,6,172,19,194,64,222,25,
47,157,68,63,126,195,103,66,173,131,156,83,14,217,200,218,216,210,144,49,174,255,156,193,102,54,29,234,73,0,227,176,207,219,232,133,129,185,240,205,63,238,253,184,255,182,47,65,136,210,166,80,157,176,
148,130,113,187,118,56,15,7,27,232,11,238,208,58,227,217,52,130,45,22,157,204,83,92,162,86,18,177,45,238,251,145,77,93,255,39,64,196,186,46,146,40,139,227,68,199,137,138,18,173,212,234,241,221,118,251,
180,94,63,174,215,79,82,74,154,232,78,235,10,152,204,4,21,229,144,192,142,85,150,120,204,109,100,216,150,115,109,232,250,177,108,232,170,96,124,212,243,105,12,37,241,236,75,252,10,73,201,49,59,184,191,
73,50,244,74,125,232,175,117,187,230,16,57,184,28,77,149,158,142,198,40,140,58,18,74,131,72,191,19,14,121,60,189,232,65,55,234,33,50,164,162,23,145,244,204,3,206,107,1,135,214,127,167,154,210,192,196,
254,2,140,250,154,82,183,145,169,15,163,225,134,39,161,65,51,59,248,20,164,75,164,182,44,207,19,16,23,35,27,34,116,45,158,40,132,173,35,217,198,164,182,93,221,169,251,69,208,53,232,83,171,236,101,69,182,
105,93,136,54,202,246,165,33,203,43,157,205,126,136,131,182,209,8,236,243,19,145,205,46,216,162,150,79,17,248,106,82,160,138,245,71,0,108,241,170,105,106,165,100,54,159,207,146,89,150,45,102,217,98,245,
248,176,217,62,110,214,79,219,245,170,40,143,89,186,24,244,191,155,46,134,134,249,208,145,112,126,108,240,22,77,228,67,97,232,31,58,214,165,195,191,238,117,60,97,123,113,97,4,208,121,179,140,161,97,232,
135,147,208,51,233,221,201,210,217,223,162,71,254,124,134,225,87,127,193,139,161,231,212,218,57,49,248,62,132,206,94,5,198,99,235,233,49,93,15,135,158,147,30,12,71,197,141,137,165,104,76,41,245,145,92,
245,34,128,246,14,200,73,219,20,54,119,78,37,140,166,18,163,61,232,156,134,81,28,50,83,107,192,236,139,45,206,192,201,162,152,13,165,133,27,107,213,73,71,18,89,128,19,0,198,149,119,208,41,7,108,169,170,
29,224,110,141,156,125,246,83,8,73,100,132,176,175,117,226,194,225,159,184,52,130,7,220,208,229,207,107,53,208,239,97,22,94,119,229,226,122,175,0,243,122,166,214,245,42,155,221,204,102,139,249,252,118,
57,95,54,166,193,118,78,47,51,66,154,204,2,115,89,51,96,160,35,60,212,143,55,232,201,236,47,201,220,122,210,104,190,40,93,58,103,215,254,49,62,108,83,73,207,51,119,47,211,204,81,235,229,15,37,163,215,
139,219,255,83,76,70,250,90,163,95,8,152,31,81,154,159,18,192,142,14,44,28,192,107,175,17,46,36,170,224,10,6,157,244,232,176,165,114,138,153,78,21,154,198,106,247,52,149,16,24,110,95,153,6,29,157,167,
116,42,46,133,4,115,168,124,10,26,150,224,12,140,6,100,211,207,131,227,32,168,111,205,222,93,122,209,155,111,218,160,216,206,4,13,231,142,216,194,186,253,0,109,157,199,182,39,217,214,38,79,54,109,245,
223,25,223,177,157,33,42,68,27,197,219,95,249,103,112,163,119,209,3,177,101,163,190,182,238,108,74,44,166,91,170,219,54,86,133,68,201,242,83,239,227,231,48,186,211,29,207,252,255,181,247,229,241,81,20,
105,255,213,221,147,153,100,38,115,37,33,144,4,194,29,32,42,114,137,171,175,34,130,226,177,138,108,184,20,87,22,1,193,11,84,22,89,69,14,79,188,16,86,94,69,23,241,98,5,239,8,40,176,2,2,27,20,4,103,247,
245,231,250,190,187,186,171,238,122,114,229,228,48,215,116,255,254,168,233,154,234,170,234,158,158,139,12,240,124,63,126,112,50,211,211,93,85,83,253,237,231,126,180,64,32,207,239,11,120,189,65,159,63,
160,34,212,208,80,93,95,95,91,87,87,75,117,139,165,59,34,24,220,241,228,95,220,159,139,126,135,116,80,96,82,63,77,154,130,168,220,102,101,131,102,44,85,215,248,108,127,150,53,213,121,221,92,178,14,138,
138,21,46,158,84,84,83,204,32,167,152,235,144,106,82,181,34,238,228,210,61,227,149,208,213,152,99,96,4,52,18,199,74,76,1,70,213,135,21,57,77,154,206,26,130,240,19,101,82,51,101,223,240,90,120,42,161,228,
203,8,164,116,95,79,59,26,189,132,44,99,242,41,11,99,196,78,74,140,155,36,230,137,22,66,137,115,70,175,102,20,117,196,171,42,38,56,82,88,79,213,181,114,21,139,168,152,164,104,45,30,247,8,161,189,16,84,
12,188,68,241,157,172,139,135,100,90,178,49,154,149,24,16,232,6,39,56,49,31,209,5,252,73,42,170,110,150,213,72,18,42,17,189,241,218,182,182,182,120,189,94,151,43,219,229,204,201,118,231,40,14,71,245,161,
253,13,13,213,245,245,53,117,117,135,116,207,126,180,208,44,230,79,134,43,41,191,124,24,251,148,140,28,106,16,66,185,234,77,154,69,108,147,125,59,96,50,100,97,198,167,54,51,17,45,77,162,199,137,67,237,
60,78,210,167,227,167,245,204,54,100,115,45,150,154,207,150,184,215,249,84,88,169,86,53,9,138,138,190,67,57,160,108,117,236,16,42,245,38,108,104,74,178,118,36,80,122,202,68,151,151,204,53,122,45,166,127,
201,194,221,132,244,116,113,157,98,136,122,27,209,160,73,233,15,218,213,163,139,129,146,46,57,70,76,159,8,33,28,33,132,253,227,216,71,143,195,76,195,97,73,150,37,221,87,30,73,7,34,238,126,221,170,45,233,
211,193,39,145,72,7,58,18,28,138,253,233,186,74,110,104,109,34,73,164,95,54,34,226,187,166,97,111,123,164,244,137,206,170,6,35,70,184,181,197,237,118,187,221,254,92,183,223,147,235,207,117,251,15,29,250,
169,161,190,166,166,190,166,190,246,208,177,159,143,186,156,57,36,155,141,105,174,29,14,171,70,38,53,152,71,117,93,158,87,228,217,42,162,164,70,142,200,12,106,85,105,216,102,220,98,188,90,100,92,220,103,
214,213,195,194,232,153,60,135,218,166,209,116,121,150,210,20,127,26,175,91,201,186,23,30,103,31,100,169,147,40,245,38,174,121,67,158,142,40,224,73,208,92,211,38,153,242,204,24,211,37,101,214,212,147,
151,45,162,177,77,154,177,146,37,173,173,11,101,79,251,52,74,181,183,36,191,68,52,14,84,150,37,93,56,141,188,161,170,42,157,8,175,23,181,83,245,244,33,124,206,72,104,17,174,96,130,195,230,37,41,18,60,
68,90,47,99,55,17,49,164,114,1,170,36,156,158,20,79,137,184,128,112,61,61,98,11,215,151,65,211,75,67,145,192,14,68,85,68,149,105,182,165,106,65,233,35,87,85,87,118,182,39,215,239,203,245,229,122,189,94,
95,176,181,181,25,203,157,146,22,214,52,213,153,229,162,123,108,113,110,247,40,117,98,45,158,104,247,84,163,152,176,89,162,167,201,166,209,248,78,115,102,129,77,169,106,161,110,78,118,22,202,190,205,236,
26,59,65,227,241,53,167,179,57,253,227,47,21,38,208,221,51,37,15,21,203,106,135,154,136,55,77,211,234,25,119,37,159,116,111,225,89,74,136,76,85,51,23,191,157,147,112,204,169,49,49,9,14,70,145,231,95,32,
99,57,81,251,52,74,89,82,36,58,145,9,159,146,144,44,254,63,69,214,209,98,104,68,96,196,138,60,126,29,14,171,56,2,148,120,111,112,84,147,94,99,148,116,232,140,70,248,115,81,253,18,125,90,124,69,44,219,
98,41,82,85,177,215,62,42,81,226,196,36,108,79,212,221,253,134,230,81,250,1,68,150,215,244,236,96,228,116,102,249,124,126,159,47,224,245,7,189,190,160,26,110,85,35,154,187,214,210,210,218,210,210,106,
44,240,165,82,110,162,8,123,210,106,187,206,161,17,249,148,39,92,161,31,201,88,125,86,179,236,46,103,223,0,170,165,226,30,182,203,167,49,89,32,153,16,72,123,100,170,37,192,56,105,19,78,181,100,158,91,
41,20,201,17,151,58,69,243,11,87,114,20,153,151,104,16,84,56,102,140,164,124,177,177,148,144,105,98,127,34,190,110,19,163,209,115,69,151,17,39,159,162,120,116,124,205,40,156,18,63,187,65,8,165,172,159,
88,85,143,152,23,177,116,137,29,80,186,69,21,7,114,226,116,38,76,109,50,233,59,143,131,165,72,89,41,42,69,149,80,36,206,118,71,148,12,78,126,84,73,47,147,170,81,143,16,68,218,120,232,81,26,132,104,232,
48,55,156,93,26,149,193,179,28,14,159,47,136,255,203,245,5,100,89,110,85,213,250,218,67,117,117,53,53,53,7,107,106,14,25,29,232,76,24,19,145,64,13,174,36,146,176,132,59,115,209,156,171,103,43,241,81,77,
209,130,99,162,252,206,152,221,229,82,207,11,118,40,47,102,39,116,251,188,105,83,8,51,83,88,227,161,200,244,74,166,118,122,35,39,60,125,155,207,21,230,210,220,211,87,51,81,243,5,135,241,218,189,153,115,
9,177,21,60,5,239,36,250,167,105,41,9,139,192,38,54,62,148,215,232,105,26,69,198,154,35,200,94,40,190,126,18,137,50,74,202,250,46,215,40,98,194,50,41,45,39,26,136,146,82,186,35,94,157,112,88,85,20,82,
172,36,18,177,47,203,145,234,30,152,58,233,73,145,202,178,164,121,189,254,67,74,244,111,70,156,66,38,130,57,17,57,105,253,197,80,205,4,191,19,53,4,107,173,62,183,55,59,219,237,114,121,114,178,221,89,178,
35,220,218,90,95,95,83,87,95,93,91,123,240,208,161,253,76,86,59,23,201,20,22,137,162,81,159,18,71,160,196,179,20,173,197,64,170,219,114,185,116,246,205,160,233,37,5,59,242,105,188,218,168,148,34,206,72,
102,250,199,61,116,244,56,153,17,68,148,106,109,11,210,44,98,161,204,203,232,153,201,161,72,216,84,49,133,2,102,44,163,1,107,165,101,124,74,108,35,79,100,236,241,201,177,164,41,111,82,133,50,217,50,37,
56,218,156,244,145,215,233,53,226,110,34,38,81,108,253,196,86,78,42,168,62,90,160,158,74,165,71,148,228,136,249,20,123,150,20,35,117,146,135,4,62,6,81,214,0,146,214,41,25,41,146,158,148,225,97,78,90,156,
234,209,87,170,177,147,146,166,106,154,223,23,244,120,131,94,159,223,231,11,184,61,190,112,75,107,109,125,117,93,221,161,186,186,234,131,7,127,162,203,50,9,43,137,16,246,212,51,59,105,50,85,185,216,38,
91,37,239,76,234,221,9,131,153,218,224,94,141,217,199,34,125,92,153,73,92,166,37,241,105,10,77,213,118,13,56,102,229,157,44,140,0,188,91,137,209,235,69,86,84,49,187,197,212,235,19,83,252,77,216,89,48,
12,7,167,200,211,242,151,193,191,68,211,168,80,169,143,182,88,51,70,227,211,113,182,164,37,142,158,38,47,233,1,64,145,216,82,172,98,147,178,29,84,156,41,150,167,16,214,245,113,71,16,20,41,5,173,96,78,
36,210,40,173,158,235,2,181,164,147,29,102,76,246,182,100,230,142,181,117,189,223,137,65,139,167,210,76,137,180,78,164,218,104,41,89,95,32,223,239,207,15,250,243,2,254,60,159,47,175,165,185,169,174,254,
80,93,125,77,93,221,193,125,251,246,133,195,45,92,119,57,38,23,158,17,66,163,65,245,164,229,150,46,150,170,198,30,220,76,11,16,164,247,233,102,131,153,204,45,161,109,38,233,196,67,145,82,162,95,76,33,
87,182,129,67,41,181,73,98,169,27,128,149,185,131,215,127,173,157,75,241,235,245,200,194,94,153,40,189,34,179,119,88,93,158,78,150,23,241,105,124,52,202,203,167,148,13,148,20,46,138,186,101,40,67,167,
76,242,103,244,48,38,141,46,246,76,105,235,81,10,51,86,179,167,101,94,214,52,161,143,71,35,133,236,232,92,85,66,145,196,194,128,51,226,245,170,75,68,133,143,92,66,255,215,224,156,209,165,90,9,33,41,16,
8,248,125,65,95,32,224,11,4,253,254,252,166,166,159,235,235,107,234,107,107,234,234,15,238,219,255,99,107,107,43,215,14,94,21,10,161,198,136,250,168,13,148,207,239,100,66,154,232,126,74,250,239,173,26,
163,65,153,206,60,169,33,80,155,197,107,210,70,1,233,19,75,181,228,216,246,100,208,229,173,7,16,75,20,213,236,168,246,49,229,80,36,10,194,183,239,116,50,211,253,109,24,91,133,130,48,34,245,67,73,46,144,
36,50,143,218,165,81,198,216,44,122,39,98,81,68,145,98,75,18,97,61,61,38,84,150,101,137,138,37,210,40,218,138,8,161,132,76,73,124,187,174,155,71,210,153,244,106,76,180,109,55,162,239,227,60,78,60,36,44,
150,226,244,36,234,14,212,168,162,191,26,169,86,71,107,244,228,162,212,206,208,162,70,9,77,243,7,243,252,254,130,96,176,192,239,207,11,250,243,154,155,27,235,235,107,106,107,171,107,235,14,29,216,247,
125,83,115,19,211,253,149,46,253,73,11,152,186,34,175,241,26,61,195,185,162,6,176,170,176,7,3,50,102,199,243,27,55,221,119,114,27,113,235,201,79,97,41,210,223,237,60,66,236,102,253,210,37,247,45,204,238,
54,93,246,54,249,84,104,202,76,224,29,51,35,44,226,106,5,56,140,38,63,51,26,69,140,181,212,132,70,37,122,125,72,115,33,242,185,110,9,149,244,162,247,26,137,163,212,121,16,139,150,88,239,214,72,94,16,73,
132,39,110,65,253,29,146,215,68,181,134,140,238,12,137,62,70,207,37,149,40,185,56,18,65,37,209,246,91,137,110,116,30,77,121,162,206,16,93,49,234,95,252,150,230,11,228,5,131,249,126,127,158,215,27,240,
123,3,205,205,173,181,181,53,245,117,7,235,234,170,15,236,251,161,177,169,81,143,32,214,40,238,163,101,201,86,74,246,36,25,241,180,58,47,172,96,79,159,77,88,116,89,156,22,98,191,10,81,170,110,93,163,145,
39,101,55,188,197,240,18,187,78,252,211,61,37,132,80,100,163,114,66,204,190,217,9,136,162,102,222,39,139,16,40,107,125,159,23,72,205,5,91,196,85,71,53,60,0,28,188,47,94,68,163,136,254,200,204,197,100,
172,242,169,25,227,162,162,201,248,88,94,211,52,137,54,32,202,50,34,37,236,116,121,19,7,114,70,75,105,233,39,140,170,210,186,7,9,233,62,34,68,183,54,193,45,228,104,87,18,206,83,34,55,21,81,207,121,105,
134,34,74,68,187,215,168,159,153,216,67,137,37,65,11,6,219,229,7,242,125,190,2,191,63,223,235,207,107,85,91,107,107,107,106,107,15,212,213,213,236,219,255,93,83,99,35,19,201,36,170,166,44,116,34,145,148,
164,48,35,183,82,153,157,97,97,13,90,190,111,45,179,35,99,18,232,241,188,111,147,16,39,143,155,115,41,163,229,80,190,102,80,186,23,193,186,176,172,153,115,201,204,135,153,128,151,201,134,118,143,236,113,
165,80,230,21,68,11,48,108,110,136,177,231,237,161,70,26,69,66,165,158,210,142,37,58,160,146,24,28,169,86,69,209,91,69,119,163,71,114,34,9,75,82,189,148,177,192,70,172,156,184,4,61,210,109,142,72,87,207,
9,229,105,122,234,39,29,203,73,58,139,32,100,44,65,175,7,195,75,20,143,144,154,243,228,12,180,81,213,176,72,36,178,45,66,253,146,20,12,20,248,131,249,62,127,126,32,16,240,230,6,144,218,90,91,91,93,91,
123,176,174,174,250,199,31,255,211,212,212,196,56,124,136,75,157,184,218,117,121,211,224,74,162,15,192,82,170,117,3,37,203,4,249,56,8,180,205,69,158,20,17,129,116,226,210,165,240,231,72,201,239,146,240,
218,198,28,134,232,253,152,13,235,5,190,77,115,55,148,89,32,84,12,6,52,99,79,235,55,205,44,9,244,24,152,154,35,81,129,203,142,109,84,168,194,27,173,159,204,58,226,14,72,145,209,96,5,156,26,40,110,77,44,
233,165,142,37,61,71,8,231,32,73,250,183,104,127,14,17,15,163,174,33,156,53,79,169,229,184,156,93,180,10,50,173,200,235,70,0,242,154,52,140,148,72,127,99,250,225,162,139,195,136,242,197,171,8,201,121,
193,252,64,94,126,48,152,231,15,20,100,101,185,106,235,14,34,132,106,107,171,107,107,15,125,255,253,55,205,205,205,92,11,45,83,63,18,71,163,108,172,168,206,191,26,85,48,84,80,230,206,216,135,22,113,177,
244,90,38,19,104,70,217,64,51,74,185,206,152,159,198,174,85,212,236,79,139,112,186,120,165,81,11,155,169,253,55,121,209,213,14,129,34,166,6,179,125,26,165,196,73,83,215,60,149,32,36,25,227,129,52,61,180,
30,183,232,192,46,29,77,247,38,17,199,17,29,218,73,42,46,107,122,111,225,40,105,146,81,145,43,170,170,134,131,240,137,17,19,143,80,150,163,182,78,93,187,103,138,78,74,180,144,75,154,56,209,142,123,34,
125,35,20,105,153,151,87,80,152,23,200,15,4,11,242,2,237,16,66,63,255,124,180,174,246,144,134,212,154,67,135,190,251,241,235,150,230,38,204,101,230,190,120,150,43,195,225,86,58,224,137,54,143,82,95,212,
168,194,245,164,94,9,221,28,145,200,164,136,233,205,112,18,16,232,241,164,215,140,90,144,204,25,76,60,37,101,99,210,40,138,55,230,41,94,5,63,46,223,20,50,143,249,231,175,43,204,151,143,77,163,76,50,168,
133,94,111,212,241,105,163,106,164,43,39,211,137,94,146,232,103,69,52,5,72,111,200,97,230,160,144,113,118,19,85,208,68,162,152,14,179,167,76,196,79,82,229,151,162,84,131,154,79,103,240,19,119,188,206,
170,81,63,146,162,56,10,10,219,7,124,249,129,64,65,208,223,14,211,91,93,221,129,154,218,234,112,184,245,187,111,191,110,105,109,214,12,93,12,196,37,65,105,139,39,225,83,163,46,31,61,76,111,76,24,166,79,
104,86,209,203,168,16,197,32,208,147,128,61,147,103,213,12,95,132,76,26,94,28,101,185,227,53,140,218,167,78,20,35,152,212,46,171,38,70,160,72,88,63,52,94,26,165,137,210,68,223,215,168,24,117,77,23,60,
37,44,123,82,145,155,180,142,172,81,252,21,29,27,201,185,148,229,232,148,240,9,73,161,123,124,114,172,164,227,94,73,186,209,128,102,207,168,154,79,183,44,166,154,154,69,6,166,103,1,32,99,32,173,170,105,
146,203,229,202,111,87,28,240,5,125,129,252,96,32,47,28,110,169,107,168,86,91,213,154,186,234,131,7,126,56,220,80,135,105,142,145,64,77,56,148,216,58,25,153,84,156,149,196,20,171,231,203,45,115,15,221,
83,154,64,81,234,171,35,3,135,198,215,218,192,66,50,141,229,166,143,79,38,53,99,79,51,241,211,218,44,96,135,190,217,154,35,198,73,218,162,81,19,243,168,32,160,140,68,116,146,175,144,190,152,250,152,72,
174,39,46,101,175,16,3,40,221,232,28,59,142,136,146,142,137,149,114,169,71,77,159,244,168,136,181,148,68,50,209,66,40,197,143,18,189,30,36,65,158,121,48,248,131,193,64,110,190,63,16,244,249,242,114,115,
131,173,173,225,218,186,3,245,53,181,170,26,254,241,199,111,142,30,59,66,217,34,13,29,226,68,237,61,88,163,39,35,120,114,4,170,209,89,73,84,171,66,218,23,207,186,227,233,78,12,167,26,129,158,68,79,2,237,
196,25,79,220,162,104,234,100,210,56,140,167,22,95,177,41,255,58,152,96,32,179,148,121,158,70,145,40,138,158,118,40,81,31,69,196,79,74,80,197,69,231,52,42,47,94,82,20,137,4,12,17,2,165,42,146,176,105,
15,252,239,71,251,226,233,40,78,61,58,74,162,3,6,176,119,139,238,122,70,159,158,137,141,69,84,149,126,73,82,242,243,11,243,243,219,231,228,120,2,254,60,77,66,117,117,7,52,77,173,173,173,174,62,184,175,
174,161,186,185,185,153,235,68,104,40,41,34,106,239,209,202,145,105,152,33,92,170,209,60,109,22,48,88,66,169,252,78,190,13,33,226,189,159,64,160,64,163,25,46,141,34,203,130,79,201,176,106,50,236,73,31,
192,198,54,137,148,122,100,38,111,154,9,164,28,201,106,180,34,79,180,111,61,159,18,81,54,59,85,81,112,238,166,66,170,89,235,129,250,180,213,85,163,178,57,163,44,41,226,68,67,245,19,66,181,204,59,36,128,
148,18,63,17,117,81,149,156,208,233,204,110,87,80,232,243,183,11,4,130,30,143,239,231,159,143,34,53,92,83,87,173,105,232,167,159,254,83,95,95,67,113,153,198,213,100,50,107,201,25,83,2,53,8,161,76,227,
79,146,20,111,94,91,36,250,60,107,147,202,76,128,83,85,20,69,49,203,6,90,248,151,204,120,51,94,35,105,202,63,101,14,112,240,138,60,95,249,141,183,75,138,244,122,51,147,147,68,169,234,204,191,40,26,95,
137,100,170,122,8,113,58,17,141,91,163,122,1,146,56,80,77,119,163,27,18,52,233,204,34,230,133,241,35,68,190,69,138,154,82,159,146,135,135,74,114,153,130,193,2,175,63,232,243,5,2,190,60,135,44,31,61,218,
80,95,95,163,170,234,161,67,63,213,213,215,52,55,53,49,173,223,152,194,160,38,149,153,4,133,69,184,138,203,6,15,18,109,6,37,29,62,168,124,36,182,105,18,16,232,73,198,162,39,16,173,199,236,135,106,222,
109,37,110,35,105,154,216,211,140,70,13,117,236,227,162,81,196,186,215,13,102,80,81,166,19,157,159,110,48,23,208,55,54,213,191,83,162,171,225,225,122,239,138,130,244,196,118,67,210,183,158,1,69,146,229,
233,99,100,61,146,73,210,93,237,50,237,94,48,10,161,56,166,138,68,254,19,218,141,72,160,46,151,43,47,175,40,63,63,47,59,219,227,241,4,16,82,171,107,15,132,195,106,117,245,129,134,134,186,163,71,27,140,
121,99,136,88,63,141,98,99,152,116,223,52,147,67,117,105,148,9,5,37,4,26,166,79,142,244,26,81,36,31,73,212,57,75,3,2,5,57,52,195,104,52,190,92,166,132,197,210,132,216,211,14,59,27,70,226,16,82,167,5,141,
34,113,238,60,95,13,158,225,86,154,43,233,34,240,136,202,101,34,205,59,35,234,179,158,59,143,84,21,235,248,26,93,148,94,151,28,201,73,36,42,8,137,156,95,163,13,155,84,227,114,18,159,100,144,61,137,22,
79,74,130,202,178,146,159,95,232,245,250,189,222,96,32,80,208,216,120,164,182,118,191,170,170,245,245,213,13,135,235,235,235,106,152,230,89,140,10,111,12,102,98,189,67,162,16,122,182,241,28,35,198,242,
93,179,169,104,80,54,255,215,218,12,10,28,10,28,122,124,164,227,152,134,209,152,146,105,42,172,165,118,117,115,51,222,52,43,149,98,106,15,181,67,163,200,178,126,51,61,2,225,49,56,214,146,184,143,136,16,
42,203,10,21,164,25,185,20,246,44,225,134,34,52,159,234,163,162,203,203,71,221,208,186,26,142,244,238,29,17,145,147,68,224,227,79,169,166,199,68,62,85,101,89,246,120,114,243,243,219,7,2,5,217,217,217,
8,73,53,53,251,17,66,245,245,7,143,28,61,82,171,183,241,16,18,168,49,32,212,208,249,221,210,30,42,116,193,135,25,235,167,177,60,168,69,78,39,104,241,192,161,153,50,176,184,252,75,49,237,164,118,42,63,
217,161,87,235,99,172,197,79,50,42,43,123,168,57,141,34,161,121,148,115,52,209,206,40,68,215,244,164,101,82,58,59,30,215,147,215,213,97,82,107,25,81,20,41,92,125,214,250,73,187,140,140,133,69,12,37,162,
137,72,139,181,120,242,14,102,207,96,176,157,59,55,215,235,9,200,178,220,216,248,51,66,232,224,193,253,71,143,53,28,110,168,197,34,38,98,43,110,97,122,51,40,242,84,186,145,38,236,134,100,52,137,242,77,
58,195,116,92,148,177,25,161,74,217,13,172,244,119,32,80,224,208,12,228,208,20,42,245,54,101,70,59,166,213,120,9,212,52,62,148,235,164,36,104,58,47,234,91,199,202,158,140,175,137,82,219,17,21,162,175,
82,101,61,53,93,222,140,90,69,53,77,197,157,230,244,2,37,146,222,26,40,218,166,73,146,228,162,162,78,71,26,26,142,53,30,37,101,240,233,114,121,136,106,4,175,15,44,82,196,4,69,251,145,72,178,172,120,60,
222,188,188,194,92,183,207,229,201,149,36,212,218,218,210,208,208,112,236,216,145,35,71,235,143,28,174,35,203,139,76,138,188,18,253,154,107,115,20,21,69,141,77,225,163,69,66,133,236,105,222,225,3,145,
232,125,32,80,224,208,19,81,163,79,64,169,79,64,175,183,175,149,91,188,176,176,42,56,248,9,8,133,80,132,16,247,154,238,180,33,96,82,202,36,138,76,120,157,9,200,87,245,158,198,42,78,84,199,246,80,236,86,
194,233,243,122,139,121,73,231,68,69,39,89,45,24,44,232,216,177,235,177,99,71,170,171,15,28,59,118,180,165,165,69,211,84,77,195,142,126,21,183,30,161,74,148,98,134,141,188,112,56,148,28,183,219,235,203,
203,117,251,157,217,174,28,87,118,107,115,83,67,93,109,83,203,209,198,99,199,234,235,107,91,90,154,184,135,129,184,133,0,195,122,76,129,37,198,173,100,164,84,171,106,76,228,79,198,244,73,196,82,36,42,
174,44,36,80,224,80,224,208,54,28,94,194,74,61,138,51,16,42,46,137,50,46,246,100,73,76,150,101,235,150,179,54,94,75,204,59,164,223,28,21,155,41,235,7,68,147,218,73,110,187,94,66,73,193,217,153,248,5,126,
41,73,178,162,40,146,36,203,178,162,40,178,254,66,209,63,114,200,58,60,30,175,223,27,12,22,22,121,178,93,138,226,104,9,135,127,62,122,184,177,177,169,165,165,185,181,53,172,170,173,100,12,248,91,138,195,
225,204,114,185,221,158,156,220,92,167,226,114,185,60,146,140,13,41,162,227,0,0,32,0,73,68,65,84,194,173,77,225,22,181,169,165,241,232,209,195,199,142,29,110,110,110,54,123,208,105,108,169,23,67,217,36,
51,26,165,36,208,40,141,138,84,120,85,232,149,210,147,145,12,215,69,108,58,60,16,40,112,232,201,163,212,219,161,209,100,56,49,94,94,230,95,75,84,246,186,41,141,154,177,167,241,24,137,225,77,33,135,82,
101,228,9,163,201,58,135,202,58,111,98,62,149,101,89,146,101,5,179,170,44,203,146,164,232,132,169,240,148,138,191,162,40,74,118,118,142,219,237,113,187,189,30,143,55,199,149,227,80,92,146,83,82,36,7,118,
88,41,138,164,34,135,34,33,73,210,144,170,132,53,53,140,90,194,205,173,205,77,141,141,45,141,205,141,77,45,45,205,116,15,3,254,151,230,233,147,14,125,199,194,50,233,90,204,84,89,230,98,236,197,236,137,
181,123,94,2,101,98,0,56,47,60,219,54,30,8,20,56,244,4,85,234,227,213,235,99,241,102,188,60,107,139,61,25,93,94,51,235,115,41,180,150,154,89,72,45,108,169,220,87,84,61,26,137,182,0,104,148,163,95,211,
52,137,168,199,122,239,226,232,127,76,197,63,85,213,20,69,83,85,181,177,241,231,230,230,230,134,134,122,76,172,138,226,112,56,28,138,226,80,20,135,172,200,18,146,233,242,195,122,19,118,68,203,227,124,
141,31,62,217,214,168,77,35,97,18,17,223,116,83,68,157,81,175,145,46,165,106,92,120,169,102,52,125,34,51,2,5,51,232,169,192,162,39,1,209,199,107,27,181,67,157,9,176,167,181,160,138,108,149,155,50,216,
67,53,70,32,181,166,81,11,11,41,50,134,52,233,39,151,245,102,33,116,89,60,77,143,61,50,52,67,214,109,124,132,85,181,112,56,140,171,219,17,218,66,8,41,138,3,33,77,85,195,8,225,170,163,18,54,125,146,26,
160,56,22,42,28,110,37,18,46,49,95,80,189,149,100,20,171,137,2,95,28,155,238,183,65,103,37,25,181,120,166,99,135,202,201,164,81,50,101,138,227,81,114,40,83,73,132,145,64,145,69,212,27,16,40,136,162,39,
28,147,218,215,235,81,60,129,165,113,177,173,77,246,68,140,95,94,40,144,242,94,38,36,114,58,197,100,82,134,85,69,100,26,241,149,99,170,197,102,62,157,230,34,85,235,117,185,47,210,242,147,184,193,101,89,
193,47,36,73,197,77,149,49,31,233,181,156,101,85,149,36,41,140,167,38,203,178,170,106,70,187,130,38,52,239,10,77,39,76,53,57,97,218,37,99,211,100,216,147,106,72,199,132,223,179,146,44,173,206,243,21,152,
128,64,129,64,79,252,161,198,221,102,57,214,159,201,202,170,49,25,147,255,211,97,50,177,56,244,122,19,86,141,193,164,204,107,189,169,28,113,184,203,132,29,36,73,35,254,116,132,36,89,70,186,142,175,170,
106,228,79,85,149,21,133,80,42,194,149,74,176,71,94,211,36,132,194,122,62,190,172,215,94,66,184,69,29,93,60,212,76,133,55,233,2,168,209,66,162,80,8,165,222,9,115,225,162,42,95,149,153,102,79,42,70,202,
112,93,146,222,106,159,64,129,67,129,67,51,214,242,144,128,109,212,190,154,111,91,156,76,156,64,17,83,251,46,46,26,181,33,144,34,75,237,30,49,127,234,113,245,42,85,168,73,213,243,139,36,28,240,164,203,
155,184,0,190,38,73,17,181,94,81,36,85,197,229,71,53,189,29,19,254,87,65,40,172,11,179,184,128,136,76,181,84,138,148,19,165,18,228,145,80,8,165,2,134,12,17,69,52,211,113,188,41,240,173,147,48,38,254,96,
230,60,66,2,213,69,93,201,162,102,23,16,40,216,67,79,62,219,40,138,167,219,157,125,77,60,73,246,140,218,67,205,105,20,89,232,245,49,45,164,200,216,251,147,102,82,19,177,20,233,145,155,154,30,36,31,181,
135,234,52,138,16,146,116,3,40,10,135,145,162,72,154,134,173,165,154,166,105,138,130,3,66,181,112,56,172,40,72,85,17,14,203,215,133,92,76,166,136,24,70,195,97,100,172,96,111,161,197,179,69,237,8,233,243,
66,168,137,140,201,118,239,48,6,129,34,242,117,134,64,49,165,210,198,4,32,80,16,66,79,166,49,219,164,209,148,91,75,147,54,29,32,68,231,122,34,177,71,37,6,147,10,57,209,228,79,250,218,196,11,79,235,209,
50,66,116,24,60,34,138,185,36,73,148,122,30,105,176,33,73,14,132,48,75,98,146,69,178,172,133,195,26,54,143,234,209,84,17,39,21,214,224,177,55,9,135,115,73,186,16,107,237,71,98,124,241,38,162,40,50,139,
232,20,146,41,197,158,12,5,71,59,202,113,114,168,65,16,70,162,82,52,118,126,111,0,48,233,137,110,30,77,94,223,183,115,167,216,187,149,56,123,168,137,64,42,86,237,121,153,52,22,183,106,84,17,79,141,42,
123,76,14,86,53,77,82,20,133,148,19,37,221,59,140,148,26,17,85,85,53,172,119,72,214,244,160,126,89,150,145,170,106,146,36,99,135,146,36,69,149,119,108,1,208,139,66,33,186,183,82,60,4,138,184,238,111,116,
65,16,38,182,201,144,247,105,228,80,193,23,249,190,114,198,138,118,200,36,60,24,8,20,56,244,228,49,68,196,211,185,62,238,172,167,4,216,51,166,25,193,193,31,109,78,163,40,94,38,53,227,86,170,51,157,65,
56,69,136,168,243,145,62,75,196,60,168,105,154,174,173,99,217,19,105,26,194,175,49,189,18,114,195,226,38,54,167,202,178,140,144,170,75,160,228,69,148,58,45,218,61,138,252,224,188,58,207,70,32,241,210,
40,31,39,207,177,167,192,255,46,108,120,45,202,227,4,2,5,147,232,41,161,218,199,169,245,199,205,140,9,219,19,28,102,95,179,41,144,10,105,215,216,191,147,149,73,141,87,161,171,223,71,10,136,144,48,123,
34,126,74,18,214,208,53,61,128,20,17,123,40,190,136,44,163,112,56,66,178,178,172,97,93,30,203,171,88,121,167,162,169,84,125,44,226,136,122,147,180,78,65,94,16,173,125,27,157,66,6,9,212,66,234,164,13,2,
102,93,176,205,58,17,2,129,130,40,122,114,15,62,46,129,212,38,111,218,22,51,109,177,167,41,135,198,171,215,155,209,174,136,91,85,90,6,52,231,214,72,169,80,100,168,131,169,226,186,159,132,88,49,117,226,
23,170,170,41,138,172,203,164,154,36,201,122,72,169,68,234,153,234,185,249,200,34,152,73,168,41,155,8,134,26,157,32,207,208,162,145,61,53,206,243,46,86,219,113,184,62,159,13,133,68,229,90,128,64,129,61,
79,65,2,77,82,54,79,57,129,26,196,49,179,143,45,62,180,254,10,253,93,34,147,210,28,74,154,117,208,17,239,56,107,158,174,75,130,139,146,48,133,72,140,249,245,228,95,250,91,50,95,223,132,142,106,98,42,0,
152,48,17,91,213,152,150,25,121,53,156,206,89,226,73,147,137,136,226,104,20,153,215,81,214,168,178,129,18,16,40,112,232,41,50,139,184,122,47,39,47,123,198,203,158,200,36,79,41,46,189,30,153,25,73,153,
111,233,25,156,136,41,219,76,72,129,54,152,226,54,112,152,238,100,153,72,151,97,76,196,122,29,60,236,163,143,104,250,84,207,15,25,135,130,170,170,70,103,115,154,17,168,29,69,30,153,198,54,209,221,147,
132,124,170,137,100,207,232,107,218,101,100,210,201,195,42,122,9,8,20,56,244,212,152,139,22,239,25,82,245,190,157,75,75,177,132,77,155,50,169,88,44,165,249,145,73,166,52,10,134,204,27,172,44,73,36,76,
166,188,19,126,129,45,158,70,174,148,169,92,120,58,53,94,138,57,107,154,170,140,250,187,153,109,212,16,24,47,180,114,50,178,39,93,6,148,9,87,178,38,80,58,68,12,8,20,104,244,164,153,80,242,179,142,215,
13,149,48,117,34,97,140,189,253,95,206,146,70,53,51,237,222,216,180,142,149,112,153,146,78,68,114,213,157,75,209,216,123,74,164,141,124,87,119,37,201,196,6,170,19,168,166,51,38,155,152,164,183,6,137,173,
200,27,235,201,105,162,214,73,188,53,83,179,102,79,51,187,170,80,127,23,90,102,45,45,15,0,96,207,147,147,64,211,177,98,169,90,76,201,182,152,137,226,57,210,170,108,51,163,80,83,29,222,89,165,155,49,98,
226,210,161,8,73,180,221,211,88,206,57,106,3,53,218,67,197,87,180,88,86,161,69,146,175,90,207,37,98,170,38,82,170,176,239,102,108,241,19,9,202,128,2,129,158,234,68,122,138,63,27,18,22,72,109,92,40,145,
239,74,241,243,99,124,7,147,174,238,220,87,4,26,61,67,157,140,34,79,116,118,250,125,164,251,166,232,3,48,171,162,104,17,104,41,38,123,10,105,212,134,85,84,88,136,68,101,107,52,155,216,58,237,137,159,145,
159,150,23,63,129,64,65,32,5,50,77,250,24,45,201,51,72,137,49,99,194,52,106,198,161,200,80,0,223,138,70,121,25,147,131,44,180,180,34,211,2,119,130,5,53,146,38,18,201,140,102,129,247,98,246,228,41,152,
57,63,138,149,255,110,150,9,6,0,246,4,14,77,19,129,38,200,161,9,48,169,245,87,152,150,33,60,141,50,26,61,166,93,11,165,94,248,39,201,130,103,62,98,216,217,98,168,66,218,50,83,234,53,222,92,26,91,85,103,
169,211,126,249,37,32,80,192,41,165,127,196,59,193,228,93,252,9,95,61,225,224,208,248,142,55,90,69,101,102,0,118,104,84,200,143,140,181,148,23,105,45,124,241,102,81,77,136,75,150,231,88,15,241,228,40,
20,81,17,219,45,142,81,222,227,16,63,1,128,83,103,63,156,64,4,26,131,67,147,145,73,173,9,75,212,19,84,230,105,212,168,212,11,172,165,196,36,202,16,43,50,122,174,132,209,160,49,57,84,72,118,76,188,61,18,
121,132,172,131,228,205,120,51,102,253,121,81,244,2,0,152,20,38,155,56,93,38,115,9,205,164,234,112,230,210,40,18,57,136,120,247,17,239,130,183,232,225,108,185,142,49,2,140,44,248,52,94,246,68,246,26,120,
88,119,124,2,0,161,192,124,19,227,208,196,46,17,55,135,38,207,167,136,115,139,155,177,155,144,70,245,119,12,125,234,105,98,181,163,194,199,28,121,76,141,30,153,56,154,204,121,19,153,229,188,67,251,35,
0,144,105,186,249,49,181,139,38,252,186,35,177,19,165,90,26,210,248,126,162,84,206,168,161,182,19,9,149,199,53,153,200,241,122,242,168,64,127,215,180,104,169,124,115,35,70,236,70,213,214,37,148,204,120,
214,130,55,109,18,168,48,125,22,0,236,9,4,154,9,203,158,248,61,153,140,118,111,34,24,138,165,81,234,48,94,26,69,150,241,243,241,9,161,102,4,106,201,131,154,185,101,51,149,236,153,18,61,0,0,236,121,42,
19,104,50,171,103,241,221,84,222,141,137,229,221,155,209,40,31,212,105,65,151,60,105,90,88,12,236,255,78,22,41,67,150,138,185,149,197,211,190,242,110,124,19,120,19,144,65,66,217,201,253,116,73,89,108,
83,250,36,83,59,52,74,18,228,173,11,151,88,31,128,44,253,90,214,107,103,230,98,178,230,214,120,217,19,197,83,152,11,152,20,0,236,153,81,4,154,250,123,50,153,164,123,33,253,9,133,74,11,38,141,105,40,72,
76,20,181,124,161,217,62,50,1,241,19,152,20,0,236,153,185,4,218,54,119,163,133,129,210,194,60,26,147,73,205,206,44,164,117,190,130,148,77,129,212,34,6,222,62,117,198,197,158,96,253,4,28,55,6,129,229,74,
132,208,218,144,67,237,211,168,181,152,105,205,188,241,50,145,101,85,36,91,242,105,170,216,19,104,20,0,4,10,28,154,60,141,198,96,210,184,148,119,155,21,155,236,208,159,240,117,92,45,173,227,253,81,129,
73,1,192,158,25,184,98,109,121,91,90,71,29,217,97,82,100,55,21,42,5,139,30,207,159,201,244,189,2,38,5,0,123,158,72,139,150,65,55,100,50,76,106,79,158,77,118,221,109,20,63,182,85,29,217,230,47,10,116,9,
0,110,205,124,100,214,93,106,143,70,217,97,167,156,61,227,148,31,227,144,49,227,14,155,0,26,5,0,129,2,135,166,74,93,141,73,166,233,224,157,184,186,86,165,163,121,11,208,40,0,8,20,56,52,221,76,26,123,46,
118,152,40,177,94,43,201,245,111,1,26,5,0,129,2,135,30,119,26,181,241,105,74,230,149,190,214,87,64,163,0,96,79,224,208,204,96,210,227,201,47,41,234,129,5,76,10,0,246,4,14,205,84,62,77,21,221,164,188,191,
32,48,41,0,216,19,56,244,196,99,82,216,205,0,0,0,56,52,35,40,21,72,19,0,0,156,156,28,154,38,62,5,210,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,116,163,83,167,30,247,222,251,210,230,205,251,119,237,106,92,182,108,83,97,97,9,172,9,108,0,0,0,96,11,35,70,
140,191,229,150,69,189,123,15,112,58,93,94,111,96,212,168,169,11,22,60,15,203,2,27,0,0,0,196,198,144,33,87,118,239,126,58,243,102,223,190,231,38,127,230,236,108,247,220,185,207,62,245,212,251,109,56,187,
76,24,67,134,143,54,125,27,0,0,176,15,249,4,29,247,25,103,252,226,243,207,247,124,245,213,231,204,251,159,127,254,113,146,103,46,46,238,90,81,49,109,203,150,55,246,239,255,174,173,102,151,9,99,200,240,
209,166,111,3,0,0,39,63,138,139,187,6,131,237,210,113,230,94,189,250,63,246,216,219,138,226,24,54,108,116,191,126,231,181,201,236,50,97,12,25,62,218,244,109,0,0,224,228,135,219,237,45,40,40,74,211,157,
249,214,91,127,199,78,137,138,138,233,109,245,120,104,243,49,100,248,104,211,183,1,0,128,83,2,157,58,245,72,139,81,67,86,94,124,113,247,133,23,254,10,33,84,88,88,82,94,62,232,248,79,45,19,198,144,249,
163,77,211,6,0,0,78,17,45,190,139,36,73,233,56,243,132,9,183,63,252,240,235,248,117,91,105,208,153,48,134,12,31,109,250,54,0,0,112,242,35,55,215,239,247,231,167,227,204,249,249,29,54,108,248,54,63,191,
3,66,168,99,199,238,62,95,222,241,159,93,38,140,129,65,97,97,73,105,105,207,204,25,109,250,54,0,0,112,74,160,180,180,44,77,103,94,176,224,133,177,99,111,70,8,185,221,222,142,29,187,183,201,236,50,97,12,
4,146,36,205,156,249,232,206,157,71,114,115,253,153,51,218,244,109,0,0,32,97,56,18,254,166,44,43,231,158,123,233,5,23,92,85,94,62,168,168,168,75,110,174,239,232,209,195,95,126,249,233,186,117,207,111,
218,180,90,211,180,212,14,180,83,167,30,251,246,253,39,29,75,208,187,247,128,238,221,79,123,240,193,169,178,44,151,148,116,253,231,63,63,51,59,178,111,223,115,174,190,122,230,192,129,67,3,129,130,35,71,
234,247,237,251,246,163,143,54,173,94,189,164,190,190,250,184,141,225,56,64,81,28,23,95,60,206,231,203,251,236,179,93,71,142,212,103,200,104,211,183,1,98,10,191,19,39,222,121,201,37,215,180,111,223,105,
255,254,239,254,244,167,53,175,191,254,223,53,53,7,78,41,154,152,50,101,222,77,55,61,96,113,192,191,255,253,143,49,99,250,0,159,198,129,17,35,198,175,91,247,213,178,101,155,134,13,27,93,80,80,36,203,74,
110,174,255,172,179,134,61,250,232,155,161,144,118,199,29,79,164,246,114,78,167,171,103,207,190,105,154,203,138,21,59,202,203,207,66,8,157,118,218,96,193,67,198,145,53,120,240,240,62,125,6,22,21,117,246,
122,3,111,189,245,247,101,203,54,186,221,185,57,57,158,243,206,251,229,134,13,223,174,88,177,35,221,99,56,158,200,202,114,14,29,58,74,81,28,79,63,189,249,150,91,22,101,200,104,211,186,1,44,48,100,200,
149,171,87,255,117,252,248,25,237,218,21,43,138,163,176,176,100,220,184,91,183,110,61,184,104,209,171,3,7,14,61,117,238,247,226,226,46,129,64,129,211,153,93,94,62,40,20,210,38,78,156,35,203,145,208,242,
236,108,119,89,217,153,131,7,15,7,86,180,191,155,179,23,45,122,117,227,198,239,7,13,186,80,120,192,140,25,143,252,246,183,191,79,237,69,207,58,107,152,80,223,92,178,100,93,146,185,49,195,134,141,158,55,
239,57,89,86,206,56,227,23,178,172,48,159,22,20,20,61,253,244,230,194,194,142,248,207,171,174,154,178,109,91,13,54,2,98,12,29,58,106,207,158,150,36,103,199,143,161,176,176,227,184,113,183,16,7,116,74,
102,106,147,170,6,13,186,16,59,109,54,110,252,254,146,75,174,137,119,197,18,48,26,240,83,99,166,111,182,1,18,59,185,253,165,152,55,239,185,167,159,222,204,91,96,43,42,166,127,242,137,42,92,156,227,99,
102,137,185,98,233,219,48,79,60,177,118,241,226,119,210,61,157,76,3,191,33,147,186,199,150,47,223,242,198,27,159,231,229,181,55,59,230,140,51,126,209,163,199,25,41,156,64,81,81,231,222,189,7,8,223,223,
190,189,118,216,176,138,100,166,243,202,43,127,41,41,233,54,112,224,80,161,183,183,180,180,103,113,113,87,242,188,221,180,233,135,171,174,154,66,31,208,175,223,121,175,191,254,183,36,151,148,25,131,44,
203,43,87,238,164,197,174,228,103,106,115,36,189,122,245,39,10,108,40,164,241,191,99,204,21,75,224,199,101,166,38,156,190,112,3,36,112,114,155,112,185,114,158,121,230,131,197,139,223,113,56,178,248,79,
251,244,25,120,235,173,15,183,213,253,108,115,197,210,177,97,6,12,24,178,117,235,193,212,102,55,28,159,189,157,12,248,229,77,10,247,222,251,210,166,77,63,88,151,198,17,110,59,251,40,41,233,198,60,148,
24,218,74,33,38,77,186,107,254,252,149,167,159,126,182,157,131,111,186,233,129,23,94,216,197,16,199,212,169,243,135,15,31,147,218,49,140,25,115,147,181,237,41,77,4,218,185,115,47,242,103,223,190,231,238,
221,219,234,116,186,108,174,152,44,43,179,103,63,153,146,145,240,211,79,223,6,48,195,67,15,173,121,241,197,221,78,103,182,240,211,220,92,127,146,155,220,108,171,167,106,197,210,67,37,202,154,53,159,94,
118,217,181,167,154,230,157,202,229,29,49,226,234,189,123,195,3,6,12,73,235,136,151,46,125,183,111,223,115,200,159,131,6,93,216,167,207,192,244,200,231,37,47,191,188,199,230,67,181,164,164,219,135,31,
30,37,98,26,33,26,236,155,78,225,24,124,190,224,234,213,127,117,185,114,142,51,129,50,46,239,209,163,111,172,172,252,194,254,138,93,120,225,175,254,240,135,237,244,59,137,5,60,241,211,79,223,6,48,195,
47,127,57,113,219,182,154,246,237,59,197,245,173,4,230,203,108,245,196,206,99,127,195,36,19,130,166,40,142,27,110,88,240,204,51,31,208,111,186,221,185,137,233,7,137,161,77,2,254,82,121,63,58,157,174,141,
27,191,187,243,206,101,214,66,111,94,94,251,65,131,46,84,148,216,238,126,73,146,238,184,227,9,102,81,134,12,25,249,155,223,252,142,62,97,74,158,0,194,107,61,248,224,234,115,207,189,204,230,25,150,44,89,
119,247,221,207,32,132,178,178,156,133,133,37,3,6,92,48,100,200,149,101,101,103,166,124,12,183,223,190,248,56,27,218,178,178,156,99,199,222,204,252,100,119,221,181,252,137,39,214,50,71,90,172,216,242,
229,91,70,142,188,158,86,208,118,236,168,51,147,227,44,192,76,63,85,27,192,62,220,110,239,150,45,7,70,143,190,49,94,133,52,222,249,50,91,61,225,243,216,220,48,9,255,34,24,239,189,247,159,80,72,227,255,
123,235,173,191,199,117,158,174,93,251,220,112,195,130,196,84,254,100,198,159,48,82,121,63,86,84,76,223,177,163,78,248,28,120,246,217,109,244,178,142,28,57,25,191,159,147,227,89,182,108,83,126,126,135,
91,111,125,120,253,250,111,150,47,223,66,204,73,203,150,109,10,133,180,221,187,155,186,116,233,77,63,235,230,207,95,57,111,222,115,239,190,251,111,252,206,168,81,83,3,129,130,242,242,179,254,240,135,237,
140,160,116,217,101,215,50,202,163,199,227,187,243,206,101,85,85,13,152,236,172,175,85,94,62,136,140,199,206,118,223,182,173,198,239,207,119,187,189,219,182,85,63,250,232,155,196,41,201,160,111,223,115,
214,172,249,159,247,223,255,137,49,159,197,28,131,203,149,243,224,131,171,23,47,126,103,219,182,234,21,43,254,188,98,197,142,21,43,118,220,117,215,114,126,166,5,5,69,139,22,189,70,63,219,238,190,251,153,
101,203,54,198,28,134,153,225,229,230,155,31,122,255,253,159,232,95,240,157,119,254,249,214,91,127,159,49,227,17,250,72,179,21,27,57,242,250,173,91,15,110,218,244,67,86,150,19,33,212,161,67,233,117,215,
205,30,48,224,130,55,223,252,63,114,140,217,78,32,83,51,155,190,217,6,176,179,8,54,119,8,131,235,174,155,189,110,221,87,246,125,101,194,249,198,28,30,191,213,133,231,41,44,44,89,190,124,11,253,197,152,
43,198,79,92,120,230,9,19,238,88,184,240,69,167,211,53,122,244,141,51,103,62,102,195,18,122,65,101,229,151,49,197,49,225,105,125,190,188,254,253,207,31,49,98,188,44,203,14,71,214,199,31,55,155,253,70,
194,125,18,215,248,19,187,59,248,179,89,44,111,226,120,241,197,221,102,107,221,161,67,105,187,118,197,89,89,206,165,75,223,173,172,252,130,152,138,230,205,123,110,218,180,133,62,95,208,120,203,77,94,191,
254,155,9,19,110,231,61,155,163,70,77,189,225,134,5,197,197,93,177,22,153,147,227,121,249,229,61,110,119,238,140,25,143,48,194,72,113,113,151,205,155,247,209,133,39,218,181,43,158,57,243,209,252,252,14,
87,94,57,233,201,39,55,196,188,214,147,79,110,96,212,40,179,96,114,183,59,119,195,134,111,39,76,184,29,255,57,113,226,156,61,123,90,186,117,43,231,143,236,214,237,180,17,35,198,223,116,211,3,11,23,190,
104,103,190,252,24,238,189,247,165,113,227,110,177,158,233,237,183,47,174,168,152,62,105,210,93,203,151,111,145,101,165,188,252,172,80,72,27,50,100,164,245,48,204,20,180,41,83,230,121,189,1,102,190,147,
39,223,19,10,105,87,94,57,201,122,180,133,133,29,71,140,24,95,88,88,50,113,226,28,44,82,149,148,116,91,181,106,175,207,23,44,44,236,184,126,253,55,228,200,183,223,254,7,191,19,248,169,205,158,253,36,61,
125,139,13,16,115,17,108,238,16,30,111,188,241,249,132,9,119,88,63,117,200,96,204,230,251,242,203,123,172,135,199,108,117,225,121,100,89,217,187,183,181,125,251,78,36,44,36,230,138,241,199,8,207,156,147,
227,9,133,180,190,125,207,205,207,239,176,116,233,187,110,119,174,245,62,201,201,241,84,86,126,25,51,150,43,39,199,243,202,43,127,225,79,235,247,231,207,159,191,114,252,248,25,72,47,82,99,54,29,158,49,
226,29,127,2,119,135,217,176,133,203,155,56,60,30,223,39,159,168,56,36,208,12,87,92,241,155,80,72,251,175,255,186,28,255,89,90,218,179,170,170,129,201,20,188,228,146,107,42,43,191,44,44,44,89,184,240,
197,103,159,221,70,171,108,231,159,127,197,156,57,79,201,178,114,246,217,23,227,113,79,157,58,255,190,251,94,118,58,179,215,172,249,52,39,199,67,139,117,143,63,94,121,253,245,119,147,119,178,179,221,75,
150,172,199,114,126,94,94,123,44,44,87,84,76,55,187,214,213,87,207,100,140,119,5,5,69,102,126,183,217,179,159,92,187,246,95,88,200,66,8,57,157,217,27,55,126,247,220,115,85,140,115,169,160,160,104,235,
214,131,107,215,254,107,202,148,121,228,41,50,97,194,237,246,199,48,120,240,69,161,144,198,56,43,152,153,22,22,118,124,247,221,127,95,124,241,184,49,99,110,250,237,111,127,47,203,202,213,87,207,188,255,
254,85,214,195,16,6,81,200,178,60,109,218,189,66,227,166,203,149,19,10,105,116,10,124,143,30,103,48,163,237,210,165,247,130,5,207,75,146,116,218,105,131,55,111,222,231,241,248,20,197,241,202,43,127,25,
49,98,60,66,232,188,243,126,185,120,241,59,103,159,125,113,118,182,251,142,59,158,8,133,52,62,103,148,153,90,207,158,125,183,110,61,72,79,127,234,212,249,191,250,213,13,252,6,56,255,252,43,94,127,253,
111,22,139,192,159,92,184,67,60,30,31,51,164,64,160,32,20,210,104,93,129,95,180,7,30,120,5,27,52,204,230,59,125,250,125,85,85,135,45,134,151,147,227,161,183,58,62,207,156,57,255,205,156,103,230,204,199,
66,33,141,118,235,197,92,49,230,24,69,113,172,89,243,233,168,81,83,153,51,191,251,238,191,151,44,89,151,155,235,31,61,250,70,114,195,34,132,204,110,240,187,239,126,230,158,123,86,196,100,137,73,147,238,
154,61,251,73,225,105,95,127,253,111,56,198,99,226,196,59,207,63,255,10,225,116,186,116,233,205,236,19,179,21,54,27,255,144,33,35,173,55,134,240,238,152,53,107,169,112,216,87,94,57,105,253,250,175,83,
226,60,140,144,119,40,164,89,60,175,70,141,154,186,119,111,235,178,101,155,200,59,11,22,60,255,235,95,255,214,248,132,236,186,121,243,190,206,157,123,245,234,213,127,207,158,22,218,152,56,116,232,168,
138,138,233,110,119,174,162,56,102,205,90,34,203,10,222,205,197,197,93,199,142,189,121,226,196,57,228,200,94,189,250,15,30,60,124,243,230,253,217,217,110,242,230,67,15,173,25,51,230,38,250,90,221,187,
159,30,10,105,102,215,90,184,240,69,90,36,204,203,43,60,239,188,95,10,231,117,250,233,103,239,221,27,190,232,162,177,244,155,151,95,254,235,80,72,99,174,56,119,238,179,131,7,95,196,184,89,226,26,195,182,
109,213,215,93,55,219,168,64,13,97,102,250,194,11,31,221,119,223,203,62,95,222,195,15,191,142,11,182,47,93,250,46,77,145,252,48,202,202,250,241,145,3,146,36,221,122,235,195,197,197,93,132,179,198,171,
71,71,95,220,115,207,10,227,104,219,175,95,255,181,203,149,83,80,80,84,89,249,229,244,233,247,33,132,198,141,187,229,237,183,255,129,31,45,195,134,141,246,120,124,171,86,125,178,97,195,183,235,214,125,
197,236,4,225,212,86,175,254,235,196,137,119,210,116,182,122,245,95,101,89,225,55,192,130,5,47,220,123,239,75,22,139,192,159,156,223,33,57,57,30,158,50,186,117,43,15,133,52,51,163,155,211,153,189,104,
209,107,68,27,51,155,111,101,229,23,214,195,27,57,114,50,189,213,199,141,187,37,20,210,138,138,58,51,231,25,56,112,232,239,126,247,244,188,121,207,217,92,49,254,24,124,102,108,119,34,103,174,170,58,188,
115,231,145,172,44,167,207,23,124,232,161,53,212,35,124,56,163,145,144,115,126,244,209,177,64,160,32,166,239,229,247,191,127,79,120,218,64,160,96,199,142,58,69,113,180,107,87,76,12,205,252,116,94,126,
121,15,179,255,133,43,108,49,254,135,31,126,221,122,229,249,187,99,208,160,11,67,33,77,120,182,37,75,214,51,227,73,10,185,185,254,61,123,90,186,118,21,228,114,149,150,246,188,237,182,199,23,44,120,254,
227,143,155,201,3,188,168,168,243,27,111,252,47,67,225,15,60,240,202,212,169,243,253,254,252,197,139,223,89,180,232,85,242,254,165,151,78,40,47,63,107,192,128,11,16,66,99,199,222,140,37,163,53,107,62,
197,73,50,149,149,95,18,93,166,188,252,172,220,92,255,138,21,59,166,77,91,72,179,79,85,85,67,73,73,55,250,241,245,252,243,31,154,93,171,176,176,99,85,213,97,178,39,186,116,233,141,181,12,225,61,243,246,
219,255,88,181,234,19,158,128,94,122,233,227,170,170,195,132,131,156,78,87,85,213,97,250,25,51,124,248,152,80,72,179,63,134,107,175,157,85,85,117,152,9,226,101,102,58,112,224,208,247,223,255,169,176,176,
164,71,143,51,176,209,167,115,231,94,180,105,175,95,191,243,152,71,221,240,225,99,46,191,252,58,126,106,179,102,45,177,136,232,194,131,39,94,38,60,59,122,180,149,149,95,92,122,233,132,252,252,14,119,223,
253,204,246,237,181,94,111,64,146,164,245,235,191,185,246,218,89,152,230,72,26,130,112,39,240,83,11,6,219,237,218,245,51,61,253,219,111,95,140,5,40,102,3,12,24,112,193,198,141,223,89,44,66,121,249,89,
239,189,247,159,152,59,68,248,252,240,249,242,246,238,13,211,49,94,212,163,232,204,53,107,254,231,206,59,151,225,91,218,108,190,101,101,253,172,135,119,209,69,99,177,145,4,111,117,73,146,66,33,109,206,
156,167,152,243,96,244,238,61,96,247,238,38,155,43,198,28,35,73,210,246,237,181,248,241,67,206,44,203,202,83,79,189,143,111,228,25,51,30,193,153,11,178,44,87,84,76,163,215,199,120,206,63,175,93,251,47,
179,173,82,88,88,50,108,88,133,245,105,203,202,250,45,90,244,106,94,94,251,115,207,189,212,108,3,148,149,157,73,155,1,205,86,216,226,66,195,134,85,88,175,60,127,119,140,24,49,62,20,210,132,103,235,220,
185,23,127,63,38,139,89,179,150,174,89,243,233,160,65,23,230,228,120,156,78,87,113,113,151,75,47,157,240,216,99,111,255,238,119,79,23,23,119,217,177,163,142,206,239,156,59,247,217,75,47,157,192,88,3,62,
254,184,249,236,179,47,30,56,112,232,135,31,30,197,150,53,89,150,39,76,184,189,99,199,238,21,21,211,156,78,215,197,23,143,11,4,10,122,246,236,123,229,149,147,54,111,222,231,112,100,149,148,116,11,133,
180,178,178,126,37,37,221,42,42,166,249,124,121,133,133,29,137,192,47,203,178,44,43,157,59,247,10,133,52,98,237,198,189,201,44,174,133,85,134,178,178,51,11,10,138,174,191,254,238,73,147,238,50,159,242,
18,218,58,65,227,180,211,6,239,221,27,94,185,114,39,126,200,151,150,150,133,66,218,192,129,67,179,179,221,103,159,125,241,194,133,47,94,124,241,184,184,198,128,223,113,187,189,248,137,85,90,90,198,204,
84,81,28,207,61,87,213,191,255,249,14,71,214,202,149,59,241,142,191,247,222,151,206,60,243,191,244,13,113,245,229,151,95,199,12,131,222,181,52,61,17,191,159,16,147,39,207,13,133,180,62,125,6,98,222,100,
70,59,109,218,194,15,62,56,212,191,255,249,147,38,221,181,113,227,119,88,29,195,191,84,105,105,153,203,149,67,23,18,229,119,2,182,72,48,63,34,51,253,51,206,248,69,101,229,151,252,6,240,251,243,99,46,194,
176,97,163,99,238,16,51,151,32,66,232,190,251,94,94,181,234,147,190,125,207,117,185,114,178,178,156,29,58,148,14,31,62,230,241,199,43,55,109,250,97,196,136,171,105,59,29,63,95,73,146,98,14,111,193,130,
231,233,173,62,97,194,237,204,121,112,95,128,64,160,192,237,206,189,227,142,39,112,116,68,204,21,227,55,76,105,105,79,126,132,231,156,115,9,150,182,92,174,156,170,170,134,252,252,14,253,251,159,127,207,
61,43,204,8,20,33,180,107,215,207,31,127,220,124,254,249,87,56,157,46,69,113,4,131,237,122,245,234,63,98,196,248,153,51,31,125,233,165,143,151,44,89,95,80,80,100,125,218,81,163,166,86,84,76,167,251,92,
241,211,225,247,137,112,133,205,46,212,177,99,247,4,238,142,89,179,150,154,13,155,95,222,20,112,168,44,203,99,199,222,252,199,63,134,62,252,240,232,238,221,77,149,149,95,222,121,231,50,44,120,206,158,
253,228,166,77,63,224,235,97,44,91,182,137,217,166,197,197,93,183,109,171,190,226,138,223,224,193,229,229,21,246,233,51,112,206,156,167,138,139,187,14,31,62,6,167,135,142,26,53,117,248,240,49,237,218,
21,23,21,117,198,230,33,183,219,187,126,253,215,248,70,197,207,40,175,55,80,89,249,101,65,65,81,97,97,71,108,213,202,202,114,62,243,204,7,23,92,112,85,48,216,174,176,176,99,118,182,219,226,90,216,39,176,
114,229,206,93,187,26,87,174,220,105,97,38,239,215,239,188,189,123,195,155,55,239,51,203,198,153,61,251,201,80,72,155,54,237,94,108,110,91,189,250,175,187,118,53,190,246,218,103,147,38,221,229,118,123,
227,29,67,78,142,167,178,242,139,135,31,126,125,196,136,171,241,15,207,204,180,83,167,30,56,131,246,194,11,127,133,61,230,129,64,193,158,61,45,5,5,69,229,229,131,230,206,253,67,121,249,32,126,24,252,176,
175,185,230,182,251,239,255,163,245,111,125,221,117,179,43,43,191,188,241,198,251,133,163,237,208,161,244,207,127,174,159,62,253,190,41,83,230,189,255,254,79,88,29,11,4,10,54,111,222,151,151,215,158,200,
140,102,59,65,248,35,50,211,55,219,0,118,22,193,206,14,177,118,25,77,158,60,247,181,215,62,195,220,177,113,227,247,75,151,190,123,213,85,83,24,151,180,112,190,49,135,55,99,198,35,204,86,231,207,227,112,
100,45,90,244,234,71,31,29,219,186,245,224,156,57,79,97,185,41,230,138,241,199,8,71,216,187,247,0,44,109,181,111,223,169,170,234,240,134,13,223,78,155,182,208,218,219,62,113,226,156,119,222,249,231,174,
93,63,127,242,137,26,10,105,123,247,182,110,220,248,253,227,143,87,142,27,119,75,135,14,165,49,79,123,219,109,143,207,159,191,146,233,59,192,79,135,223,39,113,141,63,177,187,195,98,216,252,242,166,17,
61,123,246,221,179,167,101,232,208,81,54,143,119,185,114,42,43,191,216,186,245,224,140,25,143,100,103,187,101,89,126,228,145,55,134,14,29,21,111,72,115,2,215,74,237,201,115,114,60,111,191,253,143,189,
123,195,195,134,141,110,147,49,248,253,249,155,55,239,219,186,245,224,236,217,79,218,143,61,126,243,205,255,51,139,64,136,215,188,179,125,123,109,188,113,148,41,71,98,139,208,38,195,11,4,10,210,183,213,
1,39,214,198,160,133,83,101,213,170,189,15,60,240,74,194,103,184,236,178,107,25,201,229,4,66,143,30,103,84,85,29,222,189,187,41,201,116,207,227,137,113,227,110,77,201,121,110,184,97,193,91,111,253,221,
78,50,5,224,36,216,234,128,116,97,242,228,123,214,173,251,42,97,185,198,237,206,181,142,197,203,124,156,117,214,176,157,59,143,124,242,137,122,219,109,143,11,197,204,76,107,92,17,211,193,106,7,30,143,
111,219,182,26,18,164,2,56,21,182,58,32,245,24,48,96,200,246,237,181,101,101,253,18,62,195,117,215,205,102,226,174,79,68,148,149,157,249,234,171,255,47,20,210,254,244,167,31,167,78,157,95,86,214,47,59,
219,237,116,102,151,149,245,187,228,146,107,108,22,52,57,177,48,101,202,188,229,203,183,194,45,112,170,109,117,64,42,209,189,251,233,91,182,28,176,111,6,229,129,243,91,78,142,213,144,101,101,248,240,49,
143,60,242,198,218,181,255,218,185,243,200,174,93,141,107,214,124,58,118,236,205,41,11,208,205,44,145,202,187,101,203,129,212,150,55,60,185,113,50,109,117,64,202,36,208,15,62,56,100,17,21,100,7,179,102,
45,73,137,115,3,112,156,49,121,242,220,100,19,135,79,242,79,59,213,0,0,1,252,73,68,65,84,49,192,86,7,160,220,92,127,113,113,87,89,86,74,75,123,206,158,253,228,71,31,29,75,50,141,180,87,175,254,147,39,
207,133,133,61,17,133,208,181,107,255,5,205,53,97,171,3,226,131,36,73,115,231,62,187,107,87,227,198,141,223,47,88,240,124,242,17,167,143,61,246,54,159,173,12,56,17,132,208,123,174,185,230,54,88,7,216,
234,128,182,196,144,33,35,233,52,47,192,9,36,132,190,240,194,71,16,207,4,91,29,208,150,80,20,199,170,85,159,128,143,242,68,196,77,55,61,112,206,57,151,192,58,192,86,7,208,144,143,243,245,70,143,158,254,
151,191,236,104,104,168,133,165,207,16,204,152,241,136,157,146,195,37,37,221,218,183,239,180,123,247,251,176,98,176,213,1,109,134,220,92,255,134,13,223,50,197,105,0,109,136,14,29,74,153,34,149,226,39,
173,44,223,127,255,42,112,37,193,86,7,180,177,28,58,117,234,252,29,59,214,86,87,239,131,117,207,16,96,246,140,153,193,125,237,181,179,42,43,87,212,215,87,195,138,193,86,7,180,25,186,119,63,125,199,142,
58,166,130,11,160,173,57,52,123,207,158,150,201,147,239,177,56,230,178,203,174,205,228,246,223,176,213,1,167,4,220,238,220,53,107,62,101,218,156,1,50,1,203,150,109,218,185,243,8,221,249,131,86,225,199,
143,159,49,120,240,112,88,37,216,234,128,182,68,183,110,167,173,88,177,227,158,123,86,164,188,0,29,32,121,244,236,217,183,170,234,240,158,61,45,119,223,253,204,128,1,67,188,222,128,195,145,85,84,212,121,
228,200,201,55,222,120,127,187,118,197,176,68,176,213,1,22,72,123,85,161,190,125,207,113,58,179,63,251,108,87,115,115,19,44,119,166,222,249,229,211,167,223,215,191,255,16,191,63,239,240,225,186,31,127,
252,38,20,218,254,222,123,171,190,254,250,127,97,113,96,171,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,169,192,255,
7,189,151,254,245,227,35,200,236,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* GraceSplash::grace_png = (const char*) resource_grace_png;
const int GraceSplash::grace_pngSize = 58074;

const char* SplashComponent::grace_png = (const char*) resource_grace_png;
const int SplashComponent::grace_pngSize = 58074;
