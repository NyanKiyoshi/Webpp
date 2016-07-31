//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_TYPES_H
#define WEBPP_TYPES_H

#include <map>
#include <strings.h>


namespace WebPP {
    // From http://stackoverflow.com/a/19102250
    struct comp {
        bool operator() (const std::string& lhs, const std::string& rhs) const {
            return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;  // Compare the two values and ignore case
        }
    };
    typedef std::map<std::string, std::string, comp> t_insensitive_http_headers;

    typedef char t_template;
}


#endif //WEBPP_TYPES_H
