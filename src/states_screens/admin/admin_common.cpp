#include "states_screens/admin/admin_common.hpp"
#include "guiengine/screen.hpp"
#include "states_screens/admin/admin_screen_basic.hpp"
#include "states_screens/admin/admin_screen_misc.hpp"
#include "states_screens/admin/admin_screen_fun.hpp"
#include "states_screens/admin/admin_screen_chaos.hpp"

namespace AdminCommon
{
    void switchTab(const std::string& tab)
	{
		GUIEngine::Screen *screen = NULL;

        if (tab == "tab_basic")
            screen = AdminScreenBasic::getInstance();
        else if (tab == "tab_misc")
            screen = AdminScreenMisc::getInstance();
        else if (tab == "tab_fun")
            screen = AdminScreenFun::getInstance();
        else if (tab == "tab_chaos")
            screen = AdminScreenChaos::getInstance();


        if (screen)
            StateManager::get()->replaceTopMostScreen(screen);
	}

    void setTabStatus()
    {
    }
}
