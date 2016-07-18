//
// Created by sayuri on 7/18/16.
//

#ifndef WEBPP_RESPONSEFROMTEMPLATE_H
#define WEBPP_RESPONSEFROMTEMPLATE_H


#include "Response.h"


namespace WebPP {
    class ResponseFromTemplate : Response {
        ResponseFromTemplate(template_t path, uint16_t response_code = 200);
        void render(char *buffer);
    };
}


#endif //WEBPP_RESPONSEFROMTEMPLATE_H
