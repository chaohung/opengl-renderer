//
//  Canvas.hpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/05/02.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <string>
#include <memory>

#include "gl_headers.hpp"
#include "renderer.hpp"
#include "atlas_node.hpp"

namespace hsu {

class canvas {
public:
    canvas(int x, int y, int width, int height, uint8_t* data = nullptr);
    virtual ~canvas();

    inline std::shared_ptr<hsu::renderer const> renderer() const { return renderer_; }
    inline std::shared_ptr<hsu::atlas_node const> image_node() const { return image_node_; }

    void read(int x, int y, int width, int height, void* data) const;
    void write(int x, int y, int width, int height, void* data) const;

private:
    std::shared_ptr<hsu::atlas_node const> image_node_;
    std::shared_ptr<hsu::renderer> renderer_;
};

} // end of namespace hsu

#endif /* canvas_hpp */
