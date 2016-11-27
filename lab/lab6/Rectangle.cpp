//
// Created by CharlieHu on 2016-11-26.
//

#include "Rectangle.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height)
        : Shape(_name, _colour, _xcen, _ycen), width(_width), height(_height) {}

Rectangle::~Rectangle() {
    // no dynamic memory to delete
}

void Rectangle::print() const {
    Shape::print();
    cout << "rectangle "<< setprecision(1) << fixed;
    cout << "width: " << width;
    cout << " height: " << height;
    cout << endl;
}

void Rectangle::scale(float scaleFac) {
    width *= scaleFac;
    height *= scaleFac;
}

float Rectangle::computeArea() const {
    return width * height;
}

float Rectangle::computePerimeter() const {
    return 2 * (width + height);
}

void Rectangle::draw(easygl *window) const {
    float x1 = getXcen() - width / 2;
    float y1 = getYcen() - height / 2;
    float x2 = getXcen() + width / 2;
    float y2 = getYcen() + height / 2;
    window->gl_setcolor(getColour());
    window->gl_fillrect(x1, y1, x2, y2);
}

bool Rectangle::pointInside(float x, float y) const {
    float click_x = x - getXcen();
    float click_y = y - getXcen();
    return abs(click_x) < width / 2 && abs(click_y) < height / 2;
}

