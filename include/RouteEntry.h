//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_ROUTEENTRY_H
#define WEBPP_ROUTEENTRY_H


#include "webpp.h"


namespace WebPP {
    // XXX: replace me with a struct
    class RouteEntry {
        t_insensitive_http_headers default_headers;


        friend std::ostream& operator<<(std::ostream &ostream, const RouteEntry &entry);

        public:
        // path of this route entry
        const char* associated_path;

        RouteEntry(const char *associated_path);
        ~RouteEntry();

        // looks if the given path match the entry
        bool match(const char *&path);
        
        private:
        // Arrays of before/after_rq
        t_before_request_function _array_before_request[0];  // use malloc(sizeof(_array_before_request) + N * sizeof(_array_before_request[0]))
        t_after_request_function  _array_after_request[0];   // use malloc(sizeof(_array_after_request) + N * sizeof(_array_after_request[0]))
    };
}


#endif //WEBPP_ROUTEENTRY_H
