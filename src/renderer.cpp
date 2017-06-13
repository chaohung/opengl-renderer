//
//  renderer.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//


#include "renderer.hpp"
#include "shader.hpp"

namespace hsu {

renderer::renderer(int canvas_width, int canvas_height, std::shared_ptr<GLFWwindow> window)
    : draw_rect_vao_(0), draw_rect_vbo_(0), affine_(), window_(window) {
    {
        glGenVertexArrays(1, &draw_rect_vao_);
        glGenBuffers(1, &draw_rect_vbo_);

        glBindVertexArray(draw_rect_vao_);
        glBindBuffer(GL_ARRAY_BUFFER, draw_rect_vbo_);
        auto& draw_rect = core::shader::instance().draw_rect;
        draw_rect.enable_vertex();
        glBindVertexArray(0);
    }

    affine_ = Eigen::Affine2f::Identity();
    affine_.translate(Eigen::Vector2f(-1.0, -1.0))
        .scale(Eigen::Vector2f(2.0 / canvas_width, 2.0 / canvas_height));
}

renderer::~renderer() {
    glDeleteVertexArrays(1, &draw_rect_vao_);
    glDeleteBuffers(1, &draw_rect_vbo_);
}

void renderer::draw_rect(int x, int y, int width ,int height) const {
    glfwMakeContextCurrent(window_.get());
    glBindVertexArray(draw_rect_vao_);
    Eigen::Vector2f v0 = affine_ * Eigen::Vector2f(x, y);
    Eigen::Vector2f v1 = affine_ * Eigen::Vector2f(x + width, y);
    Eigen::Vector2f v2 = affine_ * Eigen::Vector2f(x + width, y + height);
    Eigen::Vector2f v3 = affine_ * Eigen::Vector2f(x, y + height);

    GLfloat vertices[12] {
        v0.x(), v0.y(),
        v1.x(), v1.y(),
        v2.x(), v2.y(),
        v0.x(), v0.y(),
        v2.x(), v2.y(),
        v3.x(), v3.y(),
    };

    auto& draw_rect = core::shader::instance().draw_rect;
    draw_rect.use();
    draw_rect.set_vertex(vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

} // end of namespace hsu
