//
//  canvas.cpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/05/02.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include "canvas.hpp"
#include <stdexcept>

namespace hsu {

canvas::canvas(std::string const& title, int x, int y, int width, int height) {
    static std::shared_ptr<GLFWwindow> base_window = []() {
        if (!glfwInit()) { throw std::runtime_error("glfwInit error."); }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
        auto window = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(100, 100, "base", nullptr, nullptr),
        [](GLFWwindow* window){ glfwDestroyWindow(window); });
        return window;
    }();

    window_ = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(width, height, title.c_str(), nullptr, base_window.get()),
        [](GLFWwindow* window){ glfwDestroyWindow(window); });

    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("glfwInit error.");;
    }
    glfwMakeContextCurrent(window_.get());
    renderer_ = std::make_shared<hsu::renderer>(width, height, window_);
}

canvas::~canvas() {}

std::shared_ptr<GLFWwindow> canvas::window() {
    return window_;
}

} // end of namespace hsu
