#include <QRandomGenerator>
#include <QDebug>
#include "player.h"
#include "dicegenerator.h"
Player::Player()
{
    animals.insert(animalEnum::duck, 1);
    animals.insert(animalEnum::goat, 0);
    animals.insert(animalEnum::pig, 0);
    animals.insert(animalEnum::horse, 0);
    animals.insert(animalEnum::cow, 0);
}
void Player::getCards(QPair<animalEnum, animalEnum> cards)
{
    qDebug() << "cards were get";
    if(cards.first == cards.second)
    {
        animals[cards.first] += 1 + animals[cards.first] / 2;
    }
    else
    {
        if(animals.find(cards.first) == animals.end())
        {
            bearEatsAnimals();
        }
        else //to do: think how to get rid of code duplication
        {
            animals[cards.first] += (animals[cards.first] + 1) / 2; // if odd then card makes an additional pair
        }
        if(animals.find(cards.second) == animals.end())
        {
            foxEatsAnimals();
        }
        else
        {
            animals[cards.second] += (animals[cards.second] + 1) / 2; // if odd then card makes an additional pair
        }
    }
}
bool Player::foxEatsAnimals()
{
    bool smth_changed = false;
    if(antyfox_dog)
    {
        antyfox_dog = false;
        smth_changed = true;
    }
    else if(animals[duck] > 1 || animals[goat] != 0)
    {
        animals[duck] = 1;
        animals[goat] = 0;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::bearEatsAnimals()
{
    bool smth_changed = false;
    if(antybear_dog)
    {
        antybear_dog = false;
        smth_changed = true;
    }
    else if(animals[pig] != 0 || animals[horse] != 0 || animals[cow] != 0)
    {
        animals[pig] = animals[horse] = animals[cow] = 0;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::DucksToGoat ()
{
    bool smth_changed = false;
    if(animals[duck] >= 6)
    {
        animals[goat] += 1;
        animals[duck] -= 6;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::GoatsToPig  ()
{
    bool smth_changed = false;
    if(animals[goat] >= 2)
    {
        animals[pig] += 1;
        animals[goat] -= 2;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::PigsToHorse ()
{
    bool smth_changed = false;
    if(animals[pig] >= 3)
    {
        animals[horse] += 1;
        animals[pig] -= 3;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::HorsesToCow ()
{
    bool smth_changed = false;
    if(animals[horse] >= 2)
    {
        animals[cow] += 1;
        animals[horse] -= 2;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::GoatToDog   ()
{
    bool smth_changed = false;
    if(animals[goat] >= 1 && antyfox_dog == false)
    {
        antyfox_dog = true;
        animals[goat] -= 1;
        smth_changed = true;
    }
    return smth_changed;
}
bool Player::HorseToDog  ()
{
    bool smth_changed = false;
    if(animals[horse] >= 1 && antybear_dog == false)
    {
        antybear_dog = true;
        animals[horse] -= 1;
        smth_changed = true;
    }
    return smth_changed;
}
void Player::FirstStage()
{
    QPair<animalEnum, animalEnum> cards = DiceGenerator::GetDice().GetResult();
    qDebug() << "cards: " + animalEnumToQString(cards.first) + " " + animalEnumToQString(cards.second);
    getCards(cards);
    update();
}
void Player::Exchange(actionEnum action)
{
    bool result = false;    
    switch (action)
    {
    case changeDucksToGoat:
    {       
        result = DucksToGoat();
        break;
    }
    case changeGoatsToPig:
    {
        result = GoatsToPig();
        break;
    }
    case changePigsToHorse:
    {
        result = PigsToHorse();
        break;
    }
    case changeHorsesToCow:
    {
        result = HorsesToCow();
        break;
    }
    case changeGoatToDog:
    {
        result = GoatToDog();
        break;
    }
    case changeHorseToDog:
    {
        result = HorseToDog();
        break;
    }
    }
    if(result)
    {
        update();
        qDebug() << "signal was sent"; // when goat is changed to dog, widget isn't repainted
    }
}
bool Player::IsWin() const
{
    return animals[duck] && animals[goat] && animals[pig] && animals[horse] && animals[cow];
}
int Player::GetDucks()  const
{
    return animals[duck];
}
int Player::GetGoats()  const
{
    return animals[goat];
}
int Player::GetPigs()   const
{
    return animals[pig];
}
int Player::GetHorses() const
{
    return animals[horse];
}
int Player::GetCows() const
{
    return animals[cow];
}
bool Player::GetAntyfoxDog()  const
{
    return antyfox_dog;
}
bool Player::GetAntybearDog() const
{
    return antybear_dog;
}
void Player::update()
{
  emit playerUpdated();
}
