//
// Created by CharlieHu on 2016-11-26.
//

#include <cmath>
#include <iostream>
#include <iomanip>
#include "Circle.h"

Circle::Circle(string _name, string _colour, float _xcen, float _ycen, float _raidus)
        : Shape(_name, _colour, _xcen, _ycen), radius(_raidus) {}

void Circle::print() const {
    Shape::print();
    cout << "circle " << setprecision(1) << fixed;
    cout << "radius: " << radius << endl;
}

Circle::~Circle() {}

void Circle::scale(float scaleFac) {
    radius *= scaleFac;
}

float Circle::computeArea() const {
    return (float) (radius * radius * PI);
}

float Circle::computePerimeter() const {
    return (float) (2 * radius * PI);
}

void Circle::draw(easygl *window) const {
    window->gl_setcolor(getColour());
    window->gl_fillellipticarc(getXcen(), getYcen(), radius, radius, 0, 360);
}

bool Circle::pointInside(float x, float y) const {
    float relativeX = x - getXcen();
    float relativeY = y -getYcen();
    float distance = sqrt(relativeX * relativeX + relativeY * relativeY);
    return distance < radius;
}
