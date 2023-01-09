#pragma once

#include <functional>

#include <restclient-cpp/connection.h>
#include <restclient-cpp/restclient.h>

namespace tucker
{
    // Alias for `RestClient::Connection`.
    typedef RestClient::Connection aConnection;

    // Alias for `RestClient::HeaderFields`.
    typedef RestClient::HeaderFields aHeaderFields;

    // Alias for `RestClient::Response`.
    typedef RestClient::Response aResponse;

    // Callable function which handles a
    // connection object.
    typedef std::function<aResponse(aConnection&)> ResponseFunc;

    // Calls the wrappable function with its
    // connection object, doing any pre & post
    // request handling.
    aResponse dSendRequest(aConnection& connection, ResponseFunc handler)
    {
        // Setup and tear-down RestClient as a
        // wrapper around the callable.
        RestClient::init();
        aResponse response = handler(connection);
        RestClient::disable();

        return response;
    }

    // Initiates a connection to the given
    // hostname and uses the callable to handle
    // request(s).
    aResponse iSendRequest(std::string url, ResponseFunc handler)
    {
        aConnection connection(url);
        return dSendRequest(connection, handler);
    }
}