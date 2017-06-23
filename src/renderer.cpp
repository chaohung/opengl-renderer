//
//  renderer.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//


#include "renderer.hpp"
#include "shader.hpp"
#include "canvas.hpp"

namespace hsu {

renderer::renderer(int canvas_width, int canvas_height, std::shared_ptr<GLFWwindow> window)
    : draw_rect_vao_(0), draw_rect_vbo_(0), draw_image_vao_(0), draw_image_vbo_(0), dst_affine_(), src_affine_(), window_(window) {
    glGenVertexArrays(1, &draw_rect_vao_);
    glGenBuffers(1, &draw_rect_vbo_);
    glBindVertexArray(draw_rect_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, draw_rect_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, nullptr, GL_DYNAMIC_DRAW);
    glBindVertexArray(0);

    glGenVertexArrays(1, &draw_image_vao_);
    glGenBuffers(1, &draw_image_vbo_);
    glBindVertexArray(draw_image_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, draw_image_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, nullptr, GL_DYNAMIC_DRAW);
    glBindVertexArray(0);

    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("GL Error.");
    }

    dst_affine_ = Eigen::Affine2f::Identity();
    dst_affine_.translate(Eigen::Vector2f(-1.0, -1.0))
        .scale(Eigen::Vector2f(2.0 / canvas_width, 2.0 / canvas_height));

    src_affine_ = Eigen::Affine2f::Identity();
    src_affine_.scale(Eigen::Vector2f(1.0 / canvas_width, 1.0 / canvas_height));
}

renderer::~renderer() {
    glDeleteVertexArrays(1, &draw_rect_vao_);
    glDeleteBuffers(1, &draw_rect_vbo_);
    glDeleteVertexArrays(1, &draw_image_vao_);
    glDeleteBuffers(1, &draw_image_vbo_);
}

void renderer::draw_rect(int x, int y, int width ,int height) const {
    glfwMakeContextCurrent(window_.get());
    glBindVertexArray(draw_rect_vao_);

    Eigen::Vector2f v0 = dst_affine_ * Eigen::Vector2f(x, y);
    Eigen::Vector2f v1 = dst_affine_ * Eigen::Vector2f(x + width, y);
    Eigen::Vector2f v2 = dst_affine_ * Eigen::Vector2f(x + width, y + height);
    Eigen::Vector2f v3 = dst_affine_ * Eigen::Vector2f(x, y + height);

    GLfloat vertices[12] {
        v0.x(), v0.y(),
        v1.x(), v1.y(),
        v2.x(), v2.y(),
        v0.x(), v0.y(),
        v2.x(), v2.y(),
        v3.x(), v3.y(),
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 12, vertices);

    auto& draw_rect = shader::instance().draw_rect;
    draw_rect.enable_aVertex();
    draw_rect.use();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    draw_rect.unuse();
    glBindVertexArray(0);
}

void renderer::draw_image(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, GLuint texture_id) const {
    glfwMakeContextCurrent(window_.get());
    glBindVertexArray(draw_rect_vao_);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    Eigen::Vector2f d0 = dst_affine_ * Eigen::Vector2f(dst_x, dst_y);
    Eigen::Vector2f d1 = dst_affine_ * Eigen::Vector2f(dst_x + dst_width, dst_y);
    Eigen::Vector2f d2 = dst_affine_ * Eigen::Vector2f(dst_x + dst_width, dst_y + dst_height);
    Eigen::Vector2f d3 = dst_affine_ * Eigen::Vector2f(dst_x, dst_y + dst_height);

    Eigen::Vector2f s0 = src_affine_ * Eigen::Vector2f(src_x, src_y);
    Eigen::Vector2f s1 = src_affine_ * Eigen::Vector2f(src_x + src_width, src_y);
    Eigen::Vector2f s2 = src_affine_ * Eigen::Vector2f(src_x + src_width, src_y + src_height);
    Eigen::Vector2f s3 = src_affine_ * Eigen::Vector2f(src_x, src_y + src_height);

    GLfloat vertices[24] {
        d0.x(), d0.y(), s0.x(), s0.y(),
        d1.x(), d1.y(), s1.x(), s1.y(),
        d2.x(), d2.y(), s2.x(), s2.y(),
        d0.x(), d0.y(), s0.x(), s0.y(),
        d2.x(), d2.y(), s2.x(), s2.y(),
        d3.x(), d3.y(), s3.x(), s3.y(),
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 24, vertices);

    auto& draw_image = shader::instance().draw_image;
    draw_image.enable_aVertex();
    draw_image.enable_aTexCoord();
    draw_image.enable_vSample();
    draw_image.use();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    draw_image.unuse();
    glBindVertexArray(0);
}

} // end of namespace hsu
