#ifndef __ADMIN_SCREEN_HPP__
#define __ADMIN_SCREEN_HPP__

#include <string>
#include "guiengine/screen.hpp"

namespace GUIEngine { class Widget; }

/**
 * \brief Админ-панель по образцу настроек
 */
class AdminScreen : public GUIEngine::Screen, public GUIEngine::ScreenSingleton<AdminScreen>
{
    // Дружественный класс, чтобы Singleton мог вызвать приватный конструктор
    friend class GUIEngine::ScreenSingleton<AdminScreen>;

    AdminScreen();
    bool m_inited;

public:
    /** Вызывается при загрузке XML */
    virtual void loadedFromFile() OVERRIDE;

    /** Обработка кликов */
    virtual void eventCallback(GUIEngine::Widget* widget, const std::string& name,
                               const int playerID) OVERRIDE;

    /** Инициализация при открытии */
    virtual void init() OVERRIDE;

    /** Очистка при закрытии */
    virtual void tearDown() OVERRIDE;

    /** Выгрузка из памяти */
    virtual void unloaded() OVERRIDE;

private:
    void switchAdminTab(const std::string& tab_name);
};

#endif
