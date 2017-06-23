//
//  canvas.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/05/02.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <stdexcept>

#include "canvas.hpp"
#include "context_manager.hpp"

namespace hsu {

canvas::canvas(int x, int y, int width, int height, uint8_t* data) :
    window_(), renderer_(), texture_(0) {
    window_ = context_manager::instance().create_window();

    glfwMakeContextCurrent(window_.get());
    renderer_ = std::make_shared<hsu::renderer>(width, height, window_);

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

canvas::~canvas() {}

std::shared_ptr<GLFWwindow> canvas::window() {
    return window_;
}

} // end of namespace hsu
