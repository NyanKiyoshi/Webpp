//
// Created by sayuri on 7/20/16.
//

#ifndef WEBPP_BLUEPRINT_H
#define WEBPP_BLUEPRINT_H


#include "types.h"


namespace WebPP {
    /**
     * Extends the application and create several separations from the base app to allow an easier management
     * and readability.
     */
    class Blueprint {
        public:
        const std::string name;
        Blueprint(const std::string);
        std::string get_name() {
            return this->name;
        }
    };
}


#endif //WEBPP_BLUEPRINT_H
