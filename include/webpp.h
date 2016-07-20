#ifndef WEBPP_WEBPP_H
#define WEBPP_WEBPP_H


#include "Logger.h"
#include "Response.h"
#include "RequestHandler.h"


// TODO: send files
// TODO: we should be able to register classes as bp


namespace WebPP {
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

        // Logger
        Logger logger;

        // TODO: config
        // TODO: views
        // TODO: before requests
        // TODO: after requests
        // TODO: blueprints
        // TODO: extensions

        public:
        // TODO: should we set the default static folder as "static"? Webpp(const char *static_folder = "static");

        // create app
        Webpp();
        Webpp(const char *static_folder, const char *static_url_path, const char *template_folder);

        // TODO: set headers from route or HEADERS({...})
        // TODO: map regexp routes
        // TODO: get options as dict
        // register routes
        void route(char *url, void (*fn)(...));
        void route(char *urls[], void (*fn)(...));  // array of "char *url"

        // register extensions
            // will call init() ... blblbl

        // register a before request
        void before_request(void (*fn)());
        void before_request(void (*fn)(RequestHandler request));

        // register a after request
        void after_request(void (*fn)(Response response));
        void after_request(void (*fn)(RequestHandler request, Response response));

        // Getters
        const char* get_static_folder();
        const char* get_static_url_path();
        const char* get_template_folder();
    };
}


#endif  // WEBPP_WEBPP_H
