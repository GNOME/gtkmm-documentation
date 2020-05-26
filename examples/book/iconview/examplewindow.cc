/* gtkmm example Copyright (C) 2006 gtkmm development team
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

#include "examplewindow.h"
#include <iostream>

namespace
{
  class IconEntry
  {
  public:
    IconEntry()
    {}

    IconEntry(const std::string& filename, const Glib::ustring& description)
    : m_filename(filename),
      m_description(description)
    {}


    const std::string m_filename;
    const Glib::ustring m_description;
  };
}

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::IconView (ListStore + TreeModelSort) example");
  set_default_size(400, 400);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the TreeView inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_IconView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  // Create the Tree model:
  m_refListModel = Gtk::ListStore::create( m_Columns );
  m_refListModel->set_sort_column( m_Columns.m_col_description, Gtk::SortType::ASCENDING );

  m_IconView.set_model(m_refListModel);
  m_IconView.set_markup_column(m_Columns.m_col_description);
  m_IconView.set_pixbuf_column(m_Columns.m_col_pixbuf);
  m_IconView.signal_item_activated().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_item_activated) );
  m_IconView.signal_selection_changed().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_selection_changed) );

  IconEntry entries[] =
  {
    IconEntry("mozilla-firefox.png", "<b>Mozilla Firefox</b> Logo"),
    IconEntry("xmms.xpm", "<b>XMMS</b> Logo"),
    IconEntry("gnome-dice-1.svg", "<b>Gnome Dice 1</b> Logo"),
    IconEntry("gnome-dice-2.svg", "<b>Gnome Dice 2</b> Logo"),
    IconEntry("gnome-dice-3.svg", "<b>Gnome Dice 3</b> Logo"),
    IconEntry("gnome-dice-4.svg", "<b>Gnome Dice 4</b> Logo"),
    IconEntry("gnome-dice-5.svg", "<b>Gnome Dice 5</b> Logo"),
    IconEntry("gnome-dice-6.svg", "<b>Gnome Dice 6</b> Logo")
  };

  // Fill the TreeView's model
  //
  const int count = sizeof( entries ) / sizeof( IconEntry );
  for( int idx = 0; idx < count; ++idx )
  {
    add_entry( entries[idx].m_filename, entries[idx].m_description );
  }
}

ExampleWindow::~ExampleWindow()
{
}


void ExampleWindow::on_button_quit()
{
  hide();
}


void ExampleWindow::on_item_activated(const Gtk::TreeModel::Path& path)
{
  auto iter = m_refListModel->get_iter(path);
  auto row = *iter;

  const std::string filename = row[m_Columns.m_col_filename];
  const Glib::ustring description = row[m_Columns.m_col_description];

  std::cout  << "Item activated: filename="
      << filename
      << ", description="
      << description
      << std::endl;
}


void ExampleWindow::on_selection_changed()
{
  typedef std::vector<Gtk::TreeModel::Path> type_vec_paths;
  type_vec_paths selected = m_IconView.get_selected_items();
  if(!selected.empty())
  {
    const Gtk::TreeModel::Path& path = *selected.begin();
    auto iter = m_refListModel->get_iter(path);
    auto row = *iter;

    const std::string filename = row[m_Columns.m_col_filename];
    const Glib::ustring description = row[m_Columns.m_col_description];

  std::cout  << "Selection Changed to: filename="
      << filename
      << ", description="
      << description
      << std::endl;
  }
}

void ExampleWindow::add_entry(const std::string& filename,
        const Glib::ustring& description )
{
  auto row = *(m_refListModel->append());
  row[m_Columns.m_col_filename] = filename;
  row[m_Columns.m_col_description] = description;

  try
  {
    row[m_Columns.m_col_pixbuf] = Gdk::Pixbuf::create_from_file(filename);
  }
  catch (const Gdk::PixbufError& ex)
  {
    std::cerr << "Gdk::PixbufError: " << ex.what() << std::endl;
  }
  catch (const Glib::FileError& ex)
  {
    std::cerr << "Glib::FileError: " << ex.what() << std::endl;
  }
}


