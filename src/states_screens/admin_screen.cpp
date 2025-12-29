#include "states_screens/admin_screen.hpp"
#include "states_screens/admin/admin_common.hpp"
#include "states_screens/state_manager.hpp"
#include "guiengine/widgets/ribbon_widget.hpp"
#include "states_screens/admin/admin_screen_basic.hpp"
#include "states_screens/admin/admin_screen_misc.hpp"
#include "states_screens/admin/admin_screen_fun.hpp"
#include <iostream>

using namespace GUIEngine;

// Конструктор: путь к твоему XML
AdminScreen::AdminScreen() : Screen("admin/admin_basic.stkgui")
{
    m_inited = false;
}

void AdminScreen::loadedFromFile()
{
    m_inited = false;
}

void AdminScreen::init()
{
    Screen::init();

    // 2. Получаем инстанс Basic экрана
    GUIEngine::Screen* screen = AdminScreenBasic::getInstance();
    
    if (screen)
    {
        // 3. Заменяем текущий пустой AdminScreen на AdminScreenBasic
        StateManager::get()->replaceTopMostScreen(screen);
    }

    AdminCommon::setTabStatus();
}

void AdminScreen::eventCallback(Widget* widget, const std::string& name, const int playerID)
{
    if (name == "admin_choice") // Имя Ribbon-виджета в XML
    {
        std::string selection = ((RibbonWidget*)widget)->getSelectionIDString(PLAYER_ID_GAME_MASTER);

        // Если выбрали не ту вкладку, на которой мы сейчас — переключаем!
        if (!selection.empty())
        {
             AdminCommon::switchTab(selection);
        }
    }
    else if (name == "back")
    {
        StateManager::get()->escapePressed();
    }
}

void AdminScreen::switchAdminTab(const std::string& tab_name)
{
    if (Widget* title = getWidget("tab_title"))
    {
        irr::core::stringw wideText = irr::core::stringw("ADMIN: ") + irr::core::stringw(tab_name.c_str());
        title->setText(wideText);
    }
}

void AdminScreen::tearDown()
{
    Screen::tearDown();
}

void AdminScreen::unloaded()
{
    m_inited = false;
}
