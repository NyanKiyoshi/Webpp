//
// Created by sayuri on 7/18/16.
//

#ifndef WEBPP_RESPONSE_H
#define WEBPP_RESPONSE_H
#include <inttypes.h>
#include "types.h"


namespace WebPP {
    /**
     * A base Response object that will be used to render a response to the client.
     * At the end of the request processing, the render() method of this object or of its child we be called
     * and used to send a HTTP response to the client if there was no error.
     * This object must be returned during the view processing.
     */
    class Response {
        private:
        template_t body;
        uint16_t code;
        std::string mime_type;
        public:
        void set_mimetype(const std::string &mime_type);

        private:
        insensitive_http_headers_t *headers;  // will be updated by WebPP if HEADER({...}) was set

        public:
        Response(template_t body, uint16_t response_code = 200,
                 std::string mimetype = "text/html", insensitive_http_headers_t *headers = {});

        void generate_raw_headers(std::ostringstream &string_stream);
        void generate_raw_body(std::string &buffer);

        // will be used to render the response and will return the content
        virtual void render(std::string&);

        Response();
    };
}


#endif //WEBPP_RESPONSE_H
