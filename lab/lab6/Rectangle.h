//
// Created by CharlieHu on 2016-11-26.
//

#ifndef LAB6_RECTANGLE_H
#define LAB6_RECTANGLE_H


#include "Shape.h"

class Rectangle : public Shape {
private:
    float width;
    float height;
public:
    Rectangle(string _name, string _colour, float _xcen, float _ycen, float _width, float _height);

    virtual ~Rectangle();

    virtual void print() const;

    virtual void scale(float scaleFac);

    virtual float computeArea() const;

    virtual float computePerimeter() const;

    virtual void draw(easygl *window) const;

    virtual bool pointInside(float x, float y) const;
};


#endif //LAB6_RECTANGLE_H
