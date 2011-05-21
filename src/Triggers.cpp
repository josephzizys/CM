/*=======================================================================*
   Copyright (C) 2009 Rick Taube.                                        
   This program is free software; you can redistribute it and/or modify  
   it under the terms of the Lisp Lesser Gnu Public License. The text of 
   this agreement is available at http://www.cliki.net/LLGPL             
 *=======================================================================*/

#include "Enumerations.h"
#include "TextEditor.h"
#include "Syntax.h"
#include "Triggers.h"

Trigger::Trigger (int typ)
    : button (0),
      slider (0),
      keyboard (0),
      triggertype (0),
      height (40),
      configure (0),
      close (0)
{

  switch (typ)
    {
    case TriggerIDs::SliderTrigger :
      triggertype=typ;
      height=40;
      addAndMakeVisible (slider = new Slider (String::empty));
      slider->setValue(0.0);
      slider->setRange (0.0, 100.0, 1.0);
      slider->setSliderStyle (Slider::LinearHorizontal);
      slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
      slider->addListener (this);
      vars.add(T("*trigger*"));
      vars.add(String(slider->getValue()));
      break;
    case TriggerIDs::MidiKeyboardTrigger :
      triggertype=typ;
      keyboard = new MidiKeyboardComponent
	(keyboardState, MidiKeyboardComponent::horizontalKeyboard);
      addAndMakeVisible(keyboard);
      keyboard->setOctaveForMiddleC(4);
      keyboard->setMidiChannel(0);
      keyboard->setVelocity(.5);
      keyboard->setLowestVisibleKey(36);
      vars.add(T("*trigger*"));
      vars.add(T("60"));
      keyboardState.addListener(this);
      break;
      //    case TriggerIDs::MidiInTrigger :
      //      break;
    case TriggerIDs::CounterTrigger :
      height=40;
      triggertype=typ;
      addAndMakeVisible(button = new TextButton(String::empty));
      vars.add(T("*trigger*"));
      vars.add(T("1"));
      button->setButtonText(vars[1]);
      button->addButtonListener(this);
      break;
    case TriggerIDs::ButtonTrigger :
    default:
      height=40;
      triggertype=TriggerIDs::ButtonTrigger;
      addAndMakeVisible(button = new TextButton(String::empty));
      vars.add(T("*trigger*"));
      vars.add(T(":bang!"));
      button->setButtonText(vars[1]);
      button->addButtonListener(this);
      break;
    }    
    addAndMakeVisible (configure = new TextButton(String::empty));
    configure->setTooltip (T("Configure this trigger"));
    configure->setButtonText (T("P"));
    configure->addButtonListener (this);
    // original = Colour(0xff64648d)
    // Green = Colour(0xff0dc917)
    configure->setColour (TextButton::buttonColourId, Colour(0xff64648d));
    configure->setColour (TextButton::textColourId, Colours::white);

    addAndMakeVisible (close = new TextButton(String::empty));
    close->setTooltip (T("Remove this trigger"));
    close->setButtonText (T("X"));
    close->addButtonListener (this);
    close->setColour (TextButton::buttonColourId, Colour (0xffff0000));
    close->setColour (TextButton::textColourId, Colours::white);

    setVisible(true);
    setSize (400, height);
}

Trigger::~Trigger()
{
  vars.clear();
  deleteAndZero (button);
  deleteAndZero (slider);
  deleteAndZero (keyboard);
  deleteAndZero (configure);
  deleteAndZero (close);
}

void Trigger::initFromXml(XmlElement* xml)
{
  // xml is an xml trigger description. trigger's type and GUI
  // components already set.  override the initialized properites with
  // those from the xml's properties
  if (triggertype==TriggerIDs::ButtonTrigger)
    {
      String str=xml->getStringAttribute(T("variable"));
      if (!str.isEmpty() && !str.containsAnyOf(T(" \t\r#;,(){}\"\\'`")))
	vars.set(0,str);
      str=xml->getStringAttribute(T("value")).trim();
      if (!str.isEmpty())
	{
	  vars.set(1,str);
	  button->setButtonText(str);
	}
    }
  else if (triggertype==TriggerIDs::CounterTrigger)
    {
      String str=xml->getStringAttribute(T("variable"));
      if (!str.isEmpty() && !str.containsAnyOf(T(" \t\r#;,(){}\"\\'`")))
	vars.set(0,str);
      str=xml->getStringAttribute(T("value")).trim();
      if (!str.isEmpty() && str.containsOnly(T("-0123456789")))
	{
	  vars.set(1,str);
	  button->setButtonText(str);
	}
    }
  else if (triggertype==TriggerIDs::SliderTrigger)
    {
      String str=xml->getStringAttribute(T("variable"));
      if (!str.isEmpty() && !str.containsAnyOf(T(" \t\r#;,(){}\"\\'`")))
	vars.set(0,str);
      str=xml->getStringAttribute(T("value"));
      if (!str.isEmpty())
	slider->setValue(str.getDoubleValue());
      StringArray vals;
      vals.addTokens(xml->getStringAttribute(T("range")), false);
      if (vals.size()>2)
	slider->setRange(vals[0].getDoubleValue(),
			 vals[1].getDoubleValue(),
			 vals[2].getDoubleValue());
      else if (vals.size()>1)
	slider->setRange(vals[0].getDoubleValue(),
			 vals[1].getDoubleValue(),
			 slider->getInterval());
      else if (vals.size()>0)
	slider->setRange(vals[0].getDoubleValue(),
			 slider->getMaximum(),
			 slider->getInterval());
    }
  else if (triggertype==TriggerIDs::MidiKeyboardTrigger)
    {
      String str=xml->getStringAttribute(T("variable"));
      if (!str.isEmpty() && !str.containsAnyOf(T(" \t\r#;,(){}\"\\'`")))
	vars.set(0,str);
    }
  else if (triggertype==TriggerIDs::MidiInTrigger)
    {
    }
}

String Trigger::toXml()
{
  String str=T("<trigger type=");
  str << TriggerIDs::toString(triggertype).quoted();
  switch (triggertype)
    {
    case TriggerIDs::ButtonTrigger :
      str << T(" variable=")
	  << vars[0].quoted()
	  << T(" value=")
	  << vars[1].quoted();
      break;
    case TriggerIDs::CounterTrigger :
      str << T(" variable=")
	  << vars[0].quoted()
	  << T(" value=")
	  << vars[1].quoted();
      break;
    case TriggerIDs::SliderTrigger :
      str << T(" variable=")
	  << vars[0].quoted()
	  << T(" value=")
	  << String(slider->getValue()).quoted()
	  << T(" range=\"")
	  << T(" ") << slider->getMinimum()
	  << T(" ") << slider->getMaximum()
	  << T(" ") << slider->getInterval()
	  << T("\"");
      break;
    case TriggerIDs::MidiKeyboardTrigger :
      str << T(" variable=")
	  << vars[0].quoted();
      break;
    case TriggerIDs::MidiInTrigger :
      break;
    }
  str << T("/>");
  return str;
}

void Trigger::paint (Graphics& g)
{
  g.fillAll (Colours::white);
}

void Trigger::resized()
{
  if (slider)
    slider->setBounds (8, 8, 216, 24);
  else if (button)
    button->setBounds (8, 8, 150, 24);
  else if (keyboard)
    keyboard->setBounds (0, 0, getWidth() - 70, getHeight());
  close->setBounds(getWidth()-8-24+2, 8+2, 20, 20);
  configure->setBounds(getWidth()-8-24-8-24+2, 8+2, 20, 20);
}

void Trigger::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == slider)
    {
      // update variable's value with slider value
      vars.set(1, String(slider->getValue()) );
      doTrigger();
    }
}

void Trigger::handleNoteOn (MidiKeyboardState* state, int chan,
			    int key, float vel)
{
  vars.set(1, String(key) );
  doTrigger();
}

void Trigger::handleNoteOff (MidiKeyboardState* state, int chan,
			    int key)
{
 
}

void Trigger::buttonClicked (Button* buttonThatWasClicked)
{
  if (buttonThatWasClicked == button)
    {
      doTrigger();
      if (triggertype==TriggerIDs::CounterTrigger)
	{
	  String next=String(vars[1].getIntValue()+1);
	  vars.set(1, next);
	  button->setButtonText(next);
	}      
    }
  else if (buttonThatWasClicked == configure)
    {
      configureTrigger();
    }
  else if (buttonThatWasClicked == close)
    ((TextEditorWindow*)getTopLevelComponent())->removeTrigger();
}

/*=======================================================================*
                               Trigger Actions
 *=======================================================================*/

void Trigger::doTrigger ()
{
  //  std::cout << "doButtonTrigger variable="
  //	    << vars[0].toUTF8() << " value=" << vars[1].toUTF8()
  //	    << "\n";
  TextBuffer* buf=
    ((TextEditorWindow*)getTopLevelComponent())->getTextBuffer();
  String text=(buf->isRegion()) ? buf->getRegion() : buf->getText();
  String code=String::empty;
  // TODO: This should iterate the vars array
  if (buf->isSyntax(TextIDs::Lisp))
    {
      code << T("(let ((") << vars[0] << T(" ") << vars[1] << T(")) ")
#ifdef GRACECL
	   << T("#+sbcl(declare (sb-ext:muffle-conditions cl:style-warning))")
#endif
	   << text
#ifdef GRACECL
	   << T("(values))");
#else
	   << T("(void))");
#endif
      LispSyntax::getInstance()->eval(code);
    }
  else
    {
      code << T("begin with ") << vars[0] << T(" = ") << vars[1] << T(" ")
	   << text
	   << T(" end");
      SalSyntax::getInstance()->eval(code);
    }
}

/*=======================================================================*
                               Trigger Configuring
 *=======================================================================*/

class ButtonConfig  : public Component,
                      public ButtonListener
{
private:
  Trigger* trigger;
  Label* label1;
  TextEditor* buffer1;
  Label* label2;
  TextEditor* buffer2;
  Label* label3;
  TextEditor* buffer3;
  Label* label4;
  TextEditor* buffer4;
  Label* label5;
  TextEditor* buffer5;
  TextButton* cancel;
  TextButton* ok;
public:
  
  ButtonConfig (Trigger* trig)
    : label1 (0),
      buffer1 (0),
      label2 (0),
      buffer2 (0),
      label3 (0),
      buffer3 (0),
      label4 (0),
      buffer4 (0),
      label5 (0),
      buffer5 (0),
      cancel (0),
      ok (0)
  {
    trigger=trig;
    String l1, l2, l3, l4, l5;
    String b1, b2, b3, b4, b5;
    int height;
    if (trigger->triggertype==TriggerIDs::ButtonTrigger)
      {
	l1=T("Button Label:");
	b1=trigger->button->getButtonText();
	l2=T("Button Variable:");
	b2=trigger->vars[0];
	l3=T("Button Value:");
	b3=trigger->vars[1];
	height=8+24+8+24+8+24 + 16+24+8;
      }
    if (trigger->triggertype==TriggerIDs::CounterTrigger)
      {
	l1=T("Counter Variable:");
	b1=trigger->vars[0];
	l2=T("Counter Value:");
	b2=trigger->vars[1];
	height=8+24+8+24 + 16+24+8;
      }
    else if (trigger->triggertype==TriggerIDs::SliderTrigger)
      {
	l1=T("Slider Variable:");
	b1=trigger->vars[0];
	l2=T("Value:");
	b2=String(trigger->slider->getValue());
	l3=T("Minimum:");
	b3=String(trigger->slider->getMinimum());
	l4=T("Maximum:");
	b4=String(trigger->slider->getMaximum());
	l5=T("Increment:");
	b5=String(trigger->slider->getInterval());
	height=8+24+8+24+8+24+8+24+8+24 + 16+24+8;
      }
    else if (trigger->triggertype==TriggerIDs::MidiKeyboardTrigger)
      {
	l1=T("Keyboard Variable:");
	b1=trigger->vars[0];
	height=8+24 + 16+24+8;
      }

    if (!l1.isEmpty())
      {
	addAndMakeVisible (label1 = new Label (String::empty, l1));
	label1->setFont (Font (15.0000f, Font::plain));
	label1->setJustificationType (Justification::centredRight);
	label1->setEditable (false, false, false);
	label1->setColour (TextEditor::textColourId, Colours::black);
	label1->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
	addAndMakeVisible (buffer1 = new TextEditor (String::empty));
	buffer1->setMultiLine (false);
	buffer1->setReturnKeyStartsNewLine (false);
	buffer1->setReadOnly (false);
	buffer1->setScrollbarsShown (true);
	buffer1->setCaretVisible (true);
	buffer1->setPopupMenuEnabled (true);
	buffer1->setText (b1);
      }

    if (!l2.isEmpty())
      {
	addAndMakeVisible (label2 = new Label (String::empty, l2));
	label2->setFont (Font (15.0000f, Font::plain));
	label2->setJustificationType (Justification::centredRight);
	label2->setEditable (false, false, false);
	label2->setColour (TextEditor::textColourId, Colours::black);
	label2->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
	addAndMakeVisible (buffer2 = new TextEditor (String::empty));
	buffer2->setMultiLine (false);
	buffer2->setReturnKeyStartsNewLine (false);
	buffer2->setReadOnly (false);
	buffer2->setScrollbarsShown (true);
	buffer2->setCaretVisible (true);
	buffer2->setPopupMenuEnabled (true);
	buffer2->setText(b2);
      }
    
    if (!l3.isEmpty())
      {
	addAndMakeVisible (label3 = new Label (String::empty, l3));
	label3->setFont (Font (15.0000f, Font::plain));
	label3->setJustificationType (Justification::centredRight);
	label3->setEditable (false, false, false);
	label3->setColour (TextEditor::textColourId, Colours::black);
	label3->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
	addAndMakeVisible (buffer3 = new TextEditor (String::empty));
	buffer3->setMultiLine (false);
	buffer3->setReturnKeyStartsNewLine (false);
	buffer3->setReadOnly (false);
	buffer3->setScrollbarsShown (true);
	buffer3->setCaretVisible (true);
	buffer3->setPopupMenuEnabled (true);
	buffer3->setText (b3);
      }

    if (!l4.isEmpty())
      {
	addAndMakeVisible (label4 = new Label (String::empty, l4));
	label4->setFont (Font (15.0000f, Font::plain));
	label4->setJustificationType (Justification::centredRight);
	label4->setEditable (false, false, false);
	label4->setColour (TextEditor::textColourId, Colours::black);
	label4->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
	addAndMakeVisible (buffer4 = new TextEditor (String::empty));
	buffer4->setMultiLine (false);
	buffer4->setReturnKeyStartsNewLine (false);
	buffer4->setReadOnly (false);
	buffer4->setScrollbarsShown (true);
	buffer4->setCaretVisible (true);
	buffer4->setPopupMenuEnabled (true);
	buffer4->setText (b4);
      }	

    if (!l5.isEmpty())
      {
	addAndMakeVisible (label5 = new Label (String::empty, l5));
	label5->setFont (Font (15.0000f, Font::plain));
	label5->setJustificationType (Justification::centredRight);
	label5->setEditable (false, false, false);
	label5->setColour (TextEditor::textColourId, Colours::black);
	label5->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
	addAndMakeVisible (buffer5 = new TextEditor (String::empty));
	buffer5->setMultiLine (false);
	buffer5->setReturnKeyStartsNewLine (false);
	buffer5->setReadOnly (false);
	buffer5->setScrollbarsShown (true);
	buffer5->setCaretVisible (true);
	buffer5->setPopupMenuEnabled (true);
	buffer5->setText (b5);
      }
    
    addAndMakeVisible (cancel = new TextButton (String::empty));
    cancel->setButtonText (T("Cancel"));
    cancel->addButtonListener (this);
    
    addAndMakeVisible (ok = new TextButton (String::empty));
    ok->setButtonText (T("Ok"));
    ok->addButtonListener (this);
    setSize (224, height); // 144
  }
  
  ~ButtonConfig()
  {
    deleteAndZero (label1);
    deleteAndZero (buffer1);
    deleteAndZero (label2);
    deleteAndZero (buffer2);
    deleteAndZero (label3);
    deleteAndZero (buffer3);
    deleteAndZero (label4);
    deleteAndZero (buffer4);
    deleteAndZero (label5);
    deleteAndZero (buffer5);
    deleteAndZero (cancel);
    deleteAndZero (ok);
  }
    
  void resized()
  {
    if (label1)
      {
	label1->setBounds (8, 8, 104, 24);
	buffer1->setBounds (120, 8, getWidth()-120-8, 24);
      }
    if (label2)
      {
	label2->setBounds (8, 40, 104, 24);
	buffer2->setBounds (120, 40, getWidth()-120-8, 24);
      }
    if (label3)
      {
	label3->setBounds (8, 72, 104, 24);
	buffer3->setBounds (120, 72, getWidth()-120-8, 24);
      }
    if (label4)
      {
	label4->setBounds (8, 104, 104, 24);
	buffer4->setBounds (120, 104, getWidth()-120-8, 24);
      }
    if (label5)
      {
	label5->setBounds (8, 136, 104, 24);
	buffer5->setBounds (120, 136, getWidth()-120-8, 24);
      }
    ok->setBounds (getWidth()-96-8, getHeight()-24-8, 96, 24);
    cancel->setBounds (ok->getX()-96-8, getHeight()-24-8, 96, 24);
  }
  
  void buttonClicked (Button* buttonThatWasClicked)
  {
    if (buttonThatWasClicked == cancel)
      {
	trigger=NULL;
	((DialogWindow *)getTopLevelComponent())->exitModalState (0);
      }
    else if (buttonThatWasClicked == ok)
      {
	String s=T("<trigger type=");
	s << TriggerIDs::toString(trigger->triggertype).quoted();
	if (trigger->triggertype==TriggerIDs::ButtonTrigger)
	  s //<< T(" label=") << buffer1->getText().quoted()
	    << T(" variable=") << buffer2->getText().quoted()
	    << T(" value=") << buffer3->getText().quoted();
	if (trigger->triggertype==TriggerIDs::CounterTrigger)
	  s << T(" variable=") << buffer1->getText().quoted()
	    << T(" value=") << buffer2->getText().quoted();
	else if (trigger->triggertype==TriggerIDs::SliderTrigger)
	  s << T(" variable=") << buffer1->getText().quoted()
	    << T(" value=") << buffer2->getText().quoted()
	    << T(" range=\"") << buffer3->getText()
	    << T(" ") << buffer4->getText()
	    << T(" ") << buffer5->getText() << T("\"");
	else if (trigger->triggertype==TriggerIDs::MidiKeyboardTrigger)
	  s << T(" variable=") << buffer1->getText().quoted();
	s<<T("/>");
	XmlDocument doc (s);
	trigger->initFromXml(doc.getDocumentElement());
	trigger=NULL;
	((DialogWindow *)getTopLevelComponent())->exitModalState (1);
      }
  }
};

void Trigger::configureTrigger ()
{
  ButtonConfig* comp=new ButtonConfig(this);
  String str=TriggerIDs::toPrettyString(triggertype);
  str<<T(" Preferences");
  Colour col=Colour(0xffe5e5e5);
  DialogWindow::showModalDialog(str, comp, this, col, true, true, true);
  delete comp;
}


