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

        // HTTP_HOST + DOCUMENT_URI
        char *host_uri;
        public:
        char *get_host_uri() const;

        private:

        inline const char* get_request_method();
        void _find_associated_route();

        public:
        const char* uri;
        const char* host;
        const char *USER_AGENT;
        const char *REQUEST_METHOD;
        Request(FCGX_Request &request);
        ~Request();

        // XXX: inline does not work from outside?
        char* get_from_env(const char *name);
        char* get_header(const char* header_name);

        // is_https = strcmp(REQUEST_SCHEME, "https") ? true : false

        // The following methods are using static member functions to only extract one time the headers.
        // And only if they are asked for it.
        char* raw_query_string();
        char* raw_cookies();
    };
}


#endif //WEBPP_REQUEST_H
