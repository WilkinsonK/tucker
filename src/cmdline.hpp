#pragma once
#define OPTSTR_NOT_SET "OPTSTR_NOT_SET" // Represents when a stringable option is unset.

#include <functional>
#include <memory>

#include <argparse/argparse.hpp>

#include "sessions.hpp"

namespace tucker
{
    // Alias for `argparse::ArgumentParser`.
    typedef argparse::ArgumentParser aArgumentParser;
    typedef std::function<void(aArgumentParser& parser)> cliSubParserHandler;
    typedef const char* const* cliArguments;

    namespace cli
    {
        aArgumentParser cliRootParser(TUCKER_META_NAME, TUCKER_META_VERSION);
        std::map<std::string, cliSubParserHandler> cliMapCommandHandler;
        std::map<std::string, std::unique_ptr<aArgumentParser>> cliMapCommandParser;

        void initSubParser(std::string name, cliSubParserHandler initilizer, cliSubParserHandler handler)
        {
            // Initialize parser and add as
            // sub-command to root parser.
            aArgumentParser* parser = new aArgumentParser(name);
            initilizer(*parser);
            cliRootParser.add_subparser(*parser);

            // Apply mappings for new parser.
            cliMapCommandHandler.emplace(name, handler);
            cliMapCommandParser.emplace(name, parser);
        }

        // Sub-parser initializer. Used in `initSubParser`.
        void initAuthParser(aArgumentParser& parser)
        {
            auto action = [&](const std::string value)
            {
                static const std::vector<std::string> choices = {"aquire", "delete"};
                if (std::find(choices.begin(), choices.end(), value) != choices.end())
                    return value;
                return (std::string)OPTSTR_NOT_SET;
            };

            parser.add_description("XNAT auth directives.");
            parser.add_argument("action").action(action);
            parser.add_argument("hostname");
        }

        void init()
        {
            cliRootParser.add_description("Keenan's XNAT tool.");
        }

        void parse(int argc, cliArguments argv)
        {
            try {
                cliRootParser.parse_args(argc, argv);
            } catch (std::runtime_error& error) {
                std::cerr
                    << "error: " << error.what() << "\n"
                    << cliRootParser << std::endl;
                std::exit(-1);
            }
        }
    }
} // namespace tucker
