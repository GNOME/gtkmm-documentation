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

#include "exampleglarea.h"
#include "shaders.h" // Include for shader source strings

// epoxy/gl.h is already included in exampleglarea.h, no need to include again here unless specifically needed later.
// #include <epoxy/gl.h>
#include <iostream>    // For standard input/output operations
#include <cmath>       // For mathematical functions
#include <glm/gtc/matrix_transform.hpp> // For GLM matrix transformations
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr
#include <vector>      // For std::vector

// Initialize the static constant arrays with the actual data
// No change needed here, as they are now correctly declared as static const in the header.
const GLfloat ExampleGLArea::m_default_cube_vertex_data[24 * 8] = {
    // Front face (Front: Z=0.5) - Bright Green
    -0.5f, -0.5f,  0.5f, 1.0f,   COLOR_FRONT.r, COLOR_FRONT.g, COLOR_FRONT.b, COLOR_FRONT.a,
     0.5f, -0.5f,  0.5f, 1.0f,   COLOR_FRONT.r, COLOR_FRONT.g, COLOR_FRONT.b, COLOR_FRONT.a,
     0.5f,  0.5f,  0.5f, 1.0f,   COLOR_FRONT.r, COLOR_FRONT.g, COLOR_FRONT.b, COLOR_FRONT.a,
    -0.5f,  0.5f,  0.5f, 1.0f,   COLOR_FRONT.r, COLOR_FRONT.g, COLOR_FRONT.b, COLOR_FRONT.a,

    // Back face (Back: Z=-0.5) - Yellow
    -0.5f, -0.5f, -0.5f, 1.0f,   COLOR_BACK.r, COLOR_BACK.g, COLOR_BACK.b, COLOR_BACK.a,
     0.5f, -0.5f, -0.5f, 1.0f,   COLOR_BACK.r, COLOR_BACK.g, COLOR_BACK.b, COLOR_BACK.a,
     0.5f,  0.5f, -0.5f, 1.0f,   COLOR_BACK.r, COLOR_BACK.g, COLOR_BACK.b, COLOR_BACK.a,
    -0.5f,  0.5f, -0.5f, 1.0f,   COLOR_BACK.r, COLOR_BACK.g, COLOR_BACK.b, COLOR_BACK.a,

    // Top face (Top: Y=0.5) - Light Blue
    -0.5f,  0.5f,  0.5f, 1.0f,   COLOR_TOP.r, COLOR_TOP.g, COLOR_TOP.b, COLOR_TOP.a,
     0.5f,  0.5f,  0.5f, 1.0f,   COLOR_TOP.r, COLOR_TOP.g, COLOR_TOP.b, COLOR_TOP.a,
     0.5f,  0.5f, -0.5f, 1.0f,   COLOR_TOP.r, COLOR_TOP.g, COLOR_TOP.b, COLOR_TOP.a,
    -0.5f,  0.5f, -0.5f, 1.0f,   COLOR_TOP.r, COLOR_TOP.g, COLOR_TOP.b, COLOR_TOP.a,

    // Bottom face (Bottom: Y=-0.5) - Purple
    -0.5f, -0.5f, -0.5f, 1.0f,   COLOR_BOTTOM.r, COLOR_BOTTOM.g, COLOR_BOTTOM.b, COLOR_BOTTOM.a,
     0.5f, -0.5f, -0.5f, 1.0f,   COLOR_BOTTOM.r, COLOR_BOTTOM.g, COLOR_BOTTOM.b, COLOR_BOTTOM.a,
     0.5f, -0.5f,  0.5f, 1.0f,   COLOR_BOTTOM.r, COLOR_BOTTOM.g, COLOR_BOTTOM.b, COLOR_BOTTOM.a,
    -0.5f, -0.5f,  0.5f, 1.0f,   COLOR_BOTTOM.r, COLOR_BOTTOM.g, COLOR_BOTTOM.b, COLOR_BOTTOM.a,

    // Right face (Right: X=0.5) - Red
     0.5f, -0.5f,  0.5f, 1.0f,   COLOR_RIGHT.r, COLOR_RIGHT.g, COLOR_RIGHT.b, COLOR_RIGHT.a,
     0.5f, -0.5f, -0.5f, 1.0f,   COLOR_RIGHT.r, COLOR_RIGHT.g, COLOR_RIGHT.b, COLOR_RIGHT.a,
     0.5f,  0.5f, -0.5f, 1.0f,   COLOR_RIGHT.r, COLOR_RIGHT.g, COLOR_RIGHT.b, COLOR_RIGHT.a,
     0.5f,  0.5f,  0.5f, 1.0f,   COLOR_RIGHT.r, COLOR_RIGHT.g, COLOR_RIGHT.b, COLOR_RIGHT.a,

    // Left face (Left: X=-0.5) - Dark Blue
    -0.5f, -0.5f, -0.5f, 1.0f,   COLOR_LEFT.r, COLOR_LEFT.g, COLOR_LEFT.b, COLOR_LEFT.a,
    -0.5f, -0.5f,  0.5f, 1.0f,   COLOR_LEFT.r, COLOR_LEFT.g, COLOR_LEFT.b, COLOR_LEFT.a,
    -0.5f,  0.5f,  0.5f, 1.0f,   COLOR_LEFT.r, COLOR_LEFT.g, COLOR_LEFT.b, COLOR_LEFT.a,
    -0.5f,  0.5f, -0.5f, 1.0f,   COLOR_LEFT.r, COLOR_LEFT.g, COLOR_LEFT.b, COLOR_LEFT.a
};

const GLuint ExampleGLArea::m_default_cube_index_data[36] = {
    0, 3, 2,
    0, 2, 1,

    4, 5, 6,
    4, 6, 7,

    8, 11, 10,
    8, 10, 9,

    12, 15, 14,
    12, 14, 13,

    16, 19, 18,
    16, 18, 17,

    20, 23, 22,
    20, 22, 21
};

const GLuint ExampleGLArea::m_edge_index_data[12 * 2] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0,

    4, 5,
    5, 6,
    6, 7,
    7, 4,

    0, 4,
    1, 5,
    2, 6,
    3, 7
};

// Constructor implementation
ExampleGLArea::ExampleGLArea()
{
    set_allowed_apis(Gdk::GLApi::GL);

    m_camera_position = glm::vec3(0.0f, 0.0f, 2.0f);
    m_camera_target = glm::vec3(0.0f, 0.0f, 0.0f);

    m_rotation_angles[0] = 327.479f;
    m_rotation_angles[1] = 142.582f;
    m_rotation_angles[2] = 0.0f;

    auto motion_controller = Gtk::EventControllerMotion::create();
    motion_controller->signal_motion().connect(sigc::mem_fun(*this, &ExampleGLArea::on_mouse_motion));
    add_controller(motion_controller);

    auto click_controller_middle = Gtk::GestureClick::create();
    click_controller_middle->set_button(GDK_BUTTON_MIDDLE);
    click_controller_middle->signal_pressed().connect(
        [this](int /*n_press*/, double x, double y) { this->on_mouse_press(GDK_BUTTON_MIDDLE, x, y); }
    );
    click_controller_middle->signal_released().connect(sigc::mem_fun(*this, &ExampleGLArea::on_mouse_release));
    add_controller(click_controller_middle);

    auto click_controller_right = Gtk::GestureClick::create();
    click_controller_right->set_button(GDK_BUTTON_SECONDARY);
    click_controller_right->signal_pressed().connect(
        [this](int /*n_press*/, double x, double y) { this->on_mouse_press(GDK_BUTTON_SECONDARY, x, y); }
    );
    click_controller_right->signal_released().connect(sigc::mem_fun(*this, &ExampleGLArea::on_mouse_release));
    add_controller(click_controller_right);

    auto scroll_controller = Gtk::EventControllerScroll::create();
    scroll_controller->set_flags(Gtk::EventControllerScroll::Flags::VERTICAL);
    scroll_controller->signal_scroll().connect(
        [this](double /*dx*/, double dy) { return this->on_scroll(dy); }, false
    );
    add_controller(scroll_controller);

    set_focusable(true);
    set_focus_on_click(true);
}

void ExampleGLArea::on_realize()
{
    Gtk::GLArea::on_realize();

    try {
        make_current();
        throw_if_error();

        init_buffers();
        init_shaders();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on realize: " << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
    }
}

void ExampleGLArea::on_unrealize()
{
    try {
        make_current();
        throw_if_error();

        glBindVertexArray(m_vao);
        glDeleteBuffers(1, &m_position_buffer);
        glDeleteBuffers(1, &m_index_buffer);
        glDeleteBuffers(1, &m_edge_index_buffer);
        glDeleteProgram(m_program);
        glDeleteVertexArrays(1, &m_vao);

    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on unrealize: " << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
    }

    Gtk::GLArea::on_unrealize();
}

bool ExampleGLArea::on_render(const Glib::RefPtr<Gdk::GLContext>& /*context*/)
{
    try {
        make_current();
        throw_if_error();

        glViewport(0, 0, get_width(), get_height());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_object();

        glFlush();

        return true;
    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on render: " << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
        return false;
    }
}

void ExampleGLArea::on_mouse_press(int button, double x, double y)
{
    m_last_mouse_pos = glm::vec2(x, y);
    m_is_rotating = false;
    m_is_panning = false;

    if (button == GDK_BUTTON_MIDDLE) {
        m_is_rotating = true;
    } else if (button == GDK_BUTTON_SECONDARY) {
        m_is_panning = true;
    }
    grab_focus();
}

void ExampleGLArea::on_mouse_release(int /*n_press*/, double /*x*/, double /*y*/)
{
    m_is_rotating = false;
    m_is_panning = false;
}

void ExampleGLArea::on_mouse_motion(double x, double y)
{
    if (m_is_rotating) {
        float delta_x = static_cast<float>(x - m_last_mouse_pos.x);
        float delta_y = static_cast<float>(y - m_last_mouse_pos.y);

        m_rotation_angles[1] += -delta_x * m_rotation_speed;
        m_rotation_angles[0] += -delta_y * m_rotation_speed;

        m_rotation_angles[0] = fmod(m_rotation_angles[0], 360.0f);
        m_rotation_angles[1] = fmod(m_rotation_angles[1], 360.0f);

        queue_draw();
    } else if (m_is_panning) {
        float delta_x = static_cast<float>(x - m_last_mouse_pos.x);
        float delta_y = static_cast<float>(y - m_last_mouse_pos.y);

        float current_zoom_scale = m_camera_position.z / 2.0f;

        glm::vec3 camera_direction = glm::normalize(m_camera_target - m_camera_position);
        glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 camera_right = glm::normalize(glm::cross(camera_direction, world_up));
        glm::vec3 camera_up = glm::normalize(glm::cross(camera_right, camera_direction));

        m_camera_position -= camera_right * delta_x * m_pan_speed * current_zoom_scale;
        m_camera_target -= camera_right * delta_x * m_pan_speed * current_zoom_scale;

        m_camera_position += camera_up * delta_y * m_pan_speed * current_zoom_scale;
        m_camera_target += camera_up * delta_y * m_pan_speed * current_zoom_scale;

        queue_draw();
    }
    m_last_mouse_pos = glm::vec2(x, y);
}

bool ExampleGLArea::on_scroll(double double_y)
{
    m_camera_position.z += static_cast<float>(double_y) * m_zoom_speed;
    m_camera_position.z = glm::clamp(m_camera_position.z, 0.5f, 50.0f);

    queue_draw();
    return true;
}

void ExampleGLArea::init_buffers()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    if (m_position_buffer != 0) glDeleteBuffers(1, &m_position_buffer);
    if (m_index_buffer != 0) glDeleteBuffers(1, &m_index_buffer);
    if (m_edge_index_buffer != 0) glDeleteBuffers(1, &m_edge_index_buffer);

    glGenBuffers(1, &m_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_default_cube_vertex_data), m_default_cube_vertex_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 4));

    glGenBuffers(1, &m_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_default_cube_index_data), m_default_cube_index_data, GL_STATIC_DRAW);

    glGenBuffers(1, &m_edge_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_edge_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_edge_index_data), m_edge_index_data, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint ExampleGLArea::create_shader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        std::vector<char> buffer(log_len + 1);
        glGetShaderInfoLog(shader, log_len, nullptr, buffer.data());
        std::cerr << "Shader compile failure (" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "):\n" << buffer.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void ExampleGLArea::init_shaders()
{
    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, VERTEX_SHADER_SRC);
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC);

    if (vertex_shader == 0 || fragment_shader == 0) {
        m_program = 0;
        return;
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);

    glBindAttribLocation(m_program, 0, "in_position");
    glBindAttribLocation(m_program, 1, "in_color");

    glLinkProgram(m_program);

    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &log_len);
        std::vector<char> buffer(log_len + 1);
        glGetProgramInfoLog(m_program, log_len, nullptr, buffer.data());
        std::cerr << "Program linking failure:\n" << buffer.data() << std::endl;
        glDeleteProgram(m_program);
        m_program = 0;
    } else {
        m_mvp_location = glGetUniformLocation(m_program, "mvp");
        m_use_vertex_color_location = glGetUniformLocation(m_program, "use_vertex_color");
        m_line_color_uniform_location = glGetUniformLocation(m_program, "line_color_uniform");
    }

    glDetachShader(m_program, vertex_shader);
    glDeleteShader(vertex_shader);
    glDetachShader(m_program, fragment_shader);
    glDeleteShader(fragment_shader);
}

glm::mat4 ExampleGLArea::compute_mvp()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_rotation_angles[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation_angles[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation_angles[2]), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view = glm::lookAt(
        m_camera_position,
        m_camera_target,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    float view_height = 1.0f * m_camera_position.z;
    float aspect_ratio = (float)get_width() / (float)get_height();
    float view_width = view_height * aspect_ratio;

    glm::mat4 projection = glm::ortho(-view_width / 2.0f, view_width / 2.0f,
                                      -view_height / 2.0f, view_height / 2.0f,
                                      0.1f, 100.0f);

    return projection * view * model;
}

void ExampleGLArea::draw_object()
{
    if (m_program == 0) return;

    glm::mat4 mvp = compute_mvp();

    glUseProgram(m_program);
    glUniformMatrix4fv(m_mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(m_vao);

    glUniform1i(m_use_vertex_color_location, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthMask(GL_TRUE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glDrawElements(GL_TRIANGLES, sizeof(m_default_cube_index_data) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glLineWidth(3.0f);
    glUniform1i(m_use_vertex_color_location, 0);
    glUniform4f(m_line_color_uniform_location, 1.0f, 1.0f, 1.0f, 1.0f);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_edge_index_buffer);
    glDrawElements(GL_LINES, sizeof(m_edge_index_data) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(0);
    glUseProgram(0);
}
