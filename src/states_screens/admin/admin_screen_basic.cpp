#include "states_screens/admin/admin_screen_basic.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"

using namespace GUIEngine;

AdminScreenBasic::AdminScreenBasic() : Screen("admin/admin_basic.stkgui") {}

void AdminScreenBasic::init()
{
    Screen::init();
    bool active = UserConfigParams::m_display_inputs;
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_basic", PLAYER_ID_GAME_MASTER);
    }
    if (CheckBoxWidget* inputs = getWidget<CheckBoxWidget>("show_inputs"))
    {
        inputs->setState(UserConfigParams::m_display_inputs);
        inputs->setTooltip(_("Adds on-screen buttons that highlight your current\n"
                    "actions, such as drifting, using nitro, or accelerating.\n"
                    "Only active during races."));
    }
    if (GUIEngine::SpinnerWidget* size = getWidget<GUIEngine::SpinnerWidget>("input_overlay_size"))
    {
        size->setValue(UserConfigParams::m_input_overlay_size);
        size->setTooltip(_("Adjusts the scale of the input overlay buttons."));
    }
    if (GUIEngine::SpinnerWidget* pos_x = getWidget<GUIEngine::SpinnerWidget>("input_overlay_pos"))
    {
        pos_x->setValue(UserConfigParams::m_input_overlay_offset);
        pos_x->setTooltip(_("Adjusts the horizontal of the input overlay buttons.\n"
							"Negative values move it left, positive values move it right."));
    }

    if (GUIEngine::SpinnerWidget* pos_y = getWidget<GUIEngine::SpinnerWidget>("input_overlay_pos_y"))
    {
        pos_y->setValue(UserConfigParams::m_input_overlay_offset_y);
        pos_y->setTooltip(_("Adjusts the horizontal of the input overlay buttons.\n"
							"Negative values move it left, positive values move it right."));
    }
    if (CheckBoxWidget* debug = getWidget<CheckBoxWidget>("debug_mode"))
    {
        debug->setState(UserConfigParams::m_artist_debug_mode);
        debug->setTooltip(_("Enables the built-in Artist Debug mode.\n"
							"Use it to test tracks or just explore."));
    }
    if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("show_check"))
	{
		check->setState(UserConfigParams::m_check_debug);
		check->setTooltip(_("Displays track checklines.\n"
							"Originally these were only visible via Artist Debug mode."));
	}
	if (CheckBoxWidget* start = getWidget<CheckBoxWidget>("fast_start"))
	{
		start->setState(UserConfigParams::m_fast_start);
		start->setTooltip(_("Disables the fast countdown when starting a race\n"
							"in Artist Debug mode with no other karts."));
	}
	if (CheckBoxWidget* start = getWidget<CheckBoxWidget>("restart_bind"))
	{
		start->setState(UserConfigParams::m_allow_restart_bind);
		start->setTooltip(_("Enables restart bind function.\n"
							"Bind can be configured in Controls settings."));
	}
    if (Widget* w = getWidget("input_overlay_size"))  w->setActive(active);
    if (Widget* w = getWidget("input_overlay_pos"))   w->setActive(active);
    if (Widget* w = getWidget("input_overlay_pos_y")) w->setActive(active);
}

void AdminScreenBasic::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
    if (name == "admin_choice")
    {
        std::string selection = ((RibbonWidget*)widget)->getSelectionIDString(PLAYER_ID_GAME_MASTER);
        if (selection != "tab_basic") AdminCommon::switchTab(selection);
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
    else if (name == "show_inputs")
    {
        bool active = ((CheckBoxWidget*)widget)->getState();
        UserConfigParams::m_display_inputs = active;
			
		if (Widget* w = getWidget("input_overlay_size"))  w->setActive(active);
		if (Widget* w = getWidget("input_overlay_pos"))   w->setActive(active);
		if (Widget* w = getWidget("input_overlay_pos_y")) w->setActive(active);
    }
    else if (name == "input_overlay_size")
    {
        UserConfigParams::m_input_overlay_size = ((GUIEngine::SpinnerWidget*)widget)->getValue();
    }
    else if (name == "input_overlay_pos")
    {
        UserConfigParams::m_input_overlay_offset = ((GUIEngine::SpinnerWidget*)widget)->getValue();
    }
    else if (name == "input_overlay_pos_y")
    {
        UserConfigParams::m_input_overlay_offset_y = ((GUIEngine::SpinnerWidget*)widget)->getValue();
    }
    if (name == "debug_mode")
    {
        UserConfigParams::m_artist_debug_mode = ((CheckBoxWidget*)widget)->getState();
    }
    if (name == "show_check")
    {
        UserConfigParams::m_check_debug = ((CheckBoxWidget*)widget)->getState();
    }
    if (name == "fast_start")
    {
        UserConfigParams::m_fast_start = ((CheckBoxWidget*)widget)->getState();
    }
    if (name == "restart_bind")
    {
        UserConfigParams::m_allow_restart_bind = ((CheckBoxWidget*)widget)->getState();
    }
}

void AdminScreenBasic::tearDown() { Screen::tearDown(); }
