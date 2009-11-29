/*--------------------------------------------------------------------*\
| Copyright (C) 2008 William Andrew Burnson, Rick Taube.               |
| This program is free software; you can redistribute it and/or modify |
| it under the terms of the GNU General Public License v3. The text of |
| this agreement is available at http://www.gnu.org/copyleft/gpl.html  |
\*--------------------------------------------------------------------*/

#ifndef Skin_h
#define Skin_h

#include "Fonts.h"

///An attempt to make the menu system a little more like normal Windows menus.
class WindowsSkin : public juce::LookAndFeel
{
public:
  juce::Font* fontMenuBar;
  CustomTypeface* defaultTypeface;
  MemoryInputStream* defaultFontTypefaceStream;

 WindowsSkin()
  {
    fontMenuBar = new juce::Font(16, 0);
    if(SystemStats::getOperatingSystemType() != SystemStats::MacOSX)
    {
      //Create the Bitstream Vera font from the resource.
      defaultFontTypefaceStream = new MemoryInputStream(Fonts::vera_typeface, 
                                                        Fonts::vera_typefaceSize, 
                                                        false);
      defaultTypeface = new CustomTypeface(*defaultFontTypefaceStream);
      Typeface::Ptr RefTypeface = juce::ReferenceCountedObjectPtr<juce::Typeface>(defaultTypeface);
      *fontMenuBar = juce::Font(RefTypeface);
      fontMenuBar->setHeight(15);
    }
    else
    {
      fontMenuBar->setTypefaceName(T("Lucida Grande"));
      fontMenuBar->setHeight(16); 
    }
  }

  virtual ~WindowsSkin()
  {
    delete fontMenuBar;
    //Can't delete because reference counter is still being held...
    //delete defaultTypeface;
    //delete defaultFontTypefaceStream;
  }

  virtual void drawPopupMenuBackground(juce::Graphics &g, int width, int height)
  {
    g.fillAll(juce::Colour::Colour(255,255,255));
    g.setColour(juce::Colour::Colour(157,157,161));
    g.drawRect(0,0,width,height);
  }

  virtual void drawPopupMenuItem(juce::Graphics& g, int width, int height,
    const bool isSeparator, const bool isActive, const bool isHighlighted,
    const bool isTicked, const bool hasSubMenu, const juce::String& text,
    const juce::String& shortcutKeyText, juce::Image* image, 
    const juce::Colour* const textColourToUse)
  {
    using namespace juce;
    const float halfH = height * 0.5f;

    if(isSeparator)
    {
      const float separatorIndent = 5.5f;
      g.setColour(Colour::Colour(157,157,161));
      g.drawLine(separatorIndent, halfH, width - separatorIndent, halfH);
    }
    else
    {
      Colour textColour(findColour(PopupMenu::textColourId));

      if(textColourToUse != 0)
        textColour = *textColourToUse;

      if(isHighlighted)
      {
	
        if(SystemStats::getOperatingSystemType()==SystemStats::MacOSX)
        {
          juce::GradientBrush gb(juce::Colour::Colour(83,112,248), 0, 0, 
            juce::Colour::Colour(30,67,246), 0, (float)height, false);
          g.setBrush(&gb);
        }
        else
          g.setColour(Colour::Colour(187,183,199));
        
        g.fillRect(1, 1, width - 2, height - 2);

        if(SystemStats::getOperatingSystemType()==SystemStats::MacOSX)
          g.setColour(Colours::white);
        else
          g.setColour(Colours::black);
      }
      else
        g.setColour(textColour);

      if(!isActive)
        g.setOpacity(0.3f);

      Font font(getPopupMenuFont());

      if(font.getHeight() > height / 1.3f)
        font.setHeight (height / 1.3f);

      g.setFont(font);

      const int leftBorder = (height * 5) / 4;
      const int rightBorder = 4;

      if(image != 0)
      {
        g.drawImageWithin(image,
          2, 1, leftBorder - 4, height - 2,
          RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
          false);
      }
      else if(isTicked)
      {
        const Path tick(getTickShape (1.0f));
        const float th = font.getAscent();
        const float ty = halfH - th * 0.5f;

        g.fillPath(tick, tick.getTransformToScaleToFit (2.0f, ty,
          (float)(leftBorder - 4), th, true));
      }

      g.drawFittedText(text,
        leftBorder, 0,
        width - (leftBorder + rightBorder), height,
        Justification::centredLeft, 1);

      if(shortcutKeyText.isNotEmpty())
      {
        String revised = shortcutKeyText;

        revised = revised.replace(String(" "), String::empty);
        revised = revised.replace(String("shortcut"), String::empty);
        revised = revised.replace(String("'"), String::empty);
        revised = revised.replace(String(":"), String::empty);
        if(SystemStats::getOperatingSystemType()==SystemStats::MacOSX)
        {
          //http://www.macosxhints.com/article.php?story=20071028203517911
          //http://web.sabi.net/mockups/source/keychars.html
          revised = revised.replace(String("return"), String("_"), true);
          revised = revised.replace(String("ctrl"), String::charToString(0x2303), true);
          revised = revised.replace(String("command"), String("$"), true);
          revised = revised.replace(String("shift"), String("^"), true);
          revised = revised.replace(String("alt"), String("`"), true);
          revised = revised.replace(String("+"), String::empty);
          revised = revised.replace(String("$^"), String("^$"), true);
          revised = revised.replace(String("$`"), String("`$"), true);
          revised = revised.replace(String("$"), String::charToString(0x2318), true);
          revised = revised.replace(String("`"), String::charToString(0x2325), true);
          revised = revised.replace(String("^"), String::charToString(0x21E7), true);
          revised = revised.replace(String("_"), String::charToString(0x21B5), true);
          revised = revised.replace(String("tab"), String::charToString(0x21E5), true);
        }
        else
        {
          revised = revised.replace(String("return"), String("Enter"), true);
          revised = revised.replace(String("ctrl"), String("Ctrl"), true);
          revised = revised.replace(String("shift"), String("Shift"), true);
          revised = revised.replace(String("alt"), String("Alt"), true);
        }

        int right = width - (rightBorder + 4);
        g.drawText(revised,
          right - fontMenuBar->getStringWidth(revised),
          0,
          right,
          height,
          Justification::centredLeft,
          false);
      }

      if(hasSubMenu)
      {
        const float arrowH = 0.6f * getPopupMenuFont().getAscent();
        const float x = width - height * 0.6f;

        Path p;
        p.addTriangle(x, halfH - arrowH * 0.5f,
          x, halfH + arrowH * 0.5f,
          x + arrowH * 0.6f, halfH);

        g.fillPath(p);
      }
    }
  }


  virtual void drawMenuBarItem(juce::Graphics &g, int width, int height, 
    int itemIndex, const juce::String &itemText, bool isMouseOverItem, 
    bool isMenuOpen, bool isMouseOverBar, juce::MenuBarComponent &menuBar)
  {
    g.setFont(*fontMenuBar);
    
    if(!(SystemStats::getOperatingSystemType()==SystemStats::MacOSX) && isMouseOverItem)
    {
      g.setColour(juce::Colour::Colour(187,183,199));
      g.fillRect(0,0,width,height-2);

      g.setColour(juce::Colour::Colour(178,180,191));
      g.drawRect(0,0,width,height-2);
      
      g.setColour(juce::Colours::black);
    }
    else if((SystemStats::getOperatingSystemType()==SystemStats::MacOSX) && isMenuOpen)
    {
      juce::GradientBrush gb(juce::Colour::Colour(83,112,248), 0, 0, 
        juce::Colour::Colour(30,67,246), 0, (float)height, false);
      g.setBrush(&gb);
      g.fillRect(0,0,width,height-2);
      
      g.setColour(juce::Colours::white);
    }
    else
      g.setColour(juce::Colours::black);

    g.drawText(itemText,0,0,width,height,juce::Justification::centred,false);
  }

  virtual void drawMenuBarBackground(juce::Graphics &g, int width, int height, 
    bool isMouseOverBar, juce::MenuBarComponent &menuBar)
  {
    g.fillAll(juce::Colour::Colour(237,237,237));
    
    g.setColour(juce::Colour::Colour(216,210,189));
    g.drawHorizontalLine(height-2,0,(float)width);

    g.setColour(juce::Colour::Colour(255,255,255));
    g.drawHorizontalLine(height-1,0,(float)width);
  }

  virtual const juce::Font getMenuBarFont(juce::MenuBarComponent &menuBar,
    int itemIndex, const juce::String &itemText)
  {
    return *fontMenuBar;
  }

  virtual const juce::Font getPopupMenuFont(void)
  {
    return *fontMenuBar;
  }

  virtual DropShadower* createDropShadowerForComponent(Component 
    *component)
  {
    return new DropShadower(0.4f, 2, 2, 2.0f);
  }
};

class LinuxSkin : public WindowsSkin
{
public: 
};

class MacSkin : public WindowsSkin
{
public: 
};

#endif

