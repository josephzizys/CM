/*=======================================================================*
  Copyright (c) 2009 Rick Taube.                                        
  This program is free software; you can redistribute it and/or modify  
  it under the terms of the Lisp Lesser Gnu Public License. The text of 
  this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Osc.h"
#include "Console.h"
#include "Preferences.h"
//#include "Scheme.h"
//#include "lo/lo.h"
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
  text << num << T(" in path ") << String(path) << T(": ") 
       << String(msg) << T("\n");
  Console::getInstance()->printError(text);
}

void loInputHandler(const char *path, const char *types, lo_arg **argv, 
                    int argc, void *data, void *user_data)
{
  ((OscPort *)user_data)->handleMessage(path, types, argc, (void **)argv);
  ////((OscPort *)user_data)->handleMessage2(path,types,argc,(void **)argv);
}

/*=======================================================================*
                            Osc Port Singleton
 *=======================================================================*/

OscPort::OscPort() 
  :
  traceInput (false),
  traceOutput (false),
  //  handle (NULL), 
  //  cloned (NULL),
  //  hook (NULL),
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

  loServer=lo_server_thread_new(sourcePort.toUTF8(), 
                                (lo_err_handler)loErrorHandler);
  
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
#ifdef GRACE
  Preferences::getInstance()->setIntProp(T("OscServerPort"),
                                         getServerPort()); 
  Preferences::getInstance()->setStringProp(T("OscTargetHost"),
                                            getTargetHost()); 
  Preferences::getInstance()->setIntProp(T("OscTargetPort"),
                                         getTargetPort()); 
#endif
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
  return (isOpen) ? String(lo_address_get_port(loTarget)).getIntValue() : 0;
}

String OscPort::getTargetHost()
{
  return (isOpen) ? String(lo_address_get_hostname(loTarget)) : String::empty;
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
      text << T("OSC open, server=") 
           << getServerPort()
           << T(", target=")
           << getTargetHost()
           << T(":") 
           << getTargetPort()
           << T("\n");
    }
  else
    {
      text << T("OSC closed\n");
    }
  Console::getInstance()->printOutput(text);
}

/*=======================================================================*
                               Sending Osc
 *=======================================================================*/

/* int OscPort::sendMessage(String path, String types, Array<int> &ints, Array<double> &flos,StringArray &strs, double time)
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
*/

int OscPort::sendMessage(String path, lo_message msg)
{
  return lo_send_message_from(loTarget,
                              lo_server_thread_get_server(loServer),
                              path.toUTF8(),
                              msg);
}

int OscPort::sendBundle(lo_bundle bndl)
{
  return lo_send_bundle_from(loTarget,
                             lo_server_thread_get_server(loServer),
                             bndl);
}

/*=======================================================================*
                               Receiving Osc
 *=======================================================================*/

void OscPort::handleMessage(const char *path, const char *types, int argc, void **data)
{
  SchemeThread* st=SchemeThread::getInstance();
  bool isHook=st->isOscHook();
  if (! (traceInput || isHook))
    {
      //std::cout << "no osc hook\n";
      return;
    }
  lo_arg **argv=(lo_arg **)data;
  String text = String(path);
  bool flag=true;
  XOscNode* node=new XOscNode(0.0, text, String(types));
  //std::cout << "handleMessage " << path << " " << types << "\n";
  for (int i=0; i<argc && flag; i++)
    {     
      char t=types[i];
      switch (t)
        {
        case LO_INT32:
          node->ints.add((s7_Int)argv[i]->i32);
          break;
        case LO_INT64:
          node->ints.add((s7_Int)argv[i]->i64);
          break;
        case LO_FLOAT:
          node->flos.add((double)argv[i]->f32);
          break;
        case LO_DOUBLE:
          node->flos.add(argv[i]->f64);
          break;
        case LO_TIMETAG:
          {
            double t=argv[i]->t.sec + (argv[i]->t.frac/4294967295.0);
            node->flos.add(t);
          }
          break;
        case LO_STRING:
          node->strs.add(String(&argv[i]->s));
          break;
        case LO_SYMBOL:
          node->strs.add(String(&argv[i]->S));
          break;
        case LO_CHAR:
          node->ints.add(argv[i]->c);
          break;
        case LO_MIDI:
          {
            for (int m=0; m<4; m++)
              node->ints.add(argv[i]->m[m]);
          }
          break;
        case LO_BLOB:
          {
            int s=lo_blob_datasize((lo_blob)argv[i]);
            char* b=(char*)lo_blob_dataptr((lo_blob)argv[i]);
            node->ints.add(s); // add size then data
            for (int j=0; j<s; j++)
              node->ints.add(b[j]);
          }
          break;
        case LO_TRUE:
        case LO_FALSE:
        case LO_NIL:
        case LO_INFINITUM:
          break;
        default:
          flag=false;
          break;
        }
    }
  if (!flag)
    {
      String msg=T("OSC: dropped non-numeric message (path ");
      msg << text.quoted() << T(")\n");
      Console::getInstance()->printWarning(msg);
      delete node;
      return;
    }

  if (isHook)
    SchemeThread::getInstance()->addNode(node);
  if (traceInput)
    {
      String msg=text.quoted();
      for (int i=0; i<argc; i++) 
        switch (types[i])
          {
          case 'i':
          case 'h':
            msg << T(" ") << String((juce::int64)node->ints[i]) ;
            break;
          case 'f':
          case 'd':
            msg << T(" ") << String((double)node->flos[i]) ;
            break;
          }
      msg << T("\n");
      Console::getInstance()->printOutput(msg);
    }
}

/*
//  s7 cloning doesn't work :(
void OscPort::handleMessage2(const char *path, const char *types, int argc, void **data)
{
  lockHook();
  //  s7_scheme* sc=(s7_scheme*)NULL;
  //s7_pointer hook = NULL;
  s7_scheme* sc=cloned;
  if (hook!=NULL)
    {
      lo_arg **argv=(lo_arg **)data;
      s7_pointer snil = s7_nil(sc);
      // head holds first cons cell of the message data
      s7_pointer head = s7_cons(sc, s7_make_string(sc, path), snil);
      // tail holds last cons cell of the message data
      s7_pointer tail = head;
      // iterate osc types adding data to message list
      for (int i=0; i<argc; i++)
        {
          switch (types[i])
            {
            case LO_INT32:
              s7_set_cdr(tail, s7_cons(sc, s7_make_integer(sc, argv[i]->i32), snil));
            case LO_INT64:
              s7_set_cdr(tail, s7_cons(sc, s7_make_integer(sc, argv[i]->i64), snil));
              break;
            case LO_FLOAT:
              s7_set_cdr(tail, s7_cons(sc, s7_make_real(sc, argv[i]->f32), snil));
              break;
            case LO_DOUBLE:
              s7_set_cdr(tail, s7_cons(sc, s7_make_real(sc, argv[i]->f64), snil));
              break;
            case LO_TRUE:
              s7_set_cdr(tail, s7_cons(sc, s7_t(sc), snil));
              break;
            case LO_FALSE:
              s7_set_cdr(tail, s7_cons(sc,  s7_f(sc), snil));
              break;
            case LO_STRING:
              s7_set_cdr(tail, s7_cons(sc, s7_make_string(sc, (const char*)argv[i]->s), snil));
              break;
            case LO_SYMBOL:
              s7_set_cdr(tail, s7_cons(sc, s7_make_symbol(sc, (const char*)argv[i]->s), snil));
              break;
            case LO_CHAR:
              s7_set_cdr(tail, s7_cons(sc, s7_make_character(sc, argv[i]->c), snil));
              break;
            case LO_NIL:
              s7_set_cdr(tail, s7_cons(sc, s7_make_keyword(sc, "N"), snil));
              break;
            case LO_INFINITUM: 
              s7_set_cdr(tail, s7_cons(sc, s7_make_keyword(sc, "I"), snil));
              break;
            case LO_TIMETAG: 
              {
                double t=0.0;
                if (argv[i]->t.sec!=LO_TT_IMMEDIATE.sec ||
                    argv[i]->t.frac!=LO_TT_IMMEDIATE.frac)
                  {
                    lo_timetag now;
                    lo_timetag_now(&now);
                    t=lo_timetag_diff(argv[i]->t, now);
                  }
                s7_set_cdr(tail, s7_cons(sc, s7_make_real(sc, t), snil));
              }
              break;
            case LO_BLOB: 
              //s7_set_cdr(tail, s7_cons(sc, ???, snil));
              break;
            case LO_MIDI: 
              //s7_set_cdr(tail, s7_cons(sc, ???, snil));
              break;
            }
          tail=s7_cdr(tail);
        }
      // now create hook's arglist holding the single (list) of data
      s7_pointer args=s7_cons(sc, head, s7_nil(sc));
      // protect newly consed args from GC
      int prot = s7_gc_protect(sc, args);
      // call the hook and save the return value
      s7_pointer res=s7_call(sc, hook, args);
      // release args
      s7_gc_unprotect_at(sc, prot);
      // hook returns #t if no error. otherwise an error occured under
      // the callback and so we automatically clear the hook
      if (res != s7_t(sc))
        {
          clearHook();
          Console::getInstance()->printError(">>> Cancelled OSC hook.\n");
        }
    }
  unlockHook();
}
*/

/* ==============================================================================
                                     OSC Open Dialog
  =============================================================================*/

#ifdef GRACE

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
  String host=Preferences::getInstance()->
    getStringProp(T("OscTargetHost"), T("localhost"));
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

#endif

