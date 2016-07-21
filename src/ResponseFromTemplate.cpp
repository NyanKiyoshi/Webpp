//
// Created by sayuri on 7/18/16.
//

#include "Response.h"
#include "ResponseFromTemplate.h"
using namespace WebPP;


ResponseFromTemplate::ResponseFromTemplate(template_t path, uint16_t response_code, insensitive_http_headers_t *headers)
        : path(path), response_code(response_code) {

}

void ResponseFromTemplate::render(std::string &buffer) {
    Response::render(buffer);
}
