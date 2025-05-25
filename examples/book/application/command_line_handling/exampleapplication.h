/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#ifndef GTKMM_EXAMPLEAPPLICATION_H
#define GTKMM_EXAMPLEAPPLICATION_H

#include <gtkmm.h>

class ExampleApplication: public Gtk::Application
{
protected:
  ExampleApplication();

public:
  static Glib::RefPtr<ExampleApplication> create();

protected:
  //Overrides of default signal handlers:
  void on_activate()  override;
  void on_open(const Gio::Application::type_vec_files& files,
    const Glib::ustring& hint) override;
  int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line) override;
  int on_handle_local_options(const Glib::RefPtr<Glib::VariantDict>& options) override;

  //Callback functions for handling some command-line arguments
  bool on_option_arg_string(const Glib::ustring& option_name,
    const Glib::ustring& value, bool has_value);
  bool on_option_arg_filename(const Glib::ustring& option_name,
    const std::string& value, bool has_value);

  // These members should live as long as the OptionGroup to which they are added,
  // and as long as the Application to which that OptionGroup is added.
  int m_arg_int = 0;
  Glib::ustring m_arg_ustring;
  bool m_arg_boolean = false;
  Glib::OptionGroup m_option_group;

private:
  void create_window(const Glib::RefPtr<Gio::File>& file = Glib::RefPtr<Gio::File>());
};

#endif /* GTKMM_EXAMPLEAPPLICATION_H */
