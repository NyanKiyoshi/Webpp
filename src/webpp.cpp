#include <assert.h>
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

void WebPP::Webpp::route(char *url, void (*fn)(...), WebPP::http_headers_t headers) {

}

void WebPP::Webpp::route(char *urls[], void (*fn)(...), WebPP::http_headers_t headers) {

}

void WebPP::Webpp::before_request(before_request_function_t fn) {

}

void WebPP::Webpp::after_request(after_request_function_t fn) {

}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp) {
    assert(this->blueprints.count(bp->get_name()) < 1 && "A Blueprint has already been registered under this name.");
    this->blueprints[bp->name] = bp;
}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp,
                                      const char *static_folder, const char *static_url_path,
                                      const char *template_folder, const char *url_prefix) {
    this->register_blueprint(bp);
    // TODO
    // We should call Blueprint.register(...) or something like that.
    // Because someone should add rules in our app to allow to easily go through the subdomains and urls.
}
