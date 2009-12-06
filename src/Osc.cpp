/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Osc.h"
#include "Console.h"
#include "Preferences.h"
#include "Scheme.h"
#include "lo/lo.h"
#include <iostream>

juce_ImplementSingleton(OscPort) ;

/*=======================================================================*
                               Liblo Interface
 *=======================================================================*/

static lo_server_thread loServer = 0;
static lo_address loTarget = 0;

void loErrorHandler(int num, const char *msg, const char *path)
{
  String text=T("OSC server error ");
  text << num << T(" in path ") << String(path) << T(": ") << String(msg) << T("\n");
  Console::getInstance()->printError(text);
}

void loInputHandler(const char *path, const char *types, lo_arg **argv, 
                    int argc, void *data, void *user_data)
{
  ((OscPort *)user_data)->handleMessage(path, types, argc, (void **)argv);
  //OscPort::getInstance()->handleMessage(path, types, argc, (void **)argv);
}

/*=======================================================================*
                            Osc Port Singleton
 *=======================================================================*/

OscPort::OscPort() 
  :
  traceInput (false),
  traceOutput (false),
  isHookActive (false),
  isOpen (false)
{

}

OscPort::~OscPort()
{
  close(true);
}  

int OscPort::open(String in, String out)
{
  String text;
  String sourcePort, targetHost, targetPort;

  if (isOpen) 
    return 0;
  int i=out.indexOfChar(':');
  if (i>-1)
    {
      targetHost=out.substring(0,i);
      targetPort=out.substring(i+1);
    }
  else
    {
      targetHost=T("localhost");
      targetPort=out;
    }
  sourcePort=in;

  //std::cout << "open -> sourcePort=" << sourcePort.toUTF8() << ",  targetHost=" << targetHost.toUTF8() << " targetPort=" << targetPort.toUTF8() << "\n";

  loServer=lo_server_thread_new(sourcePort.toUTF8(), (lo_err_handler)loErrorHandler);
  
  //std::cout << "  adding target host...\n";
  loTarget=lo_address_new(targetHost.toUTF8(),targetPort.toUTF8());
  //std::cout << "  adding server method...\n";
  lo_server_thread_add_method(loServer, NULL, NULL, 
                              (lo_method_handler)loInputHandler, 
                              this);
  //std::cout << "  starting server thread...\n";
  int flag=lo_server_thread_start(loServer);

  if (flag<0)
    {
      lo_server_free(loServer);
      loServer=0;
      lo_address_free(loTarget);
      loTarget=0;
      Console::getInstance()->printError(text);
      return flag;
    }
  isOpen=true;

  //std::cout << "  open!\n";

  // update preferences with current port
  Preferences::getInstance()->setIntProp(T("OscServerPort"), getServerPort()); 
  Preferences::getInstance()->setStringProp(T("OscTargetHost"), getTargetHost()); 
  Preferences::getInstance()->setIntProp(T("OscTargetPort"), getTargetPort()); 
  showStatus();
  return 0;
}  

int OscPort::close(bool force)
{
  if (!isOpen) 
    return 0;
  int flag=lo_server_thread_stop(loServer);
  if (flag<0 && !force)
    {
      return flag;
    }
  lo_server_thread_del_method(loServer, NULL, NULL);
  lo_server_thread_free(loServer);
  loServer=0;
  lo_address_free(loTarget);
  loTarget=0;
  isOpen=false;
  if (!force)
    showStatus();
  return 0;
}

int OscPort::getServerPort()
{
  return (isOpen) ? lo_server_thread_get_port(loServer) : 0;
}

int OscPort::getTargetPort()
{
  //std::cout << "getTargetPort -> " << lo_address_get_port(loTarget) << "\n";
  return (isOpen) ? String(lo_address_get_port(loTarget)).getIntValue() : 0;
}

String OscPort::getTargetHost()
{
  return (isOpen) ? String( lo_address_get_hostname(loTarget )) : String::empty;
}

bool OscPort::isValidPort(String text)
{
  if (text.isNotEmpty() && text.containsOnly(T("012345679")))
    return (text.getIntValue()>0);
  else
    return false;
}

bool OscPort::isValidHost(String text)
{
  if (text.isEmpty())
    return false;
  else if (text.containsOnly(T(".0123456789")))
    {
      if (text.matchesWildcard(T("*.*.*.*"), true))
        return true;
      else
        return false;
    }
  else if (text.containsOnly(T("0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz.-")))
    return true;
  else
    return false;
}

void OscPort::showStatus()
{
  String text=String::empty; 
  if (isOpen)
    {
      text << T("OSC open: server=") 
           << getServerPort()
           << T(", target=")
           << getTargetHost()
           << T(":") 
           << getTargetPort()
           << T("\n");
    }
  else
    {
      text << T("OSC closed.\n");
    }
  Console::getInstance()->printOutput(text);
}

int OscPort::sendMessage(String path, String types, Array<int> &ints,
                         Array<double> &flos,StringArray &strs, double time)
{
  //std::cout << "OscPort::sendMessage: path=" << path.toUTF8() << " types=" << types.toUTF8() << ":\n";
  if (!isOpen) return -1;
  int size=types.length();

  if (size>0)
    {
      lo_message msg=NULL;
      int I=0, F=0, S=0;
      int flag=-1;
      msg=lo_message_new();
      for (int i=0; i<types.length(); i++)
        {
          char t=types[i];
          switch (t)
            {
            case LO_INT32:
              // std::cout << "  int32: " << ints[I++] << "\n";
              flag=lo_message_add_int32(msg, ints[I++]);
              break;
            case LO_FLOAT:
              //std::cout << "  float: " << flos[F++] << "\n";
              flag=lo_message_add_float(msg, (float)flos[F++]);
              break;
            case LO_STRING:
              //std::cout << "  string: " << strs[S++].toUTF8() << "\n";
              flag=lo_message_add_string(msg, strs[S++].toUTF8());
              break;
            case LO_BLOB:
              {
                int siz=ints[I++];
                char data[siz];
                //std::cout << "adding blob size=" << siz << "\n";
                for (int j=0; j<siz; j++)
                  {
                    data[j]=(char)ints[I+j];
                    //std::cout << "  data[" << j << "]: " << data[j] << "\n";
                  }
                lo_blob blob=lo_blob_new(siz, data);
                flag=lo_message_add_blob(msg, blob);
                I+=siz;
                //std::cout << "  blob: " << "\n";
                //flag=lo_message_add_blob(msg, blob);
              }
              break;
            case LO_INT64:
              //std::cout << "  int64: " << ints[I++] << "\n";
              flag=lo_message_add_int64(msg, (int64)ints[I++]);
              break;
            case LO_TIMETAG:
              //std::cout << "  timetag: " << flos[F++] << "\n";
              {
                double f=flos[F++];
                lo_timetag tag;
                tag.sec=(juce::uint32)f;
                tag.frac=(juce::uint32)((f-tag.sec) * 4294967295.0);
                flag=lo_message_add_timetag(msg, tag);
              }
              break;
            case LO_DOUBLE:
              //std::cout << "  double: " << flos[F++] << "\n";
              flag=lo_message_add_double(msg, (double)flos[F++]);
              break;
            case LO_SYMBOL:
              //std::cout << "  symbol: " << strs[S++].toUTF8() << "\n";
              flag=lo_message_add_symbol(msg, strs[S++].toUTF8());
              break;
            case LO_CHAR:
              //std::cout << "  char: " << strs[S++].toUTF8() << "\n";
              flag=lo_message_add_char(msg, strs[S++][0]);
              break;
            case LO_MIDI:
              //std::cout << "  midi: " << ints[I] << ", " << ints[I+1] << ", " << ints[I+2] << ", " << ints[I+3] << "\n";
              juce::uint8 midi[4];
              for (int j=0; j<4; j++)
                midi[j]=(juce::uint8)ints[I+j];
              flag=lo_message_add_midi(msg, midi);
              I += 4;
              break;
            case LO_TRUE:
              //std::cout << "  true" << "\n";
              flag=lo_message_add_true(msg);
              break;
            case LO_FALSE:
              //std::cout << "  false" << "\n";
              flag=lo_message_add_false(msg);
              break;
            case LO_NIL:
              //std::cout << "  nil" << "\n";
              flag=lo_message_add_nil(msg);
              break;
            case LO_INFINITUM:
              //std::cout << "  INFINITUM" << "\n";
              flag=lo_message_add_infinitum(msg);
              break;
            default:
              break;
            }
          if (flag<0)
            {
              return -1;
            }
        }
      return lo_send_message_from(loTarget,
                                  lo_server_thread_get_server(loServer),
                                  path.toUTF8(),
                                  msg);	 
    }
  else
    return lo_send(loTarget, path.toUTF8(), NULL);
}

void OscPort::handleMessage(const char *path, const char *types, int argc, void **data)
{
  lo_arg **argv=(lo_arg **)data;
  String text = String(path).quoted();

  //std::cout << "path: <" << path << ">\n";
  for (int i=0; i<argc; i++)
    {     
      //std::cout << "arg " << i << " '" << types[i] << "':\n";
      //lo_arg_pp((lo_type)types[i], argv[i]);
      //std::cout << "\n";
      
      text << T(" ");
      char t=types[i];
      switch (t)
        {
        case LO_INT32:
          text << argv[i]->i32;
          break;
        case LO_FLOAT:
          text << argv[i]->f32;
          break;
        case LO_STRING:
          text << String(&argv[i]->s).quoted();
          break;
        case LO_BLOB:
          {
            int siz=lo_blob_datasize((lo_blob)argv[i]);
            char* dat=(char*)lo_blob_dataptr((lo_blob)argv[i]);
            text << T(":b (");
            for (int j=0; j<siz; j++)
              { 
                if (j>0) text << T(" ");
                text << (int)dat[j] ;
              }
            text << T(")");
          }
          break;
        case LO_INT64:
          text << String(argv[i]->i64);
          break;
        case LO_TIMETAG:
          {
          }
          break;
        case LO_DOUBLE:
          text << argv[i]->f64;
          break;
        case LO_SYMBOL:
          text << String(&argv[i]->s);
          break;
        case LO_CHAR:
          text << T("#\\") << String(argv[i]->c);
          break;
        case LO_MIDI:
          text << T(":m (") << argv[i]->m[0]
               << T(" ") << argv[i]->m[1]
               << T(" ") << argv[i]->m[2]
               << T(" ") << argv[i]->m[3]
               << T(")");
          break;
        case LO_TRUE:
          text << T("#t");
          break;
        case LO_FALSE:
          text << T("#f");
          break;
        case LO_NIL:
          text << T(":N");
          break;
        case LO_INFINITUM:
          text << T(":I");
          break;
        default:
          break;
        }
    }
  //std::cout << "\n";

  if (isHookActive)
    {
      String lisp=T("(osc:call-hook '("); 
      lisp<<text<<T("))");
      Scheme::getInstance()->eval(lisp);
    }

  if (traceInput)
    {
      text << T("\n");
      Console::getInstance()->printOutput(text);
    }
}

/* ==============================================================================
                                     OSC Open Dialog
  =============================================================================*/

class OscOpenDialog : public Component, 
                      public ButtonListener,
                      public TextEditorListener
{
public:
  OscOpenDialog();
  ~OscOpenDialog();
  void resized();
  void buttonClicked (Button* buttonThatWasClicked);
  void textEditorReturnKeyPressed(TextEditor& editor);
  void textEditorTextChanged(TextEditor& editor){}
  void textEditorEscapeKeyPressed(TextEditor& editor){}
  void textEditorFocusLost(TextEditor& editor){}
private:
  GroupComponent* serverGroup;
  GroupComponent* targetGroup;
  TextButton* openButton;
  Label* serverPortLabel;
  Label* targetHostLabel;
  Label* targetPortLabel;
  Label* serverProtocolLabel;
  TextEditor* serverPortEditor;
  TextEditor* serverProtocolEditor;
  TextEditor* targetHostEditor;
  TextEditor* targetPortEditor;
};

void OscPort::openDialog()
{
  DialogWindow::showModalDialog(T("Open OSC Connection"),
				new OscOpenDialog(),
				NULL,
				Colour(0xffe5e5e5),
				true);
}


OscOpenDialog::OscOpenDialog ()
  : serverGroup (0),
    targetGroup (0),
    openButton (0),
    serverPortLabel (0),
    targetHostLabel (0),
    targetPortLabel (0),
    serverProtocolLabel (0),
    serverPortEditor (0),
    serverProtocolEditor (0),
    targetHostEditor (0),
    targetPortEditor (0)
{
  addAndMakeVisible(serverGroup = new GroupComponent(String::empty, T("Server")));
  addAndMakeVisible(targetGroup = new GroupComponent(String::empty, T("Target")));
  
  addAndMakeVisible(serverProtocolLabel=new Label(String::empty, T("Protocol:")));
  serverProtocolLabel->setFont (Font (15.0000f, Font::plain));
  serverProtocolLabel->setJustificationType (Justification::centredLeft);
  serverProtocolLabel->setEditable(false, false, false);
  serverProtocolLabel->setEnabled(false);
  
  addAndMakeVisible(serverProtocolEditor = new TextEditor(String::empty));
  serverProtocolEditor->setMultiLine(false);
  serverProtocolEditor->setReturnKeyStartsNewLine(false);
  serverProtocolEditor->setReadOnly(true);
  serverProtocolEditor->setScrollbarsShown(true);
  serverProtocolEditor->setCaretVisible(true);
  serverProtocolEditor->setPopupMenuEnabled(false );
  serverProtocolEditor->setSelectAllWhenFocused(false );
  serverProtocolEditor->setColour(TextEditor::textColourId, Colours::grey);
  serverProtocolEditor->setText (T("UDP"));
  serverProtocolEditor->setEnabled(false);
  serverProtocolEditor->setReadOnly(true);
 
  addAndMakeVisible(serverPortLabel = new Label(String::empty, T("Port:")));
  serverPortLabel->setFont(Font (15.0000f, Font::plain));
  serverPortLabel->setJustificationType(Justification::centredLeft);
  serverPortLabel->setEditable(false, false, false);

  addAndMakeVisible(serverPortEditor = new TextEditor(String::empty));
  serverPortEditor->setMultiLine(false);
  serverPortEditor->setReturnKeyStartsNewLine(false);
  serverPortEditor->setReadOnly(false);
  serverPortEditor->setScrollbarsShown(true);
  serverPortEditor->setCaretVisible(true);
  serverPortEditor->setPopupMenuEnabled(true);
  int port=Preferences::getInstance()->getIntProp(T("OscServerPort"), 57100);
  serverPortEditor->setText(String(port));
 
  addAndMakeVisible(targetHostLabel = new Label(String::empty, T("Host:")));
  targetHostLabel->setFont(Font(15.0000f, Font::plain));
  targetHostLabel->setJustificationType(Justification::centredLeft);
  targetHostLabel->setEditable(false, false, false);

  addAndMakeVisible(targetHostEditor = new TextEditor (String::empty));
  targetHostEditor->setMultiLine(false);
  targetHostEditor->setReturnKeyStartsNewLine(false);
  targetHostEditor->setReadOnly(false);
  targetHostEditor->setScrollbarsShown(true);
  targetHostEditor->setCaretVisible(true);
  targetHostEditor->setPopupMenuEnabled(true);
  String host=Preferences::getInstance()->getStringProp(T("OscTargetHost"), T("localhost"));
  targetHostEditor->setText(host);
  targetHostEditor->setCaretPosition(0);
  
  addAndMakeVisible(targetPortLabel = new Label(String::empty, T("Port:")));
  targetPortLabel->setFont(Font(15.0000f, Font::plain));
  targetPortLabel->setJustificationType(Justification::centredLeft);
  targetPortLabel->setEditable(false, false, false);
  
  addAndMakeVisible (targetPortEditor = new TextEditor(String::empty));
  targetPortEditor->setMultiLine(false);
  targetPortEditor->setReturnKeyStartsNewLine (false);
  targetPortEditor->setReadOnly(false);
  targetPortEditor->setScrollbarsShown(true);
  targetPortEditor->setCaretVisible(true);
  targetPortEditor->setPopupMenuEnabled(true);
  port=Preferences::getInstance()->getIntProp(T("OscTargetPort"), 57110);
  targetPortEditor->setText(String(port));
  
  addAndMakeVisible(openButton = new TextButton(String::empty));
  openButton->setButtonText(T("Open"));
  openButton->addButtonListener(this);
  
  serverPortEditor->addListener(this);
  targetHostEditor->addListener(this);
  targetPortEditor->addListener(this);
  setSize (384, 144);
}

OscOpenDialog::~OscOpenDialog()
{
  deleteAndZero (serverGroup);
  deleteAndZero (targetGroup);
  deleteAndZero (openButton);
  deleteAndZero (serverPortLabel);
  deleteAndZero (targetHostLabel);
  deleteAndZero (targetPortLabel);
  deleteAndZero (serverProtocolLabel);
  deleteAndZero (serverPortEditor);
  deleteAndZero (serverProtocolEditor);
  deleteAndZero (targetHostEditor);
  deleteAndZero (targetPortEditor);
}

void OscOpenDialog::resized()
{
    serverGroup->setBounds (8, 8, 184, 96);
    targetGroup->setBounds (199, 8, 185, 96);
    openButton->setBounds (152, 112, 96, 24);
    serverPortLabel->setBounds (16, 64, 48, 24);
    targetHostLabel->setBounds (207, 32, 56, 24);
    targetPortLabel->setBounds (207, 64, 48, 24);
    serverProtocolLabel->setBounds (16, 32, 64, 24);
    serverPortEditor->setBounds (88, 64, 88, 24);
    serverProtocolEditor->setBounds (88, 32, 88, 24);
    targetHostEditor->setBounds (256, 32, 112, 24);
    targetPortEditor->setBounds (256, 64, 88, 24);
}

void  OscOpenDialog::textEditorReturnKeyPressed(TextEditor& editor)
{
  openButton->triggerClick();
}

void OscOpenDialog::buttonClicked (Button* buttonThatWasClicked)
{
  bool ok=true;
  if (buttonThatWasClicked == openButton)
    {
      String sp=serverPortEditor->getText().trim();
      String th=targetHostEditor->getText().trim();
      String tp=targetPortEditor->getText().trim();
      if (! OscPort::isValidPort(sp))
        {
          PlatformUtilities::beep();
          serverPortEditor->grabKeyboardFocus();
          serverPortEditor->setHighlightedRegion(0,10000);
          ok=false;
        }
      else if (! OscPort::isValidHost(th) )
        {
          if (th.isEmpty())            
            {
              th=T("localhost");
              targetHostEditor->setText(th);
              //              targetHostEditor->grabKeyboardFocus();
              targetHostEditor->setHighlightedRegion(0,10000);
            }
          else
            {
              PlatformUtilities::beep();
              targetHostEditor->grabKeyboardFocus();
              targetHostEditor->setHighlightedRegion(0,10000);
              ok=false;
            }
        }
      else if (! OscPort::isValidPort(tp))
        {
          PlatformUtilities::beep();
          targetPortEditor->grabKeyboardFocus();
          targetPortEditor->setHighlightedRegion(0,10000);
          ok=false;
        }

      if (ok)
        {
          int flag=OscPort::getInstance()->open(sp, th+T(":")+tp );
          if (flag<0)
            Console::getInstance()->printError(T("OSC port failed to open with status ") + String(flag) + T("\n"));
          else
            {
              DialogWindow* dw=findParentComponentOfClass((DialogWindow*)0);
              if (dw != 0)
                dw->exitModalState(1);
            }
        }
    }
}
