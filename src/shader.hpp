//
//  shader.hpp
//  HSURenderer
//
//  Created by Hsu Chaohung on 2017/06/03.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include "gl_headers.hpp"

namespace core {

class shader {
public:
    inline static core::shader& instance() {
        static auto shader = core::shader();
        return shader;
    }
    struct {
    friend class shader;
    void enable_vertex() const {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(aVertex_);
    }
    void set_vertex(GLfloat* vertices) const {
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 12, vertices);
    }
    void use() const {
        glUseProgram(program_);
    }
    void unuse() const {
        glUseProgram(0);
    }
    private:
        GLuint program_;
        GLint aVertex_;
    } draw_rect;
private:
    shader();
};

} // end of namespace hsu

#endif /* shader_hpp */
