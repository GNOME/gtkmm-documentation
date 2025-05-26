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

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Label("Press a or b to see a list of possible completions and actions."),
  m_Button_Close("Close")
{
  //set_size_request(200, 100);
  set_title("Gtk::EntryCompletion");

  add(m_VBox);
  m_VBox.pack_start(m_Entry, Gtk::PACK_SHRINK);

  m_VBox.pack_start(m_Label, Gtk::PACK_EXPAND_WIDGET);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_VBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);
  m_Button_Close.set_can_default();
  m_Button_Close.grab_default();

  //Add an EntryCompletion:
  auto completion =
      Gtk::EntryCompletion::create();
  m_Entry.set_completion(completion);

  //Create and fill the completion's filter model
  auto refCompletionModel =
      Gtk::ListStore::create(m_Columns);
  completion->set_model(refCompletionModel);

  // For more complex comparisons, use a filter match callback, like this.
  // See the comment below for more details:
  //completion->set_match_func( sigc::mem_fun(*this,
              //&ExampleWindow::on_completion_match) );

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(refCompletionModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Alan Zebedee";

  row = *(refCompletionModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Adrian Boo";

  row = *(refCompletionModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Bob McRoberts";

  row = *(refCompletionModel->append());
  row[m_Columns.m_col_id] = 4;
  row[m_Columns.m_col_name] = "Bob McBob";

  //Tell the completion what model column to use to
  //- look for a match (when we use the default matching, instead of
  //  set_match_func().
  //- display text in the entry when a match is found.
  completion->set_text_column(m_Columns.m_col_name);

  //Add actions to the completion:
  //These are just extra items shown at the bottom of the list of possible
  //completions.

  //Remember them for later.
  m_CompletionActions[0] = "Use Wizard";
  m_CompletionActions[1] = "Browse for Filename";

  for(const auto& the_pair : m_CompletionActions)
  {
    auto position = the_pair.first;
    auto title = the_pair.second;
    completion->insert_action_text(title, position);
  }

  completion->signal_action_activated().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_completion_action_activated) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  hide();
}

/* You can do more complex matching with a handler like this.
 * For instance, you could check for substrings inside the string instead of the start,
 * or you could look for the key in extra model columns as well as the model column that will be displayed.
 * The code here is not actually more complex - it's a reimplementation of the default behaviour.
 *
bool ExampleWindow::on_completion_match(const Glib::ustring& key, const
        Gtk::TreeModel::const_iterator& iter)
{
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring::size_type key_length = key.size();
    Glib::ustring filter_string = row[m_Columns.m_col_name];

    Glib::ustring filter_string_start = filter_string.substr(0, key_length);
    //The key is lower-case, even if the user input is not.
    filter_string_start = filter_string_start.lowercase();

    if(key == filter_string_start)
      return true; //A match was found.
  }

  return false; //No match.
}
*/

void ExampleWindow::on_completion_action_activated(int index)
{
  type_actions_map::iterator iter = m_CompletionActions.find(index);
  if(iter != m_CompletionActions.end()) //If it's in the map
  {
    Glib::ustring title = iter->second;
    std::cout << "Action selected: " << title << std::endl;
  }
}

