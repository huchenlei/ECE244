//
// Created by CharlieHu on 2016-11-26.
//

#ifndef LAB6_POLYGON_H
#define LAB6_POLYGON_H


#include "easygl_constants.h"
#include "Triangle.h"

class Polygon : public Shape {
private:
    t_point *polVertex;
    int nPoint;

    t_point getVecBetweenPoints(t_point start, t_point end) const;

    float getDistanceBetweenPoints(t_point start, t_point end) const;

    t_point computeCenter();

    // cross product of vector(p1,p2) and (p1, p3)
    float crossArea(t_point p1, t_point p2, t_point p3) const;

public:
    Polygon(string _name, string _colour, t_point *tPoints, int nPoint);

    virtual ~Polygon();

    virtual void print() const;

    virtual void scale(float scaleFac);

    virtual float computeArea() const;

    virtual float computePerimeter() const;

    virtual void draw(easygl *window) const;

    virtual bool pointInside(float x, float y) const;


};


#endif //LAB6_POLYGON_H
