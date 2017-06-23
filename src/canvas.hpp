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

namespace hsu {

class canvas {
public:
    canvas(int x, int y, int width, int height, uint8_t* data = nullptr);
    virtual ~canvas();

    std::shared_ptr<GLFWwindow> window();

    inline std::shared_ptr<hsu::renderer const> renderer() { return renderer_; }
    inline GLuint texture() const { return texture_; }

private:
    std::shared_ptr<GLFWwindow> window_;
    std::shared_ptr<hsu::renderer> renderer_;
    GLuint texture_;
};

} // end of namespace hsu

#endif /* canvas_hpp */
