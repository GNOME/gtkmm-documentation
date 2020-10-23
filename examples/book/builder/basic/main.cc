#include <gtkmm.h>
#include <iostream>

Gtk::Dialog* pDialog = nullptr;

static
void on_button_clicked()
{
  if(pDialog)
    pDialog->hide(); //hide() will cause Gtk::Application::run() to end.
}

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  // The application must be registered when the builder adds widgets from
  // the basic.glade file.
  // Calling Gio::Application::register_application() explicitly is necessary
  // in this example because the .glade file is loaded in the main() function.
  // There are better ways. See other examples, such as examples/book/buildapp/,
  // and examples/book/menus/ and examples/book/menus_and_toolbars/.
  app->register_application();

  //Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("basic.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  //Get the GtkBuilder-instantiated Dialog:
  pDialog = refBuilder->get_widget<Gtk::Dialog>("DialogBasic");

  int status = 1;
  if (pDialog)
  {
    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    auto pButton = refBuilder->get_widget<Gtk::Button>("quit_button");
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }

    // All widgets must be deleted before app->run() returns.
    // This is yet another reason why you should usually not use the builder
    // in the main() function.
    pDialog->signal_hide().connect([&refBuilder] ()
    {
      delete pDialog;
      refBuilder.reset();
    });

    // We can call add_window() before run() because we have registered the
    // application. (run() registers the application, if it has not been done.)
    app->add_window(*pDialog);
    pDialog->show();
    status = app->run(argc, argv);
  }

  return status;
}
