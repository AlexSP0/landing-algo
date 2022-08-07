#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum ACTIONS
{
    NOTHING      = 0,
    ROTATE_RIGHT = 1,
    ROTATE_LEFT  = 2,
    THRUST       = 3,
    ZERO         = 4
} ACTIONS;

const double THRUST_PER_SECOND   = 700.0;
const double ROTATION_PER_SECOND = 20.0;
const double GRAVITY             = -1.63;
const double SCALING_FACTOR      = 3;

#endif // CONSTANTS_H
