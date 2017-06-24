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

namespace hsu {

class shader {
public:
    inline static hsu::shader& instance() {
        static auto shader = hsu::shader();
        return shader;
    }

    struct {
    friend class shader;
    void enable_aVertex() const {
        glVertexAttribPointer(aVertex_, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(aVertex_);
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

    struct {
    friend class shader;
    void enable_aVertex() const {
        glVertexAttribPointer(aVertex_, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)0);
        glEnableVertexAttribArray(aVertex_);
    }
    void enable_aTexCoord() const {
        glVertexAttribPointer(aTexCoord_, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(aTexCoord_);
    }
    void enable_vSample() const {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(uSample_, 0);
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
        GLint aTexCoord_;
        GLint uSample_;
    } draw_image;

private:
    shader();
    ~shader();
};

} // end of namespace hsu

#endif /* shader_hpp */
