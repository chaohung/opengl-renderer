//
//  command_queue.cpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/29.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <algorithm>

#include "command_queue.hpp"
#include "shader.hpp"

namespace hsu {

command_queue::command_queue(std::shared_ptr<hsu::buffer_manager> buffer_manager, std::shared_ptr<hsu::atlas_node const> image_node) :
    buffer_manager_(buffer_manager), image_node_(image_node), vao_map_(), vbo_map_(), vertex_queue_map_() {}

command_queue::~command_queue() {
    std::for_each(vao_map_.begin(), vao_map_.end(), [](std::pair<std::string,GLuint> element) {
        glDeleteVertexArrays(1, &(element.second));
    });
    std::for_each(vbo_map_.begin(), vbo_map_.end(), [](std::pair<std::string,GLuint> element) {
        glDeleteVertexArrays(1, &(element.second));
    });
}

void command_queue::create_buffer(std::string const& buffer_id, int vertex_num) {
    GLuint vao;
    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_num, nullptr, GL_DYNAMIC_DRAW);
    glBindVertexArray(0);
    vao_map_[buffer_id] = vao;
    vbo_map_[buffer_id] = vbo;

    vertex_queue_map_[buffer_id] = std::vector<GLfloat>();
    vertex_queue_map_[buffer_id].reserve(vertex_num);
}

void command_queue::insert_vertex(std::string const& buffer_id, std::vector<GLfloat> vertexs) {
    auto& vertex_queue = vertex_queue_map_[buffer_id];
    auto reserve_space = vertex_queue.capacity() - vertex_queue.size();
    if (reserve_space < vertexs.size()) flush(buffer_id);
    vertex_queue.insert(vertex_queue.end(), vertexs.begin(), vertexs.end());
}

void command_queue::flush(std::string const& buffer_id) {
    auto vao = vao_map_[buffer_id];
    auto vbo = vbo_map_[buffer_id];
    auto& vertex_queue = vertex_queue_map_[buffer_id];
    std::function<void()> input_handler = [&]() {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertex_queue.size(), vertex_queue.data());
    };
    std::function<void()> draw_handler = [&]() {
        glScissor(image_node_->rect().x, image_node_->rect().y, image_node_->rect().width, image_node_->rect().height);
        glDrawArrays(GL_TRIANGLES, 0, vertex_queue.size() / 2);
        glScissor(0, 0, buffer_manager_->atlas_width(), buffer_manager_->atlas_height());
        glBindVertexArray(0);
    };
    if (buffer_id == "draw_rect") {
        buffer_manager_->bind_frame_buffer();
        input_handler();
        auto& draw_rect = shader::instance().draw_rect;
        draw_rect.use();
        draw_rect.enable_aVertex();
        draw_handler();
        draw_rect.unuse();
        buffer_manager_->unbind_frame_buffer();
    } else if (buffer_id == "draw_image") {
        buffer_manager_->bind_frame_buffer();
        buffer_manager_->bind_texture_buffer();
        input_handler();
        auto& draw_image = shader::instance().draw_image;
        draw_image.use();
        draw_image.enable_aVertex();
        draw_image.enable_aTexCoord();
        draw_image.enable_vSample();
        draw_handler();
        draw_image.unuse();
        buffer_manager_->unbind_texture_buffer();
        buffer_manager_->unbind_frame_buffer();
    } else if (buffer_id == "draw_window") {
        buffer_manager_->bind_texture_buffer();
        input_handler();
        auto& draw_image = shader::instance().draw_image;
        draw_image.use();
        draw_image.enable_aVertex();
        draw_image.enable_aTexCoord();
        draw_image.enable_vSample();
        draw_handler();
        draw_image.unuse();
        buffer_manager_->unbind_texture_buffer();
    }
    vertex_queue.clear();
}

} // end of namespace hsu
