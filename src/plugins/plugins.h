#ifndef __VIDE_PLUGIN_PLUGIN_H_
#define __VIDE_PLUGIN_PLUGIN_H_

#include <vector>
#include <string>

class Vide;
class VidePlugin;

class VidePluginInit
{
 private:

 public:
    VidePluginInit() {}
    virtual ~VidePluginInit() {}

    virtual VidePlugin* create(Vide* vide) { return NULL; }

    virtual const char* getName() { return ""; }
};

class VidePlugin
{
 private:
    Vide* m_vide;
    std::string m_pluginName;

 public:
    VidePlugin(Vide* vide);
    VidePlugin(Vide* vide, std::string pluginName);
    virtual ~VidePlugin();

    virtual void setPluginName(std::string name) { m_pluginName = name; }
    virtual std::string getPluginName() { return m_pluginName; }

    virtual bool init();
    virtual bool shutdown();

    Vide* getVide() { return m_vide; }
};

class VidePluginManager
{
 private:
    Vide* m_vide;

 public:
    static std::vector<VidePluginInit*> g_pluginInits;
    std::vector<VidePlugin*> m_plugins;

    VidePluginManager();
    ~VidePluginManager();

    bool init(Vide* vide);

    static void registerPluginInit(VidePluginInit* pluginInit);

    VidePlugin* findPlugin(std::string name);
};


#define VIDE_PLUGIN(_name)  \
    class _name##Init : public VidePluginInit \
    { \
     private: \
        static _name##Init* const init __attribute__ ((unused)); \
     public: \
        _name##Init() \
        { \
            VidePluginManager::registerPluginInit(this); \
        } \
        const char* getName() \
        { \
            return #_name; \
        } \
        _name* create(Vide* vide) \
        { \
            return new _name(vide); \
        } \
    }; \
    _name##Init* const _name##Init::init = new _name##Init();

#endif
