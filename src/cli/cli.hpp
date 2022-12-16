#pragma once

#include <argparse/argparse.hpp>
#pragma once

#include <iostream>

namespace cli
{

    // Initializes this module.
    void init();

    // Parse the given arguments using the
    // parser.
    void parse(int argc, const char *const *argv);

    // Performs teardown tasks related to this
    // module.
    void stop();

} // namespace cli
