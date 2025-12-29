#ifndef __HEADER_ADMIN_SCREEN_MISC_HPP__
#define __HEADER_ADMIN_SCREEN_MISC_HPP__

#include "guiengine/screen.hpp"

class AdminScreenMisc : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<AdminScreenMisc>
{
    AdminScreenMisc();
    friend class GUIEngine::ScreenSingleton<AdminScreenMisc>;

public:
    virtual void init() OVERRIDE;
    virtual void eventCallback(GUIEngine::Widget* widget, const std::string& name, const int playerID) OVERRIDE;
    virtual void tearDown() OVERRIDE;
    virtual void loadedFromFile() override {}
};

#endif
