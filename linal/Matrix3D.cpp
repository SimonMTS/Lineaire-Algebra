#include "Matrix3D.h"

Matrix3D::Matrix3D(vector<vector<double>> state) : State(state) { }

Matrix3D Matrix3D::GetTranslationMatrix(const double x, const double y, const double z) {
    vector<vector<double>> s(4, vector<double>(4, 0));
    s[0][0] = 1.0;
    s[1][1] = 1.0;
    s[2][2] = 1.0;
    s[3][3] = 1.0;

    s[0][3] = x;
    s[1][3] = y;
    s[2][3] = z;

    return Matrix3D(s);
}

Matrix3D Matrix3D::GetScalingMatrix(const double x, const double y, const double z) {
    vector<vector<double>> s(4, vector<double>(4, 0));
    s[0][0] = x;
    s[1][1] = y;
    s[2][2] = z;

    s[3][3] = 1.0;

    return Matrix3D(s);
}

Matrix3D Matrix3D::GetRotationMatrix(const double angle) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    return Matrix3D(s);
}

vector<double> Matrix3D::operator[](int i) {
    return State.at(i);
}

Matrix3D Matrix3D::operator-(Matrix3D m) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    for (int i = 0; i < (*this).size(); i++) {
        for (int j = 0; j < (*this)[i].size(); j++) {
            s[i][j] = (*this).State[i][j] - m[i][j];
        }
    }

    return Matrix3D(s);
}

Matrix3D Matrix3D::operator+(Matrix3D m) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    for (int i = 0; i < (*this).size(); i++) {
        for (int j = 0; j < (*this)[i].size(); j++) {
            s[i][j] = (*this).State[i][j] + m[i][j];
        }
    }

    return Matrix3D(s);
}

Matrix3D Matrix3D::operator*(int i) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    for (int i = 0; i < (*this).size(); i++) {
        for (int j = 0; j < (*this)[i].size(); j++) {
            s[i][j] = (*this).State[i][j] * i;
        }
    }

    return Matrix3D(s);
}

Matrix3D Matrix3D::operator*(Matrix3D m) {
    vector<vector<double>> s(4, vector<double>(4, 0));

    for (int i = 0; i < (*this).size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            s[i][j] = (*this)[i][0] * m[0][j] + 
                        (*this)[i][1] * m[1][j] + 
                        (*this)[i][2] * m[2][j] + 
                        (*this)[i][3] * m[3][j];
        }
    }

    return Matrix3D(s);
}
