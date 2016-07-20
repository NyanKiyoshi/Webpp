//
// Created by sayuri on 7/19/16.
//

#ifndef WEBPP_HTTPEXCEPTION_H
#define WEBPP_HTTPEXCEPTION_H


#include <exception>
#include "Response.h"


namespace WebPP {
    /**
     * Base descriptor of a HTTPException allow to throw some HTTP errors during the request processing.
     * The HTTPException and its children will be handled by the application and render a error on the client's browser.
     */
    class HTTPException : public std::exception {
        protected:
        virtual int _code;
        virtual int _description;

        public:
        void get_body(char *buffer) const;
        void get_headers(char *buffer) const;

        Response generated_response() const;

        int get_code() const {
            return this->_code;
        }

        int get_description() const {
            return this->_description;
        }
    };


    class BadRequest : public HTTPException {
    };


    class ClientDisconnected : public HTTPException {
    };


    class SecurityError : public HTTPException {
    };


    class BadHost : public HTTPException {
    };


    class Unauthorized : public HTTPException {
    };


    class Forbidden : public HTTPException {
    };


    class NotFound : public HTTPException {
    };


    class MethodNotAllowed : public HTTPException {
    };


    class NotAcceptable : public HTTPException {
    };


    class RequestTimeout : public HTTPException {
    };


    class Conflict : public HTTPException {
    };


    class Gone : public HTTPException {
    };


    class LengthRequired : public HTTPException {
    };


    class PreconditionFailed : public HTTPException {
    };


    class RequestEntityTooLarge : public HTTPException {
    };


    class RequestURITooLarge : public HTTPException {
    };


    class UnsupportedMediaType : public HTTPException {
    };


    class RequestedRangeNotSatisfiable : public HTTPException {
    };


    class ExpectationFailed : public HTTPException {
    };


    class ImATeapot : public HTTPException {
    };


    class UnprocessableEntity : public HTTPException {
    };


    class PreconditionRequired : public HTTPException {
    };


    class TooManyRequests : public HTTPException {
    };


    class RequestHeaderFieldsTooLarge : public HTTPException {
    };


    class InternalServerError : public HTTPException {
    };


    class NotImplemented : public HTTPException {
    };


    class BadGateway : public HTTPException {
    };


    class ServiceUnavailable : public HTTPException {
    };


    class GatewayTimeout : public HTTPException {
    };


    class HTTPVersionNotSupported : public HTTPException {
    };
}
#endif //WEBPP_HTTPEXCEPTION_H
