#include "tictactoe.h"
#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <iostream>

void
win (TicTacToe* ttt)
{
  std::cout << "Yay!\n";
  ttt->clear();
}

class MyWindow : public Gtk::Window
{
public:
  MyWindow();
};

MyWindow::MyWindow()
{
  set_title("Tic-Tac-Toe");

  auto ttt = Gtk::make_managed<TicTacToe>();
  ttt->tictactoe.connect([ttt](){ win(ttt); });
  ttt->set_margin(10);
  set_child(*ttt);
}

int
main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<MyWindow>(argc, argv);
}
