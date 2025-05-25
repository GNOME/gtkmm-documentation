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

#ifndef GTKMM_EXAMPLETREEMODEL_H
#define GTKMM_EXAMPLETREEMODEL_H

#include <gtkmm.h>
#include <vector>
#include <utility>

class MemoryTreeModel;

// One MemoryItem will represent one chunk of information to
// be shown in the Treeview, i.e. one row with subnodes.
struct MemoryItem
{
  MemoryItem(int i);

  // data for top level nodes
  int mi_1 = 0;
  Glib::ustring mi_2;

  // for first level of subnodes
  int mi_A1 = 0;
  Glib::ustring mi_A2;

  // for second level of subnodes
  int mi_B1 = 0;
  Glib::ustring mi_B2;
};

class Memory
{
public:
  template <typename... Args>
  void emplace_back(Args&&... args);

  void push_back(const MemoryItem& item);
  void pop_back();
  void set_model(const Glib::RefPtr<MemoryTreeModel>& model);
  const MemoryItem& operator[](int i) const;
  std::size_t size() const;

private:
  // These we will show in the TreeView
  std::vector<MemoryItem> m_item;

  Glib::RefPtr<MemoryTreeModel> m_model;
};

class MemoryColumns: public Gtk::TreeModel::ColumnRecord
{
public:
  MemoryColumns();
  virtual ~MemoryColumns();

  Gtk::TreeModelColumn<int>           col_i; // A column for the ints
  Gtk::TreeModelColumn<Glib::ustring> col_s; // A column for the strings
};

class MemoryTreeModel : public Gtk::TreeModel, public Glib::Object
{
public:
  MemoryTreeModel();
  virtual ~MemoryTreeModel();

  static Glib::RefPtr<MemoryTreeModel> create();

  void set_memory(const Memory* m = nullptr);
  void memory_row_inserted(unsigned long i);
  void memory_row_deleted(unsigned long i);

protected:
  // Overrides:
  Gtk::TreeModel::Flags get_flags_vfunc() const override;
  int get_n_columns_vfunc() const override;
  GType get_column_type_vfunc(int index) const override;
  void get_value_vfunc(const const_iterator& iter, int column, Glib::ValueBase& value) const override;
  bool iter_next_vfunc(const iterator& iter, iterator& iter_next) const override;
  bool iter_children_vfunc(const iterator& parent, iterator& iter) const override;
  bool iter_has_child_vfunc(const const_iterator& iter) const override;
  int iter_n_children_vfunc(const const_iterator& iter) const override;
  int iter_n_root_children_vfunc() const override;
  bool iter_nth_child_vfunc(const iterator& parent, int n, iterator& iter) const override;
  bool iter_nth_root_child_vfunc(int n, iterator& iter) const override;
  bool iter_parent_vfunc(const iterator& child, iterator& iter) const override;
  Path get_path_vfunc(const const_iterator& iter) const override;
  bool get_iter_vfunc(const Path& path, iterator& iter) const override;

  // These vfuncs are optional to implement.
  // void ref_node_vfunc(const iterator& iter) const override;
  // void unref_node_vfunc(const iterator& iter) const override;

  bool is_valid(const const_iterator& iter) const;

private:
  using IntColumn    = Gtk::TreeModelColumn<int>;
  using StringColumn = Gtk::TreeModelColumn<Glib::ustring>;

  mutable IntColumn::ValueType    m_ic;
  mutable StringColumn::ValueType m_sc;

  MemoryColumns m_Columns;

  // The gate for the model to the information to be shown.
  // The MemoryTreeModel does not own the data. 
  const Memory* m_Memory = nullptr;
  // When the model's stamp and the TreeIter's stamp are equal, the TreeIter is valid.
  int m_stamp = 0;
};

template <typename... Args>
void Memory::emplace_back(Args&&... args)
{
  m_item.emplace_back(std::forward<Args>(args)...);
  if (m_model)
    m_model->memory_row_inserted(m_item.size()-1);
}

#endif // GTKMM_EXAMPLETREEMODEL_H
