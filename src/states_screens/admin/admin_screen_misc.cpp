#include "main_loop.hpp"
#include "states_screens/admin/admin_screen_misc.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"
#include "config/stk_config.hpp"
#include "io/file_manager.hpp"
#include "audio/music_manager.hpp"
#include "items/attachment_manager.hpp"
#include "karts/kart_properties_manager.hpp"
#include "karts/kart_properties.hpp"
#include "modes/world.hpp"

extern void handleXmasMode();
extern void handleEasterEarMode();

extern AttachmentManager* attachment_manager;
extern KartPropertiesManager* kart_properties_manager;

using namespace GUIEngine;

AdminScreenMisc::AdminScreenMisc() : Screen("admin/admin_misc.stkgui") {}

void AdminScreenMisc::init()
{
    Screen::init();
    m_current_page = 1;
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_misc", PLAYER_ID_GAME_MASTER);
    }
    if (Widget* p1 = getWidget("page_1")) p1->setVisible(true);
    if (Widget* p2 = getWidget("page_2")) p2->setVisible(false);
    if (GUIEngine::SpinnerWidget* menu_music = getWidget<GUIEngine::SpinnerWidget>("menu_music"))
    {
        menu_music->m_properties[PROP_WRAP_AROUND] = "true";
        menu_music->clearLabels();
        menu_music->addLabel(core::stringw(_("0.8 - 1.5")));
        menu_music->addLabel(core::stringw(_("0.6 - 0.7")));
        menu_music->addLabel(core::stringw(_("0.4 - 0.5")));
        menu_music->m_properties[GUIEngine::PROP_MIN_VALUE] = "0";
        menu_music->m_properties[GUIEngine::PROP_MAX_VALUE] = "2";
        menu_music->setValue(UserConfigParams::m_menu_music_theme);
        menu_music->setTooltip(_("Allows you to switch between every\n"
								 "existing official menu theme."));
    }
    if (CheckBoxWidget* privacy = getWidget<CheckBoxWidget>("privacy_mode"))
    {
        privacy->setState(UserConfigParams::m_privacy_mode);
        privacy->setTooltip(_("Hides save paths shown when you record\n"
						"video, replay or screenshot."));
    }
    if (CheckBoxWidget* unlock = getWidget<CheckBoxWidget>("unlock_everything"))
	{
		unlock->setState(UserConfigParams::m_unlock_everything > 0);
		unlock->setTooltip(_("Unlock all karts, tracks and challenges."));
	}
	if (CheckBoxWidget* fps = getWidget<CheckBoxWidget>("fps_limit"))
	{
		fps->setState(UserConfigParams::m_disable_fps_limit);
		fps->setTooltip(_("If enabled, every frame will render as soon as it can."));
	}
	if (CheckBoxWidget* acc = getWidget<CheckBoxWidget>("accessories"))
	{
		acc->setState(UserConfigParams::m_disable_accessories);
		acc->setTooltip(_("Toggles accessories shown on Christmas and Easter."));
	}
	if (CheckBoxWidget* lap = getWidget<CheckBoxWidget>("lap_times"))
	{
		lap->setState(UserConfigParams::m_show_lap_times);
		lap->setTooltip(_("If enabled, best, last and current lap\n"
						  "time will be shown on screen."));
	}
	if (CheckBoxWidget* replay = getWidget<CheckBoxWidget>("replay_merge"))
	{
		replay->setState(UserConfigParams::m_allow_replay_merge);
		replay->setTooltip(_("Allows you to merge replays into one."));
	}
	if (LabelWidget* merge = getWidget<LabelWidget>("merge_label"))
	{
		merge->setColor(video::SColor(255, 0, 191, 255));
	}
	if (CheckBoxWidget* coord = getWidget<CheckBoxWidget>("show_coords"))
	{
		coord->setState(UserConfigParams::m_show_coordinates);
		coord->setTooltip(_("Shows your kart coorinates on screen."));
	}
	if (CheckBoxWidget* coord = getWidget<CheckBoxWidget>("highscores"))
	{
		coord->setState(UserConfigParams::m_no_high_scores);
		coord->setTooltip(_("If enabled, your time records will not be saved."));
	}
	if (GUIEngine::SpinnerWidget* ghost = getWidget<GUIEngine::SpinnerWidget>("ghost_opacity"))
    {
        ghost->setValue(UserConfigParams::m_replay_ghost_opacity);
        ghost->setTooltip(_("Adjusts opacity of ghosts in replays."));
    }
	if (World::getWorld())
    {
		getWidget<CheckBoxWidget>("accessories")->setActive(false);
		getWidget<GUIEngine::SpinnerWidget>("menu_music")->setActive(false);
	}
	else
	{
		getWidget<CheckBoxWidget>("accessories")->setActive(true);
		getWidget<GUIEngine::SpinnerWidget>("menu_music")->setActive(true);
	}
	updatePageIndicator();
    this->calculateLayout();
}

void AdminScreenMisc::updatePageIndicator()
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

void AdminScreenMisc::eventCallback(Widget* widget, const std::string& name, const int playerID)
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
        if (selection != "tab_misc") AdminCommon::switchTab(selection);
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
    else if (name == "menu_music")
	{
		UserConfigParams::m_menu_music_theme = ((GUIEngine::SpinnerWidget*)widget)->getValue();
		int val = UserConfigParams::m_menu_music_theme;
		if (stk_config)
		{
			if (music_manager)
			{
				music_manager->stopMusic();
				music_manager->startMusic(NULL); 
			}
			
			// NOTE: We intentionally don't 'delete' the old m_title_music here.
			// The SFXManager often tries to access it after 'deletion'.
			// A small memory leak is preferred over a race condition SEGFAULT.
			stk_config->m_title_music = NULL; 
	
			stk_config->initMusicFiles();
			
			if (music_manager && stk_config->m_title_music)
			{
				music_manager->startMusic(stk_config->m_title_music, true);
			}
		}
	}
	else if (name == "privacy_mode")
    {
		UserConfigParams::m_privacy_mode = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "unlock_everything")
	{
		bool active = ((CheckBoxWidget*)widget)->getState();
		UserConfigParams::m_unlock_everything = active ? 2 : 0;
	}
	else if (name == "fps_limit")
    {
		UserConfigParams::m_disable_fps_limit = ((CheckBoxWidget*)widget)->getState();
		main_loop->setThrottleFPS(!UserConfigParams::m_disable_fps_limit);
    }
    else if (name == "accessories")
    {
		bool is_enabled = ((CheckBoxWidget*)widget)->getState();
		UserConfigParams::m_xmas_mode = is_enabled ? 2 : 0;
		UserConfigParams::m_easter_ear_mode = is_enabled ? 2 : 0;
		UserConfigParams::m_disable_accessories = is_enabled;
		handleXmasMode();
		handleEasterEarMode();
	
		for (int i = 0; ; i++)
		{
			const KartProperties* const_props = kart_properties_manager->getKartById(i);
			if (!const_props) break;
			KartProperties* props = const_cast<KartProperties*>(const_props);
	
			std::string hat = "";
			if (!is_enabled) 
			{
				if (UserConfigParams::m_xmas_mode == 0) hat = "christmas_hat.spm";
				else if (UserConfigParams::m_easter_ear_mode == 0) hat = "easter_ears.spm";
			}
			
			props->setHatMeshName(hat); 
		}
    }
    else if (name == "lap_times")
    {
		UserConfigParams::m_show_lap_times = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "replay_merge")
    {
		UserConfigParams::m_allow_replay_merge = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "show_coords")
    {
		UserConfigParams::m_show_coordinates = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "highscores")
    {
		UserConfigParams::m_no_high_scores = ((CheckBoxWidget*)widget)->getState();
    }
    else if (name == "ghost_opacity")
    {
        UserConfigParams::m_replay_ghost_opacity = ((GUIEngine::SpinnerWidget*)widget)->getValue();
    }
}

void AdminScreenMisc::tearDown() { Screen::tearDown(); }
