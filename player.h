#ifndef PLAYER_H
#define PLAYER_H

#include <QPair>
#include <QMap>
#include "actionEnum.h"
#include "animalEnum.h"

class Player
{
    QMap<animalEnum, size_t> animals;
    bool antyfox_dog = false;
    bool antybear_dog = false;
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
