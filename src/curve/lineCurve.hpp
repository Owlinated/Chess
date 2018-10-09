#ifndef LINECURVE_H
#define LINECURVE_H

#define GLM_FORCE_RADIANS

#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/gl.h>
#include "curve.hpp"

class LineCurve : public Curve{
    public:
    LineCurve(float radius = .2f);
    virtual vector<vec2> InterpolatedPoints(int resolution = 10) override;
    virtual vec2 InterpolatedPoint(float value) override;
    virtual vector<vec2> InterpolatedTangents() override;
    virtual vec2 InterpolatedTangent(float value) override;

    protected:
    float _radius;

    private:
};


#endif // LINECURVE_H