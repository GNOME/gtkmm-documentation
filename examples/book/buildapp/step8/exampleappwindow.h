/* gtkmm example Copyright (C) 2016 gtkmm development team
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

#ifndef GTKMM_EXAMPLEAPPWINDOW_H_
#define GTKMM_EXAMPLEAPPWINDOW_H_

#include <gtkmm.h>

#define HAS_SEARCH_ENTRY2 GTKMM_CHECK_VERSION(4,13,2)

class ExampleAppWindow : public Gtk::ApplicationWindow
{
public:
  ExampleAppWindow(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder);

  static ExampleAppWindow* create();

  void open_file_view(const Glib::RefPtr<Gio::File>& file);

protected:
  // Signal handlers
  void on_search_text_changed();
  void on_visible_child_changed();
  void on_find_word(const Gtk::Button* button);
  void on_reveal_child_changed();

  void update_words();
  void update_lines();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gio::Settings> m_settings;
  Gtk::Stack* m_stack {nullptr};
  Gtk::ToggleButton* m_search {nullptr};
  Gtk::SearchBar* m_searchbar {nullptr};
#if HAS_SEARCH_ENTRY2
  Gtk::SearchEntry2* m_searchentry {nullptr};
#else
  Gtk::SearchEntry* m_searchentry {nullptr};
#endif
  Gtk::MenuButton* m_gears {nullptr};
  Gtk::Revealer* m_sidebar {nullptr};
  Gtk::ListBox* m_words {nullptr};
  Gtk::Label* m_lines {nullptr};
  Gtk::Label* m_lines_label {nullptr};
  Glib::RefPtr<Glib::Binding> m_binding_search_enabled;
  Glib::RefPtr<Glib::Binding> m_binding_lines_visible;
};

#endif /* GTKMM_EXAMPLEAPPWINDOW_H */
