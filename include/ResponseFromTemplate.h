//
// Created by sayuri on 7/18/16.
//

#ifndef WEBPP_RESPONSEFROMTEMPLATE_H
#define WEBPP_RESPONSEFROMTEMPLATE_H


#include "Response.h"


namespace WebPP {
    /**
     * Inherits from WebPP::Response but doesn't render a "WebPP::template_t" but a template file.
     */
    class ResponseFromTemplate : public Response {
        private:
        std::string _path;
        const char *_response_code;

        public:
        ResponseFromTemplate(std::string path, const char* response_code = "200", t_insensitive_http_headers *headers = {});
        void render(std::string &buffer);
    };
}


#endif //WEBPP_RESPONSEFROMTEMPLATE_H
