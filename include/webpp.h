#ifndef WEBPP_WEBPP_H
#define WEBPP_WEBPP_H

#include <vector>
#include <iostream>
#include <map>
#include <fcgio.h>
#include <stdlib.h>
#include <set>
#include "Logger.h"
#include "Response.h"
#include "Request.h"
#include "Blueprint.h"
#include "typedef_fn.h"
#include "RouteEntry.h"


#define DEFAULT_THREAD_COUNT 20


// TODO: send files
// TODO: we should be able to register classes as bp


namespace WebPP {

    // Blueprints
    typedef std::string t_str_blueprint_name;

    static const unsigned long STDIN_MAX = 1000000;  // TODO: load from config


    /**
     * Controller of this framework, it manages everything.
     */
    class Webpp {
        private:
        // See https://web.archive.org/web/20110815203321/http://www.fastcgi.com/drupal/node/6?q=node/22#S4
        const int _THREAD_COUNT;

        // Static folder
        const char *_STATIC_FOLDER;
        const char *_STATIC_URL_PATH;

        // Templates
        const char *_TEMPLATE_FOLDER;

        // List of registered blueprints
        // <instance name, instance>
        std::map<const t_str_blueprint_name, Blueprint*> _blueprints = {};
        std::vector<RouteEntry> route_entries;

        // Logger
        Logger _logger;


        std::streambuf *_cin_streambuf = std::cin.rdbuf();
        std::streambuf *_cout_streambuf = std::cout.rdbuf();
        std::streambuf *_cerr_streambuf = std::cerr.rdbuf();

        void _process_request(FCGX_Request fcgx_request);

        inline void _start_wrtting_to_fastcgi_buffers(FCGX_Request request);
        inline void _write_to_fastcgi(FCGX_Request &fcgx_request, Response *response, Request *request);
        inline void _stop_wrtting_to_fastcgi_buffers();  // restores IO stream buffers
        inline void _debug_print_environment(char **environment);

        void create_rule(const std::string &rule);

        // TODO: config
        // TODO: views -> registrations from add_route(...) and blueprint.add_route(...). Will be functions to call
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

        // TODO: set headers from route or HEADERS({...})
        // TODO: map regexp routes
        // TODO: get options as dict
        // register routes
        void add_route(
                // TODO: needs to handle #26
                char *url,

                // TODO: (*fn)(Request, URIParamsDict)->URIParamsDict=parsed from route regex groups
                // FIXME: we should be able to *return* nothing, a string or a ResponseObj. Maybe pass Response_ptr as arg?
                t_view_fn_to_call,

                std::set<const char *> allowed_methods = {"GET"},
                t_insensitive_http_headers headers = {}
        );
        void add_route(
                std::vector<char *> &urls,   // array of "char *url"
                t_view_fn_to_call,
                std::set<const char *> allowed_methods = {"GET"},
                t_insensitive_http_headers headers = {}
        );

        // register extensions
            // will call init() ... blblbl

        // register a function to call before starting to process the newly received request
        void before_processing_request(void *before_processing_request());

        // register a before request
        void before_request(t_before_request_function fn);

        /**
         * Call every registered `before_request` after having generated the Request object and before calling
         * the associated route.
         * @param request
         */
        void preprocess_request(Request request);

        // register a after request
        void after_request(t_after_request_function fn);

        /**
         * Call every registered `after_request` after having called the view and rendered the Response right
         * before sending the generated response.
         */
        void process_response(Request request, Response response);

        // register a function to call after having to processed everything (called after the after_request())
        void after_processing_request(void *before_processing_request());

        // register a blueprint
        // FIXME: let's decide if the blueprint must be a const of the Blueprint instance
        // blueprint.register will be called to register everything
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
