#include "api.hpp"
#include "cli.hpp"

using namespace std;

int main(int argc, const char *const *argv)
{
    cli::init();
    cli::parse(argc, argv);
    return 0;
}
