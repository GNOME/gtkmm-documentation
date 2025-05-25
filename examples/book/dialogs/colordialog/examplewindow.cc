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
: m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Button_Dialog("Choose Color")
{
  set_title("Gtk::ColorDialog example");
  set_default_size(200, 200);

  m_pDialog = Gtk::ColorDialog::create();
  m_ColorDialogButton.set_dialog(m_pDialog);

  set_child(m_VBox);

  m_VBox.append(m_ColorDialogButton);
  m_ColorDialogButton.property_rgba().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_color_button_color_set));

  m_VBox.append(m_Button_Dialog);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );

  //Set start color:
  m_Color.set_red(0.0);
  m_Color.set_green(0.0);
  m_Color.set_blue(1.0);
  m_Color.set_alpha(1.0); //opaque
  m_ColorDialogButton.set_rgba(m_Color);

  m_VBox.append(m_DrawingArea);
  m_DrawingArea.set_expand(true);
  m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &ExampleWindow::on_drawing_area_draw));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_color_button_color_set()
{
  //Store the chosen color:
  m_Color = m_ColorDialogButton.get_rgba();
  m_DrawingArea.queue_draw();
}

void ExampleWindow::on_button_dialog_clicked()
{
  m_pDialog->choose_rgba(*this, m_Color,
    sigc::mem_fun(*this, &ExampleWindow::on_dialog_finish));
}

void ExampleWindow::on_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  try
  {
    // If this call changes the color, it will trigger a call to
    // on_color_button_color_set().
    m_ColorDialogButton.set_rgba(m_pDialog->choose_rgba_finish(result));

    // This is what you should do if m_ColorDialogButton and
    // on_color_button_color_set() did not exist:
    //m_Color = m_pDialog->choose_rgba_finish(result);
    //m_DrawingArea.queue_draw();
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by m_pDialog->choose_rgba_finish(result).
    std::cout << "No color selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void ExampleWindow::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();
}
