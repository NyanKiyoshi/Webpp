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
        t_template _path;
        uint16_t _response_code;

        public:
        ResponseFromTemplate(t_template path, uint16_t response_code = 200, t_insensitive_http_headers *headers = {});
        void render(std::string &buffer);
    };
}


#endif //WEBPP_RESPONSEFROMTEMPLATE_H
