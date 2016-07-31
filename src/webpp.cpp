#include <assert.h>
#include <ResponseFromTemplate.h>
#include <Request.h>
#include <HTTPException.h>
#include <exception>
#include "webpp.h"
#include "utils/string_utils.h"


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

void WebPP::Webpp::add_route(char *url, t_view_fn_to_call fn, std::set<const char*> allowed_methods, WebPP::t_insensitive_http_headers headers) {
    // TODO: look for duplicates (must call a function to check)
    RouteEntry entry = RouteEntry(url, fn, allowed_methods, headers);
    this->route_entries.push_back(entry);
}

void WebPP::Webpp::add_route(std::vector<char *> &urls, t_view_fn_to_call fn, std::set<const char *> allowed_methods,
                             WebPP::t_insensitive_http_headers headers) {
    for (const auto &url : urls) {
        this->add_route(url, fn, allowed_methods, headers);
    }
}

void WebPP::Webpp::before_request(t_before_request_function fn) {

}

void WebPP::Webpp::after_request(t_after_request_function fn) {

}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp) {
    assert(this->_blueprints.count(bp->get_name()) < 1 && "A Blueprint has already been registered under this name.");
    this->_blueprints[bp->NAME] = bp;
}

void WebPP::Webpp::register_blueprint(WebPP::Blueprint *bp,
                                      const char *static_folder, const char *static_url_path,
                                      const char *template_folder, const char *url_prefix) {
    this->register_blueprint(bp);
    // TODO:
    //    We should call Blueprint.register(...) or something like that.
    //    Because someone should add rules in our app to allow to easily go through the subdomains and urls.
}

void WebPP::Webpp::_process_request(FCGX_Request fcgx_request) {
    Response *resp_ptr = nullptr;

    // TODO: call before_processing_request

    // generate request object
    Request rq = Request(fcgx_request);

    try {
        // search for the requested resource or raise HTTPNotFound
        RouteEntry *route = this->find(rq.uri);
        // ---

        // TODO: call preprocess_request
            // pass (Request rq)
        // ---

        // call view
        route->call_associated_view();
        // ---

        // TODO: call process_response
            // pass (Request rq, Response resp)
        // ---
        throw WebPP::CrashMeAndCatchMeIfYouCan();  // REMOVE-ME
    }
    // Catch HTTPException or its children
    catch (HTTPException &e) {
        // XXX: make_response<T>(ERROR_OBJ)?
        Response resp = e.render();
        this->_write_to_fastcgi(fcgx_request, &resp, &rq);
    }
    // Unhandled Exception!
    catch (...) {
//        std::exception_ptr p = std::current_exception();
//        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        Response resp = WebPP::InternalServerError().render();
        this->_write_to_fastcgi(fcgx_request, &resp, &rq);
    }

    // write response
    // TODO: what to do if resp is nullptr? HTTP 204?
//    this->_write_to_fastcgi(fcgx_request, resp_ptr, &rq);

    // XXX: it probably slowdown the request process because fcgi only flush after being called
    // XXX: we should find a way to do this after having sent the response.
    // TODO: call after_processing_request
}

void WebPP::Webpp::run() {
    // XXX: we should be able from anywhere to write to the cerr buffer
    FCGX_Request fcgx_request;

    FCGX_Init();
    FCGX_InitRequest(&fcgx_request, 0, 0);

    while (FCGX_Accept_r(&fcgx_request) == 0) {
        // BEGIN -- START
        fcgi_streambuf cin_fcgi_streambuf(fcgx_request.in);
        fcgi_streambuf cout_fcgi_streambuf(fcgx_request.out);
        fcgi_streambuf cerr_fcgi_streambuf(fcgx_request.err);
        // _start_wrtting_to_fastcgi_buffers ^ ^ ^

        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);
        // END -- START

        // try:
            this->_process_request(fcgx_request);
        // except:
            // do_nothing, it should be afterafter()
    }
    this->_stop_wrtting_to_fastcgi_buffers();
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

inline void
WebPP::Webpp::_write_to_fastcgi(FCGX_Request &fcgx_request, Response *response, Request *request) {
    std::string buffer;
    response->render(buffer);

    std::cout << buffer;

//    this->_debug_print_environment(fcgx_request.envp);
    this->_stop_wrtting_to_fastcgi_buffers();
}

inline void WebPP::Webpp::_stop_wrtting_to_fastcgi_buffers() {
    std::cin.rdbuf(this->_cin_streambuf);
    std::cout.rdbuf(this->_cout_streambuf);
    std::cerr.rdbuf(this->_cerr_streambuf);
}

void WebPP::Webpp::_debug_print_environment(char **environment) {
    for (int i = 0; environment[i] != NULL; i++) {
        std::cout << environment[i] << "\n";
    }
}

void WebPP::Webpp::create_rule(const std::string &rule) {
    std::vector<std::string> tokens;
    split(rule, tokens, "/");
}

WebPP::RouteEntry * WebPP::Webpp::find(const char *url) {
    for (RouteEntry &entry : this->route_entries) {
        if (strcmp(entry.associated_path, url) == 0) {
            return &entry;
        }
    }
    throw WebPP::NotFound();
}
