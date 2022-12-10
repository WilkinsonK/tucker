#ifndef TUCKER_PACKAGE_PLUGIN_OBJECT_H
#define TUCKER_PACKAGE_PLUGIN_OBJECT_H

#include <string>

using namespace std;

namespace plugin
{
    // Interface for plugins loaded by
    // `Plugin Source`.
    class PluginObject
    {
        public:
            // Load this plugin.
            virtual void load();

            // Destroy this plugin.
            virtual void destroy();

            std::string name;
            std::string version;
            std::string tuckerVersion;
    };
} // namespace plugin

#endif // TUCKER_PACKAGE_PLUGIN_OBJECT_H