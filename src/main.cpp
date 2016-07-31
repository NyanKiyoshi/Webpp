//
// Created by sayuri on 7/18/16.
//

#include <iostream>
#include "main.h"


void route_test(...) {

}


int main() {
    Webpp *app_ptr = MainWebpp::get_app();

    WebPP::Blueprint bp = WebPP::Blueprint("bp_test");
    std::cout << bp.get_name() << "\r\n";

    app_ptr->register_blueprint(&bp);


    std::set<const char*> allowed_methods = {"GET"};
    WebPP::t_insensitive_http_headers headers = {};
    app_ptr->add_route("/debug", route_test, allowed_methods, headers);

    app_ptr->run();

    return 0;
}

Webpp MainWebpp::s_app = Webpp("static", "/static", "/templates");
