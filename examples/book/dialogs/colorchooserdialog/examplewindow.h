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

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_color_button_color_set();
  void on_button_dialog_clicked();
  bool on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr);

  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::ColorButton m_ColorButton;
  Gtk::Button m_Button_Dialog;
  Gtk::DrawingArea m_DrawingArea; //To show the color.

  Gdk::RGBA m_Color;
};

#endif //GTKMM_EXAMPLEWINDOW_H
