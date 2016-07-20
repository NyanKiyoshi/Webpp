#ifndef WEBPP_REQUESTHANDLER_H
#define WEBPP_REQUESTHANDLER_H

#include <cstdint>
#include <stdlib.h>


namespace WebPP {
    typedef struct {
        unsigned char version;
        unsigned char type;
        unsigned char requestIdB1;
        unsigned char requestIdB0;
        unsigned char contentLengthB1;
        unsigned char contentLengthB0;
        unsigned char paddingLength;
        unsigned char reserved;
//        unsigned char contentData[contentLength];
//        unsigned char paddingData[paddingLength];
    } FCGI_Record;

    /**
     * FIXME: will probably be removed soon. Not decided yet.
     */
    class RequestHandler {
        public:
//        RequestHandler(template_t &(*body), int response_code = 200);

        void t(FCGI_Record &fcgi_record);
        void decode_query();

        void parse_request();
        inline void extract_version(char *version);

        /*
   +------+-------------------------------+--------------------------+
   | Code | Reason-Phrase                 | Defined in...            |
   +------+-------------------------------+--------------------------+
   | 100  | Continue                      | Section 6.2.1            |
   | 101  | Switching Protocols           | Section 6.2.2            |
   | 200  | OK                            | Section 6.3.1            |
   | 201  | Created                       | Section 6.3.2            |
   | 202  | Accepted                      | Section 6.3.3            |
   | 203  | Non-Authoritative Information | Section 6.3.4            |
   | 204  | No Content                    | Section 6.3.5            |
   | 205  | Reset Content                 | Section 6.3.6            |
   | 206  | Partial Content               | Section 4.1 of [RFC7233] |
   | 300  | Multiple Choices              | Section 6.4.1            |
   | 301  | Moved Permanently             | Section 6.4.2            |
   | 302  | Found                         | Section 6.4.3            |
   | 303  | See Other                     | Section 6.4.4            |
   | 304  | Not Modified                  | Section 4.1 of [RFC7232] |
   | 305  | Use Proxy                     | Section 6.4.5            |
   | 307  | Temporary Redirect            | Section 6.4.7            |
   | 400  | Bad Request                   | Section 6.5.1            |
   | 401  | Unauthorized                  | Section 3.1 of [RFC7235] |
   | 402  | Payment Required              | Section 6.5.2            |
   | 403  | Forbidden                     | Section 6.5.3            |
   | 404  | Not Found                     | Section 6.5.4            |
   | 405  | Method Not Allowed            | Section 6.5.5            |
   | 406  | Not Acceptable                | Section 6.5.6            |
   | 407  | Proxy Authentication Required | Section 3.2 of [RFC7235] |
   | 408  | Request Timeout               | Section 6.5.7            |
   | 409  | Conflict                      | Section 6.5.8            |
   | 410  | Gone                          | Section 6.5.9            |
   | 411  | Length Required               | Section 6.5.10           |
   | 412  | Precondition Failed           | Section 4.2 of [RFC7232] |
   | 413  | Payload Too Large             | Section 6.5.11           |
   | 414  | URI Too Long                  | Section 6.5.12           |
   | 415  | Unsupported Media Type        | Section 6.5.13           |
   | 416  | Range Not Satisfiable         | Section 4.4 of [RFC7233] |
   | 417  | Expectation Failed            | Section 6.5.14           |
   | 426  | Upgrade Required              | Section 6.5.15           |
   | 500  | Internal Server Error         | Section 6.6.1            |
   | 501  | Not Implemented               | Section 6.6.2            |
   | 502  | Bad Gateway                   | Section 6.6.3            |
   | 503  | Service Unavailable           | Section 6.6.4            |
   | 504  | Gateway Timeout               | Section 6.6.5            |
   | 505  | HTTP Version Not Supported    | Section 6.6.6            |
   +------+-------------------------------+--------------------------+
         */
    };
}

#endif  // WEBPP_REQUESTHANDLER_H
