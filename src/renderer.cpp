//
//  renderer.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//


#include "renderer.hpp"

#include <glm/ext.hpp>

#include "shader.hpp"
#include "canvas.hpp"
#include "opengl_system.hpp"

namespace hsu {

renderer::renderer(std::shared_ptr<hsu::buffer_manager> buffer_manager, std::shared_ptr<atlas_node const> image_node) :
    buffer_manager_(buffer_manager), image_node_(image_node), command_queue_(nullptr) {
    command_queue_ = std::make_shared<hsu::command_queue>(buffer_manager, image_node);
    command_queue_->create_buffer("draw_rect", 12 * 100);
    command_queue_->create_buffer("draw_image", 24 * 100);
    command_queue_->create_buffer("draw_window", 24 * 1);

    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        printf("GL Error: %d\n", err);
    }
}

renderer::~renderer() {}

void renderer::draw_rect(int x, int y, int width ,int height, std::array<float, 4> const& color) const {
    auto dst_affine = buffer_manager_->dst_affine();

    dst_affine = glm::translate(dst_affine, glm::vec3(image_node_->rect().x, image_node_->rect().y, 0));
    dst_affine *= state_affine;
    dst_affine = glm::translate(dst_affine, glm::vec3(x, y, 0));
    dst_affine = glm::scale(dst_affine, glm::vec3(width, height, 1));

    auto v0 = dst_affine * glm::vec4(0, 0, 1, 1);
    auto v1 = dst_affine * glm::vec4(1, 0, 1, 1);
    auto v2 = dst_affine * glm::vec4(1, 1, 1, 1);
    auto v3 = dst_affine * glm::vec4(0, 1, 1, 1);

    std::vector<GLfloat> vertices = {
        v0.x, v0.y, color[0], color[1], color[2], color[3],
        v1.x, v1.y, color[0], color[1], color[2], color[3],
        v2.x, v2.y, color[0], color[1], color[2], color[3],
        v0.x, v0.y, color[0], color[1], color[2], color[3],
        v2.x, v2.y, color[0], color[1], color[2], color[3],
        v3.x, v3.y, color[0], color[1], color[2], color[3],
    };
    command_queue_->insert_vertex("draw_rect", vertices);
}

void renderer::draw_image(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const {
    auto dst_affine = buffer_manager_->dst_affine();
    auto src_affine = buffer_manager_->src_affine();

    dst_affine = glm::translate(dst_affine, glm::vec3(image_node_->rect().x, image_node_->rect().y, 0));
    dst_affine *= state_affine;
    dst_affine = glm::translate(dst_affine, glm::vec3(dst_x, dst_y, 0));
    dst_affine = glm::scale(dst_affine, glm::vec3(dst_width, dst_height, 1));

    auto d0 = dst_affine * glm::vec4(0, 0, 0, 1);
    auto d1 = dst_affine * glm::vec4(1, 0, 0, 1);
    auto d2 = dst_affine * glm::vec4(1, 1, 0, 1);
    auto d3 = dst_affine * glm::vec4(0, 1, 0, 1);

    src_affine = glm::translate(src_affine, glm::vec3(canvas.image_node()->rect().x, canvas.image_node()->rect().y, 0));
    src_affine = glm::translate(src_affine, glm::vec3(src_x, src_y, 0));
    src_affine = glm::scale(src_affine, glm::vec3(src_width, src_height, 1));

    auto s0 = src_affine * glm::vec4(0, 0, 0, 1);
    auto s1 = src_affine * glm::vec4(1, 0, 0, 1);
    auto s2 = src_affine * glm::vec4(1, 1, 0, 1);
    auto s3 = src_affine * glm::vec4(0, 1, 0, 1);

    std::vector<float> vertices = {
        d0.x, d0.y, s0.x, s0.y,
        d1.x, d1.y, s1.x, s1.y,
        d2.x, d2.y, s2.x, s2.y,
        d0.x, d0.y, s0.x, s0.y,
        d2.x, d2.y, s2.x, s2.y,
        d3.x, d3.y, s3.x, s3.y,
    };

    command_queue_->insert_vertex("draw_image", vertices);
}

void renderer::draw_window(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const {
    auto dst_affine = buffer_manager_->dst_affine();
    auto src_affine = buffer_manager_->src_affine();
    dst_affine = glm::translate(dst_affine, glm::vec3(image_node_->rect().x, image_node_->rect().y, 0));
    dst_affine *= state_affine;
    dst_affine = glm::translate(dst_affine, glm::vec3(dst_x, dst_y, 0));
    dst_affine = glm::scale(dst_affine, glm::vec3(dst_width, dst_height, 1));

    auto d0 = dst_affine * glm::vec4(0, 0, 0, 1);
    auto d1 = dst_affine * glm::vec4(1, 0, 0, 1);
    auto d2 = dst_affine * glm::vec4(1, 1, 0, 1);
    auto d3 = dst_affine * glm::vec4(0, 1, 0, 1);

    src_affine = glm::translate(src_affine, glm::vec3(canvas.image_node()->rect().x, canvas.image_node()->rect().y, 0));
    src_affine = glm::translate(src_affine, glm::vec3(src_x, src_y, 0));
    src_affine = glm::scale(src_affine, glm::vec3(src_width, src_height, 1));

    auto s0 = src_affine * glm::vec4(0, 0, 0, 1);
    auto s1 = src_affine * glm::vec4(1, 0, 0, 1);
    auto s2 = src_affine * glm::vec4(1, 1, 0, 1);
    auto s3 = src_affine * glm::vec4(0, 1, 0, 1);

    std::vector<float> vertices = {
        d0.x, d0.y, s0.x, s3.y,
        d1.x, d1.y, s1.x, s2.y,
        d2.x, d2.y, s2.x, s1.y,
        d0.x, d0.y, s0.x, s3.y,
        d2.x, d2.y, s2.x, s1.y,
        d3.x, d3.y, s3.x, s0.y,
    };

    command_queue_->insert_vertex("draw_window", vertices);
}

void renderer::flush() const {
    command_queue_->flush();
}

} // end of namespace hsu
