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
        unsigned char contentData[contentLength];
        unsigned char paddingData[paddingLength];
    } FCGI_Record;

    class RequestHandler {
        public:
//        RequestHandler(template_t &(*body), int response_code = 200);

        void t(FCGI_Record &fcgi_record);
        void decode_query();
    };
}

#endif  // WEBPP_REQUESTHANDLER_H
