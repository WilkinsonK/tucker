#ifndef TUCKER_PACKAGE_PLUGIN_SOURCE_H
#define TUCKER_PACKAGE_PLUGIN_SOURCE_H

#include <string>
#include <filesystem>

#include "metadata.hpp"
#include "object.hpp"

using namespace std;

namespace plugin
{
    // Manages metadata and handling of loading
    // and destroying a target plugin.
    class PluginSource
    {
        public:
            PluginSource(std::filesystem::path sourceFile);

            // Load the target plugin. Including
            // all assets and metadata.
            void plug();

            // Destroy the target plugin.
            //Including all assets and metadata.
            void unplug();

            // Get the release version of this
            // plugin.
            std::string getVersion();

            // Get the name of the plugin.
            std::string getName();

            // Get version of Tucker Plugin API
            // this plugin is compatible with.
            std::string getAPIVersion();

        protected:
            // Shared object file which holds
            // expected plugin behaviors.
            std::filesystem::path m_source_file;

            // Internal plugin from this source.
            PluginObject * m_plugin_object;

            // Loaded object file which contains
            // the plugin object implementation.
            void * m_plugin_handle;

            // Relevant data related to the
            // plugin.
            PluginMeta * m_plugin_metadata;

            // Whether or not the plugin, and all
            // assets loaded sucessfully.
            bool m_plugin_loaded;

            void m_loadPluginMetaData();
            void m_loadPluginObject();
            void m_destroyPluginObject();
    };

} // namespace plugin;

#endif // TUCKER_PACKAGE_PLUGIN_SOURCE_H
