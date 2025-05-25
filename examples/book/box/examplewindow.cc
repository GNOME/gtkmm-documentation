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
#include "packbox.h"

ExampleWindow::ExampleWindow(int which)
: m_box1(Gtk::Orientation::VERTICAL),
  m_buttonQuit("Quit")
{
  set_title("Gtk::Box example");

  m_separator1.set_margin_top(5);
  m_separator1.set_margin_bottom(5);
  m_separator2.set_margin_top(5);
  m_separator2.set_margin_bottom(5);

  switch(which)
  {
    case 1:
    {
      m_Label1.set_text("Gtk::Box(Gtk::Orientation::HORIZONTAL, 0); set_homogeneous(false);");

      // Align the label to the left side.
      m_Label1.set_halign(Gtk::Align::START);
      m_Label1.set_valign(Gtk::Align::START);

      // Pack the label into the vertical box (vbox box1).  Remember that
      // widgets added to a vbox will be packed one on top of the other in
      // order.
      m_box1.append(m_Label1);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // expand = false, Gtk::Align::FILL, margin = 0
      // These are the default values.
      auto pPackBox = Gtk::make_managed<PackBox>();
      m_box1.append(*pPackBox);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // expand = true, Gtk::Align::CENTER, margin = 0
      pPackBox = Gtk::make_managed<PackBox>(false, 0, true, Gtk::Align::CENTER);
      m_box1.append(*pPackBox);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // expand = true, Gtk::Align::FILL, margin = 0
      pPackBox = Gtk::make_managed<PackBox>(false, 0, true);
      m_box1.append(*pPackBox);

      // pack the separator into the vbox.  Remember each of these
      // widgets are being packed into a vbox, so they'll be stacked
      // vertically.
      m_box1.append(m_separator1);

      // create another new label, and show it.
      m_Label2.set_text("Gtk::Box(Gtk::Orientation::HORIZONTAL, 0); set_homogeneous(true);");
      m_Label2.set_halign(Gtk::Align::START);
      m_Label2.set_valign(Gtk::Align::START);
      m_box1.append(m_Label2);

      // Args are: homogeneous, spacing, expand, align, margin
      pPackBox = Gtk::make_managed<PackBox>(true, 0, true, Gtk::Align::CENTER);
      m_box1.append(*pPackBox);

      // Args are: homogeneous, spacing, expand, align, margin
      pPackBox = Gtk::make_managed<PackBox>(true, 0, true);
      m_box1.append(*pPackBox);

      m_box1.append(m_separator2);

      break;
    }

    case 2:
    {
      m_Label1.set_text("Gtk::Box(Gtk::Orientation::HORIZONTAL, 10); set_homogeneous(false);");
      m_Label1.set_halign(Gtk::Align::START);
      m_Label1.set_valign(Gtk::Align::START);
      m_box1.append(m_Label1);

      auto pPackBox = Gtk::make_managed<PackBox>(false, 10, true, Gtk::Align::CENTER);
      m_box1.append(*pPackBox);

      pPackBox = Gtk::make_managed<PackBox>(false, 10, true);
      m_box1.append(*pPackBox);

      m_box1.append(m_separator1);

      m_Label2.set_text("Gtk::Box(Gtk::Orientation::HORIZONTAL, 0); set_homogeneous(false);");
      m_Label2.set_halign(Gtk::Align::START);
      m_Label2.set_valign(Gtk::Align::START);
      m_box1.append(m_Label2);

      pPackBox = Gtk::make_managed<PackBox>(false, 0, false, Gtk::Align::FILL, 10);
      m_box1.append(*pPackBox);

      pPackBox = Gtk::make_managed<PackBox>(false, 0, true, Gtk::Align::FILL, 10);
      m_box1.append(*pPackBox);

      m_box1.append(m_separator2);

      break;
    }

    case 3:
    {
      // This demonstrates the ability to use Gtk::Align::END to
      // right justify widgets.  First, we create a new box as before.
      auto pPackBox = Gtk::make_managed<PackBox>();

      // create the label that will be put at the end.
      m_Label1.set_text("end");

      // pack it using Gtk::Align::END, so it is put on the right side
      // of the PackBox.
      m_Label1.set_halign(Gtk::Align::END);
      m_Label1.set_hexpand(true);
      pPackBox->append(m_Label1);

      m_box1.append(*pPackBox);

      // This explicitly sets the separator to 700 pixels wide by 5 pixels
      // high.  This is so the hbox we created will also be 700 pixels wide,
      // and the "end" label will be separated from the other labels in the
      // hbox.  Otherwise, all the widgets in the hbox would be packed as
      // close together as possible.
      m_separator1.set_size_request(700, 5);

      // pack the separator into the vbox.
      m_box1.append(m_separator1);

      break;
    }

    default:
    {
      std::cerr << "Unexpected command-line option." << std::endl;
      break;
    }
  }

  // Connect the signal to hide the window:
  m_buttonQuit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit_clicked) );

  // pack the button into the quitbox.
  m_boxQuit.append(m_buttonQuit);
  m_buttonQuit.set_hexpand(true);
  m_buttonQuit.set_halign(Gtk::Align::CENTER);
  m_box1.append(m_boxQuit);

  // pack the vbox (box1) which now contains all our widgets, into the
  // main window.
  set_child(m_box1);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit_clicked()
{
  set_visible(false);
}

