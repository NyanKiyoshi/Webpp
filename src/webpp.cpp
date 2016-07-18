#include "webpp.h"


WebPP::Webpp::Webpp() {

}

WebPP::Webpp::Webpp(const char *static_folder, const char *static_url_path, const char *template_folder) {
    this->static_folder = static_folder;
    this->static_url_path = static_url_path;
    this->template_folder = template_folder;
}

const char *WebPP::Webpp::get_static_folder() {
    return this->static_folder;
}

const char *WebPP::Webpp::get_static_url_path() {
    return this->static_url_path;
}

const char *WebPP::Webpp::get_template_folder() {
    return this->template_folder;
}

void WebPP::Webpp::route(char *url, void (*fn)(...)) {

}

void WebPP::Webpp::route(char *urls[], void (*fn)(...)) {

}

void WebPP::Webpp::before_request(void (*fn)(RequestHandler request)) {

}

void WebPP::Webpp::after_request(void (*fn)(RequestHandler request, Response response)) {

}

void WebPP::Webpp::after_request(void (*fn)(WebPP::Response)) {

}

void WebPP::Webpp::before_request(void (*fn)()) {

}
