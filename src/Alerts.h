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

#ifndef Alerts_h
#define Alerts_h

#include "juce.h"

namespace juce
{
class Alerts
{
public:
  static void showMessageBox(AlertWindow::AlertIconType iconType, 
    const String &title, const String &message,
    const String &buttonText = String::empty);

  static bool showOkCancelBox(AlertWindow::AlertIconType iconType,
    const String &title, const String &message,
    const String &button1Text = String::empty,
    const String &button2Text = String::empty);

  static int showYesNoCancelBox(AlertWindow::AlertIconType iconType,
    const String &title, const String &message,
    const String &button1Text = String::empty, 
    const String &button2Text = String::empty,
    const String &button3Text = String::empty);
};
}
#endif
