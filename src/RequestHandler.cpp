#include "RequestHandler.h"


/**
 * Following the RFC7230.
 * As the RFC7230 says in A.2 "The expectation to support HTTP/0.9 requests has been removed.", the HTTP/0.9
 * requests will be no longer handled.
 */
void WebPP::RequestHandler::parse_request() {
    // must close connection = False (default)(keep alive)

    // read first stream line from the TCP data
    // split the spaces from the first line

    // There are three possibilities:
    // 1. there are three words -> <COMMAND>, <PATH>, <VERSION>
    // 2. there are two words   -> <COMMAND>, <PATH>
    // 3. there less than two words

    // IF == 3
        // SETTING <COMMAND>, <PATH>, <VERSION>

        // version_number = this->extract_version(VERSION)
        // IF version_number < 1.1
            // must close connection = True (don't keep alive)
        // IF version_number >= 2.0
            // ------ R::505 ------ //-> don't know how to handle that
    // ELIF == 2
        // <COMMAND>, <PATH>
    // ELSE
        // Do nothing (empty response data)
        // ------ R ------
    // ------ R::RESULTS ------
}

inline void WebPP::RequestHandler::extract_version(char *version) {
    // RFC 7230 section 2.6 define the syntax:
    //      "HTTP" "/" DIGIT "." DIGIT
    // With "HTTP" case-sensitive.

    // IF doesn't starts with "HTTP/" -> 400
        // ------ R::400 ------
    // SPLIT("/") one time (can be spaces between)
    // IF LEN != 2 -> 400
        // ------ R::400 ------
    // TRY
        // version_number[2] = int(version_number[0]), int(version_number[1])
    // THROW
        // ------ R::400 ------
}
