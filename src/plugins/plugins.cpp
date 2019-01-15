
#include "plugins/plugins.h"

using namespace std;

struct VidePluginInitList
{
    vector<VidePluginInit*> inits;
};

static VidePluginInitList* g_pluginInitList = NULL;

VidePluginManager::VidePluginManager()
{
    m_vide = NULL;
}

VidePluginManager::~VidePluginManager()
{
    for (VidePlugin* plugin : m_plugins)
    {
        plugin->shutdown();

        delete plugin;
    }
}

bool VidePluginManager::init(Vide* vide)
{
    m_vide = vide;

    if (g_pluginInitList == NULL)
    {
        printf("VidePluginManager::init: No plugins found\n");
        return true;
    }

    for (VidePluginInit* init : g_pluginInitList->inits)
    {
        printf("VidePluginManager::init: Plugin: %s\n", init->getName());
        VidePlugin* plugin = init->create(vide);
        if (plugin != NULL)
        {
            plugin->setLoggerName(string("Plugin[") + init->getName() + "]");
            plugin->setPluginName(init->getName());

            bool res;
            res = plugin->init();
            if (res)
            {
                m_plugins.push_back(plugin);
            }
            else
            {
                delete plugin;
            }
        }
    }
    return true;
}

void VidePluginManager::registerPluginInit(VidePluginInit* pluginInit)
{
    if (g_pluginInitList == NULL)
    {
        g_pluginInitList = new VidePluginInitList();
    }

    g_pluginInitList->inits.push_back(pluginInit);
}

VidePlugin* VidePluginManager::findPlugin(string name)
{
    for (VidePlugin* plugin : m_plugins)
    {
        if (plugin->getPluginName() == name)
        {
            return plugin;
        }
    }
    return NULL;
}

VidePlugin::VidePlugin(Vide* vide) : Logger(L"VidePlugin")
{
    m_vide = vide;
}

VidePlugin::~VidePlugin()
{
}

bool VidePlugin::init()
{
    return true;
}

bool VidePlugin::shutdown()
{
    return true;
}

