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

  bool on_tree_view_button_release_event(GdkEventButton* event);
  void on_tree_selection_changed();
};

