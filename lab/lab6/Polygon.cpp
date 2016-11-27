//
// Created by CharlieHu on 2016-11-26.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "Polygon.h"

Polygon::Polygon(string _name, string _colour, t_point *tPoints, int nPoint)
        : Shape(_name, _colour, 0, 0), nPoint(nPoint) {
    polVertex = new t_point[nPoint];
    for (int i = 0; i < nPoint; ++i) {
        polVertex[i] = tPoints[i];
    }
    // compute and set center
    t_point center = computeCenter();
    setXcen(center.x);
    setYcen(center.y);
}

Polygon::~Polygon() {
    delete[] polVertex;
}

void Polygon::print() const {
    Shape::print();
    cout << "Polygon";
    for (int i = 0; i < nPoint; ++i) {
        cout << " (" << polVertex[i].x << ","
             << polVertex[i].y << ")";
    }
    cout << endl;
}

void Polygon::scale(float scaleFac) {
    for (int i = 0; i < nPoint; i++) {
        polVertex[i].x = (polVertex[i].x - getXcen()) * scaleFac + getXcen();
        polVertex[i].y = (polVertex[i].y - getYcen()) * scaleFac + getYcen();
    }
}

float Polygon::computeArea() const {
    float result = 0;
    for (int i = 1; i < nPoint - 1; ++i)
        result += crossArea(polVertex[0], polVertex[i], polVertex[i + 1]);
    return abs(result);
}

float Polygon::computePerimeter() const {
    float result = 0;
    for (int i = 0; i < nPoint - 1; ++i)
        result += getDistanceBetweenPoints(polVertex[i], polVertex[i + 1]);
    return result + getDistanceBetweenPoints(polVertex[0], polVertex[nPoint - 1]);
}

void Polygon::draw(easygl *window) const {
    window->gl_setcolor(getColour());
    window->gl_fillpoly(polVertex, nPoint);
}

bool Polygon::pointInside(float x, float y) const {
    // if crossArea is negative -> clockwise
    float area = 0;
    for (int i = 1; i < nPoint - 1; ++i)
        area += crossArea(polVertex[0], polVertex[i], polVertex[i + 1]);
    int sign = area > 0 ? 1 : -1;
    // if the point is in at least 1 sub-triangle with positive crossArea
    // and is not in all sub-triangle with negative crossArea, it is considered
    // as in the polygon
    bool inPos = false, inNeg = false;
    for (int i = 1; i < nPoint - 1; ++i) {
        float area = sign * crossArea(polVertex[0], polVertex[i], polVertex[i + 1]);
        t_point tPoints[3] = {polVertex[0], polVertex[i], polVertex[i + 1]};
        bool insideTri = Triangle("null", "null", tPoints).pointInside(x, y);
        if(inPos == false) inPos = insideTri && (area > 0);
        if(inNeg == false) inNeg = insideTri && (area < 0);
    }
    return inPos && (!inNeg);
}

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints(t_point start, t_point end) const {
    t_point vec;
    vec.x = end.x - start.x;
    vec.y = end.y - start.y;
    return (vec);
}

float Polygon::getDistanceBetweenPoints(t_point start, t_point end) const {
    t_point point = getVecBetweenPoints(start, end);
    return sqrt(point.x * point.x + point.y * point.y);
}

t_point Polygon::computeCenter() {
    float totalArea = 0;
    float totalAreaTimesX = 0;
    float totalAreaTimesY = 0;
    for (int i = 1; i < nPoint - 1; ++i) {
        float area = crossArea(polVertex[0], polVertex[i], polVertex[i + 1]);
        totalArea += area;
        // reuse code in Triangle
        t_point tPoints[3] = {polVertex[0], polVertex[i], polVertex[i + 1]};
        Triangle tri("null", "red", tPoints);
        totalAreaTimesX += area * tri.getXcen();
        totalAreaTimesY += area * tri.getYcen();
    }
    t_point result;
    result.x = totalAreaTimesX / totalArea;
    result.y = totalAreaTimesY / totalArea;
    return result;
}

float Polygon::crossArea(t_point p1, t_point p2, t_point p3) const {
    float v1x = p2.x - p1.x;
    float v1y = p2.y - p1.y;
    float v2x = p3.x - p1.x;
    float v2y = p3.y - p1.y;
    return (v1x * v2y - v1y * v2x) / 2;
}
