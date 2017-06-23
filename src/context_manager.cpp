//
//  context_manager.cpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/13.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include "context_manager.hpp"

namespace hsu {

std::shared_ptr<GLFWwindow> context_manager::create_window() {
   static std::shared_ptr<GLFWwindow> window = []() {
        if (!glfwInit()) { throw std::runtime_error("glfwInit error."); }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
        auto window = std::shared_ptr<GLFWwindow>(
            glfwCreateWindow(512, 512, "base", nullptr, nullptr),
            [](GLFWwindow* window){ glfwDestroyWindow(window); });
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("glfwInit error.");
        }
        glfwMakeContextCurrent(window.get());
        glViewport(0, 0, 512, 512);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return window;
    }();
    return window;
}

} // end of namespace hsu
