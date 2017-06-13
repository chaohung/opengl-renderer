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

#include "gl_headers.hpp"

namespace hsu {

class renderer {
public:
    renderer(int canvas_width, int canvas_height, std::shared_ptr<GLFWwindow> window);
    ~renderer();

    void draw_rect(int x, int y, int width, int height) const;

private:
    GLuint draw_rect_vao_;
    GLuint draw_rect_vbo_;

    Eigen::Affine2f affine_;
    std::shared_ptr<GLFWwindow> window_;
};

} // end of namespace hsu

#endif /* renderer_hpp */
