#include <QRandomGenerator>
#include "player.h"
Player::Player()
{
    animals.insert(animalEnum::duck, 1);
    animals.insert(animalEnum::goat, 0);
    animals.insert(animalEnum::pig, 0);
    animals.insert(animalEnum::horse, 0);
    animals.insert(animalEnum::cow, 0);
}
QPair<animalEnum, animalEnum> Player::throwDice()
{
    static constexpr animalEnum die1[12] = { duck, duck, duck, duck, duck, duck, goat, goat, goat, bear, pig, horse};
    static constexpr animalEnum die2[12] = { duck, duck, duck, duck, duck, duck, goat, goat, pig, pig, fox, cow};
    size_t num1 = QRandomGenerator::global()->bounded(1, 13);
    size_t num2 = QRandomGenerator::global()->bounded(1, 13);
    return QPair<animalEnum, animalEnum>(die1[num1], die2[num2]); // to do: is it normal?
}
void Player::getCards(QPair<animalEnum, animalEnum> cards)
{
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
            animals[cards.first] += (animals[cards.first] + 1) / 2; // if odd then card makes an additional pair
        }
    }
}
bool Player::foxEatsAnimals()
{
    if(animals[duck] == 0 && animals[goat] == 0)
    {
        return false;
    }
    if(antyfox_dog)
    {
        antyfox_dog = false;
    }
    else
    {
        if(animals[duck] != 0)
        {
            animals[duck] = 1;
        }
        animals[goat] = 0;
    }
    return true;
}
bool Player::bearEatsAnimals()
{
    if(animals[pig] == 0 && animals[horse] == 0 && animals[cow] == 0)
    {
        return false;
    }
    if(antybear_dog)
    {
        antybear_dog = false;
    }
    else
    {
        animals[pig] = animals[horse] = animals[cow] = 0;
    }
    return true;
}
bool Player::DucksToGoat ()
{
    if(animals[duck] >= 6)
    {
        animals[goat] += 1;
        animals[duck] -= 6;
        return true;
    }
    return false;
}
bool Player::GoatsToPig  ()
{
    if(animals[goat] >= 2)
    {
        animals[pig] += 1;
        animals[goat] -= 2;
        return true;
    }
    return false;
}
bool Player::PigsToHorse ()
{
    if(animals[pig] >= 3)
    {
        animals[horse] += 1;
        animals[pig] -= 3;
        return true;
    }
    return false;
}
bool Player::HorsesToCow ()
{
    if(animals[horse] >= 2)
    {
        animals[cow] += 1;
        animals[horse] -= 2;
    }
    return false;
}
bool Player::GoatToDog   ()
{
    if(animals[goat] >= 1)
    {
        antyfox_dog = true;
        animals[goat] -= 1;
    }
    return false;
}
bool Player::HorseToDog  ()
{
    if(animals[horse] >= 1)
    {
        antybear_dog = true;
        animals[horse] -= 1;
    }
    return false;
}
bool Player::FirstStage()
{
    QPair<animalEnum, animalEnum> cards = throwDice();
    getCards(cards);
    return true;
}
bool Player::Exchange(actionEnum action)
{
    switch (action)
    {
    case changeDucksToGoat:
    {
        DucksToGoat();
        break;
    }
    case changeGoatsToPig:
    {
        GoatsToPig();
        break;
    }
    case changePigsToHorse:
    {
        PigsToHorse();
        break;
    }
    case changeHorsesToCow:
    {
        HorsesToCow();
        break;
    }
    case changeGoatToDog:
    {
        GoatToDog();
        break;
    }
    case changeHorseToDog:
    {
        HorseToDog();
        break;
    }
    }
}
bool Player::Win()
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
int Player::GetCows()   const
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
