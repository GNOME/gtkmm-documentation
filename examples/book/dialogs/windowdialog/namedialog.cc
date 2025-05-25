/* gtkmm example Copyright (C) 2023 gtkmm development team
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
 
 #include "namedialog.h"

NameDialog::NameDialog()
: m_Label1("_First name", true),
  m_Label2("_Second name", true),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL, 5),
  m_Button_OK("_OK", true),
  m_Button_Cancel("_Cancel", true)
{
  set_destroy_with_parent(true);

  set_title("Name Dialog");
  set_child(m_Grid);

  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_Grid.set_expand(true);

  m_Image.set_from_icon_name("dialog-question");
  m_Image.set_icon_size(Gtk::IconSize::LARGE);
  m_Grid.attach(m_Image, 0, 0, 1, 2);

  m_Grid.attach(m_Label1, 1, 0);
  m_Grid.attach(m_Entry1, 2, 0);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 1, 1);
  m_Grid.attach(m_Entry2, 2, 1);
  m_Label2.set_mnemonic_widget(m_Entry2);

  m_Grid.attach(m_ButtonBox, 0, 2, 3, 1);
  m_ButtonBox.set_halign(Gtk::Align::END);
  m_ButtonBox.append(m_Button_OK);
  m_ButtonBox.append(m_Button_Cancel);
}

void NameDialog::buttons_clicked_connect(
  const sigc::slot<void(const Glib::ustring&)>& slot)
{
  m_Button_OK.signal_clicked().connect(sigc::bind(slot, "OK"));
  m_Button_Cancel.signal_clicked().connect(sigc::bind(slot, "Cancel"));
}

Glib::ustring NameDialog::get_entry1() const
{
  return m_Entry1.get_text();
}

Glib::ustring NameDialog::get_entry2() const
{
  return m_Entry2.get_text();
}

NameDialog::~NameDialog()
{
}
