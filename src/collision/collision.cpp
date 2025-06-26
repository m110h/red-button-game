#include "collision.h"

/**
    \ ����������� 2-� �����������
*/
bool CircleCollision(hgeVector c1, hgeVector c2, float r1, float r2) {
    if ( sqrtf(powf(c2.x - c1.x, 2) + powf(c2.y - c1.y, 2)) < r1 + r2 )
        return true;

    return false;
}
