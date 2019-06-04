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

#include "cellrendererpopup.h"

#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>


class CellRendererList : public CellRendererPopup
{
public:
  CellRendererList();
  virtual ~CellRendererList();

  void append_list_item(const Glib::ustring& text);
  Glib::ustring get_selected_item();

protected:
  void on_show_popup(const Glib::ustring& path, int x1, int y1, int x2, int y2) override;

private:
  typedef CellRendererList Self;

  Glib::RefPtr<Gtk::ListStore>  list_store_;
  Gtk::TreeView                 tree_view_;
  Glib::RefPtr<Gtk::GestureClick> gesture_;

  void on_tree_view_released(int n_press, double x, double y);
  void on_tree_selection_changed();
};

