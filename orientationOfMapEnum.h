#include <QString>

#ifndef ORIENTATIONOFMAPENUM_H
#define ORIENTATIONOFMAPENUM_H

enum orientationOfMapEnum
{
    left_side_map, right_side_map
};

inline QString orientationOfMapEnumToQString(orientationOfMapEnum type)
{
    switch (type)
    {
    case left_side_map:
        return "left_side_map";
    case right_side_map:
        return "right_side_map";
    }
    return "error";
}

#endif // ORIENTATIONOFMAPENUM_H
