//
// Created by sayuri on 7/18/16.
//

// REMOVE-ME
// REMOVE-ME
// REMOVE-ME

#ifndef WEBPP_MAIN_H
#define WEBPP_MAIN_H

#include <webpp.h>
using namespace WebPP;

/**
 * Testing purposes.
 * Will be removed as soon as it will become useless.
 */
class MainWebpp {

    private:
    static Webpp s_app;

    public:
    static Webpp *get_app() {
        return &s_app;
    }

//    Property int ll() { return 0; }
};

#endif //WEBPP_MAIN_H
