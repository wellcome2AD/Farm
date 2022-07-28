#include "exchangebutton.h"

ExchangeButton::ExchangeButton(const QIcon &icon, const QString& text, QWidget* parent)
    : QPushButton(parent)
{
    installEventFilter(this);
    setMinimumSize(90, 30);
    setIcon(icon);
    setIconSize(minimumSize());
    setToolTip(text);
}
