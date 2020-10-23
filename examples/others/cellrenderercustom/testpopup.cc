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

#include <gtkmm.h>
#include "cellrendererlist.h"
#include <sstream>


namespace
{

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  Gtk::TreeModelColumn<Glib::ustring> text1;
  Gtk::TreeModelColumn<Glib::ustring> text2;

  ModelColumns() { add(text1); add(text2); }
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

  void on_cell_edited(const Glib::ustring& path, const Glib::ustring& new_text);
};


AppWindow::AppWindow()
:
  list_columns_ (),
  list_store_   (Gtk::ListStore::create(list_columns_)),
  tree_view_    (list_store_)
{
  set_child(tree_view_);

  tree_view_.append_column("Text 1", list_columns_.text1);

  {
    CellRendererList    *const renderer = new CellRendererList();
    Gtk::TreeViewColumn *const column   = new Gtk::TreeViewColumn("Text 2", *Gtk::manage(renderer));

    tree_view_.append_column(*Gtk::manage(column));

    column->add_attribute(renderer->property_text(), list_columns_.text2);

    renderer->append_list_item("foo");
    renderer->append_list_item("bar");
    renderer->append_list_item("bazz");
    renderer->append_list_item("fuzz");
    renderer->append_list_item("sliff");
    renderer->append_list_item("sloff");

    renderer->property_editable() = true;

    renderer->signal_edited().connect(sigc::mem_fun(*this, &AppWindow::on_cell_edited));
  }

  std::ostringstream output (std::ios::ate);

  for(int i = 1; i <= 10; ++i)
  {
    output.str("row #");
    output << i;

    auto row = *list_store_->append();

    row[list_columns_.text1] = output.str();
    row[list_columns_.text2] = "foobar!";
  }
}

AppWindow::~AppWindow()
{}

void AppWindow::on_cell_edited(const Glib::ustring& path, const Glib::ustring& new_text)
{
  // Get the model row that has been edited.
  auto row = *list_store_->get_iter(Gtk::TreeModel::Path(path));

  row[list_columns_.text2] = new_text;
}

} // anonymous namespace


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<AppWindow>(argc, argv);
}

