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
        const char* ENV_HEADER_PREFIX = "HTTP_";
        const size_t PREFIX_LENGTH = strlen(ENV_HEADER_PREFIX);

        const FCGX_Request &REQUEST;

        inline char* get_from_env(const char *name);
        void find_associated_route();

        public:
        Request(FCGX_Request &request);

        char* get_header(const char* header_name);

        char* request_method();
        char* raw_query_string();
        char* raw_cookies();
        char* user_agent();
        char* host();
    };
}


#endif //WEBPP_REQUEST_H
