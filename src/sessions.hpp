#pragma once
#define JSESSION_TOKEN_EXPIRES_IN (60 * 20) // Time in seconds that a token will expire.

#include <ctime>
#include <iostream>
#include <string>

#include "rest.hpp"

namespace tucker
{
    class JSessionID
    {
        public:
            JSessionID(
                std::string hostname,
                std::string username,
                std::string password)
            {
                aquireToken(hostname, username, password);
                expires_at = std::time(nullptr) + JSESSION_TOKEN_EXPIRES_IN;
            }

            const std::string asString()
            {
                return "JSessionID['"
                    + sessionToken
                    + "' expires_at: " + std::to_string(expires_at)
                    + "]";
            }

            const std::string asRepr()
            {
                return sessionToken;
            }

        protected:
            void aquireToken(
                std::string hostname,
                std::string username,
                std::string password)
            {
                ResponseFunc handler =
                    [username, password](aConnection& connection)
                    {
                        aHeaderFields headers; std::string agentName;
                        headers["Accept"] = "*/*";

                        agentName =
                            "REST" +
                            (std::string)TUCKER_META_NAME + "-" +
                            (std::string)TUCKER_META_VERSION;

                        connection.SetBasicAuth(username, password);
                        connection.SetTimeout(5);
                        connection.SetUserAgent(agentName);
                        connection.SetHeaders(headers);

                        return connection.get("/data/JSESSIONID");
                    };

                std::string url = "https://" + hostname;
                aResponse response = iSendRequest(url, handler);
                if (response.code == 200)
                    sessionToken = response.body;
                    return;

                // TODO: replace with custom exception.
                std::cerr
                    << "error: got response '"
                    << response.code << "'\n"
                    << response.body << std::endl;
                std::exit(1);
            }

        private:
            std::string sessionToken;
            long expires_at;

            friend std::ostream& operator<<(std::ostream& ost, JSessionID& jid)
            {
                return ost << jid.asString();
            }
    };
} // namespace tucker
