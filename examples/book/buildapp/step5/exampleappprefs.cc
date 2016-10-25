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

#include "exampleappprefs.h"
#include "exampleappwindow.h"
#include <stdexcept>

ExampleAppPrefs::ExampleAppPrefs(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::Dialog(cobject),
  m_refBuilder(refBuilder),
  m_settings(),
  m_font(nullptr),
  m_transition(nullptr)
{
  m_refBuilder->get_widget("font", m_font);
  if (!m_font)
    throw std::runtime_error("No \"font\" object in prefs.ui");

  m_refBuilder->get_widget("transition", m_transition);
  if (!m_transition)
    throw std::runtime_error("No \"transition\" object in prefs.ui");

  m_settings = Gio::Settings::create("org.gtkmm.exampleapp");
  m_settings->bind("font", m_font->property_font_name());
  m_settings->bind("transition", m_transition->property_active_id());
}

//static
ExampleAppPrefs* ExampleAppPrefs::create(Gtk::Window& parent)
{
  // Load the Builder file and instantiate its widgets.
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/prefs.ui");

  ExampleAppPrefs* dialog = nullptr;
  refBuilder->get_widget_derived("prefs_dialog", dialog);
  if (!dialog)
    throw std::runtime_error("No \"prefs_dialog\" object in prefs.ui");

  dialog->set_transient_for(parent);

  return dialog;
}
