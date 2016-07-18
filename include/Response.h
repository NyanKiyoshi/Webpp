//
// Created by sayuri on 7/18/16.
//

#ifndef WEBPP_RESPONSE_H
#define WEBPP_RESPONSE_H
#include <inttypes.h>
#include <bits/stl_map.h>


typedef char *template_t;

namespace WebPP {
    class Response {
        private:
        template_t body;
        uint16_t code = 200;

        std::map headers;  // will be updated by WebPP if HEADER({...}) was set

        public:
        Response();
        Response(template_t body, uint16_t response_code = 200);

        // will be used to render the response and will return the content
        virtual void render(char *buffer);
    };
}


#endif //WEBPP_RESPONSE_H
