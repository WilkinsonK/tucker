#include <string>
#include <filesystem>
#include <iostream>

#include <dlfcn.h>

#include "source.hpp"

using namespace std;

namespace plugin
{

    PluginSource::PluginSource(std::filesystem::path sourceFile)
    {
        m_source_file = sourceFile;
        m_plugin_loaded = false;
    }

    void PluginSource::plug()
    {
        m_loadPluginObject();
        if (!m_plugin_metadata) {
            m_loadPluginMetaData();
        }

        m_plugin_loaded = true;
    }

    // Destroy the target plugin.
    //Including all assets and metadata.
    void PluginSource::unplug()
    {
        if (!m_plugin_loaded) { return; }
        m_destroyPluginObject();
        m_plugin_loaded = false;
    }

    std::string PluginSource::getVersion()
    {
        return m_plugin_metadata->plugin_version;
    }

    std::string PluginSource::getName()
    {
        return m_plugin_metadata->name;
    }

    std::string PluginSource::getAPIVersion()
    {
        return m_plugin_metadata->tucker_version;
    }

    void PluginSource::m_loadPluginMetaData()
    {
        // This may, more or less, be
        // redundant. What is the
        // justification for moving this
        // information to another object?
        if (!m_plugin_object) { return; }
        
        PluginMeta plugin_meta(
            m_plugin_object->name,
            m_plugin_object->version,
            m_plugin_object->tuckerVersion);
        m_plugin_metadata = &plugin_meta;
    }

    void PluginSource::m_loadPluginObject()
    {
        void* pluginHandle = dlopen(m_source_file.c_str(), RTLD_LAZY);
        if (!pluginHandle)
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

        PluginObject plugin_object = Plugin();

        // kalm
        m_plugin_object = &plugin_object;
        m_plugin_object->load();
        m_plugin_handle = pluginHandle;
    }

    void PluginSource::m_destroyPluginObject()
        {
            PluginObject * plugin_object = m_plugin_object;
            void * pluginHandle = m_plugin_handle;

            m_plugin_object = nullptr;
            m_plugin_handle = nullptr;

            plugin_object->destroy();
            dlclose(pluginHandle);
            delete plugin_object;
        }
} // namespace plugin
