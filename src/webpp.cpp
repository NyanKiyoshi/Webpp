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

void WebPP::Webpp::run() {
    // XXX: we should check if in multithread it still works
    // XXX: because `this->request` is in a precise RAM address unlike a local:request in run()!
    // ---
    // XXX: we should be able from anywhere to write to the cerr buffer

    FCGX_Init();
    FCGX_InitRequest(&(this->request), 0, 0);

    while (FCGX_Accept_r(&(this->request)) == 0) {
        this->write_to_fastcgi((char *)"Hello");
    }
}

inline void WebPP::Webpp::start_wrtting_to_fastcgi_buffers() {
    fcgi_streambuf cin_fcgi_streambuf(request.in);
    fcgi_streambuf cout_fcgi_streambuf(request.out);
    fcgi_streambuf cerr_fcgi_streambuf(request.err);

    // FIXME: it creates null ptr!!!
    std::cin.rdbuf(&cin_fcgi_streambuf);
    std::cout.rdbuf(&cout_fcgi_streambuf);
    std::cerr.rdbuf(&cerr_fcgi_streambuf);
}

// TODO: get a Response instance
inline void WebPP::Webpp::write_to_fastcgi(char *buffer) {
    fcgi_streambuf cin_fcgi_streambuf(this->request.in);
    fcgi_streambuf cout_fcgi_streambuf(this->request.out);
    fcgi_streambuf cerr_fcgi_streambuf(this->request.err);
    // start_wrtting_to_fastcgi_buffers ^ ^ ^

    std::cin.rdbuf(&cin_fcgi_streambuf);
    std::cout.rdbuf(&cout_fcgi_streambuf);
    std::cerr.rdbuf(&cerr_fcgi_streambuf);

//    this->start_wrtting_to_fastcgi_buffers();

    std::cout << "Content-type: text/html\r\n"
              << "\r\n"   // Don't remove (RFC2616 section 6)
              << buffer
              << "\r\n";

    this->stop_wrtting_to_fastcgi_buffers();
}

inline void WebPP::Webpp::stop_wrtting_to_fastcgi_buffers() {
    std::cin.rdbuf(this->cin_streambuf);
    std::cout.rdbuf(this->cout_streambuf);
    std::cerr.rdbuf(this->cerr_streambuf);
}
