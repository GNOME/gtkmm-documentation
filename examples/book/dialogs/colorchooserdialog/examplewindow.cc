/* gtkmm example Copyright (C) 2002 gtkmm development team
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

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Button_Dialog("Choose Color")
{
  set_title("Gtk::ColorChooserDialog example");
  set_default_size(200, 200);

  set_child(m_VBox);

  m_VBox.append(m_ColorButton);
  m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_color_button_color_set) );

  m_VBox.append(m_Button_Dialog);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );

  //Set start color:
  m_Color.set_red(0.0);
  m_Color.set_green(0.0);
  m_Color.set_blue(1.0);
  m_Color.set_alpha(1.0); //opaque
  m_ColorButton.set_rgba(m_Color);

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
  m_Color = m_ColorButton.get_rgba();
  m_DrawingArea.queue_draw();
}

void ExampleWindow::on_button_dialog_clicked()
{
  if (!m_pDialog)
  {
    m_pDialog = std::make_unique<Gtk::ColorChooserDialog>("Please choose a color", *this);
    m_pDialog->set_modal(true);
    m_pDialog->set_hide_on_close(true);
    m_pDialog->signal_response().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_dialog_response));
  }

  //Get the previously selected color:
  m_pDialog->set_rgba(m_Color);

  m_pDialog->show();
}

void ExampleWindow::on_dialog_response(int response_id)
{
  m_pDialog->hide();

  //Handle the response:
  switch (response_id)
  {
    case Gtk::ResponseType::OK:
    {
      //Store the chosen color:
      m_Color = m_pDialog->get_rgba();
      m_ColorButton.set_rgba(m_Color);
      m_DrawingArea.queue_draw();
      break;
    }
    case Gtk::ResponseType::CANCEL:
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked: " << response_id << std::endl;
      break;
    }
  }
}

void ExampleWindow::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();
}
