#ifndef HEADER_ADMIN_ITEMS_SETTINGS_HPP
#define HEADER_ADMIN_ITEMS_SETTINGS_HPP

#include "guiengine/modaldialog.hpp"
#include <string>

class AdminItemsSettingsDialog : public GUIEngine::ModalDialog
{
public:
    AdminItemsSettingsDialog(const float percentWidth, const float percentHeight);
    virtual ~AdminItemsSettingsDialog();

    virtual void beforeAddingWidgets();
    void updateActivation();
    virtual GUIEngine::EventPropagation processEvent(const std::string& eventSource);
};

#endif
