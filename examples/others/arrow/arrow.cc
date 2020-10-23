/* example-start arrow arrow.c */

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

// 2014-09-06: The pan-[up,down,start,end]-symbolic icons are new.
// See https://bugzilla.gnome.org/show_bug.cgi?id=729565
// If they are not available in your selected icon theme, perhaps you can
// use the go-[up,down,previous,next]-symbolic icons.

class ArrowButton : public Gtk::Button
{
public:
   ArrowButton(Gtk::ArrowType arrow_type);
   ~ArrowButton();
};

/* Create a button with an arrow image of the specified direction.
 * Gtk::Arrow has been deprecated. This is how to do it now. */
ArrowButton::ArrowButton(Gtk::ArrowType arrow_type)
  : Gtk::Button()
{
  Glib::ustring icon_name;
  switch (arrow_type)
  {
    case Gtk::ArrowType::UP:    icon_name = "pan-up-symbolic"; break;
    case Gtk::ArrowType::DOWN:  icon_name = "pan-down-symbolic"; break;
    case Gtk::ArrowType::LEFT:  icon_name = "pan-start-symbolic"; break;
    case Gtk::ArrowType::RIGHT: icon_name = "pan-end-symbolic"; break;
    default:                    icon_name = "dialog-question"; break;
  }
  set_image_from_icon_name(icon_name, Gtk::IconSize::INHERIT, true);
}

ArrowButton::~ArrowButton()
{}

/* We will derive our new application window from window */
class AppWindow : public Gtk::Window
{
public:
  AppWindow();
  virtual ~AppWindow();
};

AppWindow::AppWindow()
{
  ArrowButton* button = nullptr;
  Gtk::Grid* grid = nullptr;

  set_title ("Arrow Buttons");

  /* Create a grid to hold the arrows/buttons */
  grid = Gtk::make_managed<Gtk::Grid>();
  grid->set_row_homogeneous(true);
  grid->set_column_homogeneous(true);

  /* Set the margin around the grid. */
  grid->set_margin(12);

  /* Pack and show all our widgets */
  button = Gtk::make_managed<ArrowButton>(Gtk::ArrowType::UP);
  grid->attach(*button, 1, 0);

  button = Gtk::make_managed<ArrowButton>(Gtk::ArrowType::LEFT);
  grid->attach(*button, 0, 1);

  button = Gtk::make_managed<ArrowButton>(Gtk::ArrowType::RIGHT);
  grid->attach(*button, 2, 1);

  button = Gtk::make_managed<ArrowButton>(Gtk::ArrowType::DOWN);
  grid->attach(*button, 1, 2);

  grid->set_row_spacing(5);
  grid->set_column_spacing(5);

  set_child (*grid);
}

AppWindow::~AppWindow()
{}

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<AppWindow>(argc, argv);
}

/* example-end */
