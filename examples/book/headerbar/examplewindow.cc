/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
 : m_title_buttons_label("Show title buttons:", Gtk::Align::END, Gtk::Align::CENTER),
   m_title_label("Title:", Gtk::Align::END, Gtk::Align::CENTER)
{
  // Window properties
  set_title("HeaderBar Example");

  // Button
  m_button.set_image_from_icon_name("go-home-symbolic", Gtk::IconSize::INHERIT, true);
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_clicked));

  // Entries
  m_title_entry.set_text("HeaderBar title");
  m_title_entry.signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_title_entry_changed));

  // Header bar
  on_title_entry_changed();
  m_header_bar.set_show_title_buttons();
  m_header_bar.pack_start(m_button);

  // Set headerbar as titlebar
  set_titlebar(m_header_bar);

  // Switch
  m_switch.set_active(true);
  m_switch.set_halign(Gtk::Align::START);
  m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_switch_active_changed));

  // Layout
  m_grid.set_column_spacing(6);
  m_grid.set_row_spacing(6);
  m_grid.attach(m_title_buttons_label, 0, 0);
  m_grid.attach(m_switch, 1, 0);
  m_grid.attach(m_title_label, 0, 1);
  m_grid.attach(m_title_entry, 1, 1);
  m_grid.set_margin(12);
  set_child(m_grid);

  // Dialog, shown after a button click
  m_dialog = Gtk::AlertDialog::create("Button clicked");
  m_dialog->set_modal();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_switch_active_changed()
{
  bool show_title_buttons = m_switch.get_active();
  m_header_bar.set_show_title_buttons(show_title_buttons);
}

void ExampleWindow::on_title_entry_changed()
{
  const auto title = m_title_entry.get_text();
  if(!title.empty())
  {
    set_title(title);
  }
}

void ExampleWindow::on_button_clicked()
{
  m_dialog->show(*this);
}
