/* gtkmm example Copyright (C) 2007 gtkmm development team
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

  //Methods:
  void prepare_textview();
  void connect_signals();

  //Signal handlers:
  void on_markup_checkbutton_toggled();
  bool on_textview_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
  bool on_button_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);

  //Child widgets:
  Gtk::Box m_vbox;

  Gtk::CheckButton m_checkbutton;
  Gtk::Label m_label;

  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::TextView m_text_view;
  Glib::RefPtr<Gtk::TextBuffer> m_ref_text_buffer;
  Glib::RefPtr<Gtk::TextTag> m_ref_bold_tag;

  Gtk::Button m_button;
  Gtk::Box m_button_tooltip_widget;
};

#endif // GTKMM_EXAMPLEWINDOW_H
