/* gtkmm example Copyright (C) 2016 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_EXAMPLEAPPPREFS_H_
#define GTKMM_EXAMPLEAPPPREFS_H_

#include <gtkmm.h>

class ExampleAppPrefs : public Gtk::Window
{
public:
  ExampleAppPrefs(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder);

  static ExampleAppPrefs* create(Gtk::Window& parent);

protected:
  // Signal handlers
  void on_font_setting_changed(const Glib::ustring& key);
  void on_font_selection_changed();
  void on_transition_setting_changed(const Glib::ustring& key);
  void on_transition_selection_changed();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gio::Settings> m_settings;
  Gtk::FontDialogButton* m_font {nullptr};
  Gtk::DropDown* m_transition {nullptr};
};

#endif /* GTKMM_EXAMPLEAPPPREFS_H_ */
