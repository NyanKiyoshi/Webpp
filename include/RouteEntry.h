//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_ROUTEENTRY_H
#define WEBPP_ROUTEENTRY_H


#include <set>
#include <ostream>
#include "typedef_fn.h"


namespace WebPP {
    // XXX: replace me with a struct
    class RouteEntry {
        t_insensitive_http_headers default_headers;
        std::set<const char *> allowed_methods;

        t_view_fn_to_call associated_view;


        friend std::ostream& operator<<(std::ostream &ostream, const RouteEntry &entry);

        public:
        // path of this route entry
        const char* associated_path;

        RouteEntry(const char *associated_path, t_view_fn_to_call fn,
                           std::set<const char *> allowed_methods,
                           WebPP::t_insensitive_http_headers default_headers);
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
