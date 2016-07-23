//
// Created by sayuri on 7/20/16.
//

#include <cstring>
#include "Request.h"

WebPP::Request::Request(FCGX_Request &request) : _REQUEST(request),
                                                 USER_AGENT(_get_from_env("HTTP_USER_AGENT")),
                                                 REQUEST_METHOD(_get_from_env("HTTP_REQUEST_METHOD")) {

}

/**
 * @param header_name
 * @example get_header("USER_AGENT") -> Mozilla/5.0 (X11; Linux x86_64; rv:47.0) Gecko/20100101 Firefox/47.0
 * @return
 */
char* WebPP::Request::get_header(const char* header_name) {
    size_t header_length = strlen(header_name);
    char new_header_name[this->_PREFIX_LENGTH + header_length];

    strcpy(new_header_name, this->_ENV_HEADER_PREFIX);
    strcat(new_header_name, header_name);

    return FCGX_GetParam(new_header_name, this->_REQUEST.envp);
}

inline char* WebPP::Request::_get_from_env(const char *name) {
    return FCGX_GetParam(name, this->_REQUEST.envp);
}
