#ifndef WEBPP_WEBPP_H
#define WEBPP_WEBPP_H

#include <iostream>
#include <map>
#include <fcgio.h>
#include <stdlib.h>
#include "Logger.h"
#include "Response.h"
#include "RequestHandler.h"
#include "Blueprint.h"


#define DEFAULT_THREAD_COUNT 20


#define HTTP_GET          1  // Information is appended onto the end of the request URI being requested
#define HTTP_POST         2  // Transmits all data immediately after the request URI.
#define HTTP_HEAD         3  // Headers of a GET request - Information about a document
#define HTTP_PUT          4  // The URI in a PUT request identifies the entity enclosed with the request.
#define HTTP_DELETE       5  // delete the resource identified by the Request-URI
#define HTTP_OPTIONS      6  // enum supported Methods
#define HTTP_TRACE        7  // enum each node along the path
#define HTTP_CONNECT      8  // Request web proxy dynamically switch to a secure IP-based connection (an SSL tunnel)
#define HTTP_UNKNOWN      9  // None of the Above


// TODO: send files
// TODO: we should be able to register classes as bp


namespace WebPP {
    // Type of functions to call
    typedef void (*before_request_function_t)(RequestHandler request);
    typedef void (*after_request_function_t)(RequestHandler request, Response response);

    // Blueprints
    typedef std::string str_blueprint_name_t;

    static const unsigned long STDIN_MAX = 1000000;


    /**
     * Controller of this framework, it manages everything.
     */
    class Webpp {
        private:
        // See https://web.archive.org/web/20110815203321/http://www.fastcgi.com/drupal/node/6?q=node/22#S4
        const int THREAD_COUNT;

        // Static folder
        const char *static_folder;
        const char *static_url_path;

        // Templates
        const char *template_folder;

        // List of registered blueprints
        // <instance name, instance>
        std::map<const str_blueprint_name_t, Blueprint*> blueprints = {};

        // Logger
        Logger logger;


        std::streambuf *cin_streambuf = std::cin.rdbuf();
        std::streambuf *cout_streambuf = std::cout.rdbuf();
        std::streambuf *cerr_streambuf = std::cerr.rdbuf();

        inline void start_wrtting_to_fastcgi_buffers(FCGX_Request request);
        inline void write_to_fastcgi(FCGX_Request &request, Response *response);
        inline void stop_wrtting_to_fastcgi_buffers();  // restores IO stream buffers

        // TODO: config
        // TODO: views
        // TODO: before requests
        // TODO: after requests
        // TODO: blueprints
        // TODO: extensions

        public:
        // TODO: should we set the default static folder as = "static"? Webpp(const char *static_folder = "static");

        // create app
        Webpp(const int THREAD_COUNT=DEFAULT_THREAD_COUNT);
        Webpp(const char *static_folder, const char *static_url_path, const char *template_folder,
              const int THREAD_COUNT=DEFAULT_THREAD_COUNT);

        void run();     // uses fastcgi and wait for requests
        void serve();   // TODO: serves a HTTPServer and wait for requests

        // TODO: set headers from route or HEADERS({...})
        // TODO: map regexp routes
        // TODO: get options as dict
        // register routes
        void route(char *url,    void (*fn)(...), insensitive_http_headers_t *headers = {});
        void route(char *urls[], void (*fn)(...), insensitive_http_headers_t *headers = {});  // array of "char *url"

        // register extensions
            // will call init() ... blblbl

        // register a before request
        void before_request(before_request_function_t fn);

        // register a after request
        void after_request(after_request_function_t fn);

        // register a blueprint
        // FIXME: let's decide if the blueprint must be a const of the Blueprint instance
        void register_blueprint(Blueprint *bp);
        void register_blueprint(Blueprint *bp,
                                const char *static_folder, const char *static_url_path,
                                const char *template_folder,
                                const char *url_prefix
        );

        // TODO: find resource http://stackoverflow.com/questions/17253690/finding-in-a-std-map-using-regex
        //       app.find(...)

        // Getters
        const char* get_static_folder();
        const char* get_static_url_path();
        const char* get_template_folder();
    };
}


#endif  // WEBPP_WEBPP_H
