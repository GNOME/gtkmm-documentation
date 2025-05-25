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

#ifndef GTKMM_EXAMPLEAPPPREFS_H_
#define GTKMM_EXAMPLEAPPPREFS_H_

#include <gtkmm.h>

#ifdef GLIBMM_CHECK_VERSION
#define HAS_GIO_SETTINGS_BIND_WITH_MAPPING GLIBMM_CHECK_VERSION(2,75,0)
#else
#define HAS_GIO_SETTINGS_BIND_WITH_MAPPING 0
#endif

class ExampleAppPrefs : public Gtk::Window
{
public:
  ExampleAppPrefs(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder);

  static ExampleAppPrefs* create(Gtk::Window& parent);

protected:
#if HAS_GIO_SETTINGS_BIND_WITH_MAPPING
  // Mappings from Gio::Settings to properties
  static std::optional<unsigned int> map_from_ustring_to_int(const Glib::ustring& transition);
  static std::optional<Glib::ustring> map_from_int_to_ustring(const unsigned int& pos);
#else
  // Signal handlers
  void on_font_setting_changed(const Glib::ustring& key);
  void on_font_selection_changed();
  void on_transition_setting_changed(const Glib::ustring& key);
  void on_transition_selection_changed();
#endif
  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gio::Settings> m_settings;
  Gtk::FontDialogButton* m_font {nullptr};
  Gtk::DropDown* m_transition {nullptr};
};

#endif /* GTKMM_EXAMPLEAPPPREFS_H_ */
