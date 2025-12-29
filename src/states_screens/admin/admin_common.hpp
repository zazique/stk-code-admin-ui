#ifndef __HEADER_ADMIN_COMMON_HPP__
#define __HEADER_ADMIN_COMMON_HPP__

// По аналогии с options_common: базовые конфиги и виджеты
#include "config/user_config.hpp"
#include "guiengine/widgets/button_widget.hpp"
#include "guiengine/widgets/check_box_widget.hpp"
#include "guiengine/widgets/ribbon_widget.hpp" 
#include "guiengine/widgets/label_widget.hpp"

// Сюда будем добавлять инклуды новых вкладок
#include "states_screens/admin_screen.hpp" // Твой текущий экран (как General)

#include "states_screens/state_manager.hpp"
#include "utils/translation.hpp"

namespace AdminCommon
{
    void switchTab(const std::string& selected_tab);
    void setTabStatus();
}

#endif
