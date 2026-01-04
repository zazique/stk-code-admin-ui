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

using namespace GUIEngine;

AdminScreenMisc::AdminScreenMisc() : Screen("admin/admin_misc.stkgui") {}

void AdminScreenMisc::init()
{
    Screen::init();
    
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_misc", PLAYER_ID_GAME_MASTER);
    }
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
}

void AdminScreenMisc::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
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
}

void AdminScreenMisc::tearDown() { Screen::tearDown(); }
