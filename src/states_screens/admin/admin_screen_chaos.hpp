#ifndef __HEADER_ADMIN_SCREEN_CHAOS_HPP__
#define __HEADER_ADMIN_SCREEN_CHAOS_HPP__

#include "guiengine/screen.hpp"

class AdminScreenChaos : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<AdminScreenChaos>
{
    AdminScreenChaos();
    friend class GUIEngine::ScreenSingleton<AdminScreenChaos>;

public:
    virtual void init() OVERRIDE;
    virtual void eventCallback(GUIEngine::Widget* widget, const std::string& name, const int playerID) OVERRIDE;
    virtual void tearDown() OVERRIDE;
    virtual void loadedFromFile() override {}
};

#endif
