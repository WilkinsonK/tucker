#include <argparse/argparse.hpp>

namespace tucker
{
    argparse::ArgumentParser root_parser("tucker");

    void parseArgs(int argc, const char *const *argv)
    {
        root_parser.parse_args(argc, argv);
    }
} // namespace tucker

int main(int argc, const char *const *argv)
{
    return 0;
}
