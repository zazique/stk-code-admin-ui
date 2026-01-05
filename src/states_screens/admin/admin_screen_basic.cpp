#include "states_screens/admin/admin_screen_basic.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"
#include "guiengine/widgets/label_widget.hpp"

using namespace GUIEngine;

AdminScreenBasic::AdminScreenBasic() : Screen("admin/admin_basic.stkgui") {}

void AdminScreenBasic::init()
{
    Screen::init();
    m_current_page = 1;
    bool active = UserConfigParams::m_display_inputs;
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_basic", PLAYER_ID_GAME_MASTER);
    }
	if (Widget* p1 = getWidget("page_1")) p1->setVisible(true);
    if (Widget* p2 = getWidget("page_2")) p2->setVisible(false);
    if (CheckBoxWidget* rename = getWidget<CheckBoxWidget>("allow_replay_rename"))
    {
        rename->setState(UserConfigParams::m_allow_rename_replay);
        rename->setTooltip(_("Allows you to rename replay files from in-game\n"
							 "menu, which will help you to found replay faster"));
    }
    if (LabelWidget* rnm = getWidget<LabelWidget>("rename_label"))
	{
		rnm->setColor(video::SColor(255, 0, 191, 255));
	}
    if (CheckBoxWidget* inputs = getWidget<CheckBoxWidget>("show_inputs"))
    {
        inputs->setState(UserConfigParams::m_display_inputs);
        inputs->setTooltip(_("Adds on-screen buttons that highlight your current\n"
                    "actions, such as drifting, using nitro, or accelerating.\n"
                    "Only active during races."));
    }
    if (LabelWidget* input = getWidget<LabelWidget>("input_label"))
	{
		input->setColor(video::SColor(255, 0, 191, 255));
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
    if (LabelWidget* dbg = getWidget<LabelWidget>("debug_label"))
	{
		dbg->setColor(video::SColor(255, 0, 191, 255));
	}
    if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("show_check"))
	{
		check->setState(UserConfigParams::m_check_debug);
		check->setTooltip(_("Displays track checklines.\n"
							"Originally these were only visible via Artist Debug mode."));
	}
	if (CheckBoxWidget* track = getWidget<CheckBoxWidget>("show_drive"))
	{
		track->setState(UserConfigParams::m_track_debug);
		track->setTooltip(_("Displays track driveline.\n"
							"Originally this are only visible via Artist Debug mode."));
	}
	if (CheckBoxWidget* start = getWidget<CheckBoxWidget>("fast_start"))
	{
		start->setState(UserConfigParams::m_fast_start);
		start->setTooltip(_("Disables the fast countdown when starting a race\n"
							"in Artist Debug mode with no other karts."));
	}
	if (LabelWidget* start = getWidget<LabelWidget>("start_label"))
	{
		start->setColor(video::SColor(255, 0, 191, 255));
	}
	if (CheckBoxWidget* start = getWidget<CheckBoxWidget>("restart_bind"))
	{
		start->setState(UserConfigParams::m_allow_restart_bind);
		start->setTooltip(_("Enables restart bind function.\n"
							"Bind can be configured in Controls settings."));
	}
	if (CheckBoxWidget* replay = getWidget<CheckBoxWidget>("record_replay"))
	{
		replay->setState(UserConfigParams::m_always_record_replay);
		replay->setTooltip(_("Always records replay in Time Trial mode.\n"
							"You can save replay on race result screen."));
	}
	if (CheckBoxWidget* check = getWidget<CheckBoxWidget>("checkpoints_btn"))
	{
		check->setState(UserConfigParams::m_allow_checkpoints);
		check->setTooltip(_("Enables checkpoint bind function, which allows\n"
							"you to create checkpoint to train part of the track.\n"
							"Bind can be configured in Controls settings."));
	}
	if (CheckBoxWidget* att = getWidget<CheckBoxWidget>("save_atts"))
	{
		att->setState(UserConfigParams::m_save_attempts);
		att->setTooltip(_("Allows game to save attempt count for tracks in\n"
						  "Time trial mode when you play alone."));
	}
	if (LabelWidget* att = getWidget<LabelWidget>("att_label"))
	{
		att->setColor(video::SColor(255, 0, 191, 255));
	}
    if (Widget* w = getWidget("input_overlay_size"))  w->setActive(active);
    if (Widget* w = getWidget("input_overlay_pos"))   w->setActive(active);
    if (Widget* w = getWidget("input_overlay_pos_y")) w->setActive(active);
    
    updatePageIndicator();
    
    this->calculateLayout();
}

void AdminScreenBasic::updatePageIndicator()
{
    if (LabelWidget* indicator = getWidget<LabelWidget>("page_indicator"))
    {
		indicator->setText(_("Page %d/%d", m_current_page, 2), false);
    }
    if (Widget* prev = getWidget("prev_page"))
        prev->setActive(m_current_page > 1);
        
    if (Widget* next = getWidget("next_page"))
        next->setActive(m_current_page < 2);
}

void AdminScreenBasic::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
	if (name == "next_page" && m_current_page < 2)
    {
        m_current_page = 2;
        if (Widget* p1 = getWidget("page_1")) p1->setVisible(false);
        if (Widget* p2 = getWidget("page_2")) p2->setVisible(true);
        updatePageIndicator();
        this->calculateLayout();
    }
    else if (name == "prev_page" && m_current_page > 1)
    {
        m_current_page = 1;
        if (Widget* p1 = getWidget("page_1")) p1->setVisible(true);
        if (Widget* p2 = getWidget("page_2")) p2->setVisible(false);
        updatePageIndicator();
        this->calculateLayout();
    }
    if (name == "admin_choice")
    {
        std::string selection = ((RibbonWidget*)widget)->getSelectionIDString(PLAYER_ID_GAME_MASTER);
        if (selection != "tab_basic") AdminCommon::switchTab(selection);
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
    else if (name == "allow_replay_rename")
    {
        UserConfigParams::m_allow_rename_replay = ((CheckBoxWidget*)widget)->getState();
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
    else if (name == "debug_mode")
    {
        UserConfigParams::m_artist_debug_mode = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "show_check")
    {
        UserConfigParams::m_check_debug = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "show_drive")
    {
        UserConfigParams::m_track_debug = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "fast_start")
    {
        UserConfigParams::m_fast_start = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "restart_bind")
    {
        UserConfigParams::m_allow_restart_bind = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "record_replay")
    {
        UserConfigParams::m_always_record_replay = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "checkpoints_btn")
    {
        UserConfigParams::m_allow_checkpoints = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "save_atts")
    {
        UserConfigParams::m_save_attempts = ((CheckBoxWidget*)widget)->getState();
    }
}

void AdminScreenBasic::tearDown() { Screen::tearDown(); }
