#include "states_screens/admin/admin_screen_chaos.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"
#include "modes/world.hpp"

using namespace GUIEngine;

AdminScreenChaos::AdminScreenChaos() : Screen("admin/admin_chaos.stkgui") {}

void AdminScreenChaos::init()
{
    Screen::init();
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_chaos", PLAYER_ID_GAME_MASTER);
    }
    if (CheckBoxWidget* camera = getWidget<CheckBoxWidget>("camera_far_null"))
    {
        camera->setState(UserConfigParams::m_camera_far_reset);
        camera->setTooltip(_("Always sets camera distance to 0."));
    }
    if (CheckBoxWidget* bw = getWidget<CheckBoxWidget>("bw_shader"))
    {
        bw->setState(UserConfigParams::m_shader_bw);
        bw->setTooltip(_("If enabled, turns your game black-white.\n"
							 "Requires Advanced pipeline option enabled."));
    }
    if (CheckBoxWidget* neg = getWidget<CheckBoxWidget>("negative_shader"))
    {
        neg->setState(UserConfigParams::m_shader_inversion);
        neg->setTooltip(_("If enabled, inverts colors of the game.\n"
							 "Requires Advanced pipeline option enabled."));
    }
    if (CheckBoxWidget* dist = getWidget<CheckBoxWidget>("distortion_shader"))
    {
        dist->setState(UserConfigParams::m_shader_distortion);
        dist->setTooltip(_("If enabled, distorts the image on the screen.\n"
							 "Requires Advanced pipeline option enabled."));
    }
    if (CheckBoxWidget* dist = getWidget<CheckBoxWidget>("distortion_shader2"))
    {
        dist->setState(UserConfigParams::m_shader_distortion2);
        dist->setTooltip(_("If enabled, distorts the image on the screen.\n"
							 "Requires Advanced pipeline option enabled."));
    }
    if (World::getWorld())
    {
		getWidget<CheckBoxWidget>("camera_far_null")->setActive(false);
	}
	else
	{
		getWidget<CheckBoxWidget>("camera_far_null")->setActive(true);
	}
}


void AdminScreenChaos::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
    if (name == "admin_choice")
    {
        std::string selection = ((RibbonWidget*)widget)->getSelectionIDString(PLAYER_ID_GAME_MASTER);
        if (selection != "tab_chaos") AdminCommon::switchTab(selection);
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
    else if (name == "camera_far_null")
    {
		UserConfigParams::m_camera_far_reset = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "bw_shader")
    {
		UserConfigParams::m_shader_bw = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "negative_shader")
    {
		UserConfigParams::m_shader_inversion = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "distortion_shader")
    {
		UserConfigParams::m_shader_distortion = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "distortion_shader2")
    {
		UserConfigParams::m_shader_distortion2 = ((CheckBoxWidget*)widget)->getState();
    }
}

void AdminScreenChaos::tearDown() { Screen::tearDown(); }
