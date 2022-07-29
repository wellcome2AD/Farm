#ifndef DICEGENERATOR_H
#define DICEGENERATOR_H
#include <QVector>
#include <QPair>
#include <QRandomGenerator>
#include "animalEnum.h"

class DiceGenerator
{
    const QVector<animalEnum> die1{ duck, duck, duck, duck, duck, duck, goat, goat, goat, bear, pig, horse};
    const QVector<animalEnum> die2{ duck, duck, duck, duck, duck, duck, goat, goat, pig, pig, fox, cow};
    size_t num1, num2;
private:
    DiceGenerator(){}
    DiceGenerator(const DiceGenerator& root) = delete;
    DiceGenerator& operator=(const DiceGenerator&) = delete;
public:
    static DiceGenerator& GetDice()
    {
        static DiceGenerator single;
        return single;
    }
    void ThrowDice()
    {
        num1 = QRandomGenerator::global()->bounded(1, 13);
        num2 = QRandomGenerator::global()->bounded(1, 13);
    }
    QPair<animalEnum, animalEnum> GetResult()
    {
        return QPair<animalEnum, animalEnum>(die1.at(num1), die2.at(num2));
    }
};

#endif // DICEGENERATOR_H
