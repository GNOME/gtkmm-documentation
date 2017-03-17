/* gtkmm example Copyright (C) 2013 gtkmm development team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
 : m_close_button_label("Show close button:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER),
   m_title_label("Title:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER),
   m_subtitle_label("Subtitle:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER)
{
  // Window properties
  set_title("HeaderBar Example");

  // Button
  m_button.set_image_from_icon_name("go-home-symbolic", Gtk::ICON_SIZE_BUTTON, true);
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_clicked));

  // Entries
  m_title_entry.set_text("HeaderBar title");
  m_subtitle_entry.set_text("HeaderBar subtitle");
  m_title_entry.signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_title_entry_activate));
  m_subtitle_entry.signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_subtitle_entry_activate));

  // Header bar
  on_title_entry_activate();
  on_subtitle_entry_activate();
  m_header_bar.set_show_close_button();
  m_header_bar.pack_start(m_button);

  // Set headerbar as titlebar
  set_titlebar(m_header_bar);

  // Switch
  m_switch.set_active(true);
  m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_switch_active_changed));

  // Layout
  m_grid.set_column_spacing(6);
  m_grid.set_row_spacing(6);
  m_grid.attach(m_close_button_label, 0, 0);
  m_grid.attach(m_switch, 1, 0);
  m_grid.attach(m_title_label, 0, 1);
  m_grid.attach(m_title_entry, 1, 1);
  m_grid.attach(m_subtitle_label, 0, 2);
  m_grid.attach(m_subtitle_entry, 1, 2);
  m_grid.set_margin(12);
  add(m_grid);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_switch_active_changed()
{
  bool show_close_button = m_switch.get_active();
  m_header_bar.set_show_close_button(show_close_button);
}

void ExampleWindow::on_title_entry_activate()
{
  const auto title = m_title_entry.get_text();
  if(!title.empty())
  {
    m_header_bar.set_title(title);
  }
}

void ExampleWindow::on_subtitle_entry_activate()
{
  const auto subtitle = m_subtitle_entry.get_text();
  m_header_bar.set_subtitle(subtitle);
}

void ExampleWindow::on_button_clicked()
{
  Gtk::MessageDialog dialog(*this, "Button clicked", true);
  dialog.run();
}

