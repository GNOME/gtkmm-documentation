/* gtkmm example Copyright (C) 2010 Openismus GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GTKMM_EXAMPLEASSISTANT_H
#define GTKMM_EXAMPLEASSISTANT_H

#include <gtkmm.h>

class ExampleAssistant : public Gtk::Assistant
{
public:
  ExampleAssistant();
  virtual ~ExampleAssistant();

  void get_result(bool& check_state, Glib::ustring& entry_text);

private:
  // Signal handlers:
  void on_assistant_apply();
  void on_assistant_cancel();
  void on_assistant_close();
  void on_assistant_prepare(Gtk::Widget* widget);
  void on_entry_changed();

  // Member functions:
  void print_status();

  // Child widgets:
  Gtk::Box m_box;
  Gtk::Label m_label1, m_label2;
  Gtk::CheckButton m_check;
  Gtk::Entry m_entry;
};

#endif /* GTKMM_EXAMPLEASSISTANT_H */
