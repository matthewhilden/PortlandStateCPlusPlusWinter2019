#pragma once

#include "piece.h"

#include <iostream>

class t : public piece
{
    public:

        t();
        ~t();
        void rotate();
        void rotate_reverse();
};
