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

class canvas;

class renderer {
public:
    renderer(int canvas_width, int canvas_height, std::shared_ptr<GLFWwindow> window);
    ~renderer();

    void draw_rect(int x, int y, int width, int height) const;
    void draw_image(int dst_x, int dst_y, int dst_width, int dst_height,
        int src_x, int src_y, int src_width, int src_height, GLuint texture_id) const;

private:
    GLuint draw_rect_vao_;
    GLuint draw_rect_vbo_;
    GLuint draw_image_vao_;
    GLuint draw_image_vbo_;

    Eigen::Affine2f dst_affine_;
    Eigen::Affine2f src_affine_;
    std::shared_ptr<GLFWwindow> window_;
};

} // end of namespace hsu

#endif /* renderer_hpp */
