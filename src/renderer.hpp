//
//  renderer.hpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <Eigen/Geometry>
#include <memory>

#include "gl_headers.hpp"
#include "atlas_node.hpp"
#include "command_queue.hpp"
#include "buffer_manager.hpp"

namespace hsu {

class canvas;

class renderer {
public:
    renderer(std::shared_ptr<hsu::buffer_manager> buffer_manager, std::shared_ptr<atlas_node const> image_node);
    ~renderer();

    void draw_rect(int x, int y, int width, int height) const;
    void draw_image(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const;
    void draw_window(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, hsu::canvas const& canvas) const;

    void flush(std::string const& command_type) const;

private:
    std::shared_ptr<hsu::buffer_manager> buffer_manager_;
    std::shared_ptr<hsu::atlas_node const> image_node_;
    std::shared_ptr<hsu::command_queue> command_queue_;
};

} // end of namespace hsu

#endif /* renderer_hpp */
