/* gtkmm example Copyright (C) 2023 gtkmm development team
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

#include "printformdialog.h"
#include <iostream>

#if HAS_PRINT_DIALOG
PrintFormDialog::PrintFormDialog()
{
  set_page_setup(Gtk::PageSetup::create());
  set_print_settings(Gtk::PrintSettings::create());
}

PrintFormDialog::~PrintFormDialog()
{
}

Glib::RefPtr<PrintFormDialog> PrintFormDialog::create()
{
  return Glib::make_refptr_for_instance<PrintFormDialog>(new PrintFormDialog());
}

void PrintFormDialog::do_setup(Gtk::Window* parent)
{
  set_title("Print setup");
  if (parent)
    setup(*parent, sigc::mem_fun(*this, &PrintFormDialog::on_setup_finish));
  else
    setup(sigc::mem_fun(*this, &PrintFormDialog::on_setup_finish));
}

void PrintFormDialog::do_print(Gtk::Window* parent)
{
  set_title("Printing");
  if (parent)
    print(*parent, sigc::mem_fun(*this, &PrintFormDialog::on_print_finish));
  else
    print(sigc::mem_fun(*this, &PrintFormDialog::on_print_finish));
}

void PrintFormDialog::on_setup_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  try
  {
    m_refPrintSetup = setup_finish(result);
    if (m_refPrintSetup)
    {
      set_page_setup(m_refPrintSetup->get_page_setup());
      set_print_settings(m_refPrintSetup->get_print_settings());
    }
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by setup_finish(result).
    std::cout << "No setup selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void PrintFormDialog::on_print_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  Glib::RefPtr<Gio::OutputStream> outputStream;
  try
  {
    outputStream = print_finish(result);
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by print_finish(result).
    std::cout << "No output stream. " << err.what() << std::endl;
    return;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
    return;
  }
  const double paper_width = get_page_setup()->get_paper_width(Gtk::Unit::POINTS);
  const double paper_height = get_page_setup()->get_paper_height(Gtk::Unit::POINTS);
  auto cairo_surface = Cairo::PdfSurface::create_for_stream(
    sigc::bind(sigc::mem_fun(*this, &PrintFormDialog::write_func), outputStream),
    paper_width, paper_height);
  auto cairo_ctx = Cairo::Context::create(cairo_surface);

  do_printing(cairo_ctx);

  // cairo_surface->finish() calls write_func(),
  // which must be done before the stream is closed.
  cairo_surface->finish();
  try
  {
    outputStream->close();
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Error closing stream. " << err.what() << std::endl;
  }
}

Cairo::ErrorStatus PrintFormDialog::write_func(const unsigned char* data,
  unsigned int length, Glib::RefPtr<Gio::OutputStream>& stream)
{
  try
  {
    gsize bytes_written = 0;
    stream->write_all(data, length, bytes_written);
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Error writing to stream. " << err.what() << std::endl;
    return CAIRO_STATUS_WRITE_ERROR;
  }
  return CAIRO_STATUS_SUCCESS;
}
void PrintFormDialog::do_printing(const Cairo::RefPtr<Cairo::Context>& cairo_ctx)
{
  m_refLayout = Pango::Layout::create(cairo_ctx);
  m_refLayout->set_font_description(Pango::FontDescription("sans 12"));

  const auto page_setup = get_page_setup();
  const double page_width = page_setup->get_page_width(Gtk::Unit::POINTS);
  const double page_height = page_setup->get_page_height(Gtk::Unit::POINTS);
  const double left_margin = page_setup->get_left_margin(Gtk::Unit::POINTS);
  const double top_margin = page_setup->get_top_margin(Gtk::Unit::POINTS);
  m_refLayout->set_width(static_cast<int>(page_width * Pango::SCALE));
  m_refLayout->set_wrap(Pango::WrapMode::WORD_CHAR);
  cairo_ctx->translate(left_margin, top_margin);

  // Set and mark up the text to print:
  Glib::ustring marked_up_form_text =
    "<b>Name</b>: " + m_Name + "\n\n" +
    "<b>Comments</b>: " + m_Comments;
  m_refLayout->set_markup(marked_up_form_text);

  // We'll use black letters:
  cairo_ctx->set_source_rgb(0, 0, 0);

  // Render Pango LayoutLines over the Cairo context:
  const double inverse_pango_scale = 1.0 / Pango::SCALE;
  double page_y = 0.0;
  auto iter = m_refLayout->get_iter();
  double start_y_pos = iter.get_line_logical_extents().get_y() * inverse_pango_scale;
  do
  {
    const auto layout_line = iter.get_line();
    const auto logical_rect = iter.get_line_logical_extents();
    const double line_height = logical_rect.get_height() * inverse_pango_scale;

    if (page_y + line_height > page_height)
    {
      // Start a new page.
      cairo_ctx->show_page();
      page_y = 0.0;
      start_y_pos = logical_rect.get_y() * inverse_pango_scale;
    }
    page_y += line_height;

    cairo_ctx->move_to(logical_rect.get_x() * inverse_pango_scale,
      iter.get_baseline() * inverse_pango_scale - start_y_pos);
    layout_line->show_in_cairo_context(cairo_ctx);
  }
  while (iter.next_line());

  cairo_ctx->show_page();
}
#endif // HAS_PRINT_DIALOG
