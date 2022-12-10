#ifndef TUCKER_PACKAGE_PLUGIN_METADATA_H
#define TUCKER_PACKAGE_PLUGIN_METADATA_H

#include <string>

using namespace std;

namespace plugin {
    // Data related to the target plugin object.
    class PluginMeta
    {
        public:
            PluginMeta(
                std::string pluginName,
                std::string pluginVersion,
                std::string tuckerVersion);

            std::string name;
            std::string plugin_version;
            std::string tucker_version;
    };
} // namespace plugin

#endif // TUCKER_PACKAGE_PLUGIN_METADATA_H