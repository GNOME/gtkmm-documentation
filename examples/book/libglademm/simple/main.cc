#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>

Gtk::Dialog* pDialog = 0;

void on_button_clicked()
{
  if(pDialog)
    pDialog->hide(); //hide() will cause main::run() to end.
}

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> refXml;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    refXml = Gnome::Glade::Xml::create("simple.glade");
  }
  catch(const Gnome::Glade::XmlError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
#else
  std::auto_ptr<Gnome::Glade::XmlError> error;
  refXml = Gnome::Glade::Xml::create("simple.glade", "", "", error);
  if(error.get())
  {
    std::cerr << error->what() << std::endl;
    return 1;
  }
#endif

  //Get the Glade-instantiated Dialog:
  
  refXml->get_widget("DialogBasic", pDialog);
  if(pDialog)
  {
    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::Button* pButton = 0;
    refXml->get_widget("quit_button", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }

    kit.run(*pDialog);
  }

  return 0;
}

