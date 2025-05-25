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

#include "treeview_withpopup.h"
#include <iostream>

TreeView_WithPopup::TreeView_WithPopup()
{
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  set_model(m_refTreeModel);

  //Fill the TreeView's model
  auto row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "right-click on this";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "or this";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "or this, for a popup context menu";

  //Add the TreeView's view columns:
  append_column("ID", m_Columns.m_col_id);
  append_column("Name", m_Columns.m_col_name);

  // Catch button press events:
  auto refGesture = Gtk::GestureClick::create();
  refGesture->set_button(GDK_BUTTON_SECONDARY);
  refGesture->signal_pressed().connect(
    sigc::mem_fun(*this, &TreeView_WithPopup::on_popup_button_pressed));
  add_controller(refGesture);

  // Fill popup menu:
  auto gmenu = Gio::Menu::create();
  gmenu->append("_Edit", "popup.edit");
  gmenu->append("_Process", "popup.process");
  gmenu->append("_Remove", "popup.remove");

  m_MenuPopup.set_parent(*this);
  m_MenuPopup.set_menu_model(gmenu);
  m_MenuPopup.set_has_arrow(false);

  // Create actions:
  auto refActionGroup = Gio::SimpleActionGroup::create();

  refActionGroup->add_action("edit",
    sigc::mem_fun(*this, &TreeView_WithPopup::on_menu_file_popup_generic));
  refActionGroup->add_action("process",
    sigc::mem_fun(*this, &TreeView_WithPopup::on_menu_file_popup_generic));
  refActionGroup->add_action("remove",
    sigc::mem_fun(*this, &TreeView_WithPopup::on_menu_file_popup_generic));

  insert_action_group("popup", refActionGroup);
}

TreeView_WithPopup::~TreeView_WithPopup()
{
}

void TreeView_WithPopup::on_popup_button_pressed(int /* n_press */, double x, double y)
{
  const Gdk::Rectangle rect(x, y, 1, 1);
  m_MenuPopup.set_pointing_to(rect);
  m_MenuPopup.popup();
}

void TreeView_WithPopup::on_menu_file_popup_generic()
{
  std::cout << "A popup menu item was selected." << std::endl;

  auto refSelection = get_selection();
  if(refSelection)
  {
    auto iter = refSelection->get_selected();
    if(iter)
    {
      int id = (*iter)[m_Columns.m_col_id];
      std::cout << "  Selected ID=" << id << std::endl;
    }
  }
}
