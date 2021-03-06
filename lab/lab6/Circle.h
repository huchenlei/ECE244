//
// Created by CharlieHu on 2016-11-26.
//

#ifndef LAB6_CIRCLE_H
#define LAB6_CIRCLE_H


#include "Shape.h"

class Circle : public Shape {
private:
    float radius;
public:
    Circle(string _name, string _colour, float _xcen, float _ycen, float _raidus);

    virtual ~Circle();

    virtual void print() const;

    virtual void scale(float scaleFac);

    virtual float computeArea() const;

    virtual float computePerimeter() const;

    virtual void draw(easygl *window) const;

    virtual bool pointInside(float x, float y) const;

};


#endif //LAB6_CIRCLE_H
