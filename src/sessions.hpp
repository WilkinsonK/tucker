#pragma once
#define JSESSION_TOKEN_EXPIRES_IN (60 * 20) // Time in seconds that a token will expire.

#include <ctime>
#include <iostream>
#include <string>

#include <argparse/argparse.hpp>

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
                m_hostname = hostname;
                m_username = username;
                aquireSessionId(password);
                m_expiresAt = std::time(nullptr) + JSESSION_TOKEN_EXPIRES_IN;
            }

            const std::string asString()
            {
                return "JSessionID['"
                    + m_sessionId
                    + "' expires_at: " + std::to_string(m_expiresAt)
                    + "]";
            }

            const std::string asRepr()
            {
                return m_sessionId;
            }

            const std::string hostUrl()
            {
                return "https://" + m_hostname;
            }

            void aquireSessionId(std::string password)
            {
                ResponseFunc handler = [&](aConnection& connection)
                    {
                        aHeaderFields headers;
                        headers["Accept"] = "*/*";

                        connection.SetBasicAuth(m_username, password);
                        connection.SetTimeout(5);
                        connection.SetUserAgent(m_agentName);
                        connection.SetHeaders(headers);

                        return connection.get("/data/JSESSIONID");
                    };

                aResponse response = iSendRequest(hostUrl(), handler);
                if (response.code == 200)
                    m_sessionId = response.body;
                    return;

                // TODO: replace with custom exception.
                std::cerr
                    << "error: got response '"
                    << response.code << "'\n"
                    << response.body << std::endl;
                std::exit(1);
            }

            void deleteSessionId(std::string hostname)
            {
                if (!m_sessionId.size())
                    return;

                ResponseFunc handler = [&](aConnection& connection)
                    {
                        aHeaderFields headers;
                        headers["Accept"] = "*/*";
                        headers["Cookie"] = "JSESSIONID=" + m_sessionId;

                        connection.SetTimeout(5);
                        connection.SetUserAgent(m_agentName);
                        connection.SetHeaders(headers);

                        return connection.del("/data/JSESSIONID");
                    };

                aResponse response = iSendRequest(hostUrl(), handler);
                if (response.code == 200)
                    return;

                // TODO: replace with custom exception.
                std::cerr
                    << "error: got response '"
                    << response.code << "'\n"
                    << response.body << std::endl;
                std::exit(1);
            };

        protected:
            std::string m_sessionId, m_hostname, m_username;
            long m_expiresAt;

            friend std::ostream& operator<<(std::ostream& ost, JSessionID& jid)
            {
                return ost << jid.asString();
            }

        private:
            const std::string m_agentName =
                "REST" +
                (std::string)TUCKER_META_NAME + "-" +
                (std::string)TUCKER_META_VERSION;
    };

    // REST Requests have:
    // 1. an endpoint. One endpoint can have child endpoints. string
    // 2. parameters. string
    std::string getProjects(JSessionID jid, const std::string options...)
    {
        ResponseFunc handler = [&](aConnection& connection)
            {
                aHeaderFields headers;
                headers["Accept"] = "*/*";
                headers["Cookie"] = "JSESSIONID=" + jid.asRepr();
                return connection.get("/data/projects");
            };

        aResponse response = iSendRequest(jid.hostUrl(), handler);
    }
} // namespace tucker
