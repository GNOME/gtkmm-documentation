/* gtkmm example Copyright (C) 2016 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "exampleappwindow.h"
#include <iostream>
#include <stdexcept>
#include <set>

ExampleAppWindow::ExampleAppWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder),
  m_settings(),
  m_stack(nullptr),
  m_search(nullptr),
  m_searchbar(nullptr),
  m_searchentry(nullptr),
  m_gears(nullptr),
  m_sidebar(nullptr),
  m_words(nullptr),
  m_lines(nullptr),
  m_lines_label(nullptr),
  m_binding_search_enabled(),
  m_binding_lines_visible()
{
  // Get widgets from the Gtk::Builder file.
  m_refBuilder->get_widget("stack", m_stack);
  if (!m_stack)
    throw std::runtime_error("No \"stack\" object in window.ui");

  m_refBuilder->get_widget("search", m_search);
  if (!m_search)
    throw std::runtime_error("No \"search\" object in window.ui");

  m_refBuilder->get_widget("searchbar", m_searchbar);
  if (!m_searchbar)
    throw std::runtime_error("No \"searchbar\" object in window.ui");

  m_refBuilder->get_widget("searchentry", m_searchentry);
  if (!m_searchentry)
    throw std::runtime_error("No \"searchentry\" object in window.ui");

  m_refBuilder->get_widget("gears", m_gears);
  if (!m_gears)
    throw std::runtime_error("No \"gears\" object in window.ui");

  m_refBuilder->get_widget("sidebar", m_sidebar);
  if (!m_sidebar)
    throw std::runtime_error("No \"sidebar\" object in window.ui");

  m_refBuilder->get_widget("words", m_words);
  if (!m_words)
    throw std::runtime_error("No \"words\" object in window.ui");

  m_refBuilder->get_widget("lines", m_lines);
  if (!m_lines)
    throw std::runtime_error("No \"lines\" object in window.ui");

  m_refBuilder->get_widget("lines_label", m_lines_label);
  if (!m_lines_label)
    throw std::runtime_error("No \"lines_label\" object in window.ui");

  // Bind settings.
  m_settings = Gio::Settings::create("org.gtkmm.exampleapp");
  m_settings->bind("transition", m_stack->property_transition_type());
  m_settings->bind("show-words", m_sidebar->property_reveal_child());

  // Bind properties of the search button to the search bar.
  m_binding_search_enabled = Glib::Binding::bind_property(m_search->property_active(),
    m_searchbar->property_search_mode_enabled(), Glib::BINDING_BIDIRECTIONAL);

  // Connect signal handlers.
  m_searchentry->signal_search_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_search_text_changed));
  m_stack->property_visible_child().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_visible_child_changed));
  m_sidebar->property_reveal_child().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_reveal_child_changed));

  // Connect the menu to the MenuButton m_gears, and bind the show-words setting
  // to the win.show-words action and the "Words" menu item.
  // (The connection between action and menu item is specified in gears_menu.ui.)
  auto menu_builder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/gears_menu.ui");
  auto object = menu_builder->get_object("menu");
  auto menu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(object);
  if (!menu)
    throw std::runtime_error("No \"menu\" object in gears_menu.ui");

  m_gears->set_menu_model(menu);
  add_action(m_settings->create_action("show-words"));

  // Bind the "visible" property of m_lines to the win.show-lines action, to
  // the "Lines" menu item and to the "visible" property of m_lines_label.
  // The GPropertyAction class is not wrapped in a glibmm class at the time of
  // writing (october 2016). We have to call a glib function directly.
  add_action(Glib::wrap((GAction*)
    g_property_action_new("show-lines", m_lines->gobj(), "visible")));
  m_binding_lines_visible = Glib::Binding::bind_property(m_lines->property_visible(),
    m_lines_label->property_visible());

  // Display the application menu in the application, not in the desktop environment.
  auto gtk_settings = Gtk::Settings::get_default();
  if (gtk_settings)
    gtk_settings->property_gtk_shell_shows_app_menu() = false;
  set_show_menubar(true);

  // Set the window icon.
  set_icon(Gdk::Pixbuf::create_from_resource("/org/gtkmm/exampleapp/exampleapp.png"));
}

//static
ExampleAppWindow* ExampleAppWindow::create()
{
  // Load the Builder file and instantiate its widgets.
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/window.ui");

  ExampleAppWindow* window = nullptr;
  refBuilder->get_widget_derived("app_window", window);
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void ExampleAppWindow::open_file_view(const Glib::RefPtr<Gio::File>& file)
{
  const Glib::ustring basename = file->get_basename();

  auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
  scrolled->set_hexpand(true);
  scrolled->set_vexpand(true);
  scrolled->show();
  auto view = Gtk::make_managed<Gtk::TextView>();
  view->set_editable(false);
  view->set_cursor_visible(false);
  view->show();
  scrolled->add(*view);
  m_stack->add(*scrolled, basename, basename);

  auto buffer = view->get_buffer();
  try
  {
    char* contents = nullptr;
    gsize length = 0;
    
    file->load_contents(contents, length);
    buffer->set_text(contents, contents+length);
    g_free(contents);
  }
  catch (const Glib::Error& ex)
  {
    std::cout << "ExampleAppWindow::open_file_view(\"" << file->get_parse_name()
      << "\"):\n  " << ex.what() << std::endl;
    return;
  }

  auto tag = buffer->create_tag();
  m_settings->bind("font", tag->property_font());
  buffer->apply_tag(tag, buffer->begin(), buffer->end());

  m_search->set_sensitive(true);
  update_words();
  update_lines();
}

void ExampleAppWindow::on_search_text_changed()
{
  const auto text = m_searchentry->get_text();
  if (text.empty())
    return;

  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
  {
    std::cout << "ExampleAppWindow::on_search_text_changed(): No visible child." << std::endl;
    return;
  }

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::on_search_text_changed(): No visible text view." << std::endl;
    return;
  }

  // Very simple-minded search implementation.
  auto buffer = view->get_buffer();
  Gtk::TextIter match_start;
  Gtk::TextIter match_end;
  if (buffer->begin().forward_search(text, Gtk::TEXT_SEARCH_CASE_INSENSITIVE,
      match_start, match_end))
  {
    buffer->select_range(match_start, match_end);
    view->scroll_to(match_start);
  }
}

void ExampleAppWindow::on_visible_child_changed()
{
  m_searchbar->set_search_mode(false);
  update_words();
  update_lines();  
}

void ExampleAppWindow::on_find_word(const Gtk::Button* button)
{
  m_searchentry->set_text(button->get_label());
}

void ExampleAppWindow::on_reveal_child_changed()
{
  update_words();
}

void ExampleAppWindow::update_words()
{
  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
    return;

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::update_words(): No visible text view." << std::endl;
    return;
  }
  auto buffer = view->get_buffer();

  // Find all words in the text buffer.
  std::set<Glib::ustring> words;
  auto start = buffer->begin();
  Gtk::TextIter end;
  while (start)
  {
    while (start && !start.starts_word())
      ++start;

    if (!start)
      break;

    end = start;
    end.forward_word_end();
    if (start == end)
      break;

    auto word = buffer->get_text(start, end, false);
    words.insert(word.lowercase());
    start = end;
  }

  // Remove old children from the ListBox.
  auto old_children = m_words->get_children();
  for (auto child : old_children)
  {
    m_words->remove(*child);
    delete child;
  }

  // Add new child buttons, one per unique word.
  for (const auto& word : words)
  {
    auto row = Gtk::make_managed<Gtk::Button>(word);
    row->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
      &ExampleAppWindow::on_find_word), row));
    row->show();
    m_words->add(*row);
  }
}

void ExampleAppWindow::update_lines()
{
  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
    return;

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::update_lines(): No visible text view." << std::endl;
    return;
  }
  auto buffer = view->get_buffer();

  int count = 0;
  auto iter = buffer->begin();
  while (iter)
  {
    ++count;
    if (!iter.forward_line())
      break;
  }
  m_lines->set_text(Glib::ustring::format(count));
}
