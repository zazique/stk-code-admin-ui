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
    if (CheckBoxWidget* camera = getWidget<CheckBoxWidget>("camera_far_null"))
    {
        camera->setState(UserConfigParams::m_camera_far_reset);
        camera->setTooltip(_("Always sets camera distance to 0."));
    }
    if (CheckBoxWidget* hue = getWidget<CheckBoxWidget>("kart_hue"))
    {
        hue->setState(UserConfigParams::m_fun_rainbow_kart);
        hue->setTooltip(_("Enables rainbow kart color change.\n"
						"(NOTE: this feature woks only for karts\n"
						"where it is implemented)"));
    }
    if (CheckBoxWidget* jump = getWidget<CheckBoxWidget>("jump_bind"))
    {
        jump->setState(UserConfigParams::m_allow_jump_bind);
        jump->setTooltip(_("Enables jump bind function, which\n"
						   "gives ability to jump like in older STK versions.\n"
						   "Bind can be configured in Controls settings."));
    }
    if (CheckBoxWidget* jump = getWidget<CheckBoxWidget>("jump_mode"))
    {
        jump->setState(UserConfigParams::m_jump_mode);
        jump->setTooltip(_("If enabled, jump height scales from speed."));
    }
    if (CheckBoxWidget* rescue = getWidget<CheckBoxWidget>("disable_rescue"))
    {
        rescue->setState(UserConfigParams::m_disable_auto_rescue);
        rescue->setTooltip(_("Bird cannot rescue you automatically if enabled."));
    }
    if (CheckBoxWidget* power = getWidget<CheckBoxWidget>("infinite_powerup"))
    {
        power->setState(UserConfigParams::m_infinite_powerup);
        power->setTooltip(_("If enabled, you can use same powerup infinitely."));
    }
    if (Widget* w = getWidget("jump_mode")) w->setActive(UserConfigParams::m_allow_jump_bind);
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
    else if (name == "camera_far_null")
    {
		UserConfigParams::m_camera_far_reset = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "kart_hue")
    {
		UserConfigParams::m_fun_rainbow_kart = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "jump_bind")
    {
		UserConfigParams::m_allow_jump_bind = ((CheckBoxWidget*)widget)->getState();
		if (Widget* w = getWidget("jump_mode")) w->setActive(UserConfigParams::m_allow_jump_bind);
    }
    else if (name == "jump_mode")
    {
		UserConfigParams::m_jump_mode = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "disable_rescue")
    {
		UserConfigParams::m_disable_auto_rescue = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "infinite_powerup")
    {
		UserConfigParams::m_infinite_powerup = ((CheckBoxWidget*)widget)->getState();
    }
}

void AdminScreenFun::tearDown() { Screen::tearDown(); }
