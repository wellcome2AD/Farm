#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>
#include "actionEnum.h"
#include "animalEnum.h"

class Player : public QObject
{
    Q_OBJECT
    QMap<animalEnum, int> animals;
    bool antyfox_dog = false;
    bool antybear_dog = false;
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

    void FirstStage();
    void Exchange(actionEnum action);
    bool IsWin() const;

    const QMap<animalEnum, int>& GetAnimals();
    bool GetAntyfoxDog()  const;
    bool GetAntybearDog() const;
    void update();
signals:
    void playerUpdated();
};

#endif // PLAYER_H
