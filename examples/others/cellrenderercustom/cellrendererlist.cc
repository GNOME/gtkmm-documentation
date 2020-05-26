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

#include <gtkmm.h>
#include "cellrendererlist.h"
#include "popupentry.h"

namespace
{

struct PopupColumns : public Gtk::TreeModel::ColumnRecord
{
  Gtk::TreeModelColumn<Glib::ustring> item;
  PopupColumns() { add(item); }
};

const PopupColumns& popup_columns()
{
  static const PopupColumns columns;
  return columns;
}

} // anonymous namespace


CellRendererList::CellRendererList()
:
  Glib::ObjectBase  (typeid(CellRendererList)),
  CellRendererPopup (),
  list_store_       (Gtk::ListStore::create(popup_columns())),
  tree_view_        (list_store_)
{
  tree_view_.set_headers_visible(false);
  tree_view_.append_column("", popup_columns().item);

  gesture_ = Gtk::GestureClick::create();
  gesture_->set_button(GDK_BUTTON_PRIMARY);
  gesture_->signal_released().connect(
    sigc::mem_fun(*this, &Self::on_tree_view_released));
  tree_view_.add_controller(gesture_);

  const auto selection = tree_view_.get_selection();
  selection->set_mode(Gtk::SelectionMode::BROWSE);
  selection->signal_changed().connect(sigc::mem_fun(*this, &Self::on_tree_selection_changed));

  Gtk::Frame *const frame = Gtk::make_managed<Gtk::Frame>();
  get_popup_window()->set_child(*frame);

  frame->set_child(tree_view_);

  set_focus_widget(tree_view_);
}

CellRendererList::~CellRendererList()
{}

void CellRendererList::append_list_item(const Glib::ustring& text)
{
  auto row = *list_store_->append();
  row[popup_columns().item] = text;
}

Glib::ustring CellRendererList::get_selected_item()
{
  if(const auto selected = tree_view_.get_selection()->get_selected())
  {
    return (*selected)[popup_columns().item];
  }

  return Glib::ustring();
}

void CellRendererList::on_show_popup(const Glib::ustring& path, int x1, int y1, int x2, int y2)
{
  tree_view_.set_size_request(x2 - x1, -1);

  CellRendererPopup::on_show_popup(path, x1, y1, x2, y2);
}

void CellRendererList::on_tree_view_released(int /* n_press */, double /* x */, double /* y */)
{
  hide_popup();
}

void CellRendererList::on_tree_selection_changed()
{
  get_popup_entry()->set_text(get_selected_item());
}
