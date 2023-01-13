#include "cmdline.hpp"
#include "sessions.hpp"
#include "ioutil.hpp"

int main(int argc, const char *const *argv)
{

    tucker::cli::init();
    tucker::cli::parse(argc, argv);

    return 0;
}
