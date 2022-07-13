#include "exchangebutton.h"

ExchangeButton::ExchangeButton(const QIcon &icon, const QString& text, QWidget* parent)
    : QPushButton(parent)
{
    installEventFilter(this);
    setIcon(icon);
    setIconSize(size());
    setToolTip(text);
}
