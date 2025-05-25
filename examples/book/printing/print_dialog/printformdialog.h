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

#ifndef GTKMM_PRINT_FORM_DIALOG_H
#define GTKMM_PRINT_FORM_DIALOG_H

#include <gtkmm.h>
#include <pangomm.h>
#include <vector>

#define HAS_PRINT_DIALOG GTKMM_CHECK_VERSION(4,13,1)

#if HAS_PRINT_DIALOG
// We derive our own class from PrintDialog,
// so we can put the actual print implementation here.
class PrintFormDialog : public Gtk::PrintDialog
{
public:
  static Glib::RefPtr<PrintFormDialog> create();
  virtual ~PrintFormDialog();

  void set_name(const Glib::ustring& name) { m_Name = name; }
  void set_comments(const Glib::ustring& comments) { m_Comments = comments; }
  void do_setup(Gtk::Window* parent);
  void do_print(Gtk::Window* parent);

protected:
  PrintFormDialog();

  // PrintDialog callback slots:
  void on_setup_finish(const Glib::RefPtr<Gio::AsyncResult>& result);
  void on_print_finish(const Glib::RefPtr<Gio::AsyncResult>& result);
  Cairo::ErrorStatus write_func(const unsigned char* data, unsigned int length,
    Glib::RefPtr<Gio::OutputStream>& stream);
  void do_printing(const Cairo::RefPtr<Cairo::Context>& cairo_ctx);

  Glib::ustring m_Name;
  Glib::ustring m_Comments;
  Glib::RefPtr<Pango::Layout> m_refLayout;
  Glib::RefPtr<Gtk::PrintSetup> m_refPrintSetup;
};
#endif // HAS_PRINT_DIALOG

#endif // GTKMM_PRINT_FORM_DIALOG_H
