#ifndef WEBPP_WEBPP_H
#define WEBPP_WEBPP_H

#include <map>
#include "Logger.h"
#include "Response.h"
#include "RequestHandler.h"
#include "Blueprint.h"
#include "types.h"


// TODO: send files
// TODO: we should be able to register classes as bp


namespace WebPP {
    // Type of functions to call
    typedef void (*before_request_function_t)(RequestHandler request);
    typedef void (*after_request_function_t)(RequestHandler request, Response response);

    // Blueprints
    typedef std::string str_blueprint_name_t;

    /**
     * Controller of this framework, it manages everything.
     */
    class Webpp {
        private:

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

        // TODO: config
        // TODO: views
        // TODO: before requests
        // TODO: after requests
        // TODO: blueprints
        // TODO: extensions

        public:
        // TODO: should we set the default static folder as = "static"? Webpp(const char *static_folder = "static");

        // create app
        Webpp();
        Webpp(const char *static_folder, const char *static_url_path, const char *template_folder);

        // TODO: set headers from route or HEADERS({...})
        // TODO: map regexp routes
        // TODO: get options as dict
        // register routes
        void route(char *url,    void (*fn)(...), http_headers_t headers = {});
        void route(char *urls[], void (*fn)(...), http_headers_t headers = {});  // array of "char *url"

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
