//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_REQUEST_H
#define WEBPP_REQUEST_H


#include <fcgiapp.h>
#include <string.h>


namespace WebPP {
    /**
     * Contains every information from the client's HTTP request.
     */
    class Request {
        private:
        const char* _ENV_HEADER_PREFIX = "HTTP_";
        const size_t _PREFIX_LENGTH = strlen(_ENV_HEADER_PREFIX);

        const FCGX_Request &_REQUEST;

        inline char* _get_from_env(const char *name);
        void _find_associated_route();

        public:
        const char *USER_AGENT;
        const char *REQUEST_METHOD;
        Request(FCGX_Request &request);

        char* get_header(const char* header_name);

        // The following methods are using static member functions to only extract one time the headers.
        // And only if they are asked for it.
        char* raw_query_string();
        char* raw_cookies();
        char* host();
    };
}


#endif //WEBPP_REQUEST_H
