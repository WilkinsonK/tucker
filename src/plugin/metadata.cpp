#include <string>

#include "src/plugin/metadata.hpp"

using namespace std;

namespace plugin {
    PluginMeta::PluginMeta(
                std::string pluginName,
                std::string pluginVersion,
                std::string tuckerVersion) 
            {
                name = pluginName;
                plugin_version = pluginVersion;
                tucker_version = tuckerVersion;
            }
}
