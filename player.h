#ifndef PLAYER_H
#define PLAYER_H

#include <QPair>
#include <QMap>
#include "actionEnum.h"
#include "animalEnum.h"

class Player
{
    QMap<animalEnum, int> animals;
    bool antyfox_dog = true;
    bool antybear_dog = true;
private:
    //--first stage--
    static QPair<animalEnum, animalEnum> throwDice();
private:
    //--first stage--
    void getCards(QPair<animalEnum, animalEnum> cards);
    bool foxEatsAnimals();
    bool bearEatsAnimals();

    //--exchange--
    bool DucksToGoat ();
    bool GoatsToPig  ();
    bool PigsToHorse ();
    bool HorsesToCow ();
    bool GoatToDog   ();
    bool HorseToDog  ();
public:
    Player();
    ~Player() = default;

    bool FirstStage();
    bool Exchange(actionEnum action);
    bool Win();

    int GetDucks()  const;
    int GetGoats()  const;
    int GetPigs()   const;
    int GetHorses() const;
    int GetCows()   const;
    bool GetAntyfoxDog()  const;
    bool GetAntybearDog() const;
};

#endif // PLAYER_H
