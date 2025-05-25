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
  void on_setup_id(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);

  Glib::RefPtr<Gio::ListModel> create_model(
    const Glib::RefPtr<Glib::ObjectBase>& item = {});

  // A Gio::ListStore item.
  class ModelColumns : public Glib::Object
  {
  public:
    int m_col_id;
    Glib::ustring m_col_name;

    static Glib::RefPtr<ModelColumns> create(int col_id, const Glib::ustring& col_name)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(col_id, col_name));
    }

  protected:
    ModelColumns(int col_id, const Glib::ustring& col_name)
    : m_col_id(col_id), m_col_name(col_name)
    {}
  }; // ModelColumns

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::ColumnView m_ColumnView;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;

  Glib::RefPtr<Gtk::TreeListModel> m_TreeListModel;
};

#endif //GTKMM_EXAMPLEWINDOW_H
