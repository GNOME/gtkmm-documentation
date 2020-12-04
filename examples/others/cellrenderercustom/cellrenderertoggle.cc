/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 * Example Gtk::CellRendererCustom implementation.  The custom
 * MyCellRendererToggle is functionally equivalent to Gtk::CellRendererToggle.
 */

#include <gtkmm.h>
#include <gtkmm/snapshot.h>
#include <sstream>

// Can't have MyCellRendererToggle in an anonymous namespace, because then
// gcc 6.2.0 reports unused functions as errors when compiling with
// --enable-warnings=fatal.
//namespace
//{

class MyCellRendererToggle : public Gtk::CellRenderer
{
public:
  MyCellRendererToggle();
  virtual ~MyCellRendererToggle();

  Glib::PropertyProxy<bool> property_activatable();
  Glib::PropertyProxy<bool> property_active();
  Glib::PropertyProxy<bool> property_radio();

  using SignalToggled = sigc::signal<void(const Glib::ustring&)>;
  SignalToggled& signal_toggled();

protected:
  void get_preferred_width_vfunc(Gtk::Widget& widget,
    int& minimum_width, int& natural_width) const override;
  void get_preferred_width_for_height_vfunc(Gtk::Widget& widget, int height,
    int& minimum_width, int& natural_width) const override;
  void get_preferred_height_vfunc(Gtk::Widget& widget,
    int& minimum_height, int& natural_height) const override;
  void get_preferred_height_for_width_vfunc(Gtk::Widget& widget, int width,
    int& minimum_height, int& natural_height) const override;

  void snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot>& snapshot,
                      Gtk::Widget& widget,
                      const Gdk::Rectangle& background_area,
                      const Gdk::Rectangle& cell_area,
                      Gtk::CellRendererState flags) override;

  bool activate_vfunc(const Glib::RefPtr<const Gdk::Event>& event,
                      Gtk::Widget& widget,
                      const Glib::ustring& path,
                      const Gdk::Rectangle& background_area,
                      const Gdk::Rectangle& cell_area,
                      Gtk::CellRendererState flags) override;

private:
  Glib::Property<bool> property_activatable_;
  Glib::Property<bool> property_active_;
  Glib::Property<bool> property_radio_;

  SignalToggled signal_toggled_;
};


class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  Gtk::TreeModelColumn<Glib::ustring> text;
  Gtk::TreeModelColumn<bool>          active;

  ModelColumns() { add(text); add(active); }
};

class AppWindow : public Gtk::Window
{
public:
  AppWindow();
  virtual ~AppWindow();

private:
  ModelColumns                  list_columns_;
  Glib::RefPtr<Gtk::ListStore>  list_store_;
  Gtk::TreeView                 tree_view_;

  void on_cell_toggled(const Glib::ustring& path_string);
};


MyCellRendererToggle::MyCellRendererToggle()
:
  Glib::ObjectBase      (typeid(MyCellRendererToggle)),
  Gtk::CellRenderer     (),
  property_activatable_ (*this, "activatable", true),
  property_active_      (*this, "active",      false),
  property_radio_       (*this, "radio",       false)
{
  property_mode() = Gtk::CellRendererMode::ACTIVATABLE;
  property_xpad() = 2;
  property_ypad() = 2;
}

MyCellRendererToggle::~MyCellRendererToggle()
{}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_activatable()
{
  return property_activatable_.get_proxy();
}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_active()
{
  return property_active_.get_proxy();
}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_radio()
{
  return property_radio_.get_proxy();
}

MyCellRendererToggle::SignalToggled& MyCellRendererToggle::signal_toggled()
{
  return signal_toggled_;
}

enum { TOGGLE_WIDTH = 12 };

void MyCellRendererToggle::get_preferred_width_vfunc(Gtk::Widget& /* widget */,
  int& minimum_width, int& natural_width) const
{
  const unsigned int xpad = property_xpad();
  const int calc_width = xpad * 2 + TOGGLE_WIDTH;
  minimum_width = calc_width;
  natural_width = calc_width;
}

void MyCellRendererToggle::get_preferred_width_for_height_vfunc(Gtk::Widget& widget,
  int /* height */, int& minimum_width, int& natural_width) const
{
  get_preferred_width_vfunc(widget, minimum_width, natural_width);
}

void MyCellRendererToggle::get_preferred_height_vfunc(Gtk::Widget& /* widget */,
  int& minimum_height, int& natural_height) const
{
  const unsigned int ypad = property_ypad();
  const int calc_height = ypad * 2 + TOGGLE_WIDTH;
  minimum_height = calc_height;
  natural_height = calc_height;
}

void MyCellRendererToggle::get_preferred_height_for_width_vfunc(Gtk::Widget& widget,
  int /* width */, int& minimum_height, int& natural_height) const
{
  get_preferred_height_vfunc(widget, minimum_height, natural_height);
}

void MyCellRendererToggle::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot>& snapshot,
  Gtk::Widget& widget,
  const Gdk::Rectangle& /* background_area */,
  const Gdk::Rectangle& cell_area,
  Gtk::CellRendererState flags)
{
  const unsigned int cell_xpad = property_xpad();
  const unsigned int cell_ypad = property_ypad();

  //TODO: Support natural size.
  Gtk::Requisition requisition_min, requisition_natural;
  get_preferred_size(widget, requisition_min, requisition_natural);
  int width = requisition_min.get_width();
  int height = requisition_min.get_height();

  width  -= cell_xpad * 2;
  height -= cell_ypad * 2;

  if(width <= 0 || height <= 0)
    return;

  auto state = Gtk::StateFlags::INSENSITIVE;

  if (property_activatable_)
    state = (Gtk::StateFlags)0;

  if ((flags & Gtk::CellRendererState::SELECTED) == Gtk::CellRendererState::SELECTED)
    state = (widget.has_focus()) ? Gtk::StateFlags::SELECTED : Gtk::StateFlags::ACTIVE;

  if (property_active_)
    state |= Gtk::StateFlags::CHECKED;

  auto style_context = widget.get_style_context();
  style_context->set_state(state);

  // Create a cairo context to draw on.
  auto cr = snapshot->append_cairo(cell_area);

  if (property_radio_)
  {
    style_context->render_option(
      cr,
      cell_area.get_x() + cell_xpad,
      cell_area.get_y() + cell_ypad,
      width - 1, height - 1);
  }
  else
  {
    style_context->render_check(
      cr,
      cell_area.get_x() + cell_xpad,
      cell_area.get_y() + cell_ypad,
      width - 1, height - 1);
  }
}

bool MyCellRendererToggle::activate_vfunc(const Glib::RefPtr<const Gdk::Event>&,
                                          Gtk::Widget&,
                                          const Glib::ustring& path,
                                          const Gdk::Rectangle&,
                                          const Gdk::Rectangle&,
                                          Gtk::CellRendererState)
{
  if(property_activatable_)
  {
    signal_toggled_(path);
    return true;
  }

  return false;
}


AppWindow::AppWindow()
:
  list_columns_ (),
  list_store_   (Gtk::ListStore::create(list_columns_)),
  tree_view_    (list_store_)
{
  set_child(tree_view_);

  tree_view_.append_column("Text", list_columns_.text);

  {
    MyCellRendererToggle *const renderer = new MyCellRendererToggle();
    Gtk::TreeViewColumn  *const column   = new Gtk::TreeViewColumn("Active", *Gtk::manage(renderer));
    tree_view_.append_column(*Gtk::manage(column));

    column->add_attribute(renderer->property_active(), list_columns_.active);
    renderer->signal_toggled().connect(sigc::mem_fun(*this, &AppWindow::on_cell_toggled));
  }

  std::ostringstream output (std::ios::ate);

  for(int i = 1; i <= 10; ++i)
  {
    output.str("row #");
    output << i;

    auto row = *list_store_->append();

    row[list_columns_.text]   = output.str();
    row[list_columns_.active] = ((i % 2) != 0);
  }
}

AppWindow::~AppWindow()
{}

void AppWindow::on_cell_toggled(const Glib::ustring& path_string)
{
  // Get the model row that has been toggled.
  auto row = *list_store_->get_iter(Gtk::TreeModel::Path(path_string));

  // Invert the 'active' value in the toggled row.
  row[list_columns_.active] = !row[list_columns_.active];
}

//} // anonymous namespace


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<AppWindow>(argc, argv);
}
