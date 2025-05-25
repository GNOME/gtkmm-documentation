/* gtkmm example Copyright (C) 2003 gtkmm development team
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

#include "deriveddialog.h"
#include <iostream>

DerivedDialog::DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::Window(cobject),
  m_refBuilder(refBuilder),
  m_pButton(nullptr)
{
  // Get the GtkBuilder-instantiated Button, and connect a signal handler:
  m_pButton = Gtk::Builder::get_widget_derived<DerivedButton>(m_refBuilder, "quit_button");
  if (m_pButton)
  {
    m_pButton->signal_clicked().connect( sigc::mem_fun(*this, &DerivedDialog::on_button_quit) );
    std::cout << "ustring, int: " << m_pButton->property_ustring()
              << ", " << m_pButton->property_int() << std::endl;
    m_pButton->property_int() = 99;
    std::cout << "ustring, int: " << m_pButton->property_ustring()
              << ", " << m_pButton->property_int() << std::endl;
  }
}

// The first two parameters are mandatory in a constructor that will be called
// from Gtk::Builder::get_widget_derived().
// Additional parameters, if any, correspond to additional arguments in the call
// to Gtk::Builder::get_widget_derived().
DerivedDialog::DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder,
  bool is_glad)
: DerivedDialog(cobject, refBuilder) // Delegate to the other constructor
{
  // Show an icon.
  auto content_area = refBuilder->get_widget<Gtk::Box>("dialog-content_area");
  if (!content_area)
  {
    std::cerr << "Could not get the content area" << std::endl;
    return;
  }
  auto pImage = Gtk::make_managed<Gtk::Image>();
  pImage->set_from_icon_name(is_glad ? "face-smile" : "face-sad");
  pImage->set_icon_size(Gtk::IconSize::LARGE);
  pImage->set_expand();
  content_area->append(*pImage);
}

DerivedDialog::~DerivedDialog()
{
}

void DerivedDialog::on_button_quit()
{
  set_visible(false); // set_visible(false) will cause Gtk::Application::run() to end.
}
