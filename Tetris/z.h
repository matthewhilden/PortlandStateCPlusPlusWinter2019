#pragma once

#include "piece.h"

#include <iostream>

class z : public piece
{
    public:

            z();
            ~z();
            void rotate();
            void rotate_reverse();
};
