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

#include <gtkmm.h>
#include <iostream>


enum { DEF_PAD = 10 };
enum { DEF_PAD_SMALL = 5 };

enum { TM_YEAR_BASE = 1900 };

//TODO: This whole example is not very good and needs review.
class CalendarExample : public Gtk::Window
{

public:
  CalendarExample();
  virtual ~CalendarExample();

  void set_flags();
  void toggle_flag(Gtk::CheckButton *toggle);

  void month_changed();
  void day_selected();
  void day_selected_double_click();

protected:
  void on_font_button_font_set();
  void on_button_close();
  void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error);

  Gtk::CheckButton* flag_checkboxes_[5];
  bool settings_[5];

  Glib::RefPtr<Gtk::CssProvider> css_provider_;

  Gtk::FontButton* font_button_;
  Gtk::Calendar* calendar_;
  Gtk::Label* label_selected_;
  Gtk::Label* label_selected_double_click_;
  Gtk::Label* label_month_;

  Glib::Date get_date() const;
};

CalendarExample::~CalendarExample()
{
  for (int i = 0; i < 5; i++)
  {
	  delete flag_checkboxes_[i];
  }

  delete calendar_;
  delete label_selected_;
  delete label_selected_double_click_;
  delete label_month_;
}

/*
 * GtkCalendar
 */

void CalendarExample::month_changed()
{
  label_month_->set_text(get_date().format_string("%x"));
}

void CalendarExample::day_selected()
{
  label_selected_->set_text(get_date().format_string("%x"));
}

void CalendarExample::day_selected_double_click()
{
  label_selected_double_click_->set_text(get_date().format_string("%x"));
}

void CalendarExample::set_flags()
{
  int options = 0;

  for (int i = 0; i < 5; i++)
  {
    if (settings_[i])
    {
      options = options + (1 << i);
    }
  }

  if (calendar_)
    calendar_->set_display_options((Gtk::Calendar::DisplayOptions)options);
}

void CalendarExample::toggle_flag(Gtk::CheckButton *toggle)
{
  int j = 0;
  for (int i = 0; i < 5; i++)
    if (flag_checkboxes_[i] == (Gtk::CheckButton *)toggle)
      j = i;

  settings_[j] = !settings_[j];
  set_flags();
}

void CalendarExample::on_font_button_font_set()
{
  const auto font_name = font_button_->get_font();
  const Pango::FontDescription font_desc(font_name);
  const auto font_family = font_desc.get_family();
  const auto font_size = font_desc.get_size();
  const auto css =
    "* {\n" +
    (font_family.empty() ? "" : "    font-family: " + font_desc.get_family() + ";\n") +
    (font_size == 0 ? "" : "    font-size: " + std::to_string(font_size / PANGO_SCALE) + "pt;\n") +
    "}";

  css_provider_->load_from_data(css.raw());
}

void CalendarExample::on_button_close()
{
  hide();
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
  for (int i = 0; i < 5; i++) {
    settings_[i] = 0;
  }

  set_resizable(false);

  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD * 2);
  vbox->set_margin(5);
  add(*vbox);

  /*
   * The top part of the CalendarExample, flags and fontsel.
   */

  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, DEF_PAD);
  vbox->add(*hbox);
  auto hbbox = Gtk::make_managed<Gtk::Box>();
  hbox->add(*hbbox);
  hbbox->set_margin_end(DEF_PAD);
  hbbox->set_spacing(5);

  /* Calendar widget */
  auto frame = Gtk::make_managed<Gtk::Frame>("Calendar");
  hbbox->add(*frame);
  frame->set_margin_start(DEF_PAD);
  frame->set_margin_end(DEF_PAD);
  frame->set_hexpand();
  frame->set_halign(Gtk::Align::CENTER);
  calendar_ = new Gtk::Calendar();
  set_flags();
  calendar_->mark_day(19);
  frame->add(*calendar_);
  calendar_->signal_month_changed().connect(sigc::mem_fun(*this, &CalendarExample::month_changed));
  calendar_->signal_day_selected().connect(sigc::mem_fun(*this, &CalendarExample::day_selected));
  calendar_->signal_day_selected_double_click().connect(sigc::mem_fun(*this, &CalendarExample::day_selected_double_click));

  auto separator = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL);
  hbox->add(*separator);

  auto vbox2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD);
  hbox->add(*vbox2);
  vbox2->set_margin_start(DEF_PAD);
  vbox2->set_margin_end(DEF_PAD);

  /* Build the Right frame with the flags in */

  auto frameFlags = Gtk::make_managed<Gtk::Frame>("Flags");
  vbox2->add(*frameFlags);
  frameFlags->set_margin_end(DEF_PAD);
  auto vbox3 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD_SMALL);
  frameFlags->add(*vbox3);

  struct {
    const char *label;
  } flags[] =
    {
      { "Show Heading" },
      { "Show Day Names" },
      { "No Month Change" },
      { "Show Week Numbers" },
      { "Week Start Monday" }
    };

  for (int i = 0; i < 5; i++)
  {
    auto toggle = new Gtk::CheckButton(flags[i].label);
    toggle->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &CalendarExample::toggle_flag), toggle));
    vbox3->add(*toggle);
    flag_checkboxes_[i] = toggle;
  }

  /* Build the right font-button */
  font_button_ = Gtk::make_managed<Gtk::FontButton>();
  font_button_->signal_font_set().connect(sigc::mem_fun(*this, &CalendarExample::on_font_button_font_set));
  vbox2->add(*font_button_);

  // Add a StyleProvider to the Gtk::Calendar, so we can change the font.
  // This was easier before Gtk::Widget::override_font() was deprecated.
  css_provider_ = Gtk::CssProvider::create();
  auto refStyleContext = calendar_->get_style_context();
  refStyleContext->add_provider(css_provider_, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  css_provider_->signal_parsing_error().connect(
    sigc::mem_fun(*this, &CalendarExample::on_parsing_error));

  // Set initial font.
  on_font_button_font_set();

  /*
   *  Build the Signal-event part.
   */
  frame = Gtk::make_managed<Gtk::Frame>("Signal events");
  vbox->add(*frame);
  vbox2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, DEF_PAD_SMALL);
  frame->add(*vbox2);

  hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  vbox2->add(*hbox);
  auto label = Gtk::make_managed<Gtk::Label>("Day selected:");
  hbox->add(*label);
  label_selected_ = new Gtk::Label("");
  hbox->add(*label_selected_);

  hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  vbox2->add(*hbox);
  label = Gtk::make_managed<Gtk::Label>("Day selected double click:");
  hbox->add(*label);
  label_selected_double_click_ = new Gtk::Label("");
  hbox->add(*label_selected_double_click_);

  hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  vbox2->add(*hbox);
  label = Gtk::make_managed<Gtk::Label>("Month change:");
  hbox->add(*label);
  label_month_ = new Gtk::Label("");
  hbox->add(*label_month_);

  auto bbox = Gtk::make_managed<Gtk::Box>();
  vbox->add(*bbox);

  auto button = Gtk::make_managed<Gtk::Button>("Close");
  button->signal_clicked().connect(
    sigc::mem_fun(*this, &CalendarExample::on_button_close));
  bbox->add(*button);
  button->set_hexpand();
  button->set_halign(Gtk::Align::END);
  set_default_widget(*button);
}

Glib::Date CalendarExample::get_date() const
{
  using Glib::Date;
  Date date;
  calendar_->get_date(date);

  return date;
}

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");
  CalendarExample calendar;
  return app->run(calendar, argc, argv);
}

