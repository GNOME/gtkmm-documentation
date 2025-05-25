/* gtkmm example Copyright (C) 2006 gtkmm development team
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
#include <array>
#include <iostream>

namespace
{
  struct GridEntry
  {
    std::string m_filename;
    Glib::ustring m_description;
  };

  std::array<GridEntry, 8> entries =
  {
    GridEntry{"mozilla-firefox.png", "<b>Mozilla Firefox</b> Logo"},
    GridEntry{"xmms.xpm",            "<b>XMMS</b> Logo"},
    GridEntry{"gnome-dice-1.svg",    "<b>Gnome Dice 1</b> Logo"},
    GridEntry{"gnome-dice-2.svg",    "<b>Gnome Dice 2</b> Logo"},
    GridEntry{"gnome-dice-3.svg",    "<b>Gnome Dice 3</b> Logo"},
    GridEntry{"gnome-dice-4.svg",    "<b>Gnome Dice 4</b> Logo"},
    GridEntry{"gnome-dice-5.svg",    "<b>Gnome Dice 5</b> Logo"},
    GridEntry{"gnome-dice-6.svg",    "<b>Gnome Dice 6</b> Logo"}
  };

} // anonymous namespace

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::GridView (Gio::ListStore) example");
  set_default_size(400, 400);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the GridView inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_GridView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

  // Create the data model:
  m_data_model = Gio::ListStore<ModelColumns>::create();
  m_selection_model = Gtk::SingleSelection::create(m_data_model);
  m_selection_model->set_autoselect(false);

  m_factory = Gtk::SignalListItemFactory::create();
  m_factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_listitem));
  m_factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_listitem));

  // Fill the Gio::ListStore's data model and sort it.
  for (const auto& entry : entries)
    add_entry(entry.m_filename, entry.m_description);
  m_data_model->sort(sigc::mem_fun(*this, &ExampleWindow::on_model_sort));

  m_GridView.set_model(m_selection_model);
  m_GridView.set_factory(m_factory);

  m_GridView.signal_activate().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_item_activated));
  m_selection_model->property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_selection_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a vertical Box with an Image and a Label.
  auto vBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  auto picture = Gtk::make_managed<Gtk::Picture>();
  picture->set_can_shrink(false);
  picture->set_halign(Gtk::Align::CENTER);
  picture->set_valign(Gtk::Align::END);
  vBox->append(*picture);
  vBox->append(*Gtk::make_managed<Gtk::Label>());
  list_item->set_child(*vBox);
}

void ExampleWindow::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto vBox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!vBox)
    return;
  auto picture = dynamic_cast<Gtk::Picture*>(vBox->get_first_child());
  if (!picture)
    return;
  auto label = dynamic_cast<Gtk::Label*>(picture->get_next_sibling());
  if (!label)
    return;
  picture->set_paintable(col->m_texture);
  label->set_markup(col->m_description);
}

void ExampleWindow::on_item_activated(unsigned int position)
{
  auto col = m_data_model->get_item(position);
  if (!col)
    return;

  const std::string filename = col->m_filename;
  const Glib::ustring description = col->m_description;

  std::cout  << "Item activated: filename=" << filename
    << ", description=" << description << std::endl;
}

void ExampleWindow::on_selection_changed()
{
  auto position = m_selection_model->get_selected();
  auto col = m_data_model->get_item(position);
  if (!col)
    return;

  const std::string filename = col->m_filename;
  const Glib::ustring description = col->m_description;

  std::cout  << "Selection Changed to: filename=" << filename
    << ", description=" << description << std::endl;
}

int ExampleWindow::on_model_sort(const Glib::RefPtr<const ModelColumns>& a,
  const Glib::RefPtr<const ModelColumns>& b)
{
  return (a->m_description < b->m_description) ? -1 : ((a->m_description > b->m_description) ? 1 : 0);
}

void ExampleWindow::add_entry(const std::string& filename,
        const Glib::ustring& description )
{
  try
  {
     auto pixbuf = Gdk::Pixbuf::create_from_file(filename);
     auto texture = Gdk::Texture::create_for_pixbuf(pixbuf);
     m_data_model->append(ModelColumns::create(filename, description, texture));
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
