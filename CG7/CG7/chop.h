#ifndef CHOP_H
#define CHOP_H

#include "paintdata.h"
#include <vector>

const unsigned char LEFT = 0x01;
const unsigned char RIGHT = 0x02;
const unsigned char BOTTOM = 0x04;
const unsigned char TOP = 0x08;

const unsigned char ZERO = 0x00;

struct line_info {
    unsigned char p1;
    unsigned char p2;

    line_info()
    {
        p1 = ZERO;
        p2 = ZERO;
    }

    line_info(QLine& line, QRect& border)
    {
        p1 = ZERO;
        p2 = ZERO;

        //left|right
        if (line.x1() < border.left()) {
            p1 |= LEFT;
        }
        else if (line.x1() > border.right()) {
            p1 |= RIGHT;
        }
        if (line.x2() < border.left()) {
            p2 |= LEFT;
        }
        else if (line.x2() > border.right()) {
            p2 |= RIGHT;
        }
        //bottom|top
        if (line.y1() < border.bottom()) {
            p1 |= BOTTOM;
        }
        else if (line.y1() > border.top()) {
            p1 |= TOP;
        }
        if (line.y2() < border.bottom()) {
            p2 |= BOTTOM;
        }
        else if (line.y2() > border.top()) {
            p2 |= TOP;
        }
    }

    bool fully_invisible()
    {
        return (p1 & p2) != ZERO;
    }

    bool fully_visible()
    {
        return (p1 | p2) == ZERO;
    }
};

void chop(Paintdata& data);

std::vector<line_info> form_info(Paintdata& data);

#endif // CHOP_H
