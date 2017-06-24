//
//  opengl_system.cpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/23.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <stdexcept>
#include <string>

#include "opengl_system.hpp"

namespace hsu {

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void opengl_system::setup_window(int width, int height, std::string const& title) {
    if (window_) return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
    window_ = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(width, height, "base", nullptr, nullptr),
        [](GLFWwindow* window){ glfwDestroyWindow(window); });
    glfwMakeContextCurrent(window_.get());
    glfwSetKeyCallback(window_.get(), key_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void opengl_system::setup_atlas(int width, int height) {
    buffer_manager_->create_atlas(width, height);
}

void opengl_system::run_window(std::function<void()> handler) const {
    while (!glfwWindowShouldClose(window_.get())) {
        glfwPollEvents();
        handler();
        glfwSwapBuffers(window_.get());
    }
}

opengl_system::opengl_system() : window_(nullptr), buffer_manager_(nullptr) {
    if (!glfwInit()) { throw std::runtime_error("glfwInit error."); }
    buffer_manager_ = std::make_shared<hsu::buffer_manager>();
}

opengl_system::~opengl_system() {
    glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

} // end of namespace hsu
