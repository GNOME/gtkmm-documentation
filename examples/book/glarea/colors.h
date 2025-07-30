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

#ifndef GTKMM_EXAMPLE_COLORS_H
#define GTKMM_EXAMPLE_COLORS_H

// --- Color Structures ---
struct Color {
    float r, g, b, a;

    Color(float _r, float _g, float _b, float _a = 1.0f) : r(_r), g(_g), b(_b), a(_a) {}
};

// Define colors for each face of the cube.
const Color COLOR_FRONT = {0.0f, 1.0f, 0.0f, 1.0f};          // Bright green
const Color COLOR_BACK = {1.0f, 1.0f, 0.0f, 1.0f};           // Yellow
const Color COLOR_TOP = {0.6f, 0.8f, 1.0f, 1.0f};            // Light blue
const Color COLOR_BOTTOM = {0.5f, 0.0f, 0.5f, 1.0f};         // Purple
const Color COLOR_RIGHT = {1.0f, 0.0f, 0.0f, 1.0f};          // Red
const Color COLOR_LEFT = {0.2f, 0.2f, 0.7f, 1.0f};           // Dark blue

#endif // GTKMM_EXAMPLE_COLORS_H
