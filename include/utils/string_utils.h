//
// Created by sayuri on 7/24/16.
//

#ifndef WEBPP_STRING_UTILS_H
#define WEBPP_STRING_UTILS_H

#include <vector>
#include <string>


void split(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ") {
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos) {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

#endif //WEBPP_STRING_UTILS_H
