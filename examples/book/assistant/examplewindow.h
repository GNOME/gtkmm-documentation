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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include "exampleassistant.h"
#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

private:
  // Signal handlers:
  void on_button_clicked();
  void on_assistant_apply();

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button;
  Gtk::Label m_label1, m_label2;
  Gtk::CheckButton m_check;
  Gtk::Entry m_entry;
  ExampleAssistant m_assistant;
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
