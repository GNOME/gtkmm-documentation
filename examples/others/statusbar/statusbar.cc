#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>

// gtkmm version of the "statusbar" example from the gtk+ tutorial

class StatusBarExample : public Gtk::Window
{
public:
  StatusBarExample();

protected:

  void push_item(unsigned int context_id);
  void pop_item(unsigned int context_id) { m_status_bar.pop(context_id); }

  unsigned int m_context_id, m_count;
  Gtk::Box m_vbox;
  Gtk::Button m_bPush, m_bPop;
  Gtk::Statusbar m_status_bar;
};


StatusBarExample::StatusBarExample()
:
  m_count(1),
  m_vbox(Gtk::Orientation::VERTICAL, 1),
  m_bPush("push item"),
  m_bPop("pop last item")
{
  m_context_id = m_status_bar.get_context_id("Statusbar example");

  set_size_request(200, 100);
  set_title("gtkmm Statusbar Example");

  set_child(m_vbox);

  m_vbox.append(m_status_bar);
  m_status_bar.set_expand();

  m_bPush.signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &StatusBarExample::push_item), m_context_id) );
  m_bPush.set_expand();
  m_vbox.append(m_bPush);

  m_bPop.signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &StatusBarExample::pop_item), m_context_id) );
  m_bPop.set_expand();
  m_vbox.append(m_bPop);
}

void
StatusBarExample::push_item(unsigned int context_id)
{
  char buff[20];

  g_snprintf(buff, 20, "Item %d", m_count++);
  m_status_bar.push(buff, context_id);
}

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<StatusBarExample>(argc, argv);
}

