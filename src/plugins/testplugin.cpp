
#include "plugins/plugins.h"

#include <stdlib.h>

#include <string>

class TestPlugin : public VidePlugin
{
 public:
    TestPlugin(Vide* vide);
    virtual ~TestPlugin();

    virtual bool init();
};

VIDE_PLUGIN(TestPlugin);

TestPlugin::TestPlugin(Vide* vide) : VidePlugin(vide)
{
    printf("TestPlugin::TestPlugin: Here!\n");
}

TestPlugin::~TestPlugin()
{
    printf("TestPlugin::~TestPlugin: Here!\n");
}

bool TestPlugin::init()
{
    printf("TestPlugin::init: Here!\n");
    return true;
}

