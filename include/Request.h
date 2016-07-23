//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_REQUEST_H
#define WEBPP_REQUEST_H


#include <fcgiapp.h>


namespace WebPP {
    /**
     * Contains every information from the client's HTTP request.
     */
    class Request {
        private:
        const FCGX_Request &REQUEST;
        void find_associated_route();

        public:
        Request(FCGX_Request &request);

        char *request_method();
        char *raw_query_string();
        char *raw_cookies();
        char *user_agent();
        char *host();
    };
}


#endif //WEBPP_REQUEST_H
