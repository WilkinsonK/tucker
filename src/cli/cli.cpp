#include <argparse/argparse.hpp>
#include "cli.hpp"

argparse::ArgumentParser rootParser("tucker");

void cli::init()
{
    auto& root = rootParser;
}

void cli::parse(int argc, const char *const *argv)
{
    auto& root = rootParser;

    try {
        root.parse_args(argc, argv);
    } catch (const std::runtime_error &error)
    {
        std::cerr << "error: " << error.what() << std::endl;
        std::cerr << root;
        std::exit(1);
    }
}

void cli::stop()
{}
