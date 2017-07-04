//
//  opengl_system.hpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/23.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef opengl_system_hpp
#define opengl_system_hpp

#include <functional>

#include "gl_headers.hpp"
#include "buffer_manager.hpp"

namespace hsu {

class opengl_system {
public:
    ~opengl_system();

    inline static opengl_system& instance() {
        static opengl_system instance;
        return instance;
    }

    void setup_window(int width, int height, std::string const& title);
    void setup_buffer_manager(int atlas_width, int atlas_height);

    void run_window(std::function<void()> handler) const;

    inline std::shared_ptr<hsu::buffer_manager> buffer_manager() const { return buffer_manager_; }

private:
    opengl_system();

private:
    std::shared_ptr<GLFWwindow> window_;
    std::shared_ptr<hsu::buffer_manager> buffer_manager_;
};

} // end of namespace hsu

#endif /* opengl_system_hpp */
