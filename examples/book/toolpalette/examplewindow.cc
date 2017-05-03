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


void ExampleWindow::load_icon_items()
{
  auto icon_theme = Gtk::IconTheme::get_for_screen(get_screen());

  typedef std::vector<Glib::ustring> type_stringvec;
  type_stringvec icon_names = icon_theme->list_icons();

  // Obtain the names of all contexts, and the icon names per context.
  type_stringvec contexts = icon_theme->list_contexts();
  std::sort(contexts.begin(), contexts.end());

  int requested_icon_size = 0;
  int requested_icon_height = 0; //ignored
  Gtk::IconSize::lookup(Gtk::BuiltinIconSize::BUTTON, requested_icon_size, requested_icon_height);
  const guint max_icons_per_group = 10;

  for (auto iter = contexts.begin(); iter != contexts.end(); ++iter)
  {
    const auto context_name = *iter;
    Gtk::ToolItemGroup* group =
      Gtk::manage(new Gtk::ToolItemGroup(context_name));
    m_ToolPalette.add(*group);

    // Iterate through the icon names, populating the ToolItemGroup as appropriate.
    type_stringvec icon_names_for_context = icon_theme->list_icons(context_name);
    std::sort(icon_names_for_context.begin(), icon_names_for_context.end());
    guint icons_count = 0;
    for (auto iconiter = icon_names_for_context.begin(); iconiter != icon_names_for_context.end(); ++iconiter)
    {
      const auto icon_name = *iconiter;
      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      try
      {
        pixbuf = icon_theme->load_icon(icon_name, requested_icon_size, Gtk::IconLookupFlags::GENERIC_FALLBACK);
      }
      catch (const Gtk::IconThemeError& /* ex */)
      {
        // Gtk::IconTheme::list_icons() may return some names of icons
        // that can't be loaded.
        continue;
      }

      // Skip large icons, just to make the ToolPalette look better.
      if (pixbuf->get_width() > 2*requested_icon_size ||
          pixbuf->get_height() > 2*requested_icon_size)
        continue;

      auto image = Gtk::manage(new Gtk::Image(pixbuf));
      auto button = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
      button->set_tooltip_text(icon_name);
      button->set_is_important();
      group->insert(*button);

      // Prevent us having an insane number of icons:
      ++icons_count;
      if(icons_count >= max_icons_per_group)
        break;
    }
  }
}


void ExampleWindow::load_toggle_items()
{
  auto group =
    Gtk::manage(new Gtk::ToolItemGroup("Radio Item"));
  m_ToolPalette.add(*group);

  Gtk::RadioToolButton::Group radio_group;

  for(int i = 1; i <= 10; ++i)
  {
    const auto label = Glib::ustring::compose("#%1", i);
    auto button = Gtk::manage(new Gtk::RadioToolButton());
    button->set_group(radio_group);
    button->set_label(label);

    group->insert(*button);
  }
}


static Gtk::ToolItem* create_entry_item(const Glib::ustring& text)
{
  auto entry = Gtk::manage(new Gtk::Entry());
  entry->set_text(text);
  entry->set_width_chars(5);

  auto item = Gtk::manage(new Gtk::ToolItem());
  item->add(*entry);

  return item;
}

void ExampleWindow::load_special_items()
{
  auto group = Gtk::manage(new Gtk::ToolItemGroup());

  Gtk::Button *label_button = Gtk::manage(new Gtk::Button("Advanced Features"));
  label_button->show();
  group->set_label_widget(*label_button);
  m_ToolPalette.add(*group);

  auto item = create_entry_item ("homogeneous=false");
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

  Gtk::ToolButton *button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("go-up");
  button->set_tooltip_text("Show on vertical palettes only");
  group->insert(*button);
  button->set_visible_horizontal(false);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("go-next");
  button->set_tooltip_text("Show on horizontal palettes only");
  group->insert(*button);
  button->set_visible_vertical(false);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("edit-delete");
  button->set_tooltip_text("Do not show at all");
  button->hide();
  group->insert(*button);
  button->set_visible_vertical(false);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("view-fullscreen");
  button->set_tooltip_text("Expanded this item");
  group->insert(*button);
  gtk_container_child_set (GTK_CONTAINER (group->gobj()), GTK_WIDGET (button->gobj()),
                           "homogeneous", FALSE,
                           "expand", TRUE,
                           NULL);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("help-contents");
  button->set_tooltip_text("A regular item");
  group->insert(*button);
}

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL, 6),
  m_HBox(Gtk::Orientation::HORIZONTAL, 6)
{
  set_title("Gtk::ToolPalette example");
  set_size_request(600, 600);

  m_VBox.set_margin(6);
  add(m_VBox);

  //The Orientation ComboBox:
  m_refTreeModelOrientation = Gtk::ListStore::create(m_ColumnsOrientation);
  auto iter = m_refTreeModelOrientation->append();
  auto row = *iter;
  row[m_ColumnsOrientation.m_col_value] = Gtk::Orientation::HORIZONTAL;
  row[m_ColumnsOrientation.m_col_name] = "Horizontal";\
  row = *(m_refTreeModelOrientation->append());
  row[m_ColumnsOrientation.m_col_value] = Gtk::Orientation::VERTICAL;
  row[m_ColumnsOrientation.m_col_name] = "Vertical";
  m_ComboOrientation.set_model(m_refTreeModelOrientation);
  m_VBox.pack_start(m_ComboOrientation, Gtk::PackOptions::SHRINK);
  m_ComboOrientation.pack_start(m_ColumnsOrientation.m_col_name);
  m_ComboOrientation.signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_combo_orientation_changed) );
  m_ComboOrientation.set_active(iter);

  //The Style ComboBox:
  m_refTreeModelStyle = Gtk::ListStore::create(m_ColumnsStyle);
  iter = m_refTreeModelStyle->append();
  row = *iter;
  row[m_ColumnsStyle.m_col_value] = static_cast<int>(Gtk::ToolbarStyle::TEXT);
  row[m_ColumnsStyle.m_col_name] = "Text";\
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = static_cast<int>(Gtk::ToolbarStyle::BOTH);
  row[m_ColumnsStyle.m_col_name] = "Both";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = static_cast<int>(Gtk::ToolbarStyle::BOTH_HORIZ);
  row[m_ColumnsStyle.m_col_name] = "Both: Horizontal";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = static_cast<int>(Gtk::ToolbarStyle::ICONS);
  row[m_ColumnsStyle.m_col_name] = "Icons";
  row = *(m_refTreeModelStyle->append());
  row[m_ColumnsStyle.m_col_value] = -1; // A custom meaning for this demo.
  row[m_ColumnsStyle.m_col_name] = "Default";
  m_ComboStyle.set_model(m_refTreeModelStyle);
  m_VBox.pack_start(m_ComboStyle, Gtk::PackOptions::SHRINK);
  m_ComboStyle.pack_start(m_ColumnsStyle.m_col_name);
  m_ComboStyle.signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_combo_style_changed) );
  m_ComboStyle.set_active(iter);

  //Add and fill the ToolPalette:
  load_icon_items();
  load_toggle_items();
  load_special_items();

  m_VBox.pack_start(m_HBox, Gtk::PackOptions::EXPAND_WIDGET);

  m_ScrolledWindowPalette.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindowPalette.set_margin(6);
  m_ScrolledWindowPalette.add(m_ToolPalette);
  m_HBox.pack_start(m_ScrolledWindowPalette, Gtk::PackOptions::EXPAND_WIDGET);

  on_combo_orientation_changed();

  m_ScrolledWindowCanvas.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  m_ScrolledWindowCanvas.set_margin(6);
  m_ScrolledWindowCanvas.add(m_Canvas);
  m_ScrolledWindowCanvas.set_size_request(200, -1);
  m_HBox.pack_start(m_ScrolledWindowCanvas, Gtk::PackOptions::EXPAND_WIDGET);

  m_ToolPalette.add_drag_dest(m_Canvas,
    Gtk::DestDefaults::HIGHLIGHT, Gtk::ToolPaletteDragTargets::ITEMS, Gdk::DragAction::COPY);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_combo_orientation_changed()
{
  const auto iter = m_ComboOrientation.get_active();
  if(!iter)
    return;

  const auto row = *iter;
  const Gtk::Orientation value = row[m_ColumnsOrientation.m_col_value];

  m_ToolPalette.set_orientation(value);

  if(value == Gtk::Orientation::HORIZONTAL)
    m_ScrolledWindowPalette.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::NEVER);
  else
    m_ScrolledWindowPalette.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
}

void ExampleWindow::on_combo_style_changed()
{
  const auto iter = m_ComboStyle.get_active();
  if(!iter)
    return;

  const auto row = *iter;
  const int value = row[m_ColumnsStyle.m_col_value];

  if(value == -1)
    m_ToolPalette.unset_style();
  else
    m_ToolPalette.set_style((Gtk::ToolbarStyle)value);
}

