/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#include <memory>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  bool on_button_press_event(GdkEventButton* button_event) override;

  void on_menu_file_popup_generic();

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::EventBox m_EventBox;
  Gtk::Label m_Label;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  std::unique_ptr<Gtk::Menu> m_pMenuPopup;
};

#endif //GTKMM_EXAMPLEWINDOW_H
