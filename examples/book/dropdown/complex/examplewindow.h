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
  void on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_dropdown_changed();

  void create_model();
  void liststore_add_item(const Glib::ustring& title, const Glib::ustring& icon,
    const Glib::ustring& description);

  // A Gio::ListStore item.
  class ModelColumns : public Glib::Object
  {
  public:
    Glib::ustring m_title;
    Glib::ustring m_icon;
    Glib::ustring m_description;

    static Glib::RefPtr<ModelColumns> create(const Glib::ustring& title,
      const Glib::ustring& icon, const Glib::ustring& description)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(title, icon, description));
    }

  protected:
    ModelColumns(const Glib::ustring& title, const Glib::ustring& icon,
      const Glib::ustring& description)
    : m_title(title), m_icon(icon), m_description(description)
    {}
  }; // ModelColumns

  // Child widget:
  Gtk::DropDown m_DropDown;

  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_ListStore;
};

#endif //GTKMM_EXAMPLEWINDOW_H
