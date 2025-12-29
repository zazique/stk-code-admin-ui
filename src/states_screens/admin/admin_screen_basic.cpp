#include "states_screens/admin/admin_screen_basic.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "config/user_config.hpp"

using namespace GUIEngine;

AdminScreenBasic::AdminScreenBasic() : Screen("admin/admin_basic.stkgui") {}

void AdminScreenBasic::init()
{
    Screen::init();
    bool active = UserConfigParams::m_display_inputs;
    // Выделяем текущую вкладку в меню слева
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        // Сначала даем фокус, потом выбираем вкладку
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_basic", PLAYER_ID_GAME_MASTER);
    }
    if (CheckBoxWidget* inputs = getWidget<CheckBoxWidget>("show_inputs"))
    {
        inputs->setState(UserConfigParams::m_display_inputs);
    }
    if (GUIEngine::SpinnerWidget* size = getWidget<GUIEngine::SpinnerWidget>("input_overlay_size"))
    {
        size->setValue(UserConfigParams::m_input_overlay_size);
    }
    if (GUIEngine::SpinnerWidget* pos_x = getWidget<GUIEngine::SpinnerWidget>("input_overlay_pos"))
    {
        pos_x->setValue(UserConfigParams::m_input_overlay_offset);
    }

    if (GUIEngine::SpinnerWidget* pos_y = getWidget<GUIEngine::SpinnerWidget>("input_overlay_pos_y"))
    {
        pos_y->setValue(UserConfigParams::m_input_overlay_offset_y);
    }
    if (CheckBoxWidget* debug = getWidget<CheckBoxWidget>("debug_mode"))
    {
        debug->setState(UserConfigParams::m_artist_debug_mode);
    }
    if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("show_check"))
	{
		check->setState(UserConfigParams::m_check_debug);
	}
	if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("fast_start"))
	{
		check->setState(UserConfigParams::m_fast_start);
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
}

void AdminScreenBasic::tearDown() { Screen::tearDown(); }
