#include "states_screens/admin/admin_screen_fun.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"

using namespace GUIEngine;

AdminScreenFun::AdminScreenFun() : Screen("admin/admin_fun.stkgui") {}

void AdminScreenFun::init()
{
    Screen::init();
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_fun", PLAYER_ID_GAME_MASTER);
    }
    if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("show_powerup_msg"))
    {
        check->setState(UserConfigParams::m_show_powerup_msg);
        check->setTooltip(_("Enables classic STK 0.7-style messages when powerups are used. \n"
                            "Includes updated messages for modern powerups."));
    }
}

void AdminScreenFun::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
    if (name == "admin_choice")
    {
        std::string selection = ((RibbonWidget*)widget)->getSelectionIDString(PLAYER_ID_GAME_MASTER);
        if (selection != "tab_fun") AdminCommon::switchTab(selection);
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
    else if (name == "show_powerup_msg")
    {
		UserConfigParams::m_show_powerup_msg = ((CheckBoxWidget*)widget)->getState();
    }
}

void AdminScreenFun::tearDown() { Screen::tearDown(); }
