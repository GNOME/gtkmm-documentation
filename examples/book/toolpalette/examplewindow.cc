//$Id: examplewindow.cc 870 2007-07-13 19:08:46Z murrayc $ -*- c++ -*-

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

#include "examplewindow.h"

static bool sort_predicate(const Gtk::StockID& a, const Gtk::StockID& b)
{
  return a.get_string() < b.get_string();
}


void ExampleWindow::load_stock_items()
{
  Gtk::ToolItemGroup* group_af = 
    Gtk::manage(new Gtk::ToolItemGroup("Stock Icons (A-F)"));
  m_ToolPalette.add(*group_af);
  Gtk::ToolItemGroup* group_gn = 
    Gtk::manage(new Gtk::ToolItemGroup("Stock Icons (G-N)"));
  m_ToolPalette.add(*group_gn);
  Gtk::ToolItemGroup* group_or = 
    Gtk::manage(new Gtk::ToolItemGroup("Stock Icons (O-R)"));
  m_ToolPalette.add(*group_or);
  Gtk::ToolItemGroup* group_sz = 
    Gtk::manage(new Gtk::ToolItemGroup("Stock Icons (S-Z)"));
  m_ToolPalette.add(*group_sz);

  // Obtain the IDs of all stock items:
  typedef std::vector<Gtk::StockID> type_vecIDs;
  type_vecIDs vecIDs = Gtk::Stock::get_ids();

  std::sort(vecIDs.begin(), vecIDs.end(), &sort_predicate);

  Gtk::ToolItemGroup* group = 0;

  // Iterate through them, populating the ListStore as appropriate:
  for(type_vecIDs::const_iterator iterIDs = vecIDs.begin(); iterIDs != vecIDs.end(); ++iterIDs)
  {
    const Gtk::StockID& stockid = *iterIDs;
    const Glib::ustring str = stockid.get_string();
    if(str.size() < 4)
      continue;

    switch(str[4])
    {
      case 'a':
        group = group_af;
        break;
      case 'g':
        group = group_gn;
        break;
      case 'o':
        group = group_or;
        break;
      case 's':
        group = group_sz;
        break;
      default:
        //Use the previous group
        //(They are sorted.)
        break;
    }

    if(!group)
      continue;

    Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton(stockid));
    button->set_tooltip_text(str);
    button->set_is_important();
    group->insert(*button);

    Gtk::StockItem stockitem;
    if(!Gtk::StockItem::lookup(stockid, stockitem) || 
      stockitem.get_label().empty())
        button->set_label(str);
  }
}


void ExampleWindow::load_toggle_items()
{
  Gtk::ToolItemGroup* group = 
    Gtk::manage(new Gtk::ToolItemGroup("Radio Item"));
  m_ToolPalette.add(*group);

  Gtk::RadioToolButton::Group radio_group;

  for(int i = 1; i <= 10; ++i)
  {
    const Glib::ustring label = Glib::ustring::compose("#%1", i);
    Gtk::RadioToolButton* button = Gtk::manage(new Gtk::RadioToolButton());
    button->set_group(radio_group);
    button->set_label(label);
   
    group->insert(*button);
  }
}


static Gtk::ToolItem* create_entry_item(const Glib::ustring& text)
{
  Gtk::Entry* entry = Gtk::manage(new Gtk::Entry());
  entry->set_text(text);
  entry->set_width_chars(5);

  Gtk::ToolItem* item = Gtk::manage(new Gtk::ToolItem());
  item->add(*entry);

  return item;
}

void ExampleWindow::load_special_items()
{
  Gtk::ToolItemGroup* group = Gtk::manage(new Gtk::ToolItemGroup());

  Gtk::Button *label_button = Gtk::manage(new Gtk::Button("Advanced Features"));
  label_button->show();
  group->set_label_widget(*label_button);
  m_ToolPalette.add(*group);

  Gtk::ToolItem* item = create_entry_item ("homogeneous=false");
  group->insert(*item);
  //TODO: Add Gtk::Container::set_child_property().
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (item->gobj()),
                           "homogeneous", FALSE, NULL);

  item = create_entry_item ("homogeneous=FALSE, expand=TRUE");
  group->insert(*item);
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (item->gobj()),
                           "homogeneous", FALSE, "expand", TRUE,
                           NULL);

  item = create_entry_item ("homogeneous=FALSE, expand=TRUE, fill=FALSE");
  group->insert(*item);
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (item->gobj()),
                           "homogeneous", FALSE, "expand", TRUE,
                           "fill", FALSE, NULL);

  item = create_entry_item ("homogeneous=FALSE, expand=TRUE, new-row=TRUE");
  group->insert(*item);
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (item->gobj()),
                           "homogeneous", FALSE, "expand", TRUE,
                           "new-row", TRUE, NULL);

  item = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::GO_UP));
  item->set_tooltip_text("Show on vertical palettes only");
  group->insert(*item);
  item->set_visible_horizontal(false);

  item = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::GO_FORWARD));
  item->set_tooltip_text("Show on horizontal palettes only");
  group->insert(*item);
  item->set_visible_vertical(false);

  item = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::FULLSCREEN));
  item->set_tooltip_text("Expanded this item");
  group->insert(*item);
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (item->gobj()),
                           "homogeneous", FALSE,
                           "expand", TRUE,
                           NULL);

  item = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::HELP));
  item->set_tooltip_text("A regular item");
  group->insert(*item);
}

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL, 6),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL, 6)
{
  set_title("Gtk::ToolPalette example");
  set_size_request(600, 600);
  set_border_width(6);

  add(m_VBox);

  //The Orientation ComboBox:
  m_refTreeModelOrientation = Gtk::ListStore::create(m_ColumnsOrientation);
  Gtk::TreeModel::Row row = *(m_refTreeModelOrientation->append());
  row[m_ColumnsOrientation.m_col_value] = Gtk::ORIENTATION_HORIZONTAL;
  row[m_ColumnsOrientation.m_col_name] = "Horizontal";\
  row = *(m_refTreeModelOrientation->append());
  row[m_ColumnsOrientation.m_col_value] = Gtk::ORIENTATION_VERTICAL;
  row[m_ColumnsOrientation.m_col_name] = "Vertical";
  m_ComboOrientation.set_model(m_refTreeModelOrientation);
  m_VBox.pack_start(m_ComboOrientation, Gtk::PACK_SHRINK);
  m_ComboOrientation.pack_start(m_ColumnsOrientation.m_col_name);
  m_ComboOrientation.signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_combo_orientation_changed) );
  m_ComboOrientation.set_active(row);

  //The Style ComboBox:
  m_refTreeModelStyle = Gtk::ListStore::create(m_ColumnsStyle);
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = Gtk::TOOLBAR_TEXT;
  row[m_ColumnsStyle.m_col_name] = "Text";\
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = Gtk::TOOLBAR_BOTH;
  row[m_ColumnsStyle.m_col_name] = "Both";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = Gtk::TOOLBAR_BOTH_HORIZ;
  row[m_ColumnsStyle.m_col_name] = "Both: Horizontal";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = Gtk::TOOLBAR_ICONS;
  row[m_ColumnsStyle.m_col_name] = "Icons";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = -1; // A custom meaning for this demo.
  row[m_ColumnsStyle.m_col_name] = "Default";
  m_ComboStyle.set_model(m_refTreeModelStyle);
  m_VBox.pack_start(m_ComboStyle, Gtk::PACK_SHRINK);
  m_ComboStyle.pack_start(m_ColumnsStyle.m_col_name);
  m_ComboStyle.signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_combo_style_changed) );
  m_ComboStyle.set_active(row);

  //Add and fill the ToolPalette:
  load_stock_items();
  load_toggle_items();
  load_special_items();

  m_VBox.pack_start(m_HBox, Gtk::PACK_EXPAND_WIDGET);

  m_ScrolledWindowPalette.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindowPalette.set_border_width(6);
  m_ScrolledWindowPalette.add(m_ToolPalette);
  m_HBox.pack_start(m_ScrolledWindowPalette);

  on_combo_orientation_changed();

  m_ScrolledWindowCanvas.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
  m_ScrolledWindowCanvas.set_border_width(6);
  m_ScrolledWindowCanvas.add(m_Canvas);
  m_ScrolledWindowCanvas.set_size_request(200, -1);
  m_HBox.pack_start(m_ScrolledWindowCanvas);

  m_ToolPalette.add_drag_dest(m_Canvas,
    Gtk::DEST_DEFAULT_HIGHLIGHT, Gtk::TOOL_PALETTE_DRAG_ITEMS, Gdk::ACTION_COPY);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_combo_orientation_changed()
{
  Gtk::TreeModel::iterator iter = m_ComboOrientation.get_active();
  if(!iter)
    return;

  Gtk::TreeModel::Row row = *iter;
  const Gtk::Orientation value = row[m_ColumnsOrientation.m_col_value];
 
  m_ToolPalette.set_orientation(value);

  if(value == Gtk::ORIENTATION_HORIZONTAL)
    m_ScrolledWindowPalette.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_NEVER);
  else
    m_ScrolledWindowPalette.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
}

void ExampleWindow::on_combo_style_changed()
{
  Gtk::TreeModel::iterator iter = m_ComboStyle.get_active();
  if(!iter)
    return;

  Gtk::TreeModel::Row row = *iter;
  const int value = row[m_ColumnsStyle.m_col_value];
 
  if(value == -1)
    m_ToolPalette.unset_style();
  else
    m_ToolPalette.set_style((Gtk::ToolbarStyle)value);
}

