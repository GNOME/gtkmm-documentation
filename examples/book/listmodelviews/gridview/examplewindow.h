/* gtkmm example Copyright (C) 2006 gtkmm development team
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
#include <gdkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  class ModelColumns;
  // Signal handlers:
  void on_button_quit();
  void on_item_activated(unsigned int position);
  void on_selection_changed();
  void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  int on_model_sort(const Glib::RefPtr<const ModelColumns>& a, const Glib::RefPtr<const ModelColumns>& b);

  void add_entry(const std::string& filename, const Glib::ustring& description);

  // A Gio::ListStore stores filename, description and texture.
  class ModelColumns : public Glib::Object
  {
  public:
    std::string m_filename;
    Glib::ustring  m_description;
    Glib::RefPtr<Gdk::Texture> m_texture;

    static Glib::RefPtr<ModelColumns> create(const std::string& filename,
      const Glib::ustring& description, const Glib::RefPtr<Gdk::Texture>& texture)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(filename, description, texture));
    }

  protected:
    ModelColumns(const std::string& filename, const Glib::ustring& description,
      const Glib::RefPtr<Gdk::Texture>& texture)
    : m_filename(filename), m_description(description), m_texture(texture)
    { }
  }; // ModelColumns

  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_data_model;
  Glib::RefPtr<Gtk::SingleSelection> m_selection_model;
  Glib::RefPtr<Gtk::SignalListItemFactory> m_factory;

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::GridView m_GridView;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_EXAMPLEWINDOW_H
