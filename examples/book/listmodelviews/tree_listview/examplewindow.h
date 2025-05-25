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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  // Signal handlers:
  void on_button_quit();
  void on_setup_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);

  Glib::RefPtr<Gio::ListModel> create_model(
    const Glib::RefPtr<Glib::ObjectBase>& item = {});

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::Label m_Heading;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::ListView m_ListView;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;

  Glib::RefPtr<Gtk::TreeListModel> m_TreeListModel;
};

#endif //GTKMM_EXAMPLEWINDOW_H
