#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <dlfcn.h>

using namespace std;

namespace plugin
{
    class PluginMeta
    {
        public:
            PluginMeta(
                std::string pname,
                std::string pluginVersion,
                std::string tuckerVersion)
            {
                name = pname;
                plugin_version = pluginVersion;
                tucker_version = tuckerVersion;
            }

            std::string name;
            std::string plugin_version;
            std::string tucker_version;
    };

    // Interface for plugins loaded by
    // `Plugin Source`.
    class i_Plugin {
        public:
            // Load this plugin.
            virtual void load();

            // Destroy this plugin.
            virtual void destroy();
    };

    // Manages metadata and handling of loading
    // and destroying a target plugin.
    class PluginSource
    {
        public:
            PluginSource(std::filesystem::path sourceFile);

            void loadSource()
            {
                void* handle = dlopen(m_source_file.c_str(), RTLD_LAZY);
                if (!handle)
                {
                    // panik
                    std::cerr
                        << "failed to load plugin from: "
                        << m_source_file.c_str()
                        << endl;
                    return;
                }

                i_Plugin (*Plugin)() = (i_Plugin (*)())dlsym(handle, "Plugin");
                if (!Plugin)
                {
                    // panik
                    std::cerr
                        << "failed to retrieve plugin from "
                        << "loaded object."
                        << endl;
                    return;
                }

                // kalm
                i_Plugin x = Plugin();
                x.load();

                // This is probably going to break.
                // Knowing my luck with pointers,
                // closing this before the end of
                // our plugin's life cycle is
                // gonna come with a nasty bump.
                dlclose(handle);
            }

        private:
            // Relevant data related to the
            // plugin.
            PluginMeta m_metadata;

            // Shared object file which holds
            // expected plugin behaviors.
            std::filesystem::path m_source_file;

    };
} // namespace plugin
