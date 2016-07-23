//
// Created by sayuri on 7/20/16.
//

#include "Request.h"


WebPP::Request::Request(FCGX_Request &request) : REQUEST(request) {

}

char* WebPP::Request::request_method() {
    static char* request_method = FCGX_GetParam("HTTP_REQUEST_METHOD", this->REQUEST.envp);
    return request_method;
}

char* WebPP::Request::user_agent() {
    static char* user_agent = FCGX_GetParam("HTTP_USER_AGENT", this->REQUEST.envp);
    return user_agent;
}
