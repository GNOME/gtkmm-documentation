/* gtkmm example Copyright (C) 2017 gtkmm development team
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

#include "myextrainit.h"
#include <gtkmm/widget.h>
#include <gtk/gtk.h>

namespace
{
using BaseObjectType = GtkWidget;
using BaseClassType = GtkWidgetClass;

// Extra class init function.
void class_init_function(void* g_class, void* class_data)
{
  g_return_if_fail(GTK_IS_WIDGET_CLASS(g_class));

  const auto klass = static_cast<BaseClassType*>(g_class);
  const auto css_name = static_cast<Glib::ustring*>(class_data);

  gtk_widget_class_set_css_name(klass, css_name->c_str());
}

// Extra instance init function.
void instance_init_function(GTypeInstance* instance, void* /* g_class */)
{
  g_return_if_fail(GTK_IS_WIDGET(instance));

  // Nothing to do here.
  // This extra instance init function just shows how such a function can
  // be added to a custom widget, if necessary.
}

} // anonymous namespace

MyExtraInit::MyExtraInit(const Glib::ustring& css_name)
:
Glib::ExtraClassInit(class_init_function, &m_css_name, instance_init_function),
m_css_name(css_name)
{
}
