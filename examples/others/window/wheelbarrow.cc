// A wheelbarrow on a transparent background

#include <gdkmm.h>
#include <gtkmm/image.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/version.h>
#include <iostream>

#define HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY GTKMM_CHECK_VERSION(4,9,1)

namespace
{

const char *const wheelbarrow_xpm[] =
{
  "48 48 64 1",
  "       c None",
  ".      c #DF7DCF3CC71B",
  "X      c #965875D669A6",
  "o      c #71C671C671C6",
  "O      c #A699A289A699",
  "+      c #965892489658",
  "@      c #8E38410330C2",
  "#      c #D75C7DF769A6",
  "$      c #F7DECF3CC71B",
  "%      c #96588A288E38",
  "&      c #A69992489E79",
  "*      c #8E3886178E38",
  "=      c #104008200820",
  "-      c #596510401040",
  ";      c #C71B30C230C2",
  ":      c #C71B9A699658",
  ">      c #618561856185",
  ",      c #20811C712081",
  "<      c #104000000000",
  "1      c #861720812081",
  "2      c #DF7D4D344103",
  "3      c #79E769A671C6",
  "4      c #861782078617",
  "5      c #41033CF34103",
  "6      c #000000000000",
  "7      c #49241C711040",
  "8      c #492445144924",
  "9      c #082008200820",
  "0      c #69A618611861",
  "q      c #B6DA71C65144",
  "w      c #410330C238E3",
  "e      c #CF3CBAEAB6DA",
  "r      c #71C6451430C2",
  "t      c #EFBEDB6CD75C",
  "y      c #28A208200820",
  "u      c #186110401040",
  "i      c #596528A21861",
  "p      c #71C661855965",
  "a      c #A69996589658",
  "s      c #30C228A230C2",
  "d      c #BEFBA289AEBA",
  "f      c #596545145144",
  "g      c #30C230C230C2",
  "h      c #8E3882078617",
  "j      c #208118612081",
  "k      c #38E30C300820",
  "l      c #30C2208128A2",
  "z      c #38E328A238E3",
  "x      c #514438E34924",
  "c      c #618555555965",
  "v      c #30C2208130C2",
  "b      c #38E328A230C2",
  "n      c #28A228A228A2",
  "m      c #41032CB228A2",
  "M      c #104010401040",
  "N      c #492438E34103",
  "B      c #28A2208128A2",
  "V      c #A699596538E3",
  "C      c #30C21C711040",
  "Z      c #30C218611040",
  "A      c #965865955965",
  "S      c #618534D32081",
  "D      c #38E31C711040",
  "F      c #082000000820",
  "                                                ",
  "          .XoO                                  ",
  "         +@#$%o&                                ",
  "         *=-;#::o+                              ",
  "           >,<12#:34                            ",
  "             45671#:X3                          ",
  "               +89<02qwo                        ",
  "e*                >,67;ro                       ",
  "ty>                 459@>+&&                    ",
  "$2u+                  ><ipas8*                  ",
  "%$;=*                *3:.Xa.dfg>                ",
  "Oh$;ya             *3d.a8j,Xe.d3g8+             ",
  " Oh$;ka          *3d$a8lz,,xxc:.e3g54           ",
  "  Oh$;kO       *pd$%svbzz,sxxxxfX..&wn>         ",
  "   Oh$@mO    *3dthwlsslszjzxxxxxxx3:td8M4       ",
  "    Oh$@g& *3d$XNlvvvlllm,mNwxxxxxxxfa.:,B*     ",
  "     Oh$@,Od.czlllllzlmmqV@V#V@fxxxxxxxf:%j5&   ",
  "      Oh$1hd5lllslllCCZrV#r#:#2AxxxxxxxxxcdwM*  ",
  "       OXq6c.%8vvvllZZiqqApA:mq:Xxcpcxxxxxfdc9* ",
  "        2r<6gde3bllZZrVi7S@SV77A::qApxxxxxxfdcM ",
  "        :,q-6MN.dfmZZrrSS:#riirDSAX@Af5xxxxxfevo",
  "         +A26jguXtAZZZC7iDiCCrVVii7Cmmmxxxxxx%3g",
  "          *#16jszN..3DZZZZrCVSA2rZrV7Dmmwxxxx&en",
  "           p2yFvzssXe:fCZZCiiD7iiZDiDSSZwwxx8e*>",
  "           OA1<jzxwwc:$d%NDZZZZCCCZCCZZCmxxfd.B ",
  "            3206Bwxxszx%et.eaAp77m77mmmf3&eeeg* ",
  "             @26MvzxNzvlbwfpdettttttttttt.c,n&  ",
  "             *;16=lsNwwNwgsvslbwwvccc3pcfu<o    ",
  "              p;<69BvwwsszslllbBlllllllu<5+     ",
  "              OS0y6FBlvvvzvzss,u=Blllj=54       ",
  "               c1-699Blvlllllu7k96MMMg4         ",
  "               *10y8n6FjvllllB<166668           ",
  "                S-kg+>666<M<996-y6n<8*          ",
  "                p71=4 m69996kD8Z-66698&&        ",
  "                &i0ycm6n4 ogk17,0<6666g         ",
  "                 N-k-<>     >=01-kuu666>        ",
  "                 ,6ky&      &46-10ul,66,        ",
  "                 Ou0<>       o66y<ulw<66&       ",
  "                  *kk5       >66By7=xu664       ",
  "                   <<M4      466lj<Mxu66o       ",
  "                   *>>       +66uv,zN666*       ",
  "                              566,xxj669        ",
  "                              4666FF666>        ",
  "                               >966666M         ",
  "                                oM6668+         ",
  "                                  *4            ",
  "                                                ",
  "                                                "
};

const char *const transparent_background_css =
  "#wheelbarrow-window { background-color: rgba(0,0,0,0.0); }";

class Wheelbarrow : public Gtk::Window
{
public:
  Wheelbarrow();
  ~Wheelbarrow() override;

protected:
  void on_button_pressed(int n_press, double x, double y);
  static void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error);

  Glib::RefPtr<Gtk::GestureClick> m_gesture_click;
};


Wheelbarrow::Wheelbarrow()
{
  set_resizable(false);
  set_decorated(false);

  set_name("wheelbarrow-window"); // CSS name, which must be used in the CSS file.

  // Load extra CSS data.
  auto css_provider = Gtk::CssProvider::create();
#if HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY
  Gtk::StyleProvider::add_provider_for_display(get_display(), css_provider,
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#else
  Gtk::StyleContext::add_provider_for_display(get_display(), css_provider,
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif
  css_provider->signal_parsing_error().connect(
    [](const auto& section, const auto& error)
    { on_parsing_error(section, error); }
  );
  css_provider->load_from_data(transparent_background_css);

  const auto pixbuf = Gdk::Pixbuf::create_from_xpm_data(wheelbarrow_xpm);
  Gtk::Image *const image = Gtk::make_managed<Gtk::Image>(pixbuf);
  image->set_size_request(48, 48);
  set_child(*image);

  m_gesture_click = Gtk::GestureClick::create();
  m_gesture_click->set_button(0); // All mouse buttons
  m_gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &Wheelbarrow::on_button_pressed));
  add_controller(m_gesture_click);
}

Wheelbarrow::~Wheelbarrow()
{}

void Wheelbarrow::on_button_pressed(int /* n_press */, double x, double y)
{
  const auto current_button = m_gesture_click->get_current_button();
  switch (current_button)
  {
    case 1:
    {
      auto toplevel = std::dynamic_pointer_cast<Gdk::ToplevelSurfaceImpl>(get_surface());
      if (toplevel)
        toplevel->begin_move(m_gesture_click->get_current_event_device(),
          current_button, x, y, m_gesture_click->get_current_event_time());
      break;
    }
    case 3: set_visible(false); break;
  }
}

void Wheelbarrow::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
  const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    auto start_location = section->get_start_location();
    auto end_location = section->get_end_location();
    std::cerr << "  start_line = " << start_location.get_lines()+1
              << ", end_line = " << end_location.get_lines()+1 << std::endl;
    std::cerr << "  start_position = " << start_location.get_line_chars()
              << ", end_position = " << end_location.get_line_chars() << std::endl;
  }
}

} // anonymous namespace


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<Wheelbarrow>(argc, argv);
}
