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

#include "messageslist.h"
#include <sstream>

MessagesList::MessagesList()
{
  /* Create a new scrolled window, with scrollbars only if needed */
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  add(m_TreeView);

  /* create list store */
  m_refListStore = Gtk::ListStore::create(m_Columns);

  m_TreeView.set_model(m_refListStore);

  /* Add some messages to the window */
  for(int i = 0; i < 10; ++i)
  {
    std::ostringstream text;
    text << "message #" << i;

    Gtk::TreeModel::Row row = *(m_refListStore->append());
    row[m_Columns.m_col_text] = text.str();
  }

  //Add the Model's column to the View's columns:
  m_TreeView.append_column("Messages", m_Columns.m_col_text);

  show_all_children();
}

MessagesList::~MessagesList()
{
}
