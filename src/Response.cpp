//
// Created by sayuri on 7/18/16.
//

#include <sstream>
#include "Response.h"


WebPP::Response::Response(template_t body, uint16_t response_code,
                          std::string mimetype, insensitive_http_headers_t *headers)
        : body(body), code(response_code), mime_type(mimetype), headers(headers) {

}

void WebPP::Response::generate_raw_headers(std::ostringstream &string_stream) {
    // loop through the headers
    // append header and add a CRLF ending according to the RFC2616
    for (const auto& header : *(this->headers)) {
        string_stream << header.first << ":" << header.second << "\r\n";
    }
    string_stream << "Content-type:" << mime_type << "\r\n";
}


void WebPP::Response::generate_raw_body(std::string &buffer) {
    buffer += this->body;  // TODO: parse
}

void WebPP::Response::render(std::string &buffer) {
    std::ostringstream headers;
    std::string body;

    this->generate_raw_headers(headers);
    this->generate_raw_body(body);

    buffer += headers.str();
    buffer += "\r\n";   // Don't remove (RFC2616 section 6)
    buffer += body;
}

WebPP::Response::Response() {}

void WebPP::Response::set_mimetype(const std::string &mime_type) {
    Response::mime_type = mime_type;
}
