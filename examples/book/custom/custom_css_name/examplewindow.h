/* gtkmm example Copyright (C) 2022 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "mybutton.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  // Signal handlers:
  void on_button_quit();
  static void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error);

  // Child widgets:
  Gtk::Box m_VBox;
  MyButton m_Button_Child;
  Gtk::Label m_Label_Child1;
  Gtk::Label m_Label_Child2;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;

  Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
};

#endif //GTKMM_EXAMPLEWINDOW_H
