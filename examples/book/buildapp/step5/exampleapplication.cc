/* gtkmm example Copyright (C) 2016 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "exampleapplication.h"
#include "exampleappwindow.h"
#include "exampleappprefs.h"
#include <iostream>
#include <exception>

ExampleApplication::ExampleApplication()
: Gtk::Application("org.gtkmm.examples.application", Gio::APPLICATION_HANDLES_OPEN)
{
}

Glib::RefPtr<ExampleApplication> ExampleApplication::create()
{
  return Glib::RefPtr<ExampleApplication>(new ExampleApplication());
}

ExampleAppWindow* ExampleApplication::create_appwindow()
{
  auto appwindow = ExampleAppWindow::create();

  // Make sure that the application runs for as long this window is still open.
  add_window(*appwindow);

  // Gtk::Application::add_window() connects a signal handler to the window's
  // signal_hide(). That handler removes the window from the application.
  // If it's the last window to be removed, the application stops running.
  // Gtk::Window::set_application() does not connect a signal handler, but is
  // otherwise equivalent to Gtk::Application::add_window().

  // Delete the window when it is hidden.
  appwindow->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
    &ExampleApplication::on_hide_window), appwindow));

  return appwindow;
}

void ExampleApplication::on_startup()
{
  // Call the base class's implementation.
  Gtk::Application::on_startup();

  // Add actions and keyboard accelerators for the application menu.
  add_action("preferences", sigc::mem_fun(*this, &ExampleApplication::on_action_preferences));
  add_action("quit", sigc::mem_fun(*this, &ExampleApplication::on_action_quit));
  set_accel_for_action("app.quit", "<Ctrl>Q");

  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_resource("/org/gtkmm/exampleapp/app_menu.ui");
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "ExampleApplication::on_startup(): " << ex.what() << std::endl;
    return;
  }

  auto object = refBuilder->get_object("appmenu");
  auto app_menu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(object);
  if (app_menu)
    set_app_menu(app_menu);
  else
    std::cerr << "ExampleApplication::on_startup(): No \"appmenu\" object in app_menu.ui"
              << std::endl;
}

void ExampleApplication::on_activate()
{
  try
  {
    // The application has been started, so let's show a window.
    auto appwindow = create_appwindow();
    appwindow->present();
  }
  // If create_appwindow() throws an exception (perhaps from Gtk::Builder),
  // no window has been created, no window has been added to the application,
  // and therefore the application will stop running.
  catch (const Glib::Error& ex)
  {
    std::cerr << "ExampleApplication::on_activate(): " << ex.what() << std::endl;
  }
  catch (const std::exception& ex)
  {
    std::cerr << "ExampleApplication::on_activate(): " << ex.what() << std::endl;
  }
}

void ExampleApplication::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& /* hint */)
{
  // The application has been asked to open some files,
  // so let's open a new view for each one.
  ExampleAppWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<ExampleAppWindow*>(windows[0]);

  try
  {
    if (!appwindow)
      appwindow = create_appwindow();

    for (const auto& file : files)
      appwindow->open_file_view(file);

    appwindow->present();
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "ExampleApplication::on_open(): " << ex.what() << std::endl;
  }
  catch (const std::exception& ex)
  {
    std::cerr << "ExampleApplication::on_open(): " << ex.what() << std::endl;
  }
}

void ExampleApplication::on_hide_window(Gtk::Window* window)
{
  delete window;
}

void ExampleApplication::on_action_preferences()
{
  try
  {
    auto prefs_dialog = ExampleAppPrefs::create(*get_active_window());
    prefs_dialog->present();

    // Delete the dialog when it is hidden.
    prefs_dialog->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
      &ExampleApplication::on_hide_window), prefs_dialog));
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "ExampleApplication::on_action_preferences(): " << ex.what() << std::endl;
  }
  catch (const std::exception& ex)
  {
    std::cerr << "ExampleApplication::on_action_preferences(): " << ex.what() << std::endl;
  }
}

void ExampleApplication::on_action_quit()
{
  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window. See comment in create_appwindow().
  auto windows = get_windows();
  for (auto window : windows)
    window->hide();

  // Not really necessary, when Gtk::Widget::hide() is called, unless
  // Gio::Application::hold() has been called without a corresponding call
  // to Gio::Application::release().
  quit();
}
