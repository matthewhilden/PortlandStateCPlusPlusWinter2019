#pragma once

#include "piece.h"

#include <iostream>

class s : public piece
{
    public:

        s();
        ~s();
        void rotate();
        void rotate_reverse();
};
