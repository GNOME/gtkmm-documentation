#include <gtkmm.h>
#include <iostream>

Gtk::Dialog* pDialog = nullptr;

static
void on_button_clicked()
{
  if(pDialog)
    pDialog->hide(); //hide() will cause main::run() to end.
}

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

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
  if(pDialog)
  {
    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    auto pButton = refBuilder->get_widget<Gtk::Button>("quit_button");
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }

    app->run(*pDialog, argc, argv);
  }

  delete pDialog;

  return 0;
}
