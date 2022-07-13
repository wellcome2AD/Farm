#ifndef EXCHANGEBUTTON_H
#define EXCHANGEBUTTON_H

#include <QPushButton>

class ExchangeButton : public QPushButton
{
    Q_OBJECT
public:
    ExchangeButton(const QIcon &icon, const QString& text, QWidget* parent = nullptr);
};

#endif // EXCHANGEBUTTON_H
