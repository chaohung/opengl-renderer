//
//  command_queue.hpp
//  opengl-renderer-xcode
//
//  Created by Hsu Chaohung on 2017/06/29.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef command_queue_hpp
#define command_queue_hpp


#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "gl_headers.hpp"
#include "buffer_manager.hpp"
#include "atlas_node.hpp"

namespace hsu {

class command_queue {
public:
    command_queue(std::shared_ptr<hsu::buffer_manager> buffer_manager, std::shared_ptr<hsu::atlas_node const> image_node);
    ~command_queue();

    void create_buffer(std::string const& buffer_id, int vertex_num);
    void insert_vertex(std::string const& buffer_id, std::vector<GLfloat> vertexs);
    void flush(std::string const& buffer_id);

private:
    std::shared_ptr<hsu::buffer_manager> buffer_manager_;
    std::shared_ptr<hsu::atlas_node const> image_node_;
    std::unordered_map<std::string,GLuint> vao_map_;
    std::unordered_map<std::string,GLuint> vbo_map_;
    std::unordered_map<std::string,std::vector<GLfloat> > vertex_queue_map_;
};

} // end of namespace hsu

#endif /* command_queue_hpp */
