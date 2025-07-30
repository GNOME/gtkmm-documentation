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

#ifndef GTKMM_EXAMPLEGLAREA_H
#define GTKMM_EXAMPLEGLAREA_H

#include <gtkmm.h>
#include <glm/glm.hpp> // For glm::vec2, glm::vec3, glm::mat4
#include <epoxy/gl.h>  // Include Epoxy for OpenGL function loading
#include "colors.h"    // Include for Color struct and constants

// Class for our OpenGL Canvas, inherits from Gtk::GLArea.
class ExampleGLArea : public Gtk::GLArea
{
public:
    ExampleGLArea();

protected:
    // Signal handlers:
    void on_realize() override;
    void on_unrealize() override;
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;

    // Mouse handling methods:
    void on_mouse_press(int button, double x, double y);
    void on_mouse_release(int n_press, double x, double y);
    void on_mouse_motion(double x, double y);
    bool on_scroll(double double_y);

private:
    // OpenGL resource IDs
    GLuint m_vao = 0;
    GLuint m_position_buffer = 0;
    GLuint m_index_buffer = 0;
    GLuint m_edge_index_buffer = 0;
    GLuint m_program = 0;
    GLint m_mvp_location = -1;
    GLint m_use_vertex_color_location = -1;
    GLint m_line_color_uniform_location = -1;

    // Camera and interaction state
    float m_rotation_angles[3];
    glm::vec2 m_last_mouse_pos;
    bool m_is_rotating = false;
    bool m_is_panning = false;
    glm::vec3 m_camera_position;
    glm::vec3 m_camera_target;
    float m_rotation_speed = 0.5f;
    float m_pan_speed = 0.005f;
    float m_zoom_speed = 0.4f;

    // Cube data (constants) - MUST be static const when defined outside the class
    static const GLfloat m_default_cube_vertex_data[24 * 8];
    static const GLuint m_default_cube_index_data[36];
    static const GLuint m_edge_index_data[12 * 2];

    // Private helper methods for OpenGL setup and drawing
    void init_buffers();
    GLuint create_shader(GLenum type, const char* src);
    void init_shaders();
    glm::mat4 compute_mvp();
    void draw_object();
};

#endif // GTKMM_EXAMPLEGLAREA_H
