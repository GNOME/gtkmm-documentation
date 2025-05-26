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

#ifndef GTKMM_PRINT_FORM_OPERATION_H
#define GTKMM_PRINT_FORM_OPERATION_H

#include <gtkmm.h>
#include <pangomm.h>
#include <vector>

//We derive our own class from PrintOperation,
//so we can put the actual print implementation here.
class PrintFormOperation : public Gtk::PrintOperation
{
 public:
  static Glib::RefPtr<PrintFormOperation> create();
  virtual ~PrintFormOperation();

  void set_name(const Glib::ustring& name) { m_Name = name; }
  void set_comments(const Glib::ustring& comments) { m_Comments = comments; }

 protected:
  PrintFormOperation();

  //PrintOperation default signal handler overrides:
  void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context) override;
  void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr) override;

  Glib::ustring m_Name;
  Glib::ustring m_Comments;
  Glib::RefPtr<Pango::Layout> m_refLayout;
  std::vector<int> m_PageBreaks; // line numbers where a page break occurs
};

#endif // GTKMM_PRINT_FORM_OPERATION_H
