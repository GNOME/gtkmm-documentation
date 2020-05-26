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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <memory>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow(const Glib::RefPtr<Gtk::Application>& app);
  ~ExampleWindow() override;

protected:
  //Signal handlers:
  void on_menu_file_files_dialog();
  void on_menu_file_quit();
  void on_menu_file_new();
  void on_dialog_response(int response_id);

  //Child widgets:
  Gtk::Box m_Box;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;

  Glib::RefPtr<Gtk::RecentManager> m_refRecentManager;

  std::unique_ptr<Gtk::FileChooserDialog> m_pDialog;
};

#endif //GTKMM_EXAMPLEWINDOW_H
