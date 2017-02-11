#include "tictactoe.h"
#include <gtkmm/window.h>
#include <gtkmm/application.h>


void
win (TicTacToe *ttt)
{
  g_print ("Yay!\n");
  ttt->clear();
}


int
main (int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  auto ttt = manage( new TicTacToe );
  ttt->tictactoe.connect( sigc::bind (sigc::ptr_fun(&win), ttt) );

  Gtk::Window window;
  window.set_title("Tic-Tac-Toe");
  ttt->set_margin(10);
  window.add(*ttt);

  return app->run(window, argc, argv);
}
