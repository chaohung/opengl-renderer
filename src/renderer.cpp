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
#include "opengl_system.hpp"

namespace hsu {

renderer::renderer(std::shared_ptr<hsu::buffer_manager> buffer_manager, std::shared_ptr<atlas_node const> image_node) :
    buffer_manager_(buffer_manager), image_node_(image_node), command_queue_(nullptr) {
    command_queue_ = std::make_shared<hsu::command_queue>(buffer_manager, image_node);
    command_queue_->create_buffer("draw_rect", 12 * 100);
    command_queue_->create_buffer("draw_image", 24 * 100);
    command_queue_->create_buffer("draw_window", 24 * 1);

    state_affine = Eigen::Affine2f::Identity();

    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        printf("GL Error: %d\n", err);
    }
}

renderer::~renderer() {}

void renderer::draw_rect(int x, int y, int width ,int height, std::array<float, 4> const& color) const {
    Eigen::Affine2f dst_affine = buffer_manager_->dst_affine();

    dst_affine.translate(Eigen::Vector2f(image_node_->rect().x, image_node_->rect().y));
    dst_affine *= state_affine.matrix();
    dst_affine.translate(Eigen::Vector2f(x, y)).scale(Eigen::Vector2f(width, height));

    Eigen::Vector2f v0 = dst_affine * Eigen::Vector2f(0, 0);
    Eigen::Vector2f v1 = dst_affine * Eigen::Vector2f(1, 0);
    Eigen::Vector2f v2 = dst_affine * Eigen::Vector2f(1, 1);
    Eigen::Vector2f v3 = dst_affine * Eigen::Vector2f(0, 1);

    std::vector<GLfloat> vertices = {
        v0.x(), v0.y(), color[0], color[1], color[2], color[3],
        v1.x(), v1.y(), color[0], color[1], color[2], color[3],
        v2.x(), v2.y(), color[0], color[1], color[2], color[3],
        v0.x(), v0.y(), color[0], color[1], color[2], color[3],
        v2.x(), v2.y(), color[0], color[1], color[2], color[3],
        v3.x(), v3.y(), color[0], color[1], color[2], color[3],
    };
    command_queue_->insert_vertex("draw_rect", vertices);
}

void renderer::draw_image(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const {
    Eigen::Affine2f dst_affine = buffer_manager_->dst_affine();
    Eigen::Affine2f src_affine = buffer_manager_->src_affine();

    dst_affine.translate(Eigen::Vector2f(image_node_->rect().x, image_node_->rect().y));
    dst_affine *= state_affine.matrix();
    dst_affine.translate(Eigen::Vector2f(dst_x, dst_y)).scale(Eigen::Vector2f(dst_width, dst_height));

    Eigen::Vector2f d0 = dst_affine * Eigen::Vector2f(0, 0);
    Eigen::Vector2f d1 = dst_affine * Eigen::Vector2f(1, 0);
    Eigen::Vector2f d2 = dst_affine * Eigen::Vector2f(1, 1);
    Eigen::Vector2f d3 = dst_affine * Eigen::Vector2f(0, 1);

    src_affine.translate(Eigen::Vector2f(canvas.image_node()->rect().x, canvas.image_node()->rect().y))
        .translate(Eigen::Vector2f(src_x, src_y)).scale(Eigen::Vector2f(src_width, src_height));

    Eigen::Vector2f s0 = src_affine * Eigen::Vector2f(0, 0);
    Eigen::Vector2f s1 = src_affine * Eigen::Vector2f(1, 0);
    Eigen::Vector2f s2 = src_affine * Eigen::Vector2f(1, 1);
    Eigen::Vector2f s3 = src_affine * Eigen::Vector2f(0, 1);

    std::vector<float> vertices = {
        d0.x(), d0.y(), s0.x(), s0.y(),
        d1.x(), d1.y(), s1.x(), s1.y(),
        d2.x(), d2.y(), s2.x(), s2.y(),
        d0.x(), d0.y(), s0.x(), s0.y(),
        d2.x(), d2.y(), s2.x(), s2.y(),
        d3.x(), d3.y(), s3.x(), s3.y(),
    };

    command_queue_->insert_vertex("draw_image", vertices);
}

void renderer::draw_window(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const {
    Eigen::Affine2f dst_affine = buffer_manager_->dst_affine();
    Eigen::Affine2f src_affine = buffer_manager_->src_affine();

    dst_affine.translate(Eigen::Vector2f(image_node_->rect().x, image_node_->rect().y));
    dst_affine.translate(Eigen::Vector2f(dst_x, dst_y)).scale(Eigen::Vector2f(dst_width, dst_height));
    Eigen::Vector2f d0 = dst_affine * Eigen::Vector2f(0, 0);
    Eigen::Vector2f d1 = dst_affine * Eigen::Vector2f(1, 0);
    Eigen::Vector2f d2 = dst_affine * Eigen::Vector2f(1, 1);
    Eigen::Vector2f d3 = dst_affine * Eigen::Vector2f(0, 1);

    src_affine.translate(Eigen::Vector2f(canvas.image_node()->rect().x, canvas.image_node()->rect().y))
        .translate(Eigen::Vector2f(src_x, src_y)).scale(Eigen::Vector2f(src_width, src_height));
    Eigen::Vector2f s0 = src_affine * Eigen::Vector2f(0, 0);
    Eigen::Vector2f s1 = src_affine * Eigen::Vector2f(1, 0);
    Eigen::Vector2f s2 = src_affine * Eigen::Vector2f(1, 1);
    Eigen::Vector2f s3 = src_affine * Eigen::Vector2f(0, 1);

    std::vector<GLfloat> vertices = {
        d0.x(), d0.y(), s0.x(), s3.y(),
        d1.x(), d1.y(), s1.x(), s2.y(),
        d2.x(), d2.y(), s2.x(), s1.y(),
        d0.x(), d0.y(), s0.x(), s3.y(),
        d2.x(), d2.y(), s2.x(), s1.y(),
        d3.x(), d3.y(), s3.x(), s0.y(),
    };
    command_queue_->insert_vertex("draw_window", vertices);
}

void renderer::flush() const {
    command_queue_->flush();
}

} // end of namespace hsu
