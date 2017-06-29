//
//  canvas.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/05/02.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <stdexcept>

#include "canvas.hpp"
#include "opengl_system.hpp"

namespace hsu {

canvas::canvas(int x, int y, int width, int height, uint8_t* data) :
    buffer_manager_(nullptr), image_node_(nullptr), renderer_() {
    buffer_manager_ = hsu::opengl_system::instance().buffer_manager();
    image_node_ = buffer_manager_->allocate_canvas(width, height, data);
    renderer_ = std::make_shared<hsu::renderer>(buffer_manager_, image_node_);
}

void canvas::read(int x, int y, int width, int height, void* data) const {
    buffer_manager_->download_texture(x + image_node_->rect().x, y + image_node_->rect().y, width, height, data);
}

void canvas::write(int x, int y, int width, int height, void* data) const {
    buffer_manager_->upload_texture(x + image_node_->rect().x, y + image_node_->rect().y, width, height, data);
}

canvas::~canvas() {}

} // end of namespace hsu
