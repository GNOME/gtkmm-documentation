#include <gtkmm.h>
#include <iostream>

namespace
{
Gtk::Window* pDialog = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_button_clicked()
{
  if (pDialog)
    pDialog->set_visible(false); // set_visible(false) will cause Gtk::Application::run() to end.
}

void on_app_activate()
{
  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("basic.ui");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }

  // Get the GtkBuilder-instantiated dialog:
  pDialog = refBuilder->get_widget<Gtk::Window>("DialogBasic");
  if (!pDialog)
  {
    std::cerr << "Could not get the dialog" << std::endl;
    return;
  }

  // Get the GtkBuilder-instantiated button, and connect a signal handler:
  auto pButton = refBuilder->get_widget<Gtk::Button>("quit_button");
  if (pButton)
    pButton->signal_clicked().connect([] () { on_button_clicked(); });

  // It's not possible to delete widgets after app->run() has returned.
  // Delete the dialog with its child widgets before app->run() returns.
  pDialog->signal_hide().connect([] () { delete pDialog; });

  app->add_window(*pDialog);
  pDialog->set_visible(true);
}
} // anonymous namespace

int main(int argc, char** argv)
{
  app = Gtk::Application::create("org.gtkmm.example");

  // Instantiate a dialog when the application has been activated.
  // This can only be done after the application has been registered.
  // It's possible to call app->register_application() explicitly, but
  // usually it's easier to let app->run() do it for you.
  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc, argv);
}
