#ifndef TUCKER_PACKAGE_PLUGIN
#define TUCKER_PACKAGE_PLUGIN

#include <filesystem>

using namespace std;

namespace plugin
{
    class PluginMeta;
    class PluginObject;
    class PluginSource {
        public:
            PluginSource(std::filesystem::path filePath);
    };
} // namespace plugin

#endif // TUCKER_PACKAGE_PLUGIN
