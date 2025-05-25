/* gtkmm example Copyright (C) 2023 gtkmm development team
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
#include <string>

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ColumnView Editable Cells example");
  set_default_size(400, 250);

  m_AlertDialog = Gtk::AlertDialog::create();

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the ColumnView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_ColumnView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

  // Create the List model:
  m_ListStore = Gio::ListStore<ModelColumns>::create();
  m_ListStore->append(ModelColumns::create(1, "Billy Bob", true, 10));
  m_ListStore->append(ModelColumns::create(2, "Joey Jojo", true, 20));
  m_ListStore->append(ModelColumns::create(3, "Rob McRoberts", false, 30));

  // Set list model and selection model.
  auto selection_model = Gtk::SingleSelection::create(m_ListStore);
  selection_model->set_autoselect(false);
  selection_model->set_can_unselect(true);
  m_ColumnView.set_model(selection_model);
  m_ColumnView.add_css_class("data-table"); // high density table

  // Make the columns reorderable.
  // This is not necessary, but it's nice to show the feature.
  m_ColumnView.set_reorderable(true);

  // Add the ColumnView's columns:

  // Id column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_id));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_id));
  auto column = Gtk::ColumnViewColumn::create("ID", factory);
  m_ColumnView.append_column(column);

  // Name column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_name));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_name));
  column = Gtk::ColumnViewColumn::create("Name", factory);
  m_ColumnView.append_column(column);

  // Foo column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_foo));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_foo));
  column = Gtk::ColumnViewColumn::create("foo", factory);
  m_ColumnView.append_column(column);

  // Number column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_number));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_number));
  column = Gtk::ColumnViewColumn::create("Number", factory);
  m_ColumnView.append_column(column);

  // Validated number column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_number_validated));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_number_validated));
  column = Gtk::ColumnViewColumn::create("validated (<10)", factory);
  m_ColumnView.append_column(column);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_setup_id(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_halign(Gtk::Align::END);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_edited_id), list_item));
  list_item->set_child(*label);
}

void ExampleWindow::on_setup_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_halign(Gtk::Align::START);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_edited_name), list_item));
  list_item->set_child(*label);
}

void ExampleWindow::on_setup_foo(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto checkbutton = Gtk::make_managed<Gtk::CheckButton>();
  checkbutton->signal_toggled().connect(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_edited_foo), list_item));
  list_item->set_child(*checkbutton);
}

void ExampleWindow::on_setup_number(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_halign(Gtk::Align::END);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_edited_number), list_item));
  list_item->set_child(*label);
}

void ExampleWindow::on_setup_number_validated(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_halign(Gtk::Align::START);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_edited_number_validated), list_item));
  list_item->set_child(*label);
}

void ExampleWindow::on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_col_id));
}

void ExampleWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_col_name);
}

void ExampleWindow::on_bind_foo(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto checkbutton = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
  if (!checkbutton)
    return;
  checkbutton->set_active(col->m_col_foo);
}

void ExampleWindow::on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  // 10 digits, using leading zeroes.
  label->set_text(Glib::ustring::sprintf("%010d", col->m_col_number));
}

void ExampleWindow::on_bind_number_validated(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_col_number_validated));
}

void ExampleWindow::on_edited_id(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Convert the new text to a number.
  const auto new_text = label->get_text();
  try
  {
    // Why isn't there an `unsigned int std::stoui()` function?
    unsigned long new_value = std::stoul(new_text.raw());
    // Store the new value in the model.
    col->m_col_id = static_cast<unsigned int>(new_value);
  }
  catch (const std::exception& err)
  {
    m_AlertDialog->set_message(
      "Could not convert \"" + new_text + "\" to an unsigned integer");
    m_AlertDialog->set_detail(err.what());
    m_AlertDialog->show(*this);
  }
  // Show the value in the Label.
  label->set_text(Glib::ustring::format(col->m_col_id));
}

void ExampleWindow::on_edited_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Store the new text in the model.
  col->m_col_name = label->get_text();
}

void ExampleWindow::on_edited_foo(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto checkbutton = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
  if (!checkbutton)
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Store the new value in the model.
  col->m_col_foo = checkbutton->get_active();
}

void ExampleWindow::on_edited_number(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Convert the new text to a number.
  const auto new_text = label->get_text();
  try
  {
    int new_value = std::stoi(new_text.raw());
    // Store the new value in the model.
    col->m_col_number = new_value;
  }
  catch (const std::exception& err)
  {
    m_AlertDialog->set_message(
      "Could not convert \"" + new_text + "\" to an integer.");
    m_AlertDialog->set_detail(err.what());
    m_AlertDialog->show(*this);
  }
  // Show the value in the Label. 10 digits, using leading zeroes.
  label->set_text(Glib::ustring::sprintf("%010d", col->m_col_number));
}

void ExampleWindow::on_edited_number_validated(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Convert the new text to a number.
  const auto new_text = label->get_text();
  try
  {
    int new_value = std::stoi(new_text.raw());
    if (new_value < 10)
      // Store the new value in the model.
      col->m_col_number_validated = new_value;
    else
    {
      m_AlertDialog->set_message(
        "The number must be less than 10. Please try again.");
      m_AlertDialog->set_detail("");
      m_AlertDialog->show(*this);
    }
  }
  catch (const std::exception& err)
  {
    m_AlertDialog->set_message(
      "Could not convert \"" + new_text + "\" to an integer.");
    m_AlertDialog->set_detail(err.what());
    m_AlertDialog->show(*this);
  }
  // Show the value in the label.
  label->set_text(Glib::ustring::format(col->m_col_number_validated));
}
