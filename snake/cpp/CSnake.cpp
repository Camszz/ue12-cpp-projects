#include "CSnake.h"
#include <iostream>

void CSnake::deplacer()
{
    if (_direction == 0)
        _x++;
    else if (_direction == 1)
        _x--;
    else if (_direction == 2)
        _y++;
    else if (_direction == 3)
        _y--;
}



void CSnake::change_direction(int direction)
{
    _direction = direction;

}


int CSnake::get_x()
{
    return _x;

}

int CSnake::get_y()
{
    return _y;

}

int CSnake::get_direction()
{
    return _direction;

}

