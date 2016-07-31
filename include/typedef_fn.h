//
// Created by sayuri on 7/31/16.
//

#ifndef WEBPP_TYPEDEF_FN_H
#define WEBPP_TYPEDEF_FN_H

#include "Request.h"
#include "Response.h"

namespace WebPP {
    // Type of functions to call
    typedef void (*t_before_request_function)(Request);
    typedef void (*t_after_request_function)(Request, Response);

    typedef void (*t_view_fn_to_call)(...);
}


#endif //WEBPP_TYPEDEF_FN_H
