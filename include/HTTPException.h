//
// Created by sayuri on 7/19/16.
//

#ifndef WEBPP_HTTPEXCEPTION_H
#define WEBPP_HTTPEXCEPTION_H


#include <exception>
#include <sstream>
#include "Response.h"


namespace WebPP {
    /**
     * Base descriptor of a HTTPException allow to throw some HTTP errors during the request processing.
     * The HTTPException and its children will be handled by the application and render a error on the client's browser.
     */
    class HTTPException {
        private:
        const char* _CODE;
        const char* _DESCRIPTION;

        public:
        HTTPException(const char *code, const char *descr) : _CODE(code), _DESCRIPTION(descr) {};

        /*
         * A blueprint could easily handle a HTTPException and for example generate a JSON response instead of
         * a HTML one. Or anything else without necessarily change/ inherit the HTTPException class.
         */
        void get_body(char *buffer) const;
        void get_headers(char *buffer) const;
        Response generated_response() const;

        const char* get_code() const {
            return this->_CODE;
        }

        const char* get_description() const {
            return this->_DESCRIPTION;
        }

        Response render() {
            std::ostringstream body;
            body << "<!doctype html>"
                    "<html>"
                    "<head><title>" << this->_CODE << " " << this->_DESCRIPTION << "</title></head>"
                    "<body>"
                    "<center><h1>" << this->_CODE << " " << this->_DESCRIPTION << "</h1></center>"
                    "</body>"
                    "</html>";
            return Response(body.str(), this->_CODE);
        }

        char const* what() const throw () {
            return this->_DESCRIPTION;
        }
    };


    class BadRequest : public HTTPException {
        public:
        BadRequest() : HTTPException("400", "Bad Request") {}
    };


    class ClientDisconnected : public BadRequest {
    };


    class SecurityError : public BadRequest {
    };


    class Unauthorized : public HTTPException {
        public:
        Unauthorized() : HTTPException("401", "Unauthorized") {}
    };


    class Forbidden : public HTTPException {
        public:
        Forbidden() : HTTPException("403", "Forbidden") {}
    };


    class NotFound : public HTTPException {
        public:
        NotFound() : HTTPException("404", "Not Found") {}
    };


    class MethodNotAllowed : public HTTPException {
        public:
        MethodNotAllowed() : HTTPException("405", ""){}
    };


    class NotAcceptable : public HTTPException {
        public:
        NotAcceptable() : HTTPException("406", ""){}
    };


    class RequestTimeout : public HTTPException {
        public:
        RequestTimeout() : HTTPException("408", ""){}
    };


    class Conflict : public HTTPException {
        public:
        Conflict() : HTTPException("409", ""){}
    };


    class Gone : public HTTPException {
        public:
        Gone() : HTTPException("410", ""){}
    };


    class LengthRequired : public HTTPException {
        public:
        LengthRequired() : HTTPException("411", ""){}
    };


    class PreconditionFailed : public HTTPException {
        public:
        PreconditionFailed() : HTTPException("412", ""){}
    };


    class RequestEntityTooLarge : public HTTPException {
        public:
        RequestEntityTooLarge() : HTTPException("413", ""){}
    };


    class RequestURITooLarge : public HTTPException {
        public:
        RequestURITooLarge() : HTTPException("414", ""){}
    };


    class UnsupportedMediaType : public HTTPException {
        public:
        UnsupportedMediaType() : HTTPException("415", ""){}
    };


    class RequestedRangeNotSatisfiable : public HTTPException {
        public:
        RequestedRangeNotSatisfiable() : HTTPException("416", ""){}
    };


    class ExpectationFailed : public HTTPException {
        public:
        ExpectationFailed() : HTTPException("417", ""){}
    };


    class ImATeapot : public HTTPException {
        public:
        ImATeapot() : HTTPException("418", "I\'m a teapot"){}
    };


    class UnprocessableEntity : public HTTPException {
        public:
        UnprocessableEntity() : HTTPException("422", ""){}
    };


    class PreconditionRequired : public HTTPException {
        public:
        PreconditionRequired() : HTTPException("428", ""){}
    };


    class TooManyRequests : public HTTPException {
        public:
        TooManyRequests() : HTTPException("429", ""){}
    };


    class RequestHeaderFieldsTooLarge : public HTTPException {
        public:
        RequestHeaderFieldsTooLarge() : HTTPException("431", ""){}
    };


    class InternalServerError : public HTTPException {
        public:
        InternalServerError() : HTTPException("500", "Internal Server Error"){}
    };


    class NotImplemented : public HTTPException {
        public:
        NotImplemented() : HTTPException("501", ""){}
    };


    class BadGateway : public HTTPException {
        public:
        BadGateway() : HTTPException("502", ""){}
    };


    class ServiceUnavailable : public HTTPException {
        public:
        ServiceUnavailable() : HTTPException("503", ""){}
    };


    class GatewayTimeout : public HTTPException {
        public:
        GatewayTimeout() : HTTPException("504", ""){}
    };


    class HTTPVersionNotSupported : public HTTPException {
        public:
        HTTPVersionNotSupported() : HTTPException("505", ""){}
    };

    class CrashMeAndCatchMeIfYouCan : public std::exception {};
}
#endif //WEBPP_HTTPEXCEPTION_H
