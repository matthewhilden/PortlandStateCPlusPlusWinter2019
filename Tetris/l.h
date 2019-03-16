#pragma once

#include "piece.h"

#include <iostream>

class l : public piece
{
    public:

        l();
        ~l();
        void rotate();
        void rotate_reverse();
};
