//
//  context_manager.hpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/13.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef context_manager_hpp
#define context_manager_hpp

#include <memory>
#include <stdexcept>

#include "gl_headers.hpp"

namespace hsu {

class context_manager {
public:
    inline static context_manager& instance() {
        static auto instance = context_manager();
        return instance;
    }

    std::shared_ptr<GLFWwindow> create_window();

private:
    context_manager() {};
};

} // end of namespace hsu

#endif /* context_manager_hpp */
