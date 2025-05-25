/* gtkmm example Copyright (C) 2020 gtkmm development team
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

#include "exampletreemodel.h"

namespace
{
  enum
  {
    COL_INT,
    COL_STRING
  };
}

//////////////// MemoryItem

MemoryItem::MemoryItem(int i)
: mi_1(i),      mi_2(Glib::ustring::format("item ", mi_1)),
  mi_A1(11*i),  mi_A2(Glib::ustring::format("item A", mi_A1)),
  mi_B1(111*i), mi_B2(Glib::ustring::format("item B", mi_B1))
{
}

//////////////// Memory

void Memory::push_back(const MemoryItem& item)
{
  m_item.push_back(item);

  if (m_model)
    m_model->memory_row_inserted(m_item.size()-1);
}

void Memory::pop_back()
{
  if (m_item.size() > 0)
  {
    m_item.pop_back();

    if (m_model)
      m_model->memory_row_deleted(m_item.size());
  }
}

void Memory::set_model(const Glib::RefPtr<MemoryTreeModel>& model)
{
  if (m_model)
    m_model->set_memory(nullptr);

  m_model = model;
  if (m_model)
    m_model->set_memory(this);
}

const MemoryItem& Memory::operator[](int i) const
{
  return m_item[i];
}

std::size_t Memory::size() const
{
  return m_item.size();
}

//////////////// MemoryColumn

MemoryColumns::MemoryColumns()
{
  add(col_i);
  add(col_s);
}

MemoryColumns::~MemoryColumns()
{
}

//////////////// MemoryTreeModel

MemoryTreeModel::MemoryTreeModel()
: Glib::ObjectBase(typeid(MemoryTreeModel)), // Register a custom GType.
  Glib::Object() // The custom GType is actually registered here.
{
 m_ic.init(IntColumn::ValueType::value_type());
 m_sc.init(StringColumn::ValueType::value_type());
}

MemoryTreeModel::~MemoryTreeModel()
{
}

Glib::RefPtr<MemoryTreeModel> MemoryTreeModel::create()
{
  return Glib::make_refptr_for_instance<MemoryTreeModel>(new MemoryTreeModel);
}

void MemoryTreeModel::set_memory(const Memory* m)
{
  m_Memory = m;
  ++m_stamp;
}

void MemoryTreeModel::memory_row_inserted(unsigned long i)
{
  if (!m_Memory)
    return;

  // Inform TreeView that a new node has been inserted, including two subnodes.
  ++m_stamp;
  iterator iter;
  iter.set_stamp(m_stamp);
  iter.gobj()->user_data = (void*)i; // row index
  for (unsigned long depth = 1; depth <= 3; ++depth)
  {
    iter.gobj()->user_data2 = (void*)depth; // sublevel
    row_inserted(get_path(iter), iter);
  }
}

void MemoryTreeModel::memory_row_deleted(unsigned long i)
{
  if (!m_Memory)
    return;

  // Inform TreeView that a node has been deleted, including two subnodes.
  ++m_stamp;
  Path path(1, i);
  for (unsigned long depth = 1; depth <= 3; ++depth)
  {
    row_deleted(path);
    path.push_back(0); // Only one child node per level, index 0
  }
}

Gtk::TreeModel::Flags MemoryTreeModel::get_flags_vfunc() const
{
   return Gtk::TreeModel::Flags(0);
}

int MemoryTreeModel::get_n_columns_vfunc() const
{
   return m_Columns.size();
}

// What information does one row contain?
void MemoryTreeModel::get_value_vfunc(const const_iterator& iter, int column, Glib::ValueBase& value) const
{
  // user_data contains the row number
  const unsigned long row = (unsigned long)iter.gobj()->user_data;

  if (!is_valid(iter) || row >= m_Memory->size())
    return;

  // user_data2 contains the depth of the node
  const unsigned long depth = (unsigned long)iter.gobj()->user_data2;

  const MemoryItem& mi = (*m_Memory)[row];

  switch (column)
  {
  case COL_INT:
  {
    int result_int = 0;
    if (depth <= 1) // top level node
      result_int = mi.mi_1;
    else if (depth == 2) // first subnode level
      result_int = mi.mi_A1;
    else // second subnode level
      result_int = mi.mi_B1;

    m_ic.set(result_int);
    value.init(m_ic.value_type());
    value = m_ic;
    break;
  }
  case COL_STRING:
  {
    Glib::ustring result_string;
    // Same partitioning as for the ints
    if (depth <= 1)
      result_string = mi.mi_2;
    else if (depth == 2)
      result_string = mi.mi_A2;
    else
      result_string = mi.mi_B2;

    m_sc.set(result_string);
    value.init(m_sc.value_type());
    value = m_sc;
    break;
  }
  }
}

// What is the next node from this one?
bool MemoryTreeModel::iter_next_vfunc(const iterator& iter, iterator& iter_next) const
{
  const unsigned long row = (unsigned long)iter.gobj()->user_data;
  const unsigned long depth = (unsigned long)iter.gobj()->user_data2;

  if (!is_valid(iter)
      || row + 1 >= m_Memory->size() // beyond the last row
      || depth > 1) // the sublevels have just one child, no next node
  {
    iter_next = iterator(); // There is no next row.
    return false;
  }

  // Set markers for next node
  iter_next.set_stamp(m_stamp);
  iter_next.gobj()->user_data = (void*)(row + 1);
  iter_next.gobj()->user_data2 = (void*)depth;
  return true;
}

// Get the first child of this parent node
bool MemoryTreeModel::iter_children_vfunc(const iterator& parent, iterator& iter) const
{
  return iter_nth_child_vfunc(parent, 0, iter);
}

bool MemoryTreeModel::iter_has_child_vfunc(const const_iterator& iter) const
{
  return iter_n_children_vfunc(iter) > 0;
}

int MemoryTreeModel::iter_n_children_vfunc(const const_iterator& iter) const
{
  const unsigned long depth = (unsigned long)iter.gobj()->user_data2;

  if (!is_valid(iter) || depth == 0) // invalid or uninitialized node
    return 0;
  if (depth <= 2) // only two sublevels of nodes
    return 1;
  return 0; // no nodes
}

int MemoryTreeModel::iter_n_root_children_vfunc() const
{
  return m_Memory->size(); // number of rows
}

// Get the nth child of this parent node
bool MemoryTreeModel::iter_nth_child_vfunc(const iterator& parent, int n , iterator& iter) const
{
  const unsigned long row = (unsigned long)parent.gobj()->user_data;
  const unsigned long depth = (unsigned long)parent.gobj()->user_data2;

  if (!is_valid(parent)
      || depth > 2 // only two sublevels of nodes
      || n > 0) // and one child node only
  {
    iter = iterator();
    return false; // There are no children.
  }

  iter.set_stamp(m_stamp);
  iter.gobj()->user_data = (void*)row; // row index
  iter.gobj()->user_data2 = (void*)(depth + 1); // sublevel
  return true;
}

// Get the nth row
bool MemoryTreeModel::iter_nth_root_child_vfunc(int n, iterator& iter) const
{
  const unsigned long row = n;

  if (row >= m_Memory->size())
  {
    iter = iterator();
    return false; // No such row
  }

  iter.set_stamp(m_stamp);
  iter.gobj()->user_data = (void*)row; // row index
  iter.gobj()->user_data2 = (void*)1; // top level node
  return true; // n < available rows
}

// Get the parent for this child
bool MemoryTreeModel::iter_parent_vfunc(const iterator& child, iterator& iter) const
{
  const unsigned long row = (unsigned long)child.gobj()->user_data;
  const unsigned long depth = (unsigned long)child.gobj()->user_data2;

  if (!is_valid(child)
      || depth <= 1) // top level
  {
    iter = iterator();
    return false; // There is no parent.
  }

  iter.set_stamp(m_stamp);
  iter.gobj()->user_data = (void*)row; // row index
  iter.gobj()->user_data2 = (void*)(depth - 1); // one level up
  return true;
}

// Define a node
bool MemoryTreeModel::get_iter_vfunc(const Path& path, iterator& iter) const
{
  const unsigned long row = path[0]; // row_index
  const unsigned long depth = path.size();

  if (row >= m_Memory->size()
      || depth == 0 || depth > 3) // only two levels of subnodes
  {
    iter = iterator();
    return false;
  }

  iter.set_stamp(m_stamp);
  iter.gobj()->user_data = (void*)row; // row index
  iter.gobj()->user_data2 = (void*)depth; // sublevel
  iter.gobj()->user_data3 = (void*)-1; // just to show its presence, really
  return true;
}

Gtk::TreeModel::Path MemoryTreeModel::get_path_vfunc(const const_iterator& iter) const
{
  const unsigned long row = (unsigned long)iter.gobj()->user_data;
  const unsigned long depth = (unsigned long)iter.gobj()->user_data2;

  Path path(1, row);
  for (unsigned long i = 2; i <= depth; ++i)
    path.push_back(0); // Only one child node per level, index 0
  return path;
}

GType MemoryTreeModel::get_column_type_vfunc(int index) const
{
  if (index < 0 || static_cast<unsigned int>(index) >= m_Columns.size())
    return 0;

  return m_Columns.types()[index];
}

bool MemoryTreeModel::is_valid(const const_iterator& iter) const
{
  // Anything that modifies the model's structure should change the model's stamp,
  // so that old iterators are ignored.
  return m_stamp == iter.get_stamp();
}
