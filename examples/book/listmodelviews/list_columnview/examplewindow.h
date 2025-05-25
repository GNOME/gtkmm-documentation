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
  void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign);
  void on_setup_progressbar(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_percentage(const Glib::RefPtr<Gtk::ListItem>& list_item);

  // A Gio::ListStore item.
  class ModelColumns : public Glib::Object
  {
  public:
    unsigned int m_col_id;
    Glib::ustring m_col_name;
    short m_col_number;
    int m_col_percentage;

    static Glib::RefPtr<ModelColumns> create(unsigned int col_id,
      const Glib::ustring& col_name, short col_number, int col_percentage)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(col_id, col_name, col_number, col_percentage));
    }

  protected:
    ModelColumns(unsigned int col_id, const Glib::ustring& col_name,
      short col_number, int col_percentage)
    : m_col_id(col_id), m_col_name(col_name), m_col_number(col_number),
      m_col_percentage(col_percentage)
    {}
  }; // ModelColumns

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::ColumnView m_ColumnView;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;

  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_ListStore;
};

#endif //GTKMM_EXAMPLEWINDOW_H
