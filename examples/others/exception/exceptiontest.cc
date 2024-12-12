#include <iostream>
#include <gtkmm/box.h>
#include <glibmm/convert.h>
#include <glibmm/exceptionhandler.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>

namespace
{
class MyButton : public Gtk::Button
{
public:
  explicit MyButton(const Glib::ustring& label);

protected:
  void on_clicked() override; // signal handler
};

class MyException1 {};
class MyException2 {};
class MyException3 {};

MyButton::MyButton(const Glib::ustring& label)
:
  Gtk::Button(label)
{}

void MyButton::on_clicked()
{
  std::cout << "The Button was clicked.\n";
  throw MyException1();
}

void global_on_clicked()
{
  std::cout << "The Button was clicked.\n";
  throw MyException2();
}

void global_on_clicked_throw_glib_error()
{
  std::cout << "The Button was clicked.\n";
  (void)Glib::locale_from_utf8("Und tsch\xfcss!"); // invalid UTF-8
}

void global_on_clicked_throw_std_exception()
{
  std::cout << "The Button was clicked.\n";
  Glib::ustring str;
  str.at(3); // out of range
}

void handler1()
{
  std::cout << "exception handler 1\n";

  try
  {
    throw; // rethrow exception
  }
  catch(MyException1&)
  {
    std::cout << "caught MyException1\n";
  }
  // if not handled it gets passed to next handler
}

void handler2()
{
  std::cout << "exception handler 2\n";

  try
  {
    throw; // rethrow exception
  }
  catch(MyException2&)
  {
    std::cout << "caught MyException2\n";
  }
  // if not handled it gets passed to next handler
}

class MyWindow : public Gtk::Window
{
public:
  MyWindow();
private:
  sigc::connection conn_handler1;
  sigc::connection conn_handler2;
};

MyWindow::MyWindow()
{
  set_title("Exception Handlers");

  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
  box->set_margin(10);
  set_child(*box);

  // New exception handlers are inserted at the back of the per-thread
  // handler list. Thus, in this example handler2() is executed after handler1().
  conn_handler1 = Glib::add_exception_handler(&handler1);
  conn_handler2 = Glib::add_exception_handler(&handler2);

  box->append(*Gtk::make_managed<MyButton>("From virtual method"));
  auto button2 = Gtk::make_managed<Gtk::Button>("From signal handler");
  box->append(*button2);
  auto button3 = Gtk::make_managed<Gtk::Button>("Unhandled Glib::Error");
  box->append(*button3);
  auto button4 = Gtk::make_managed<Gtk::Button>("Unhandled std::exception (crash!)");
  box->append(*button4);
  auto button5 = Gtk::make_managed<Gtk::Button>("Disconnect handler 1");
  box->append(*button5);
  auto button6 = Gtk::make_managed<Gtk::Button>("Disconnect handler 2");
  box->append(*button6);

  button2->signal_clicked().connect(&global_on_clicked);
  button3->signal_clicked().connect(&global_on_clicked_throw_glib_error);
  button4->signal_clicked().connect(&global_on_clicked_throw_std_exception);
  button5->signal_clicked().connect(sigc::mem_fun(conn_handler1, &sigc::connection::disconnect));
  button6->signal_clicked().connect(sigc::mem_fun(conn_handler2, &sigc::connection::disconnect));
}
} // anonymous namespace

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<MyWindow>(argc, argv);
}
