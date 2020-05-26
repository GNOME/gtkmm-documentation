/* gtkmm example Copyright (C) 2006 gtkmm development team
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

// This file is part of the printing/simple and printing/advanced examples

#include <gtkmm.h>
#include <memory>

class PrintFormOperation;

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow(const Glib::RefPtr<Gtk::Application>& app);
  virtual ~ExampleWindow();

protected:

  void build_main_menu(const Glib::RefPtr<Gtk::Application>& app);

  void print_or_preview(Gtk::PrintOperation::Action print_action);

  //PrintOperation signal handlers.
  //We handle these so can get necessary information to update the UI or print settings.
  //Our derived PrintOperation class also overrides some default signal handlers.
  void on_printoperation_status_changed();
  void on_printoperation_done(Gtk::PrintOperation::Result result);

  //Action signal handlers:
  void on_menu_file_new();
  void on_menu_file_page_setup();
  void on_menu_file_print_preview();
  void on_menu_file_print();
  void on_menu_file_quit();

  //Printing-related objects:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;
  Glib::RefPtr<PrintFormOperation> m_refPrintFormOperation;

  //Child widgets:
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

  unsigned m_ContextId;
  Gtk::Statusbar m_Statusbar;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  std::unique_ptr<Gtk::MessageDialog> m_pDialog;
};

#endif //GTKMM_EXAMPLEWINDOW_H
