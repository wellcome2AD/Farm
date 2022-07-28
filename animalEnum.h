#include <QString>

#ifndef ANIMALENUM_H
#define ANIMALENUM_H

enum animalEnum
{
    duck,
    goat,
    pig,
    horse,
    cow,
    fox,
    bear
};

inline QString animalEnumToQString(animalEnum type)
{
    switch (type)
    {
    case duck:
        return "duck";
    case goat:
        return "goat";
    case pig:
        return "pig";
    case horse:
        return "horse";
    case cow:
        return "cow";
    case fox:
        return "fox";
    case bear:
        return "bear";
    }
    return "error";
}

#endif // ANIMALENUM_H
