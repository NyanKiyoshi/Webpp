//
// Created by sayuri on 7/18/16.
//

#include <iostream>
#include "main.h"

int main() {
    Webpp *app_ptr = MainWebpp::get_app();

    std::cout << "Hello\r\n";
    std::cout << app_ptr->get_static_folder() << "\r\n";

    WebPP::Blueprint bp = WebPP::Blueprint("bp_test");
    std::cout << bp.get_name() << "\r\n";

    app_ptr->register_blueprint(&bp);
    app_ptr->register_blueprint(&bp);
    app_ptr->register_blueprint(&bp);
    app_ptr->register_blueprint(&bp);

    return 0;
}

Webpp MainWebpp::s_app = Webpp("static", "/static", "/templates");
