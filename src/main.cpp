//
// Created by sayuri on 7/18/16.
//

#include <iostream>
#include "main.h"

int main() {
    Webpp *app_ptr = MainWebpp::get_app();

    std::cout << "Hello\r\n";
    std::cout << app_ptr->get_static_folder();
    return 0;
}

Webpp MainWebpp::s_app = Webpp("static", "/static", "/templates");
