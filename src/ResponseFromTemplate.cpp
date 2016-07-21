//
// Created by sayuri on 7/18/16.
//

#include <Response.h>
#include "ResponseFromTemplate.h"
using namespace WebPP;

ResponseFromTemplate::ResponseFromTemplate(template_t path, uint16_t response_code)
        : path(path), response_code(response_code) {

}

void ResponseFromTemplate::render(std::string &buffer) {
    buffer += R"(Content-type: text/html\r\n
                 \r\n)";
    buffer += "RESPONSE FROM TPL.";
}
