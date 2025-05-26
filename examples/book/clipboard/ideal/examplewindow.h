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
  void on_button_copy();
  void on_button_paste();

  void on_clipboard_owner_change(GdkEventOwnerChange* event);
  void on_clipboard_get(Gtk::SelectionData& selection_data, guint info);
  void on_clipboard_clear();

  void on_clipboard_received(const Gtk::SelectionData& selection_data);
  void on_clipboard_received_targets(const std::vector<Glib::ustring>& targets);

  void update_paste_status(); //Disable the paste button if there is nothing to paste.

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::Label m_Label;

  Gtk::Grid m_Grid;
  Gtk::ToggleButton m_ButtonA1, m_ButtonA2, m_ButtonB1, m_ButtonB2;

  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_Copy, m_Button_Paste;

  Glib::ustring m_ClipboardStore; //Keep copied stuff here, until it is pasted. This could be a big complex data structure.
};

#endif //GTKMM_EXAMPLEWINDOW_H
