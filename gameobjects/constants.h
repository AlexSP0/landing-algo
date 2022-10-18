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

struct LandingPad
{
    int xBegin;
    int xEnd;
    int height;

    LandingPad()
        : xBegin(0)
        , xEnd()
        , height(0)
    {}

    LandingPad(int xb, int xe, int h)
        : xBegin(xb)
        , xEnd(xe)
        , height(h)
    {}
};

const double THRUST_PER_SECOND   = 700.0;
const double ROTATION_PER_SECOND = 20.0;
const double GRAVITY             = -1.63;
const double SCALING_FACTOR      = 3;

const double MUTATION_RATE  = 0.05;
const double MUTATION_DELTA = 0.000001;

const int WINDOW_SIZE_X      = 600;
const int WINDOW_SIZE_Y      = 600;
const int LANDING_PAD_X      = 100;
const int LANDING_PAD_WIDTH  = 30;
const int LANDING_PAD_HEIGHT = 10;

const int NUMBER_GENES_IN_GENOME       = 539;
const int NUMBER_LANDERS_IN_GENERATION = 200;
const int NUMBER_GENERATION_BY_EPOCH   = 50;
const int TOTAL_EPOCHS                 = 1000;

const double SUCCESS_ROTATION_MAX     = 0.5;
const double SUCCESS_VERTICAL_SPEED   = 2;
const double SUCCESS_HORIZONTAL_SPEED = 0.5;
const double SUCCESS_HEIGHT           = 3;

#endif // CONSTANTS_H
