#ifndef TGTSMLPLATFORMINPUTCONTEXT_H
#define TGTSMLPLATFORMINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>
#include "keyboardform.h"

class TgtsmlPlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    TgtsmlPlatformInputContext();
    ~TgtsmlPlatformInputContext();

    bool isValid() const Q_DECL_OVERRIDE;
    void setFocusObject(QObject *object) Q_DECL_OVERRIDE;
    void showInputPanel() Q_DECL_OVERRIDE;
    void hideInputPanel() Q_DECL_OVERRIDE;
    bool isInputPanelVisible() const Q_DECL_OVERRIDE;

private:
    void sendKeyToFocusItem(const QString &keytext);

    KeyboardForm *m_keyboard;
    QObject *m_focusitem;
};

#endif // TGTSMLPLATFORMINPUTCONTEXT_H
