/* gtkmm example Copyright (C) 2025 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_EXAMPLE_SHADERS_H
#define GTKMM_EXAMPLE_SHADERS_H

// GLSL shaders as string literals
const char* VERTEX_SHADER_SRC = R"(
#version 130
in vec4 in_position;
in vec4 in_color;
out vec4 v_color;
uniform mat4 mvp;

void main() {
    gl_Position = mvp * in_position;
    v_color = in_color;
}
)";

const char* FRAGMENT_SHADER_SRC = R"(
#version 130
in vec4 v_color;
out vec4 frag_color;
uniform bool use_vertex_color;
uniform vec4 line_color_uniform;

void main() {
    if (use_vertex_color) {
        frag_color = v_color;
    } else {
        frag_color = line_color_uniform;
    }
}
)";

#endif // GTKMM_EXAMPLE_SHADERS_H
