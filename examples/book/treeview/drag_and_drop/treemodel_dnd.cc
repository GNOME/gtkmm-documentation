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

#include "treemodel_dnd.h"
#include <iostream>

TreeModel_Dnd::TreeModel_Dnd()
{
  //We can't just call Gtk::TreeModel(m_Columns) in the initializer list
  //because m_Columns does not exist when the base class constructor runs.
  //And we can't have a static m_Columns instance, because that would be
  //instantiated before the gtkmm type system.
  //So, we use this method, which should only be used just after creation:
  set_column_types(m_Columns);
}

Glib::RefPtr<TreeModel_Dnd> TreeModel_Dnd::create()
{
  return Glib::make_refptr_for_instance<TreeModel_Dnd>( new TreeModel_Dnd() );
}

bool
TreeModel_Dnd::row_draggable_vfunc(const Gtk::TreeModel::Path& path) const
{
  // Make the value of the "draggable" column determine whether this row can
  // be dragged:

  const const_iterator iter = get_iter(path);
  if(iter)
  {
    ConstRow row = *iter;
    bool is_draggable = row[m_Columns.m_col_draggable];
    return is_draggable;
  }

  return Gtk::TreeStore::row_draggable_vfunc(path);
}

bool
TreeModel_Dnd::row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest,
        const Glib::ValueBase& value) const
{
  //Make the value of the "receives drags" column determine whether a row can be
  //dragged into it:

  //dest is the path that the row would have after it has been dropped:
  //But in this case we are more interested in the parent row:
  auto dest_parent = dest;
  bool dest_is_not_top_level = dest_parent.up();
  if(!dest_is_not_top_level || dest_parent.empty())
  {
    //The user wants to move something to the top-level.
    //Let's always allow that.
  }
  else
  {
    //Get an iterator for the row at this path:
    const const_iterator iter_dest_parent = get_iter(dest_parent);
    if(iter_dest_parent)
    {
      ConstRow row = *iter_dest_parent;
      bool receives_drags = row[m_Columns.m_col_receivesdrags];
      return receives_drags;
    }
  }

  // You could also examine the row being dragged (via value)
  // if you must look at both rows to see whether a drop should be allowed.
  // You could use
  //   Glib::RefPtr<const Gtk::TreeModel> model_dragged_row;
  //   Gtk::TreeModel::Path path_dragged_row;
  //   Gtk::TreeModel::Path::get_row_drag_data(value,
  //     model_dragged_row, path_dragged_row);

  return Gtk::TreeStore::row_drop_possible_vfunc(dest, value);
}
