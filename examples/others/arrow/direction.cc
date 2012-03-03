/* example-start arrow arrow.c */

#include <gtkmm/arrow.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

class ArrowButton : public Gtk::Button
{
public:
   ArrowButton(Gtk::ArrowType,Gtk::ShadowType);
   ~ArrowButton();
};

/* Create an Arrow widget with the specified parameters
 * and pack it into a button */
ArrowButton::ArrowButton(Gtk::ArrowType arrow_type,Gtk::ShadowType shadow_type)
  : Gtk::Button()
{
  Gtk::Arrow* arrow = Gtk::manage (new Gtk::Arrow (arrow_type, shadow_type));
  add (*arrow);
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
  ArrowButton* button = 0;
  Gtk::Grid* grid = 0;

  set_title ("Arrow Buttons");

  /* Sets the border width of the window. */
  set_border_width (10);
  
  /* Create a grid to hold the arrows/buttons */
  grid = Gtk::manage (new Gtk::Grid ());
  grid->set_row_homogeneous(true);
  grid->set_column_homogeneous(true);
  grid->set_border_width (2);

  /* Pack and show all our widgets */
  button = Gtk::manage (new ArrowButton (Gtk::ARROW_UP, Gtk::SHADOW_ETCHED_IN));
  grid->attach (*button, 1, 0, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_LEFT, Gtk::SHADOW_ETCHED_IN));
  grid->attach (*button, 0, 1, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_RIGHT, Gtk::SHADOW_ETCHED_IN));
  grid->attach (*button, 2, 1, 1, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_DOWN, Gtk::SHADOW_ETCHED_IN));
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
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  AppWindow arrows;

  return app->run(arrows);
}

/* example-end */
