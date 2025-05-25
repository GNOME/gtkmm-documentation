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

MessagesList::MessagesList()
{
  /* Create a new scrolled window, with scrollbars only if needed */
  set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);

  set_child(m_ListView);

  /* create list store */
  m_refStringList = Gtk::StringList::create({});
  auto selection_model = Gtk::SingleSelection::create(m_refStringList);
  m_ListView.set_model(selection_model);

  /* Add some messages to the window */
  for (int i = 1; i <= 10; ++i)
    m_refStringList->append(Glib::ustring::format("message #", i));

  // Create a ListItemFactory to use for populating list items.
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::mem_fun(*this, &MessagesList::on_setup_message));
  factory->signal_bind().connect(sigc::mem_fun(*this, &MessagesList::on_bind_message));
  m_ListView.set_factory(factory);
}

MessagesList::~MessagesList()
{
}

void MessagesList::on_setup_message(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::Label>();
  label->set_halign(Gtk::Align::START);
  list_item->set_child(*label);
}

void MessagesList::on_bind_message(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(m_refStringList->get_string(pos));
}
