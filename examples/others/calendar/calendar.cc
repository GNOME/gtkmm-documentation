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
    calendar_->set_display_options((Gtk::CalendarDisplayOptions)options);
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
  try
  {
    const Glib::ustring font_name = font_button_->get_font_name();
    if (!font_name.empty())
    {
      css_provider_->load_from_data("* { font: " + font_name + "; }");
    }
  }
  catch (const Gtk::CssProviderError& ex)
  {
    std::cerr << "CssProviderError, Gtk::CssProvider::load_from_data() failed: "
              << ex.what() << std::endl;
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Error, Gtk::CssProvider::load_from_data() failed: "
              << ex.what() << std::endl;
  }
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
    std::cerr << "  URI = " << section->get_file()->get_uri() << std::endl;
    std::cerr << "  start_line = " << section->get_start_line()+1
              << ", end_line = " << section->get_end_line()+1 << std::endl;
    std::cerr << "  start_position = " << section->get_start_position()
              << ", end_position = " << section->get_end_position() << std::endl;
  }
}

CalendarExample::CalendarExample()
{
  for (int i = 0; i < 5; i++) {
    settings_[i] = 0;
  }

  set_border_width(5);

  set_resizable(false);

  auto vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, DEF_PAD));
  add(*vbox);

  /*
   * The top part of the CalendarExample, flags and fontsel.
   */

  auto hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, DEF_PAD));
  vbox->pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  auto hbbox = Gtk::manage(new Gtk::ButtonBox());
  hbox->pack_start(*hbbox, Gtk::PACK_SHRINK, DEF_PAD);
  hbbox->set_layout(Gtk::BUTTONBOX_SPREAD);
  hbbox->set_spacing(5);

  /* Calendar widget */
  auto frame = Gtk::manage(new Gtk::Frame("Calendar"));
  hbbox->pack_start(*frame, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  calendar_ = new Gtk::Calendar();
  set_flags();
  calendar_->mark_day(19);
  frame->add(*calendar_);
  calendar_->signal_month_changed().connect(sigc::mem_fun(*this, &CalendarExample::month_changed));
  calendar_->signal_day_selected().connect(sigc::mem_fun(*this, &CalendarExample::day_selected));
  calendar_->signal_day_selected_double_click().connect(sigc::mem_fun(*this, &CalendarExample::day_selected_double_click));

  auto separator = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_VERTICAL));
  hbox->pack_start (*separator, Gtk::PACK_SHRINK);

  auto vbox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, DEF_PAD));
  hbox->pack_start(*vbox2, Gtk::PACK_SHRINK, DEF_PAD);

  /* Build the Right frame with the flags in */

  auto frameFlags = Gtk::manage(new Gtk::Frame("Flags"));
  vbox2->pack_start(*frameFlags, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  auto vbox3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, DEF_PAD_SMALL));
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
    vbox3->pack_start(*toggle);
    flag_checkboxes_[i] = toggle;
  }

  /* Build the right font-button */
  font_button_ = Gtk::manage(new Gtk::FontButton());
  font_button_->signal_font_set().connect(sigc::mem_fun(*this, &CalendarExample::on_font_button_font_set));
  vbox2->pack_start(*font_button_, Gtk::PACK_SHRINK);

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
  frame = Gtk::manage(new Gtk::Frame("Signal events"));
  vbox->pack_start(*frame, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  vbox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, DEF_PAD_SMALL));
  frame->add(*vbox2);

  hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  auto label = Gtk::manage(new Gtk::Label("Day selected:"));
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_selected_ = new Gtk::Label("");
  hbox->pack_start (*label_selected_, Gtk::PACK_SHRINK);

  hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  label = Gtk::manage(new Gtk::Label("Day selected double click:"));
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_selected_double_click_ = new Gtk::Label("");
  hbox->pack_start (*label_selected_double_click_, Gtk::PACK_SHRINK);

  hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  label = Gtk::manage(new Gtk::Label("Month change:"));
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_month_ = new Gtk::Label("");
  hbox->pack_start(*label_month_, Gtk::PACK_SHRINK);

  auto bbox = Gtk::manage(new Gtk::ButtonBox());
  vbox->pack_start(*bbox, Gtk::PACK_SHRINK);
  bbox->set_layout(Gtk::BUTTONBOX_END);

  auto button = Gtk::manage(new Gtk::Button("Close"));
  button->signal_clicked().connect(
    sigc::mem_fun(*this, &CalendarExample::on_button_close));
  bbox->add(*button);
  button->set_can_default();
  button->grab_default();

  show_all();
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
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  CalendarExample calendar;
  return app->run(calendar);
}

