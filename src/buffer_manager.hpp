//
//  buffer_manager.hpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/24.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef buffer_manager_hpp
#define buffer_manager_hpp

#include <glm/glm.hpp>

#include "atlas_node.hpp"
#include "gl_headers.hpp"

namespace hsu {

class buffer_manager {
public:
    buffer_manager(int atlas_width, int atlas_height);
    ~buffer_manager();

    std::shared_ptr<hsu::atlas_node const> allocate_canvas(int width, int height, void* data) const;
    void deallocatte(std::shared_ptr<hsu::atlas_node> image_node) const {};

    void download_texture(int x, int y, int width, int height, void* data) const;
    void upload_texture(int x, int y, int width, int height, void* data) const;

    void bind_texture_buffer() const;
    void unbind_texture_buffer() const;

    void bind_frame_buffer() const;
    void unbind_frame_buffer() const;

    inline glm::mat4 const& dst_affine() const { return dst_affine_; }
    inline glm::mat4 const& src_affine() const { return src_affine_; }

    inline int atlas_width() const { return atlas_tree_->rect().width; }
    inline int atlas_height() const { return atlas_tree_->rect().height; }

private:
    GLuint generate_texture_buffer(int width, int height, void* data) const;
    GLuint generate_render_buffer(int width, int height) const;
    GLuint generate_frame_buffer(int width, int height, GLuint texture_buffer, GLuint render_buffer) const;

    void setup_affine(int width, int height);

private:
    std::shared_ptr<hsu::atlas_node> atlas_tree_;
    GLuint texture_atlas_;
    GLuint render_buffer_;
    GLuint frame_buffer_;

    glm::mat4 dst_affine_;
    glm::mat4 src_affine_;
};

} // end of namespace hsu

#endif /* buffer_manager_hpp */
