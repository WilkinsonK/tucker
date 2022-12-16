#pragma once

#include "cli.hpp"

namespace api
{
    // Initializes this module.
    void init();

    // Performs teardown tasks related to this
    // module.
    void stop();

} // namespace api
