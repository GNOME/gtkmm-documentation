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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Start("Start"),
  m_Button_Quit("_Quit", true)
{
  set_title("update-ui example");
  set_default_size(400, -1);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  m_ProgressBar.set_show_text(true);
  m_VBox.append(m_ProgressBar);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.append(m_Button_Start);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );
  m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_start) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_button_start()
{
  const double max = 20000;
  // Do intensive work, while still keeping the user interface updated and responsive.
  // An alternative would be to do the intensive work in a separate thread.
  for(double i = 0; i < max; ++i)
  {
    std::cout << "gtkmm example: example output: " << i << " of "
      << max << std::endl;

    m_ProgressBar.set_fraction(i / max);

    // Allow GTK+ to perform all updates for us. Without this, the progress bar
    // will appear to do nothing and then suddenly fill completely.
    auto main_context = Glib::MainContext::get_default();
    while (main_context->pending())
      main_context->iteration(true);
  }
}
