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

#ifndef GTKMM_EXAMPLE_MESSAGESLIST_H
#define GTKMM_EXAMPLE_MESSAGESLIST_H

#include <gtkmm.h>

class MessagesList: public Gtk::ScrolledWindow
{
public:
  MessagesList();
  ~MessagesList() override;

protected:
  // Signal handlers:
  void on_setup_message(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_message(const Glib::RefPtr<Gtk::ListItem>& list_item);

  Glib::RefPtr<Gtk::StringList> m_refStringList; // The List Model.
  Gtk::ListView m_ListView; // The List View.
};
#endif //GTKMM_EXAMPLE_MESSAGESLIST_H
