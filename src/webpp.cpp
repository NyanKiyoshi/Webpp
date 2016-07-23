#include <assert.h>
#include <ResponseFromTemplate.h>
#include <Request.h>
#include "webpp.h"


WebPP::Webpp::Webpp(const int THREAD_COUNT) : _THREAD_COUNT(THREAD_COUNT) {

}

WebPP::Webpp::Webpp(const char *static_folder, const char *static_url_path, const char *template_folder,
                    const int THREAD_COUNT
) : _STATIC_FOLDER(static_folder), _STATIC_URL_PATH(static_url_path), _TEMPLATE_FOLDER(template_folder),
    _THREAD_COUNT(THREAD_COUNT) {
}

const char *WebPP::Webpp::get_static_folder() {
    return this->_STATIC_FOLDER;
}

const char *WebPP::Webpp::get_static_url_path() {
    return this->_STATIC_URL_PATH;
}

const char *WebPP::Webpp::get_template_folder() {
    return this->_TEMPLATE_FOLDER;
}

void WebPP::Webpp::add_route(char *url, void (*fn)(...), std::set<const char*> allowed_methods, WebPP::t_insensitive_http_headers *headers) {

}

void WebPP::Webpp::add_route(char **urls, void (*fn)(...), std::set<const char*> allowed_methods, WebPP::t_insensitive_http_headers *headers) {

}

void WebPP::Webpp::before_request(t_before_request_function fn) {

}

void WebPP::Webpp::after_request(t_after_request_function fn) {

}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp) {
    assert(this->_blueprints.count(bp->get_name()) < 1 && "A Blueprint has already been registered under this name.");
    this->_blueprints[bp->name] = bp;
}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp,
                                      const char *static_folder, const char *static_url_path,
                                      const char *template_folder, const char *url_prefix) {
    this->register_blueprint(bp);
    // TODO:
    //    We should call Blueprint.register(...) or something like that.
    //    Because someone should add rules in our app to allow to easily go through the subdomains and urls.
}

void WebPP::Webpp::run() {
    // XXX: we should be able from anywhere to write to the cerr buffer
    FCGX_Request fcgx_request;

    FCGX_Init();
    FCGX_InitRequest(&fcgx_request, 0, 0);

    while (FCGX_Accept_r(&fcgx_request) == 0) {
        t_insensitive_http_headers h = {{"Content-type", "Null."}, {"X-test", "X-done"}};  // REMOVE-ME
        Response resp = Response(*fcgx_request.envp, 200, "text/html", &h);                // REMOVE-ME

        // TODO: generate request object
        // TODO: search for endpoint
        // TODO: call view
        // TODO: make_response

        this->_write_to_fastcgi(fcgx_request, &resp);
    }
}

// XXX: this method doesn't work (null pointers)
inline void WebPP::Webpp::_start_wrtting_to_fastcgi_buffers(FCGX_Request request) {
    fcgi_streambuf cin_fcgi_streambuf(request.in);
    fcgi_streambuf cout_fcgi_streambuf(request.out);
    fcgi_streambuf cerr_fcgi_streambuf(request.err);

    // FIXME: we are creating null pointers
    std::cin.rdbuf(&cin_fcgi_streambuf);
    std::cout.rdbuf(&cout_fcgi_streambuf);
    std::cerr.rdbuf(&cerr_fcgi_streambuf);
}

inline void WebPP::Webpp::_write_to_fastcgi(FCGX_Request &request, Response *response) {
    fcgi_streambuf cin_fcgi_streambuf(request.in);
    fcgi_streambuf cout_fcgi_streambuf(request.out);
    fcgi_streambuf cerr_fcgi_streambuf(request.err);
    // _start_wrtting_to_fastcgi_buffers ^ ^ ^

    std::cin.rdbuf(&cin_fcgi_streambuf);
    std::cout.rdbuf(&cout_fcgi_streambuf);
    std::cerr.rdbuf(&cerr_fcgi_streambuf);

    std::string buffer;
    response->render(buffer);

    std::cout << buffer;

    // REMOVE-ME
    Request rq = Request(request);

    // REMOVE-ME
    std::cout << rq.user_agent();

    this->_stop_wrtting_to_fastcgi_buffers();
}

inline void WebPP::Webpp::_stop_wrtting_to_fastcgi_buffers() {
    std::cin.rdbuf(this->_cin_streambuf);
    std::cout.rdbuf(this->_cout_streambuf);
    std::cerr.rdbuf(this->_cerr_streambuf);
}
