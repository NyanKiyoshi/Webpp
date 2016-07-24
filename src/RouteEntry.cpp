//
// Created by sayuri on 7/20/16.
//

#include "RouteEntry.h"


WebPP::RouteEntry::RouteEntry(const char *associated_path) : associated_path(associated_path) {

}

std::ostream& operator<<(std::ostream &ostream, const WebPP::RouteEntry &entry) {
    return ostream << "RouteEntry(" << entry.associated_path << ")";
}

WebPP::RouteEntry::~RouteEntry() {
    // free:
    // _array_before_request
    // _array_after_request
}
