#pragma once

#include "piece.h"

#include <iostream>

class j : public piece
{
    public:

        j();
        ~j();
        void rotate();
        void rotate_reverse();
};
