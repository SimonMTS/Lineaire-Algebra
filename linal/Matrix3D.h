#pragma once
#include <cmath> 
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using std::vector;

class Matrix3D {
private:
    vector<vector<double>> State;

public:
    Matrix3D(vector<vector<double>> state);

    static Matrix3D GetTranslationMatrix(const double x, const double y, const double z);
    static Matrix3D GetScalingMatrix(const double x, const double y, const double z);
    static Matrix3D GetRotationMatrix(const int axis, const double angle);
    static Matrix3D GetProjectionMatrix(const double near, const double far, const double fovy);

    vector<double> operator[] (int i);
    auto begin() const { return State.begin(); }
    auto end() const { return State.end(); }
    auto size() const { return State.size(); }

    Matrix3D operator-(Matrix3D m);
    Matrix3D operator+(Matrix3D m);
    Matrix3D operator*(int i);
    Matrix3D operator*(Matrix3D m);
};

