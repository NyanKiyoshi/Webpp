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
        std::string _body;
        const char *_status_code;
        std::string _mime_type;

        t_insensitive_http_headers *headers = {};
        static t_insensitive_http_headers default_headers;

        public:
        void set_mimetype(const std::string &mime_type);

        t_insensitive_http_headers *get_headers() const;
        // will be updated by WebPP if HEADER({...}) was set

        /**
         * @param body
         * @param response_code
         * @param mimetype
         * @param headers Those headers are case insentive.
         * @return
         */
        Response(std::string body, const char *response_code = "200",
                 std::string mimetype = "text/html", t_insensitive_http_headers *headers = &default_headers);

        void generate_raw_headers(std::ostringstream &string_stream);
        void generate_raw_body(std::string &buffer);

        // will be used to render the response and will return the content
        virtual void render(std::string&);

        protected: Response();
    };
}


#endif //WEBPP_RESPONSE_H
