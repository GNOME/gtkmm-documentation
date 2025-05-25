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
#include <iostream>

PrintFormOperation::PrintFormOperation()
  :
  m_FontDialogButton(Gtk::FontDialog::create()),
  m_FontDesc("sans 12")
{
}

PrintFormOperation::~PrintFormOperation()
{
}

Glib::RefPtr<PrintFormOperation> PrintFormOperation::create()
{
  return Glib::make_refptr_for_instance<PrintFormOperation>(new PrintFormOperation());
}

void PrintFormOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>&
        print_context)
{
  //Create and set up a Pango layout for PrintData based on the passed
  //PrintContext: We then use this to calculate the number of pages needed, and
  //the lines that are on each page.
  m_refLayout = print_context->create_pango_layout();

  m_refLayout->set_font_description(m_FontDesc);

  const double width = print_context->get_width();
  const double height = print_context->get_height();

  m_refLayout->set_width(static_cast<int>(width * Pango::SCALE));

  //Set and mark up the text to print:
  Glib::ustring marked_up_form_text;
  marked_up_form_text += "<b>Name</b>: " + m_Name + "\n\n";
  marked_up_form_text += "<b>Comments</b>: " + m_Comments;

  m_refLayout->set_markup(marked_up_form_text);

  //Set the number of pages to print by determining the line numbers
  //where page breaks occur:
  const int line_count = m_refLayout->get_line_count();

  Glib::RefPtr<Pango::LayoutLine> layout_line;
  double page_height = 0;

  for (int line = 0; line < line_count; ++line)
  {
    Pango::Rectangle ink_rect, logical_rect;

    layout_line = m_refLayout->get_line(line);
    layout_line->get_extents(ink_rect, logical_rect);

    const double line_height = logical_rect.get_height() / 1024.0;

    if (page_height + line_height > height)
    {
      m_PageBreaks.push_back(line);
      page_height = 0;
    }

    page_height += line_height;
  }

  set_n_pages(m_PageBreaks.size() + 1);
}

void PrintFormOperation::on_draw_page(
        const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
{
  if(!print_context || !m_refLayout)
    return;

  //Decide which lines we need to print in order to print the specified page:
  int start_page_line = 0;
  int end_page_line = 0;

  if(page_nr == 0)
  {
    start_page_line = 0;
  }
  else
  {
    start_page_line = m_PageBreaks[page_nr - 1];
  }

  if(page_nr < static_cast<int>(m_PageBreaks.size()))
  {
    end_page_line = m_PageBreaks[page_nr];
  }
  else
  {
    if(m_refLayout)
      end_page_line = m_refLayout->get_line_count();
  }

  //Get a Cairo Context, which is used as a drawing board:
  Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();

  //We'll use black letters:
  cairo_ctx->set_source_rgb(0, 0, 0);

  //Render Pango LayoutLines over the Cairo context:
  auto iter = m_refLayout->get_iter();

  double start_pos = 0;
  int line_index = 0;

  do
  {
    if(line_index >= start_page_line)
    {
      auto layout_line = iter.get_line();
      auto logical_rect = iter.get_line_logical_extents();
      int baseline = iter.get_baseline();

      if (line_index == start_page_line)
      {
        start_pos = logical_rect.get_y() / 1024.0;
      }

      cairo_ctx->move_to(logical_rect.get_x() / 1024.0,
        baseline / 1024.0 - start_pos);

      layout_line->show_in_cairo_context(cairo_ctx);
    }

    line_index++;
  }
  while(line_index < end_page_line && iter.next_line());
}

Gtk::Widget* PrintFormOperation::on_create_custom_widget()
{
  //Create a custom tab in the print dialog titled "Other"
  set_custom_tab_label("Other");

  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  vbox->set_margin(12);

  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 8);
  vbox->append(*hbox);
  hbox->set_margin(6);

  auto label = Gtk::make_managed<Gtk::Label>("Choose a font: ");
  hbox->append(*label);

  m_FontDialogButton.set_font_desc(m_FontDesc);
  hbox->append(m_FontDialogButton);

  return vbox;
}

void PrintFormOperation::on_custom_widget_apply(Gtk::Widget*)
{
  // Note: the returned widget is the VBox we created in
  // on_create_custom_widget().  We don't need to use it, because we can use the
  // child FontDialogButton directly:

  m_FontDesc = m_FontDialogButton.get_font_desc();
}

bool PrintFormOperation::on_preview(const
        Glib::RefPtr<Gtk::PrintOperationPreview>& preview, const
        Glib::RefPtr<Gtk::PrintContext>& context, Gtk::Window* parent)
{
  if(!parent)
  {
    std::cerr << "PrintFormOperation::on_preview(): parent was null."
              << std::endl;
    return false;
  }

  //Use our custom preview dialog:
  m_pDialog = new PreviewDialog(this, preview, context, *parent);
  m_pDialog->signal_hide().connect(sigc::mem_fun(*this,
              &PrintFormOperation::on_preview_window_hide));

  m_pDialog->set_visible(true);

  return true;
}

void PrintFormOperation::on_preview_window_hide()
{
  if(m_pDialog)
  {
    delete m_pDialog; //This would hide it anyway.
    m_pDialog = nullptr;
  }
}
