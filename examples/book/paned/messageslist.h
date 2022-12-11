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
