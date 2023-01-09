#pragma once
#define OPTSTR_NOT_SET "OPTSTR_NOT_SET" // Represents when a stringable option is unset.

#include <argparse/argparse.hpp>

namespace tucker
{
    // Alias for `argparse::ArgumentParser`.
    typedef argparse::ArgumentParser aArgumentParser;

    typedef const char* const* cliArguments;

    namespace cli
    {
        aArgumentParser cliRootParser(TUCKER_META_NAME, TUCKER_META_VERSION);

        void init()
        {
            cliRootParser.add_description("simple CLI tool.");

            // Setup positional arguments.
            cliRootParser.add_argument("hostname");

            // Setup options.
            cliRootParser.add_argument("-u", "--username")
                .default_value(std::string(OPTSTR_NOT_SET))
                .help("username for target XNAT host.");
            cliRootParser.add_argument("-p", "--password")
                .default_value(std::string(OPTSTR_NOT_SET))
                .help("password for target XNAT host.");
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

        void getHostname(std::string& target)
        {
            target = cliRootParser.get<std::string>("hostname");
        }

        void getPassword(std::string& target)
        {
            target = cliRootParser.get<std::string>("password");
        }

        void getUsername(std::string& target)
        {
            target = cliRootParser.get<std::string>("username");
        }
    }
} // namespace tucker
