//
//  buffer_manager.cpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/24.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include "buffer_manager.hpp"

namespace hsu {

buffer_manager::buffer_manager() : atlas_tree_(nullptr),
    texture_atlas_(0), frame_bufer_(0),
    dst_affine_(), src_affine_() {}

buffer_manager::~buffer_manager() {
    glDeleteFramebuffers(1, &frame_bufer_);
    glDeleteTextures(1, &texture_atlas_);
}

void buffer_manager::create_atlas(int width, int height) {
    if (atlas_tree_) return;
    atlas_tree_ = hsu::atlas_node::create_atlas_root(width, height);
    texture_atlas_ = generate_texture_buffer(width, height, nullptr);
    frame_bufer_ = generate_frame_buffer(width, height, texture_atlas_);
    setup_affine(width, height);
    atlas_tree_->resize_handler = ([](int new_width, int new_height) {
        printf("atlas reisze to: %d %d\n", new_width, new_height);
    });
}

std::shared_ptr<hsu::atlas_node const> buffer_manager::allocate_canvas(int width, int height, void* data) const {
    auto image_node = atlas_tree_->insert(width, height);
    if (data) {
        bind_texture_buffer();
        glTexSubImage2D(GL_TEXTURE_2D, 0, image_node->rect().x, image_node->rect().y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        unbind_texture_buffer();
    }
    return image_node;
}

void buffer_manager::download_texture(int x, int y, int width, int height, void* data) const {
    bind_frame_buffer();
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    unbind_frame_buffer();
}

void buffer_manager::upload_texture(int x, int y, int width, int height, void* data) const {
    bind_texture_buffer();
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    unbind_texture_buffer();
}

GLuint buffer_manager::generate_texture_buffer(int width, int height, void* data) const {
    GLuint texture_buffer;
    glGenTextures(1, &texture_buffer);
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture_buffer;
}

GLuint buffer_manager::generate_frame_buffer(int width, int height, GLuint texture_buffer) const {
    GLuint frame_buffer;
    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_buffer, 0);
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return frame_buffer;
}

void buffer_manager::bind_texture_buffer() const {
    glBindTexture(GL_TEXTURE_2D, texture_atlas_);
}

void buffer_manager::unbind_texture_buffer() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void buffer_manager::bind_frame_buffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, frame_bufer_);
}

void buffer_manager::unbind_frame_buffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void buffer_manager::setup_affine(int width, int height) {
    dst_affine_ = Eigen::Affine2f::Identity();
    dst_affine_.translate(Eigen::Vector2f(-1.0, -1.0))
        .scale(Eigen::Vector2f(2.0 / width, 2.0 / height));
    src_affine_ = Eigen::Affine2f::Identity();
    src_affine_.scale(Eigen::Vector2f(1.0 / width, 1.0 / height));
}

} // end of namespace hsu
