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

#ifndef GTKMM_NAME_DIALOG_H_
#define GTKMM_NAME_DIALOG_H_

#include <gtkmm.h>

class NameDialog : public Gtk::Window
{
public:
  NameDialog();
  ~NameDialog() override;

  void buttons_clicked_connect(const sigc::slot<void(const Glib::ustring&)>& slot);
  Glib::ustring get_entry1() const;
  Glib::ustring get_entry2() const;

protected:
  //Member widgets:
  Gtk::Grid m_Grid;
  Gtk::Image m_Image;
  Gtk::Label m_Label1;
  Gtk::Label m_Label2;
  Gtk::Entry m_Entry1;
  Gtk::Entry m_Entry2;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_OK;
  Gtk::Button m_Button_Cancel;
};

#endif /* GTKMM_NAME_DIALOG_H_ */
