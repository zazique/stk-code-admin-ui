#ifndef __HEADER_ADMIN_SCREEN_BASIC_HPP__
#define __HEADER_ADMIN_SCREEN_BASIC_HPP__

#include "guiengine/screen.hpp"

class AdminScreenBasic : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<AdminScreenBasic>
{
    AdminScreenBasic();
    friend class GUIEngine::ScreenSingleton<AdminScreenBasic>;

public:
    virtual void init() OVERRIDE;
    virtual void eventCallback(GUIEngine::Widget* widget, const std::string& name, const int playerID) OVERRIDE;
    virtual void tearDown() OVERRIDE;
    virtual void loadedFromFile() override {}
};

#endif
