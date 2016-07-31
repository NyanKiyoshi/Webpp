//
// Created by sayuri on 7/20/16.
//

#include "RouteEntry.h"

// XXX: std::set<const char *> allowed_methods could be replaced by logical binary and enums but what about the future of HTTP?
// XXX: What if in a future HTTP version there are many more HTTP verbs or if we want to add non standard verbs?
// ---
// XXX: I hesitate between ptr or copies. Copies are fine because it is during the app initialisation and it protects
// XXX: from some possible errors.
WebPP::RouteEntry::RouteEntry(const char *associated_path, t_view_fn_to_call fn,
                              std::set<const char *> allowed_methods,
                              WebPP::t_insensitive_http_headers default_headers)
        : associated_path(associated_path), associated_view(fn),
          allowed_methods(allowed_methods), default_headers(default_headers) {

}

std::ostream& operator<<(std::ostream &ostream, const WebPP::RouteEntry &entry) {
    return ostream << "RouteEntry(" << entry.associated_path << ")";
}

WebPP::RouteEntry::~RouteEntry() {
    // free:
    // _array_before_request
    // _array_after_request
}
