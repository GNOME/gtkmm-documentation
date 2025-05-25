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

class PrintFormDialog;

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow(const Glib::RefPtr<Gtk::Application>& app);
  ~ExampleWindow() override;

protected:
  void build_main_menu(const Glib::RefPtr<Gtk::Application>& app);

  // Action signal handlers:
  void on_menu_file_new();
  void on_menu_file_print_setup();
  void on_menu_file_print();
  void on_menu_file_quit();

  // Printing-related objects:
  Glib::RefPtr<PrintFormDialog> m_refPrintFormDialog;

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::Grid m_Grid;

  Gtk::Label m_NameLabel;
  Gtk::Entry m_NameEntry;

  Gtk::Label m_SurnameLabel;
  Gtk::Entry m_SurnameEntry;

  Gtk::Label m_CommentsLabel;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;

  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
};
#endif //GTKMM_EXAMPLEWINDOW_H
