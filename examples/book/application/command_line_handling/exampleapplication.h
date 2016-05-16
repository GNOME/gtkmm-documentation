/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
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

  //A regular signal handler, because there is no default signal handler for this:
  int on_handle_local_options(const Glib::RefPtr<Glib::VariantDict>& options);

  //Callback functions for handling some command-line arguments
  bool on_option_arg_string(const Glib::ustring& option_name,
    const Glib::ustring& value, bool has_value);
  bool on_option_arg_filename(const Glib::ustring& option_name,
    const std::string& value, bool has_value);

private:
  void create_window(const Glib::RefPtr<Gio::File>& file = Glib::RefPtr<Gio::File>());

  void on_window_hide(Gtk::Window* window);
};

#endif /* GTKMM_EXAMPLEAPPLICATION_H */
