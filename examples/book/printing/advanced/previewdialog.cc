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

#include "previewdialog.h"
#include "printformoperation.h"

#include <cmath>

PreviewDialog::PreviewDialog(
               PrintFormOperation* pfo,
               const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
               const Glib::RefPtr<Gtk::PrintContext>& print_ctx,
               Gtk::Window& parent)
: m_pOperation(pfo),
  m_refPreview(preview),
  m_refPrintContext(print_ctx),
  m_VBox(Gtk::Orientation::VERTICAL),
  m_SpinAdjustment( Gtk::Adjustment::create(1, 100, 1) ), //Used to construct m_PageSpin
  m_PageSpin(m_SpinAdjustment, 1, 0),
  m_CloseButton("_Close", true),
  m_Page(1),
  m_DpiX(0),
  m_DpiY(0)
{
  set_transient_for(parent);
  set_title("Preview");
  set_size_request(300, 300);

  m_VBox.set_margin(2);
  set_child(m_VBox);

  m_HBox.append(m_PageSpin);
  m_PageSpin.set_hexpand(true);
  m_PageSpin.set_vexpand(false);
  m_HBox.append(m_CloseButton);
  m_VBox.append(m_HBox);

  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand(true);
  m_VBox.append(m_ScrolledWindow);
  m_DrawingArea.set_content_width(300);
  m_DrawingArea.set_content_height(600);
  m_ScrolledWindow.set_child(m_DrawingArea);

  m_refPreview->signal_ready().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_popreview_ready));

  m_refPreview->signal_got_page_size().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_popreview_got_page_size));

  m_DrawingArea.signal_realize().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_drawing_area_realized));

  m_DrawingArea.set_draw_func(
    sigc::mem_fun(*this, &PreviewDialog::on_drawing_area_draw));

  m_CloseButton.signal_clicked().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_close_clicked));

  m_PageSpin.signal_value_changed().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_page_number_changed));
}

PreviewDialog::~PreviewDialog()
{
}

void PreviewDialog::on_drawing_area_realized()
{
  auto gtk_native = m_DrawingArea.get_native();
  if (gtk_native)
  {
    auto gdk_surface = gtk_native->get_surface();
    if (gdk_surface)
    {
      const int scale = gdk_surface->get_scale_factor();
      const int width = gdk_surface->get_width() * scale;
      const int height = gdk_surface->get_height() * scale;
      //auto cairo_surface = gdk_surface->create_similar_surface(
      //  Cairo::Content::CONTENT_COLOR, width, height);
      //>>> This is what the deprecated create_similar_surface() does:
      auto cairo_surface = Cairo::ImageSurface::create(
        Cairo::Surface::Format::RGB24, width * scale, height * scale);
      cairo_surface->set_device_scale(scale, scale);
      //<<< end of create_similar_surface()
      m_refCairoContext = Cairo::Context::create(cairo_surface);

      if (m_refPrintContext)
        m_refPrintContext->set_cairo_context(m_refCairoContext, 72, 72);
    }
  }
}

void PreviewDialog::on_page_number_changed()
{
  m_Page = m_PageSpin.get_value_as_int();
  m_DrawingArea.queue_draw();
}

void PreviewDialog::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  m_refCairoContext = cr; // Can be used in on_popreview_got_page_size()

  Cairo::RefPtr<Cairo::Context> prev_cairo_ctx;
  double dpi_x = 72.0;
  double dpi_y = 72.0;

  if(m_refPrintContext)
  {
    prev_cairo_ctx = m_refPrintContext->get_cairo_context();
    dpi_x = m_refPrintContext->get_dpi_x();
    dpi_y = m_refPrintContext->get_dpi_y();
    m_refPrintContext->set_cairo_context(cr, dpi_x, dpi_y);
  }

  if(m_refPreview)
    m_refPreview->render_page(m_Page - 1);

  if(m_refPrintContext)
    m_refPrintContext->set_cairo_context(prev_cairo_ctx, dpi_x, dpi_y);
}

void PreviewDialog::on_popreview_ready(const Glib::RefPtr<Gtk::PrintContext>&)
{
  m_PageSpin.set_range(1.0, m_pOperation->property_n_pages());
  m_DrawingArea.queue_draw();
}

void PreviewDialog::on_popreview_got_page_size(
                       const Glib::RefPtr<Gtk::PrintContext>& print_ctx,
                       const Glib::RefPtr<Gtk::PageSetup>& page_setup)
{
  const auto paper_size = page_setup->get_paper_size();

  const double width = paper_size.get_width(Gtk::Unit::INCH);
  const double height = paper_size.get_height(Gtk::Unit::INCH);

  if(m_DrawingArea.get_realized()) //Avoid getting an odd allocation.
  {
    double dpi_x = m_DrawingArea.get_width() / width;
    double dpi_y = m_DrawingArea.get_height() / height;

    // We get a cairo context for the DrawingArea and then give that cairo
    // context to the PrintOperation's pango layout so that render_page() will
    // render into the drawing area.

    if (fabs(dpi_x - m_DpiX) > 0.001 ||
        fabs(dpi_y - m_DpiY) > 0.001)
    {
      print_ctx->set_cairo_context(m_refCairoContext, dpi_x, dpi_y);
      m_DpiX = dpi_x;
      m_DpiY = dpi_y;
      m_DrawingArea.queue_draw();
    }

    if(m_pOperation)
    {
      auto layout = m_pOperation->get_pango_layout();
      if(layout)
        layout->update_from_cairo_context(m_refCairoContext);
    }
  }
}

void PreviewDialog::on_hide()
{
  m_refPreview->end_preview();

  //We will not be using these anymore, so null the RefPtrs:
  m_refPreview.reset();
  m_refPrintContext.reset();
  m_refCairoContext.reset();
}

void PreviewDialog::on_close_clicked()
{
  set_visible(false);
}
