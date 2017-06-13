//
//  shader.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <string>
#include <vector>

#include "shader.hpp"

namespace {

GLuint create_shader(GLenum type, std::string const& shader_source) {
    GLuint shader = glCreateShader(type);
    GLchar const* shader_source_c = shader_source.c_str();
    glShaderSource(shader, 1, &shader_source_c, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLsizei bufSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
        std::vector<GLchar> infoLog(bufSize);
        glGetShaderInfoLog(shader, sizeof(bufSize), NULL, infoLog.data());
        throw std::runtime_error(std::string(infoLog.begin(), infoLog.end()));
    }
    return shader;
}

GLuint create_program(std::string const& vertex_shader_source, std::string const& fragment_shader_source) {
    auto vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_source);
    auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLsizei bufSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
        std::vector<GLchar> infoLog(bufSize);
        glGetProgramInfoLog(program, bufSize, NULL, infoLog.data());
        throw std::runtime_error(std::string(infoLog.begin(), infoLog.end()));
    }
    return program;
}

} // end of namespace

namespace core {

shader::shader() {
    {
        std::string vertext_shader_source =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 aVertex;\n"
        "void main() {\n"
        "   gl_Position = vec4(aVertex, 0.0, 1.0);\n"
        "}";

        std::string fragment_shader_source =
        "#version 330 core\n"
        "\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);"
        "}";

        auto program = ::create_program(vertext_shader_source, fragment_shader_source);
        draw_rect.program_ = program;
        draw_rect.aVertex_ = glGetAttribLocation(program, "aVertex");
    }
}

} // end of namespace hsu
