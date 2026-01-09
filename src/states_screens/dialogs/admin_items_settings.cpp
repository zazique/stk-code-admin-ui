#include "states_screens/dialogs/admin_items_settings.hpp"
#include "config/user_config.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "utils/translation.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "items/powerup_manager.hpp"
#include "guiengine/message_queue.hpp"
#include "utils/string_utils.hpp"

using namespace GUIEngine;

AdminItemsSettingsDialog::AdminItemsSettingsDialog(const float w, const float h) :
    ModalDialog(w, h)
{
    loadFromFile("admin_item_settings.stkgui");
    updateActivation();
}

AdminItemsSettingsDialog::~AdminItemsSettingsDialog()
{
}

void AdminItemsSettingsDialog::beforeAddingWidgets()
{
    getWidget<CheckBoxWidget>("enable_powerup_sel")->setState(UserConfigParams::m_enable_powerup_sel);
    
    const char* items[] = {
        "item_bubblegum", "item_zipper", "item_cake", "item_plunger", 
        "item_bowling", "item_parachute", "item_swapper", 
        "item_basketball", "item_swatter", "item_anvil"
    };

    getWidget<CheckBoxWidget>("item_bubblegum")->setState(UserConfigParams::m_item_bubblegum);
    getWidget<CheckBoxWidget>("item_zipper")->setState(UserConfigParams::m_item_zipper);
    getWidget<CheckBoxWidget>("item_cake")->setState(UserConfigParams::m_item_cake);
    getWidget<CheckBoxWidget>("item_plunger")->setState(UserConfigParams::m_item_plunger);
    getWidget<CheckBoxWidget>("item_bowling")->setState(UserConfigParams::m_item_bowling);
    getWidget<CheckBoxWidget>("item_parachute")->setState(UserConfigParams::m_item_parachute);
    getWidget<CheckBoxWidget>("item_swapper")->setState(UserConfigParams::m_item_swapper);
    getWidget<CheckBoxWidget>("item_basketball")->setState(UserConfigParams::m_item_basketball);
    getWidget<CheckBoxWidget>("item_swatter")->setState(UserConfigParams::m_item_swatter);
    getWidget<CheckBoxWidget>("item_anvil")->setState(UserConfigParams::m_item_anvil);
}

void AdminItemsSettingsDialog::updateActivation()
{
    bool active = getWidget<CheckBoxWidget>("enable_powerup_sel")->getState();

    const char* items[] = {
        "item_bubblegum", "item_zipper", "item_cake", "item_plunger", 
        "item_bowling", "item_parachute", "item_swapper", 
        "item_basketball", "item_swatter", "item_anvil"
    };

    for (const char* id : items)
    {
        getWidget<CheckBoxWidget>(id)->setActive(active);
    }
}

GUIEngine::EventPropagation AdminItemsSettingsDialog::processEvent(const std::string& eventSource)
{
    if (eventSource == "enable_powerup_sel")
    {
        updateActivation();
    }
    else if (eventSource == "buttons")
    {
        const std::string& selection = getWidget<RibbonWidget>("buttons")->
                                    getSelectionIDString(PLAYER_ID_GAME_MASTER);

        if (selection == "apply")
        {
            UserConfigParams::m_enable_powerup_sel = getWidget<CheckBoxWidget>("enable_powerup_sel")->getState();
			bool any_selected = 
				getWidget<CheckBoxWidget>("item_bubblegum")->getState() ||
				getWidget<CheckBoxWidget>("item_cake")->getState()      ||
				getWidget<CheckBoxWidget>("item_bowling")->getState()   ||
				getWidget<CheckBoxWidget>("item_zipper")->getState()    ||
				getWidget<CheckBoxWidget>("item_plunger")->getState()   ||
				getWidget<CheckBoxWidget>("item_swapper")->getState()   ||
				getWidget<CheckBoxWidget>("item_swatter")->getState()   ||
				getWidget<CheckBoxWidget>("item_basketball")->getState()||
				getWidget<CheckBoxWidget>("item_parachute")->getState() ||
				getWidget<CheckBoxWidget>("item_anvil")->getState();
			if (!any_selected && UserConfigParams::m_enable_powerup_sel)
			{
				MessageQueue::discardStatic();
				MessageQueue::add(MessageQueue::MT_ERROR, 
                _("No powerups selected! Game will crash if you try to collect a powerup."));
				return GUIEngine::EVENT_BLOCK;
			}
			UserConfigParams::m_item_bubblegum = getWidget<CheckBoxWidget>("item_bubblegum")->getState();
			UserConfigParams::m_item_cake      = getWidget<CheckBoxWidget>("item_cake")->getState();
			UserConfigParams::m_item_bowling   = getWidget<CheckBoxWidget>("item_bowling")->getState();
			UserConfigParams::m_item_zipper    = getWidget<CheckBoxWidget>("item_zipper")->getState();
			UserConfigParams::m_item_plunger   = getWidget<CheckBoxWidget>("item_plunger")->getState();
			UserConfigParams::m_item_swapper   = getWidget<CheckBoxWidget>("item_swapper")->getState();
			UserConfigParams::m_item_swatter   = getWidget<CheckBoxWidget>("item_swatter")->getState();
			UserConfigParams::m_item_basketball= getWidget<CheckBoxWidget>("item_basketball")->getState();
			UserConfigParams::m_item_parachute = getWidget<CheckBoxWidget>("item_parachute")->getState();
			UserConfigParams::m_item_anvil     = getWidget<CheckBoxWidget>("item_anvil")->getState();
            powerup_manager->reloadConfig();
            ModalDialog::dismiss();
            return GUIEngine::EVENT_BLOCK;
        }
        else if (selection == "cancel")
        {
            ModalDialog::dismiss();
            return GUIEngine::EVENT_BLOCK;
        }
    }
    return GUIEngine::EVENT_LET;
}
