#include "states_screens/admin/admin_screen_misc.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/spinner_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/string_utils.hpp"
#include "config/user_config.hpp"

using namespace GUIEngine;

AdminScreenMisc::AdminScreenMisc() : Screen("admin/admin_misc.stkgui") {}

void AdminScreenMisc::init()
{
    Screen::init();
    
    // Выделяем текущую вкладку в меню слева
    RibbonWidget* tabs = getWidget<RibbonWidget>("admin_choice");
    if (tabs) 
    {
        // Сначала даем фокус, потом выбираем вкладку
        tabs->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        tabs->select("tab_misc", PLAYER_ID_GAME_MASTER);
    }

    // Пример: устанавливаем состояние галочки (пока просто в лог или память)
    CheckBoxWidget* check = getWidget<CheckBoxWidget>("test_checkbox3");
    if (check) 
    {
		check->setState(false); 
		check->setTooltip(_("Not yet implemented."));
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
    else if (name == "test_checkbox2")
    {
        CheckBoxWidget* check = (CheckBoxWidget*)widget;
        // Тут будет твоя логика, когда галочку нажали
        // printf("Checkbox state: %d\n", check->getState());
    }
}

void AdminScreenMisc::tearDown() { Screen::tearDown(); }
