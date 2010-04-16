/*
  ==============================================================================

   This file is part of Chorale Composer
   Copyright 2009 William Andrew Burnson, Heinrich Taube

  ------------------------------------------------------------------------------

   Chorale Composer can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 3 of the License, or (at your option) any later version.

   Chorale Composer is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with Chorale Composer; if not, visit www.gnu.org/licenses or write to
   the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ==============================================================================
*/

#ifdef MACOSX
#include <Carbon/Carbon.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

#include "Alerts.h"

namespace juce
{
String button1;
String button2;
String button3;

#ifdef JUCE_WIN32


int buttonLayoutType;

String takeFirstWord(String s)
{
  String t = "&";
  t << s;
  s = t;
  for(int i = 0; i < s.length(); i++)
  {
    if(s[i] == 32)
      return s.substring(0, i);
  }
  return s;
}

//Taken from demo code at:
//http://www.codeguru.com/forum/showthread.php?t=215027

LRESULT CALLBACK MsgBoxHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{// Process WH_CALLWNDPROCRET hook messages for MessageBox
 //
 // Local variables
 //
 //	szClassName				: Window classname
 // pMenu					: Pointer to system menu
 // hWndParent				: Handle to parent window

	char szClassName[100] = { NULL };
	HWND hWndParent = NULL;

		if((hWndParent = GetParent(((LPCWPRETSTRUCT)lParam)->hwnd)) == NULL)
		{// No parent found

		 // Use the desktop window as the parent			
			hWndParent = GetDesktopWindow();
		}

		if(!(nCode < 0))
		{// Process this message

		 // Get classname of window
			GetClassName(((LPCWPRETSTRUCT)lParam)->hwnd, szClassName, 100);

				if(!lstrcmpi(szClassName, "#32770"))
				{// Window is messagebox

					switch(((LPCWPRETSTRUCT)lParam)->message)
					{// Process message for window

					 // Process WM_INITDIALOG message
						case WM_INITDIALOG:

						 /*Change button text here as follows
						 IDCANCEL for OK in MB_OK or Cancel in MB_OKCANCEL, MB_RETRYCANCEL,
               and MB_YESNOCANCEL
						 IDOK for OK in MB_OKCANCEL 
						 IDABORT for Abort in MB_ABORTRETRYIGNORE
						 IDRETRY for Retry in MB_ABORTRETRYIGNORE
						 IDIGNORE for Ignore in MB_ABORTRETRYIGNORE
						 IDYES for Yes in MB_YESNO or MB_YESNOCANCEL
						 IDNO for No in MB_YESNO or MB_YESNOCANCEL*/
              if((buttonLayoutType & 0x03) == MB_OK)
              {
							  SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDCANCEL), 
                  WM_SETTEXT, 0, (LPARAM)button1.toUTF8());
              }
              else if((buttonLayoutType & 0x03) == MB_OKCANCEL)
              {
							  SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDOK), 
                  WM_SETTEXT, 0, (LPARAM)button1.toUTF8());
							  SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDCANCEL), 
                  WM_SETTEXT, 0, (LPARAM)button2.toUTF8());
              }
              else if((buttonLayoutType & 0x03) == MB_YESNOCANCEL)
              {
							  SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDYES), 
                  WM_SETTEXT, 0, (LPARAM)button1.toUTF8());
							  SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDNO), 
                  WM_SETTEXT, 0, (LPARAM)button2.toUTF8());
                SendMessage(
                  GetDlgItem(((LPCWPRETSTRUCT)lParam)->hwnd, IDCANCEL), 
                  WM_SETTEXT, 0, (LPARAM)button3.toUTF8());
              }
							break;
					}
				}
		}

 // Call next hook
	return CallNextHookEx((HHOOK)GetProp(hWndParent, "MsgBoxHook"),
    nCode, wParam, lParam);
}

int MessageBoxCustom(HWND hWnd, LPCTSTR lpszText, 
                     LPCTSTR lpszCaption, UINT uType)
{// Show message box
 //
 //	Local variables
 //
 //	mbp						: Message box parameters
 //	nRet					: MessageBoxIndirect return value

	MSGBOXPARAMS mbp = { NULL };
	int nRet;

 // Initialise message box parameters
	mbp.cbSize = sizeof(mbp);
	mbp.hwndOwner = hWnd;
	mbp.lpszText = lpszText;
	mbp.lpszCaption = lpszCaption;
	mbp.dwStyle = uType;

		if(hWnd == NULL)
		{// No window handle supplied 

		 // Use desktop window handle
			hWnd = GetDesktopWindow();
		}

 // Set a WH_CBT hook
	SetProp(hWnd, "MsgBoxHook", SetWindowsHookEx(WH_CALLWNDPROCRET,
    MsgBoxHookProc, NULL, GetCurrentThreadId()));

 // Show message box
	nRet = MessageBox(hWnd, lpszText, lpszCaption, uType);

		if(GetProp(hWnd, "MsgBoxHook"))
		{// Remove WH_CALLWNDPROC hook

		 // Remove WH_CALLWNDPROC hook
			UnhookWindowsHookEx((HHOOK)RemoveProp(hWnd, "MsgBoxHook"));
		}

 // Return MessageBox result
	return nRet;
}
#endif //JUCE_WIN32

#ifdef JUCE_MAC
int showMacAlertWindow(AlertWindow::AlertIconType at,
                       const String& title,
                       const String& bodyText,
                       int numberOfButtons,
                       const String& button1Text,
                       const String& button2Text,
                       const String& button3Text)
{
  if(numberOfButtons == 1)
    juce::AlertWindow::showMessageBox(at, title, bodyText, button1Text);
  else if(numberOfButtons == 2)
    return juce::AlertWindow::showOkCancelBox(at, title, bodyText,
    button1Text, button2Text) ? 1 : 0;
  else if(numberOfButtons == 3)
    return juce::AlertWindow::showYesNoCancelBox(at, title, bodyText,
      button1Text, button2Text, button3Text);
  
  return 0;
  
/* //StandardAlert doesn't work in 64-bit applications.
  Str255 _title, _text;
  Str255 _1, _2, _3;
  
  unsigned char* t1 = (unsigned char*) _title;
  t1[0] = 254 < title.length() ? 254 : title.length();
  title.copyToBuffer ((char*) t1 + 1, 254);
  
  unsigned char* t2 = (unsigned char*) _text;
  t2[0] = 254 < bodyText.length() ? 254 : bodyText.length();
  bodyText.copyToBuffer ((char*) t2 + 1, 254);
  
  unsigned char* _t1 = (unsigned char*) _1;
  _t1[0] = 254 < button1Text.length() ? 254 : button1Text.length();
  button1Text.copyToBuffer ((char*) _t1 + 1, 254);
  
  unsigned char* _t2 = (unsigned char*) _2;
  _t2[0] = 254 < button2Text.length() ? 254 : button2Text.length();
  button2Text.copyToBuffer ((char*) _t2 + 1, 254);
 
  unsigned char* _t3 = (unsigned char*) _3;
  _t3[0] = 254 < button3Text.length() ? 254 : button3Text.length();
  button3Text.copyToBuffer ((char*) _t3 + 1, 254);  
  
  AlertStdAlertParamRec ar;
  ar.movable = true;
  ar.helpButton = false;
  ar.filterProc = 0;
  ar.defaultText = _1;
  numberOfButtons >= 2 ? ar.cancelText = _2 : ar.cancelText = 0;
  numberOfButtons == 3 ? ar.otherText = _3 : ar.otherText = 0;
  
  ar.defaultButton = kAlertStdAlertOKButton;
  ar.cancelButton = 0;
  if(numberOfButtons == 2)
    ar.cancelButton = kAlertStdAlertCancelButton;
  else if(numberOfButtons == 3)
    ar.cancelButton = kAlertStdAlertOtherButton;
  ar.position = kWindowCenterParentWindow;
  
  SInt16 result;
  if(at == juce::AlertWindow::InfoIcon || 
     at == juce::AlertWindow::QuestionIcon)
    ShowStandardAlert(kAlertNoteAlert, _title, _text, &ar, &result);
  else if(at == juce::AlertWindow::WarningIcon)
    ShowStandardAlert(kAlertCautionAlert, _title, _text, &ar, &result);
  else
    ShowStandardAlert(kAlertPlainAlert, _title, _text, &ar, &result);
    
  return (int)result;
  */
}

#endif

void Alerts::showMessageBox(AlertWindow::AlertIconType iconType, 
  const String &title, const String &message,
  const String &buttonText)
{
  buttonText == String::empty ?
    button1 = "OK" : button1 = buttonText;

#ifdef JUCE_LINUX
  AlertWindow::showMessageBox(iconType, title, message, buttonText);
#endif

#ifdef JUCE_WIN32
  int icon = 0;
  switch(iconType)
  {
  case AlertWindow::InfoIcon:
    icon = MB_ICONINFORMATION; break;
  case AlertWindow::WarningIcon:
    icon = MB_ICONWARNING; break;
  case AlertWindow::QuestionIcon:
    icon = MB_ICONQUESTION; break;
  }
  button1 = takeFirstWord(button1);
  MessageBoxCustom(0, message.toUTF8(), title.toUTF8(), buttonLayoutType = MB_OK + icon);
#endif

#ifdef JUCE_MAC
  showMacAlertWindow(iconType, title, message, 1, button1, "", "");
#endif
}

bool Alerts::showOkCancelBox(AlertWindow::AlertIconType iconType,
  const String &title, const String &message,
  const String &button1Text, const String &button2Text)
{
  button1Text == String::empty ? 
    button1 = "OK" : button1 = button1Text;
  button2Text == String::empty ? 
    button2 = "Cancel" : button2 = button2Text;

#ifdef JUCE_LINUX
  return AlertWindow::showOkCancelBox(iconType, title, message,
    button1Text, button2Text);
#endif

#ifdef JUCE_WIN32
  int icon = 0;
  switch(iconType)
  {
  case AlertWindow::InfoIcon:
    icon = MB_ICONINFORMATION; break;
  case AlertWindow::WarningIcon:
    icon = MB_ICONWARNING; break;
  case AlertWindow::QuestionIcon:
    icon = MB_ICONQUESTION; break;
  }
  button1 = takeFirstWord(button1);
  button2 = takeFirstWord(button2);
  return MessageBoxCustom(0, message.toUTF8(), title.toUTF8(), 
    buttonLayoutType = MB_OKCANCEL + icon) == IDOK;
#endif

#ifdef JUCE_MAC
  return showMacAlertWindow(iconType, title, message, 2, button1, button2, "")
    == kAlertStdAlertOKButton;
#endif
}

int Alerts::showYesNoCancelBox(AlertWindow::AlertIconType iconType,
  const String &title, const String &message,
  const String &button1Text, const String &button2Text,
  const String &button3Text)
{
  button1Text == String::empty ?
    button1 = "Yes" : button1 = button1Text;
  button2Text == String::empty ?
    button2 = "No" : button2 = button2Text;
  button3Text == String::empty ?
    button3 = "Cancel" : button3 = button3Text;

#ifdef JUCE_LINUX
  return AlertWindow::showYesNoCancelBox(iconType, title, message,
    button1Text, button2Text, button3Text);
#endif

#ifdef JUCE_WIN32
  int icon = 0;
  switch(iconType)
  {
  case AlertWindow::InfoIcon:
    icon = MB_ICONINFORMATION; break;
  case AlertWindow::WarningIcon:
    icon = MB_ICONWARNING; break;
  case AlertWindow::QuestionIcon:
    icon = MB_ICONQUESTION; break;
  }
  button1 = takeFirstWord(button1);
  button2 = takeFirstWord(button2);
  button3 = takeFirstWord(button3);
  int value = MessageBoxCustom(0, message.toUTF8(), title.toUTF8(), 
    buttonLayoutType = MB_YESNOCANCEL + icon);
  if(value == IDYES)
    return 1;
  else if(value == IDNO)
    return 2;
  else
    return 0;
#endif

#ifdef JUCE_MAC
  int value = showMacAlertWindow(iconType, title, message, 3, button1, 
                                 button2, button3);
  if(value == kAlertStdAlertOKButton)
    return 1;
  else if(value == kAlertStdAlertCancelButton)
    return 2;
  else
    return 0;
#endif
}

}

