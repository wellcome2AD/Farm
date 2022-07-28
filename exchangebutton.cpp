#include "exchangebutton.h"

ExchangeButton::ExchangeButton(const QIcon &icon, const QString& text, QWidget* parent)
    : QPushButton(parent)
{
    installEventFilter(this);
    setMinimumSize(100, 40);
    setIcon(icon);
    setIconSize(minimumSize());
    setToolTip(text);
}
