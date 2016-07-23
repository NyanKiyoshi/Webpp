//
// Created by sayuri on 7/18/16.
//

#include "Response.h"
#include "ResponseFromTemplate.h"
using namespace WebPP;


ResponseFromTemplate::ResponseFromTemplate(t_template path, uint16_t response_code, t_insensitive_http_headers *headers)
        : _path(path), _response_code(response_code) {

}

void ResponseFromTemplate::render(std::string &buffer) {
    Response::render(buffer);
}
