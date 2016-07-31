//
// Created by sayuri on 7/18/16.
//

#include <sstream>
#include "Response.h"

#define CLRF "\r\n"

WebPP::t_insensitive_http_headers WebPP::Response::default_headers = {};


// FIXME: body should be a reference, not a copy
// TODO: body<T>
// TODO: handle response code
WebPP::Response::Response(std::string body, const char *response_code,
                          std::string mimetype, t_insensitive_http_headers *headers)
        : _body(body), _status_code(response_code), _mime_type(mimetype), headers(headers) {

}

void WebPP::Response::generate_raw_headers(std::ostringstream &string_stream) {
    // Copy the headers before modifying them
    t_insensitive_http_headers temp_headers = *(this->headers);

    // override the Status and Content-Type headers
    temp_headers["Status"] = this->_status_code;
    temp_headers["Content-type"] = this->_mime_type;

    // loop through the headers
    // append header and add a CRLF ending according to the RFC2616
    for (const auto& header : temp_headers) {
        string_stream << header.first << ":" << header.second << CLRF;
    }
}

void WebPP::Response::generate_raw_body(std::string &buffer) {
    buffer += this->_body;  // TODO: parse
}

void WebPP::Response::render(std::string &buffer) {
    std::ostringstream headers;
    std::string body;

    this->generate_raw_headers(headers);
    this->generate_raw_body(body);

    buffer += headers.str();  // Copy the raw headers string buffer to the render buffer
    buffer += CLRF;           // Separation between the HTTP header and message-body (RFC2616 section 6)
    buffer += body;
}

WebPP::Response::Response() {}

void WebPP::Response::set_mimetype(const std::string &mime_type) {
    Response::_mime_type = mime_type;
}

WebPP::t_insensitive_http_headers *WebPP::Response::get_headers() const {
    return headers;
}
