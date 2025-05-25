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

#include <gtkmm.h>
#include <iostream>
#include <algorithm>

#define HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY GTKMM_CHECK_VERSION(4,9,1)
#define HAS_FONT_DIALOG_BUTTON GTKMM_CHECK_VERSION(4,9,1)

enum { DEF_PAD = 10 };
enum { DEF_PAD_SMALL = 5 };

enum { TM_YEAR_BASE = 1900 };

//TODO: This whole example is not very good and needs review.
class CalendarExample : public Gtk::Window
{

public:
  CalendarExample();
  ~CalendarExample() override;

  void set_flags();
  void toggle_flag(Gtk::CheckButton *toggle);

  void month_changed();
  void day_selected();

protected:
  static Glib::ustring font_style_to_string(Pango::Style font_style);
  void on_font_button_font_set();
  void on_button_close();
  static void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error);

  static const int n_checkboxes = 3;
  Gtk::CheckButton* flag_checkboxes_[n_checkboxes];
  bool settings_[n_checkboxes];

  Glib::RefPtr<Gtk::CssProvider> css_provider_;

#if HAS_FONT_DIALOG_BUTTON
  Gtk::FontDialogButton* font_button_;
#else
  Gtk::FontButton* font_button_;
#endif
  Gtk::Calendar* calendar_;
  Gtk::Label* label_selected_;
  Gtk::Label* label_month_;

  Glib::DateTime get_date() const;
};

CalendarExample::~CalendarExample()
{
  for (int i = 0; i < n_checkboxes; i++)
  {
	  delete flag_checkboxes_[i];
  }

  delete calendar_;
  delete label_selected_;
  delete label_month_;
}

/*
 * GtkCalendar
 */

void CalendarExample::month_changed()
{
  label_month_->set_text(get_date().format("%x"));
}

void CalendarExample::day_selected()
{
  label_selected_->set_text(get_date().format("%x"));
}

void CalendarExample::set_flags()
{
  if (calendar_)
  {
    calendar_->set_show_heading(settings_[0]);
    calendar_->set_show_day_names(settings_[1]);
    calendar_->set_show_week_numbers(settings_[2]);
  }
}

void CalendarExample::toggle_flag(Gtk::CheckButton *toggle)
{
  int j = 0;
  for (int i = 0; i < n_checkboxes; i++)
    if (flag_checkboxes_[i] == (Gtk::CheckButton *)toggle)
      j = i;

  settings_[j] = !settings_[j];
  set_flags();
}

void CalendarExample::on_font_button_font_set()
{
  const Pango::FontDescription font_desc = font_button_->get_font_desc();
  const auto font_family = font_desc.get_family();
  const auto font_size = font_desc.get_size();
  const auto font_style = font_desc.get_style();
  const auto font_weight = font_desc.get_weight();
  // See https://www.w3.org/TR/css-fonts-3/
  const Glib::ustring css =
    "calendar {\n" +
    (font_family.empty() ? "" : "    font-family: " + font_family + ";\n") +
    (font_size == 0 ? "" : "    font-size: " + std::to_string(font_size / PANGO_SCALE) + "pt;\n") +
    ("    font-style: " + font_style_to_string(font_style) + ";\n") +
    ("    font-weight: " + std::to_string(std::clamp(static_cast<int>(font_weight), 100, 900)) + ";\n") +
    "}";

  css_provider_->load_from_data(css.raw());
}

Glib::ustring CalendarExample::font_style_to_string(Pango::Style font_style)
{
  switch (font_style)
  {
  case Pango::Style::OBLIQUE: return "oblique";
  case Pango::Style::ITALIC: return "italic";
  default: return "normal";
  }
}

void CalendarExample::on_button_close()
{
  set_visible(false);
}

void CalendarExample::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    auto start_location = section->get_start_location();
    auto end_location = section->get_end_location();
    std::cerr << "  start_line = " << start_location.get_lines()+1
              << ", end_line = " << end_location.get_lines()+1 << std::endl;
    std::cerr << "  start_position = " << start_location.get_line_chars()
              << ", end_position = " << end_location.get_line_chars() << std::endl;
  }
}

CalendarExample::CalendarExample()
{
  for (int i = 0; i < n_checkboxes; i++) {
    settings_[i] = 0;
  }

  set_resizable(false);

  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD * 2);
  vbox->set_margin(5);
  set_child(*vbox);

  /*
   * The top part of the CalendarExample, flags and fontsel.
   */

  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, DEF_PAD);
  vbox->append(*hbox);
  auto hbbox = Gtk::make_managed<Gtk::Box>();
  hbox->append(*hbbox);
  hbbox->set_margin_end(DEF_PAD);
  hbbox->set_spacing(5);

  /* Calendar widget */
  auto frame = Gtk::make_managed<Gtk::Frame>("Calendar");
  hbbox->append(*frame);
  frame->set_margin_start(DEF_PAD);
  frame->set_margin_end(DEF_PAD);
  frame->set_hexpand();
  frame->set_halign(Gtk::Align::CENTER);
  calendar_ = new Gtk::Calendar();
  set_flags();
  calendar_->mark_day(19);
  frame->set_child(*calendar_);
  calendar_->signal_prev_month().connect(sigc::mem_fun(*this, &CalendarExample::month_changed));
  calendar_->signal_next_month().connect(sigc::mem_fun(*this, &CalendarExample::month_changed));
  calendar_->signal_day_selected().connect(sigc::mem_fun(*this, &CalendarExample::day_selected));

  auto separator = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL);
  hbox->append(*separator);

  auto vbox2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD);
  hbox->append(*vbox2);
  vbox2->set_margin_start(DEF_PAD);
  vbox2->set_margin_end(DEF_PAD);

  /* Build the Right frame with the flags in */

  auto frameFlags = Gtk::make_managed<Gtk::Frame>("Flags");
  vbox2->append(*frameFlags);
  frameFlags->set_margin_end(DEF_PAD);
  auto vbox3 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD_SMALL);
  frameFlags->set_child(*vbox3);

  struct {
    const char* label;
  } flags[n_checkboxes] =
    {
      { "Show Heading" },
      { "Show Day Names" },
      { "Show Week Numbers" },
    };

  for (int i = 0; i < n_checkboxes; i++)
  {
    auto toggle = new Gtk::CheckButton(flags[i].label);
    toggle->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &CalendarExample::toggle_flag), toggle));
    vbox3->append(*toggle);
    flag_checkboxes_[i] = toggle;
  }

  /* Build the right font-button */
#if HAS_FONT_DIALOG_BUTTON
  auto font_dialog = Gtk::FontDialog::create();
  font_button_ = Gtk::make_managed<Gtk::FontDialogButton>(font_dialog);
  font_button_->property_font_desc().signal_changed().connect(
    sigc::mem_fun(*this, &CalendarExample::on_font_button_font_set));
#else
  font_button_ = Gtk::make_managed<Gtk::FontButton>();
  font_button_->signal_font_set().connect(
    sigc::mem_fun(*this, &CalendarExample::on_font_button_font_set));
#endif
  vbox2->append(*font_button_);

  // Add a StyleProvider to the Gtk::Calendar, so we can change the font.
  css_provider_ = Gtk::CssProvider::create();
#if HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY
  Gtk::StyleProvider::add_provider_for_display(
    calendar_->get_display(), css_provider_, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#else
  Gtk::StyleContext::add_provider_for_display(
    calendar_->get_display(), css_provider_, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif
  css_provider_->signal_parsing_error().connect(
    [](const auto& section, const auto& error)
    { on_parsing_error(section, error); }
  );

  // Set initial font.
  on_font_button_font_set();

  /*
   *  Build the Signal-event part.
   */
  frame = Gtk::make_managed<Gtk::Frame>("Signal events");
  vbox->append(*frame);
  vbox2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD_SMALL);
  frame->set_child(*vbox2);

  hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  vbox2->append(*hbox);
  auto label = Gtk::make_managed<Gtk::Label>("Day selected:");
  hbox->append(*label);
  label_selected_ = new Gtk::Label("");
  hbox->append(*label_selected_);

  hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  vbox2->append(*hbox);
  label = Gtk::make_managed<Gtk::Label>("Month change:");
  hbox->append(*label);
  label_month_ = new Gtk::Label("");
  hbox->append(*label_month_);

  auto bbox = Gtk::make_managed<Gtk::Box>();
  vbox->append(*bbox);

  auto button = Gtk::make_managed<Gtk::Button>("Close");
  button->signal_clicked().connect(
    sigc::mem_fun(*this, &CalendarExample::on_button_close));
  bbox->append(*button);
  button->set_hexpand();
  button->set_halign(Gtk::Align::END);
  set_default_widget(*button);
}

Glib::DateTime CalendarExample::get_date() const
{
  return calendar_->get_date();
}

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<CalendarExample>(argc, argv);
}
