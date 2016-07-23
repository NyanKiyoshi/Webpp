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
        private:
        const int _CODE;
        const int _DESCRIPTION;

        public:
        /*
         * A blueprint could easily handle a HTTPException and for example generate a JSON response instead of
         * a HTML one. Or anything else without necessarily change/ inherit the HTTPException class.
         */
        void get_body(char *buffer) const;
        void get_headers(char *buffer) const;
        Response generated_response() const;

        int get_code() const {
            return this->_CODE;
        }

        int get_description() const {
            return this->_DESCRIPTION;
        }
    };


    class BadRequest : public HTTPException {
        int _CODE = 400;
    };


    class ClientDisconnected : public BadRequest {
    };


    class SecurityError : public BadRequest {
    };


    class BadHost : public BadRequest {
        int _CODE = 401;
    };


    class Unauthorized : public HTTPException {
        int _CODE = 401;
    };


    class Forbidden : public HTTPException {
        int _CODE = 403;
    };


    class NotFound : public HTTPException {
        int _CODE = 404;
    };


    class MethodNotAllowed : public HTTPException {
        int _CODE = 405;
    };


    class NotAcceptable : public HTTPException {
        int _CODE = 406;
    };


    class RequestTimeout : public HTTPException {
        int _CODE = 408;
    };


    class Conflict : public HTTPException {
        int _CODE = 409;
    };


    class Gone : public HTTPException {
        int _CODE = 410;
    };


    class LengthRequired : public HTTPException {
        int _CODE = 411;
    };


    class PreconditionFailed : public HTTPException {
        int _CODE = 412;
    };


    class RequestEntityTooLarge : public HTTPException {
        int _CODE = 413;
    };


    class RequestURITooLarge : public HTTPException {
        int _CODE = 414;
    };


    class UnsupportedMediaType : public HTTPException {
        int _CODE = 415;
    };


    class RequestedRangeNotSatisfiable : public HTTPException {
        int _CODE = 416;
    };


    class ExpectationFailed : public HTTPException {
        int _CODE = 417;
    };


    class ImATeapot : public HTTPException {
        int _CODE = 418;
    };


    class UnprocessableEntity : public HTTPException {
        int _CODE = 422;
    };


    class PreconditionRequired : public HTTPException {
        int _CODE = 428;
    };


    class TooManyRequests : public HTTPException {
        int _CODE = 429;
    };


    class RequestHeaderFieldsTooLarge : public HTTPException {
        int _CODE = 431;
    };


    class InternalServerError : public HTTPException {
        int _CODE = 500;
    };


    class NotImplemented : public HTTPException {
        int _CODE = 501;
    };


    class BadGateway : public HTTPException {
        int _CODE = 502;
    };


    class ServiceUnavailable : public HTTPException {
        int _CODE = 503;
    };


    class GatewayTimeout : public HTTPException {
        int _CODE = 504;
    };


    class HTTPVersionNotSupported : public HTTPException {
        int _CODE = 505;
    };
}
#endif //WEBPP_HTTPEXCEPTION_H
