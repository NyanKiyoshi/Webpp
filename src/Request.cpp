//
// Created by sayuri on 7/20/16.
//

#include <cstring>
#include "Request.h"


WebPP::Request::Request(FCGX_Request &request) : REQUEST(request) {

}

char* WebPP::Request::get_header(const char* header_name) {
    size_t header_length = strlen(header_name);
    char new_header_name[this->PREFIX_LENGTH + header_length];

    strcat(new_header_name, this->ENV_HEADER_PREFIX);
    strcat(new_header_name, header_name);

    return FCGX_GetParam(new_header_name, this->REQUEST.envp);
}

inline char *WebPP::Request::get_from_env(const char *name) {
    return FCGX_GetParam(name, this->REQUEST.envp);
}

char* WebPP::Request::request_method() {
    static char* header = this->get_from_env("HTTP_REQUEST_METHOD");
    return header;
}

char* WebPP::Request::user_agent() {
    static char* header = this->get_from_env("HTTP_USER_AGENT");
    return header;
}
