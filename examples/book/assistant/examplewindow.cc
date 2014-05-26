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

#include "examplewindow.h"
#include "exampleassistant.h"

ExampleWindow::ExampleWindow()
: m_button("Show the assistant"),
  m_label1("State of assistant checkbutton:", Gtk::ALIGN_START, Gtk::ALIGN_CENTER),
  m_label2("Contents of assistant entry:", Gtk::ALIGN_START, Gtk::ALIGN_CENTER)
{
  set_title("Gtk::Assistant example");
  set_border_width(12);

  m_grid.set_row_homogeneous(true);

  m_grid.attach(m_button, 0, 0, 2, 1);
  m_button.set_hexpand(true);
  m_button.set_valign(Gtk::ALIGN_CENTER);

  m_grid.attach(m_label1, 0, 1, 1, 1);

  m_grid.attach(m_label2, 0, 2, 1, 1);

  m_grid.attach(m_check, 1, 1, 1, 1);
  m_check.set_halign(Gtk::ALIGN_START);

  m_grid.attach(m_entry, 1, 2, 1, 1);
  m_entry.set_hexpand(true);

  add(m_grid);

  m_button.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_clicked));
  m_assistant.signal_apply().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_assistant_apply));

  m_check.set_sensitive(false);
  m_entry.set_sensitive(false);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_assistant_apply()
{
  bool check_state;
  Glib::ustring entry_text;

  m_assistant.get_result(check_state, entry_text);
  m_check.set_active(check_state);
  m_entry.set_text(entry_text);
}

void ExampleWindow::on_button_clicked()
{
  m_assistant.show();
}
