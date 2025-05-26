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
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_SpinAdjustment( Gtk::Adjustment::create(1, 100, 1) ), //Used to construct m_PageSpin
  m_PageSpin(m_SpinAdjustment, 1, 0),
  m_CloseButton("_Close", true),
  m_Page(1),
  m_DpiX(0),
  m_DpiY(0)
{
  set_transient_for(parent);
  set_title("Preview");
  set_border_width(2);

  add(m_VBox);

  m_HBox.pack_start(m_PageSpin);
  m_HBox.pack_start(m_CloseButton, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_HBox, Gtk::PACK_SHRINK);

  m_DrawingArea.set_size_request(200, 300);
  m_VBox.pack_start(m_DrawingArea, Gtk::PACK_EXPAND_WIDGET);

  m_refPreview->signal_ready().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_popreview_ready));

  m_refPreview->signal_got_page_size().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_popreview_got_page_size));

  m_DrawingArea.signal_realize().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_drawing_area_realized));

  m_DrawingArea.signal_draw().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_drawing_area_draw));

  m_CloseButton.signal_clicked().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_close_clicked));

  m_PageSpin.signal_value_changed().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_page_number_changed));

  show_all_children();
}

PreviewDialog::~PreviewDialog()
{
}

void PreviewDialog::on_drawing_area_realized()
{
  auto gdk_window = m_DrawingArea.get_window();
  if(gdk_window)
  {
    m_refDrawingContext = gdk_window->begin_draw_frame(gdk_window->get_clip_region());
    auto cairo_ctx = m_refDrawingContext->get_cairo_context();

    if(m_refPrintContext)
      m_refPrintContext->set_cairo_context(cairo_ctx, 72, 72);
  }
}

void PreviewDialog::on_page_number_changed()
{
  m_Page = m_PageSpin.get_value_as_int();
  m_DrawingArea.queue_draw();
}

bool PreviewDialog::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
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

  return true;
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
  const Gtk::PaperSize paper_size = page_setup->get_paper_size();

  const double width = paper_size.get_width(Gtk::UNIT_INCH);
  const double height = paper_size.get_height(Gtk::UNIT_INCH);

  if(m_DrawingArea.get_realized()) //Avoid getting an odd allocation.
  {
    double dpi_x = m_DrawingArea.get_allocation().get_width() / width;
    double dpi_y = m_DrawingArea.get_allocation().get_height() / height;

    // We get a cairo context for the DrawingArea and then give that cairo
    // context to the PrintOperation's pango layout so that render_page() will
    // render into the drawing area.
    auto cairo_ctx = m_refDrawingContext->get_cairo_context();

    if (fabs(dpi_x - m_DpiX) > 0.001 ||
        fabs(dpi_y - m_DpiY) > 0.001)
    {
      print_ctx->set_cairo_context(cairo_ctx, dpi_x, dpi_y);
      m_DpiX = dpi_x;
      m_DpiY = dpi_y;
      m_DrawingArea.queue_draw();
    }

    if(m_pOperation)
    {
      auto layout = m_pOperation->get_pango_layout();
      if(layout)
        layout->update_from_cairo_context(cairo_ctx);
    }
  }
}

void PreviewDialog::on_hide()
{
  auto gdk_window = m_DrawingArea.get_window();
  if(gdk_window)
    gdk_window->end_draw_frame(m_refDrawingContext);

  m_refPreview->end_preview();

  //We will not be using these anymore, so null the RefPtrs:
  m_refPreview.reset();
  m_refPrintContext.reset();
  m_refDrawingContext.reset();
}

void PreviewDialog::on_close_clicked()
{
  hide();
}
