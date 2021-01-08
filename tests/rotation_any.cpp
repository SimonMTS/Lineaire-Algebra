#include "../math/cMatrix.hpp"
#include "../math/cVector.hpp"
#include "gtest/gtest.h"

TEST(rotation_matrix_axis_any, webdictaat_example) {
  cVector axis = cVector({10, 8, 6}).Normalized();
  int angle = 90;            // deg

  cMatrix m = cMatrix::GetRotationMatrix(axis, angle);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 1);
  ASSERT_EQ(round(m[0][1]), 1);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 0);
  ASSERT_EQ(round(m[1][2]), 1);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 1);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), 0);
  ASSERT_EQ(round(m[2][3]), 0);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), 0);
  ASSERT_EQ(round(m[3][3]), 1);
}

TEST(rotation_matrix_axis_any, x_90deg) {
  cVector axis = {1, 0, 0};  // x
  int angle = 90;            // deg

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

TEST(rotation_matrix_axis_any, x_45deg) {
  cVector axis = {1, 0, 0};  // x
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

TEST(rotation_matrix_axis_any, x_222deg) {
  cVector axis = {1, 0, 0};  // x
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

TEST(rotation_matrix_axis_any, y_90deg) {
  cVector axis = {0, -1, 0};  // y
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

TEST(rotation_matrix_axis_any, y_45deg) {
  cVector axis = {0, -1, 0};  // y
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

TEST(rotation_matrix_axis_any, y_222deg) {
  cVector axis = {0, -1, 0};  // y
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

TEST(rotation_matrix_axis_any, z_90deg) {
  cVector axis = {0, 0, -1};  // z
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

TEST(rotation_matrix_axis_any, z_45deg) {
  cVector axis = {0, 0, -1};  // z
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

TEST(rotation_matrix_axis_any, z_222deg) {
  cVector axis = {0, 0, -1};  // z
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
