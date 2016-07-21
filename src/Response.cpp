//
// Created by sayuri on 7/18/16.
//

#include "Response.h"


WebPP::Response::Response(template_t body, uint16_t response_code) : body(body), code(response_code) {

}

WebPP::Response::Response() {

}

void WebPP::Response::generate_raw_headers(std::string &buffer) {
    buffer += "Content-type: text/html\r\n";
}


void WebPP::Response::generate_raw_body(std::string &buffer) {
    buffer += this->body;  // TODO: parse
}

void WebPP::Response::render(std::string &buffer) {
    std::string headers;
    std::string body;

    this->generate_raw_headers(headers);
    this->generate_raw_body(body);

    buffer += headers;
    buffer += "\r\n";   // Don't remove (RFC2616 section 6)
    buffer += body;
}
