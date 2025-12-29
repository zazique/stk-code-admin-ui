#ifndef __HEADER_ADMIN_SCREEN_FUN_HPP__
#define __HEADER_ADMIN_SCREEN_FUN_HPP__

#include "guiengine/screen.hpp"

class AdminScreenFun : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<AdminScreenFun>
{
    AdminScreenFun();
    friend class GUIEngine::ScreenSingleton<AdminScreenFun>;

public:
    virtual void init() OVERRIDE;
    virtual void eventCallback(GUIEngine::Widget* widget, const std::string& name, const int playerID) OVERRIDE;
    virtual void tearDown() OVERRIDE;
    virtual void loadedFromFile() override {}
};

#endif
