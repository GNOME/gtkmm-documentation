/* gtkmm example Copyright (C) 2013 gtkmm development team
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
struct SelectionModeStruct
{
  Gtk::SelectionMode mode;
  Glib::ustring text;
};

const std::array<SelectionModeStruct, 4> selectionModes =
{
  SelectionModeStruct{Gtk::SelectionMode::NONE,     "SelectionMode::NONE"},
  SelectionModeStruct{Gtk::SelectionMode::SINGLE,   "SelectionMode::SINGLE"},
  SelectionModeStruct{Gtk::SelectionMode::BROWSE,   "SelectionMode::BROWSE"},
  SelectionModeStruct{Gtk::SelectionMode::MULTIPLE, "SelectionMode::MULTIPLE"}
};

} // anonymous namespace

ExampleWindow::ExampleWindow() :
  m_HBox(Gtk::Orientation::HORIZONTAL),
  m_VBox1(Gtk::Orientation::VERTICAL),
  m_VBox2(Gtk::Orientation::VERTICAL),
  m_ListBox(),
  m_DropDown(),
  m_CheckButton_SingleClick("single click mode", /* mnemonic= */ false),
  m_ScrolledWindow(),
  m_Row3("blah3", 3),
  m_VBox_Row(Gtk::Orientation::VERTICAL),
  m_HBox_Row(Gtk::Orientation::HORIZONTAL),
  m_Label_Row("a check box"),
  m_CheckButton_Row1(),
  m_CheckButton_Row2(),
  m_Button_Row1("hi!"),
  m_Button_Row2("focusable row"),
  m_Button_Sort("sort"),
  m_Button_ReverseSort("reverse sort"),
  m_Button_Change("change"),
  m_Button_Filter("filter"),
  m_Button_Unfilter("unfilter"),
  m_Button_Add("add"),
  m_Button_Separate("separate"),
  m_Button_Unseparate("unseparate"),
  m_Button_Visibility("visibility")
{
  set_title("ListBox example");
  set_default_size(300, 300);

  m_HBox.set_margin(5);
  set_child(m_HBox);
  m_HBox.append(m_VBox1);

  // DropDown for selection mode.
  auto string_list = Gtk::StringList::create({});
  for (const auto& selectionMode : selectionModes)
    string_list->append(selectionMode.text);

  m_DropDown.set_model(string_list);
  m_DropDown.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_selection_mode_changed));
  m_VBox1.append(m_DropDown);

  const auto mode = m_ListBox.get_selection_mode();
  int index = 0;
  for (std::size_t i = 0; i < selectionModes.size(); ++i)
  {
    if (selectionModes[i].mode == mode)
    {
      index = i;
      break;
    }
  }
  m_DropDown.set_selected(index);

  // Check button for single click.
  m_CheckButton_SingleClick.set_active(m_ListBox.get_activate_on_single_click());
  m_CheckButton_SingleClick.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_single_click_toggled));
  m_VBox1.append(m_CheckButton_SingleClick);

  // Put the ListBox in a ScrolledWindow.
  m_ScrolledWindow.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_child(m_ListBox);
  m_HBox.append(m_ScrolledWindow);

  m_ListBox.signal_row_selected().connect(sigc::mem_fun(*this, &ExampleWindow::on_row_selected));
  m_ListBox.signal_row_activated().connect(sigc::mem_fun(*this, &ExampleWindow::on_row_activated));

  // Add some rows to the ListBox.
  auto row = Gtk::make_managed<ExampleRow>("blah4", 4);
  m_ListBox.append(*row);
  m_ListBox.append(m_Row3); // blah3
  row = Gtk::make_managed<ExampleRow>("blah1", 1);
  m_ListBox.append(*row);
  row = Gtk::make_managed<ExampleRow>("blah2", 2);
  m_ListBox.append(*row);

  row = Gtk::make_managed<ExampleRow>("", 0);
  m_HBox_Row.append(m_Label_Row);
  m_HBox_Row.append(m_CheckButton_Row1);
  m_HBox_Row.append(m_Button_Row1);
  m_VBox_Row.append(m_HBox_Row);
  m_VBox_Row.append(m_CheckButton_Row2);
  row->set_child(m_VBox_Row);
  m_ListBox.append(*row);

  row = Gtk::make_managed<ExampleRow>("", 0);
  m_Button_Row2.set_hexpand(false);
  m_Button_Row2.set_halign(Gtk::Align::START);
  row->set_child(m_Button_Row2);
  m_ListBox.append(*row);

  // Put buttons in a vertical box, and connect signal handlers.
  // There are several ways of connecting to a signal or any other function that
  // takes a sigc::slot.
  m_HBox.append(m_VBox2);
  m_VBox2.append(m_Button_Sort);
  // With sigc::mem_fun() or (for non-member functions and static member functions)
  // sigc::ptr_fun(). The only way before C++11 introduced lambda expressions.
  m_Button_Sort.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_sort_clicked));
  m_VBox2.append(m_Button_ReverseSort);
  // With a lambda expression. Does not disconnect automatically when ExampleWindow
  // is deleted, like sigc::mem_fun() does.
  m_Button_ReverseSort.signal_clicked().connect([this] { on_reverse_sort_clicked(); });
  m_VBox2.append(m_Button_Change);
  // With a lambda expression and sigc::track_obj() or sigc::track_object().
  // Disconnects automatically like sigc::mem_fun().
#if SIGCXX_MINOR_VERSION >= 4
  m_Button_Change.signal_clicked().connect(
    sigc::track_object([this] { on_change_clicked(); }, *this));
#else
  m_Button_Change.signal_clicked().connect(
    sigc::track_obj([this] { on_change_clicked(); }, *this));
#endif
  m_VBox2.append(m_Button_Filter);
  m_Button_Filter.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_filter_clicked));
  m_VBox2.append(m_Button_Unfilter);
  // If the signal handler is very short, it might be easier to skip the on_xxx()
  // method and put its contents directly in the lambda expression.
  m_Button_Unfilter.signal_clicked().connect(
    [this] { m_ListBox.unset_filter_func(); /* on_unfilter_clicked() */});
  m_VBox2.append(m_Button_Add);
  m_Button_Add.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_add_clicked));
  m_VBox2.append(m_Button_Separate);
  m_Button_Separate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_separate_clicked));
  m_VBox2.append(m_Button_Unseparate);
  m_Button_Unseparate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_unseparate_clicked));
  m_VBox2.append(m_Button_Visibility);
  m_Button_Visibility.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_visibility_clicked));
}

void ExampleWindow::on_selection_mode_changed()
{
  auto index = m_DropDown.get_selected();
  if (index == GTK_INVALID_LIST_POSITION)
    index = 0;
  m_ListBox.set_selection_mode(selectionModes[index].mode);
}

void ExampleWindow::on_single_click_toggled()
{
  std::cout << "single: " << m_CheckButton_SingleClick.get_active() << std::endl;
  m_ListBox.set_activate_on_single_click(m_CheckButton_SingleClick.get_active());
}

void ExampleWindow::on_row_selected(Gtk::ListBoxRow* row)
{
  std::cout << "selected row: " << row << std::endl;
}

void ExampleWindow::on_row_activated(Gtk::ListBoxRow* row)
{
  std::cout << "activated row: " << row << std::endl;
}

void ExampleWindow::on_sort_clicked()
{
  m_ListBox.set_sort_func(
    [] (Gtk::ListBoxRow* row1, Gtk::ListBoxRow* row2)
    { return sort_func(row1, row2); }
  );
}

void ExampleWindow::on_reverse_sort_clicked()
{
  m_ListBox.set_sort_func(
    [] (Gtk::ListBoxRow* row1, Gtk::ListBoxRow* row2)
    { return sort_func(row2, row1); }
  );
}

int ExampleWindow::sort_func(Gtk::ListBoxRow* row1, Gtk::ListBoxRow* row2)
{
  const auto xrow1 = dynamic_cast<ExampleRow*>(row1);
  const auto xrow2 = dynamic_cast<ExampleRow*>(row2);
  if (xrow1 && xrow2)
    return xrow1->get_sort_id() - xrow2->get_sort_id();

  return 0;
}

void ExampleWindow::on_change_clicked()
{
  if (m_Row3.get_text() == "blah3")
  {
    m_Row3.set_text("blah5");
    m_Row3.set_sort_id(5);
  }
  else
  {
    m_Row3.set_text("blah3");
    m_Row3.set_sort_id(3);
  }
}

void ExampleWindow::on_filter_clicked()
{
  m_ListBox.set_filter_func(
   [] (Gtk::ListBoxRow* row)
   {
     auto xrow = dynamic_cast<ExampleRow*>(row);
     return xrow && xrow->get_text() != "blah3";
   });
}

//void ExampleWindow::on_unfilter_clicked()
//{
//  m_ListBox.unset_filter_func();
//}

void ExampleWindow::on_add_clicked()
{
  static int new_button_nr = 1;
  const Glib::ustring text = "blah2 new " + Glib::ustring::format(new_button_nr);
  auto new_row = Gtk::make_managed<ExampleRow>(text, new_button_nr);
  m_ListBox.append(*new_row);
  ++new_button_nr;
}

void ExampleWindow::on_separate_clicked()
{
  m_ListBox.set_header_func(
    [] (Gtk::ListBoxRow* row, Gtk::ListBoxRow* before)
    { update_header_func(row, before); }
  );
}

void ExampleWindow::on_unseparate_clicked()
{
  m_ListBox.unset_header_func();
}

void ExampleWindow::update_header_func(Gtk::ListBoxRow* row, Gtk::ListBoxRow* before)
{
  auto xrow = dynamic_cast<ExampleRow*>(row);
  if (!before || (xrow && xrow->get_text() == "blah3"))
  {
    // Create header if needed.
    if (!row->get_header())
    {
      auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
      auto label = Gtk::make_managed<Gtk::Label>("Header");
      hbox->append(*label);
      auto button = Gtk::make_managed<Gtk::Button>("button");
      hbox->append(*button);
      row->set_header(*hbox);
    }

    auto header = row->get_header();
    if (header)
    {
      auto first_child = header->get_first_child();
      if (first_child)
      {
        auto label = dynamic_cast<Gtk::Label*>(first_child);
        if (label && xrow)
          label->set_text("Header " + Glib::ustring::format(xrow->get_sort_id()));
      }
    }
  }
  else
    row->unset_header();
}

void ExampleWindow::on_visibility_clicked()
{
  m_Row3.set_visible(!m_Row3.get_visible());
}
