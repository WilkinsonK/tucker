#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <dlfcn.h>

#include "tucker/plugin/plugin.hpp"

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
    class PluginObject {
        public:
            // Load this plugin.
            virtual void load();

            // Destroy this plugin.
            virtual void destroy();

            std::string name;
            std::string version;
            std::string tuckerVersion;
    };

    // Manages metadata and handling of loading
    // and destroying a target plugin.
    class PluginSource
    {
        public:
            PluginSource(std::filesystem::path sourceFile)
            {
                m_source_file = sourceFile;
                m_plugin_loaded = false;
            }

            // Load the target plugin. Including
            // all assets and metadata.
            void plug()
            {
                m_loadPluginObject();
                if (!m_plugin_metadata) {
                    m_loadPluginMetaData();
                }

                m_plugin_loaded = true;
            }

            // Destroy the target plugin.
            //Including all assets and metadata.
            void unplug()
            {
                if (!m_plugin_loaded) { return; }
                m_destroyPluginObject();
                m_plugin_loaded = false;
            }

            // Get the release version of this
            // plugin.
            string getVersion()
            {
                return m_plugin_metadata->plugin_version;
            }

            // Get the name of the plugin.
            string getName()
            {
                return m_plugin_metadata->name;
            }

            // Get version of Tucker Plugin API
            // this plugin is compatible with.
            string getAPIVersion()
            {
                return m_plugin_metadata->tucker_version;
            }

        protected:
            // Shared object file which holds
            // expected plugin behaviors.
            std::filesystem::path m_source_file;

            // Internal plugin from this source.
            PluginObject * m_plugin;

            void * m_plugin_handle;

            // Relevant data related to the
            // plugin.
            PluginMeta * m_plugin_metadata;

            // Whether or not the plugin, and all
            // assets loaded sucessfully.
            bool m_plugin_loaded;

            void m_loadPluginMetaData()
            {
                // This may, more or less, be
                // redundant. What is the
                // justification for moving this
                // information to another object?
                if (!m_plugin) { return; }
                
                m_plugin_metadata = &PluginMeta(
                    m_plugin->name,
                    m_plugin->version,
                    m_plugin->tuckerVersion);
            }

            void m_loadPluginObject()
            {
                void* pluginHandle = dlopen(m_source_file.c_str(), RTLD_LAZY);
                if (!handle)
                {
                    // panik
                    std::cerr
                        << "failed to load plugin from: "
                        << m_source_file.c_str()
                        << endl;
                    return;
                }

                PluginObject (*Plugin)() =
                    (PluginObject (*)())dlsym(pluginHandle, "Plugin");

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
                m_plugin = &Plugin();
                m_plugin->load();
                m_plugin_handle = pluginHandle;
            }

            void m_destroyPluginObject()
            {
                PluginObject * plugin = m_plugin;
                void * pluginHandle = m_plugin_handle;

                m_plugin = nullptr;
                m_plugin_handle = nullptr;

                plugin->destroy();
                dlclose(pluginHandle);
                delete plugin;
                delete pluginHandle;
            }
    };
} // namespace plugin
