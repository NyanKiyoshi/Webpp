//
// Created by sayuri on 7/18/16.
//

#include "Response.h"


WebPP::Response::Response(template_t body, uint16_t response_code) : body(body), code(response_code) {

}

WebPP::Response::Response() {

}

void WebPP::Response::render(std::string &buffer) {
    buffer += "RESPONSE.";
}
