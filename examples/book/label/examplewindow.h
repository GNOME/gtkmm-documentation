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

  //Child widgets:
  Gtk::Box m_HBox;
  Gtk::Box m_VBox, m_VBox2;
  Gtk::Frame m_Frame_Normal, m_Frame_Multi, m_Frame_Left, m_Frame_Right,
    m_Frame_LineWrapped, m_Frame_FilledWrapped, m_Frame_Underlined;
  Gtk::Label m_Label_Normal, m_Label_Multi, m_Label_Left, m_Label_Right,
    m_Label_LineWrapped, m_Label_FilledWrapped, m_Label_Underlined;
};

#endif //GTKMM_EXAMPLEWINDOW_H
