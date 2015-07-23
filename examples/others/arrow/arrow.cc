/* example-start arrow arrow.c */

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

// 2014-09-06: The pan-[up,down,start,end]-symbolic icons are new.
// See https://bugzilla.gnome.org/show_bug.cgi?id=729565
// If they are not available in your selected icon theme, perhaps you can
// use the go-[up,down,previous,next]-symbolic icons.
#define USE_PAN_ICON_NAMES 0

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
#if USE_PAN_ICON_NAMES
    case Gtk::ARROW_UP:    icon_name = "pan-up-symbolic"; break;
    case Gtk::ARROW_DOWN:  icon_name = "pan-down-symbolic"; break;
    case Gtk::ARROW_LEFT:  icon_name = "pan-start-symbolic"; break;
    case Gtk::ARROW_RIGHT: icon_name = "pan-end-symbolic"; break;
#else
    case Gtk::ARROW_UP:    icon_name = "go-up-symbolic"; break;
    case Gtk::ARROW_DOWN:  icon_name = "go-down-symbolic"; break;
    case Gtk::ARROW_LEFT:  icon_name = "go-previous-symbolic"; break;
    case Gtk::ARROW_RIGHT: icon_name = "go-next-symbolic"; break;
#endif
    default:               icon_name = "dialog-question"; break;
  }
  set_image_from_icon_name(icon_name, Gtk::ICON_SIZE_BUTTON, true);
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

  /* Sets the border width of the window. */
  set_border_width (10);
  
  /* Create a grid to hold the arrows/buttons */
  grid = Gtk::manage (new Gtk::Grid ());
  grid->set_row_homogeneous(true);
  grid->set_column_homogeneous(true);
  grid->set_border_width (2);

  /* Pack and show all our widgets */
  button = Gtk::manage (new ArrowButton (Gtk::ARROW_UP));
  grid->attach (*button, 1, 0, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_LEFT));
  grid->attach (*button, 0, 1, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_RIGHT));
  grid->attach (*button, 2, 1, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_DOWN));
  grid->attach (*button, 1, 2, 1, 1);

  grid->set_row_spacing(5);
  grid->set_column_spacing(5);
 
  add (*grid);
  show_all ();
}

AppWindow::~AppWindow()
{}

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  AppWindow arrows;

  return app->run(arrows);
}

/* example-end */
