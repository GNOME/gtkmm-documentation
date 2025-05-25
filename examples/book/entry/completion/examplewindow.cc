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
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Label("Press a or b to see a list of possible completions."),
  m_Button_Close("Close")
{
  //set_size_request(200, 100);
  set_title("Gtk::EntryCompletion");

  set_child(m_VBox);
  m_VBox.append(m_Entry);

  m_VBox.append(m_Label);
  m_Label.set_expand(true);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_VBox.append(m_Button_Close);
  set_default_widget(m_Button_Close);

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
  auto row = *(refCompletionModel->append());
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
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  set_visible(false);
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
    const auto row = *iter;

    const auto key_length = key.size();
    auto filter_string = row[m_Columns.m_col_name];

    auto filter_string_start = filter_string.substr(0, key_length);
    //The key is lower-case, even if the user input is not.
    filter_string_start = filter_string_start.lowercase();

    if(key == filter_string_start)
      return true; //A match was found.
  }

  return false; //No match.
}
*/
