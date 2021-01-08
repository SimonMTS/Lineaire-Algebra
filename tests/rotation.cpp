#include "../math/cVector.hpp"
#include "../math/cMatrix.hpp"
#include "gtest/gtest.h"

TEST(rotation_matrix_axis_aligned, x_90deg) {
  int axis = 1; // x
  int angle = 90; // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 0);
  ASSERT_EQ(round(m[1][2]), 1);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), -1);
  ASSERT_EQ(round(m[2][2]), 0);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, x_45deg) {
  int axis = 1;    // x
  int angle = 45;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 1);
  ASSERT_EQ(round(m[1][2]), 1);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), -1);
  ASSERT_EQ(round(m[2][2]), 1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, x_222deg) {
  int axis = 1;    // x
  int angle = 222;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), -1);
  ASSERT_EQ(round(m[1][2]), -1);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), 1);
  ASSERT_EQ(round(m[2][2]), -1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, y_90deg) {
  int axis = 2;    // y
  int angle = 90;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 0);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 1);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 1);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), -1);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 0);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, y_45deg) {
  int axis = 2;    // y
  int angle = 45;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 1);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 1);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), -1);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, y_222deg) {
  int axis = 2;     // y
  int angle = 222;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), -1);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), -1);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 1);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 1);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), -1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, z_90deg) {
  int axis = 3;    // z
  int angle = 90;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 0);
  ASSERT_EQ(round(m[0][1]), -1);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 1);
  ASSERT_EQ(round(m[1][1]), 0);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, z_45deg) {
  int axis = 3;    // z
  int angle = 45;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), -1);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 1);
  ASSERT_EQ(round(m[1][1]), 1);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_aligned, z_222deg) {
  int axis = 3;     // z
  int angle = 222;  // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), -1);
  ASSERT_EQ(round(m[0][1]), 1);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), -1);
  ASSERT_EQ(round(m[1][1]), -1);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 1);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}
