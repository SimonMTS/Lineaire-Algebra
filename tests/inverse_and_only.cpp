#include "../math/cMatrix.hpp"
#include "gtest/gtest.h"

TEST(inverse_and_only, rotation_inverse) {
  // 1 5 9  13
  // 2 6 10 14
  // 3 7 11 15
  // 4 8 12 16

  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = 1;
  s[0][1] = 5;
  s[0][2] = 9;
  s[0][3] = 13;
  s[1][0] = 2;
  s[1][1] = 6;
  s[1][2] = 10;
  s[1][3] = 14;
  s[2][0] = 3;
  s[2][1] = 7;
  s[2][2] = 11;
  s[2][3] = 15;
  s[3][0] = 4;
  s[3][1] = 8;
  s[3][2] = 12;
  s[3][3] = 16;

  cMatrix m(s);
  std::cout << m << "\n";

  m = cMatrix::RotationInverse(m);
  std::cout << m << "\n";

  ASSERT_EQ(m[0][0], s[0][0]);
  ASSERT_EQ(m[0][1], s[1][0]);
  ASSERT_EQ(m[0][2], s[2][0]);
  ASSERT_EQ(m[0][3], s[0][3]);

  ASSERT_EQ(m[1][0], s[0][1]);
  ASSERT_EQ(m[1][1], s[1][1]);
  ASSERT_EQ(m[1][2], s[2][1]);
  ASSERT_EQ(m[1][3], s[1][3]);

  ASSERT_EQ(m[2][0], s[0][2]);
  ASSERT_EQ(m[2][1], s[1][2]);
  ASSERT_EQ(m[2][2], s[2][2]);
  ASSERT_EQ(m[2][3], s[2][3]);

  ASSERT_EQ(m[3][0], s[3][0]);
  ASSERT_EQ(m[3][1], s[3][1]);
  ASSERT_EQ(m[3][2], s[3][2]);
  ASSERT_EQ(m[3][3], s[3][3]);
}

TEST(inverse_and_only, translation_inverse) {
  // 1 5 9  13
  // 2 6 10 14
  // 3 7 11 15
  // 4 8 12 16

  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = 1;
  s[0][1] = 5;
  s[0][2] = 9;
  s[0][3] = 13;
  s[1][0] = 2;
  s[1][1] = 6;
  s[1][2] = 10;
  s[1][3] = 14;
  s[2][0] = 3;
  s[2][1] = 7;
  s[2][2] = 11;
  s[2][3] = 15;
  s[3][0] = 4;
  s[3][1] = 8;
  s[3][2] = 12;
  s[3][3] = 16;

  cMatrix m(s);
  std::cout << m << "\n";

  m = cMatrix::TranslationInverse(m);
  std::cout << m << "\n";

  ASSERT_EQ(m[0][0], s[0][0]);
  ASSERT_EQ(m[0][1], s[0][1]);
  ASSERT_EQ(m[0][2], s[0][2]);
  ASSERT_EQ(m[0][3], -s[0][3]);
  ASSERT_EQ(m[1][0], s[1][0]);
  ASSERT_EQ(m[1][1], s[1][1]);
  ASSERT_EQ(m[1][2], s[1][2]);
  ASSERT_EQ(m[1][3], -s[1][3]);
  ASSERT_EQ(m[2][0], s[2][0]);
  ASSERT_EQ(m[2][1], s[2][1]);
  ASSERT_EQ(m[2][2], s[2][2]);
  ASSERT_EQ(m[2][3], -s[2][3]);
  ASSERT_EQ(m[3][0], s[3][0]);
  ASSERT_EQ(m[3][1], s[3][1]);
  ASSERT_EQ(m[3][2], s[3][2]);
  ASSERT_EQ(m[3][3], s[3][3]);
}

TEST(inverse_and_only, rotation_only) {
  // 1 5 9  13
  // 2 6 10 14
  // 3 7 11 15
  // 4 8 12 16

  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = 1;
  s[0][1] = 5;
  s[0][2] = 9;
  s[0][3] = 13;
  s[1][0] = 2;
  s[1][1] = 6;
  s[1][2] = 10;
  s[1][3] = 14;
  s[2][0] = 3;
  s[2][1] = 7;
  s[2][2] = 11;
  s[2][3] = 15;
  s[3][0] = 4;
  s[3][1] = 8;
  s[3][2] = 12;
  s[3][3] = 16;

  cMatrix m(s);
  std::cout << m << "\n";

  m = cMatrix::RotationOnly(m);
  std::cout << m << "\n";

  ASSERT_EQ(m[0][0], s[0][0]);
  ASSERT_EQ(m[0][1], s[0][1]);
  ASSERT_EQ(m[0][2], s[0][2]);
  ASSERT_EQ(m[0][3], 0);
  ASSERT_EQ(m[1][0], s[1][0]);
  ASSERT_EQ(m[1][1], s[1][1]);
  ASSERT_EQ(m[1][2], s[1][2]);
  ASSERT_EQ(m[1][3], 0);
  ASSERT_EQ(m[2][0], s[2][0]);
  ASSERT_EQ(m[2][1], s[2][1]);
  ASSERT_EQ(m[2][2], s[2][2]);
  ASSERT_EQ(m[2][3], 0);
  ASSERT_EQ(m[3][0], 0);
  ASSERT_EQ(m[3][1], 0);
  ASSERT_EQ(m[3][2], 0);
  ASSERT_EQ(m[3][3], s[3][3]);
}

TEST(inverse_and_only, translation_only) {
  // 1 5 9  13
  // 2 6 10 14
  // 3 7 11 15
  // 4 8 12 16

  vector<vector<double>> s(4, vector<double>(4, 0));

  s[0][0] = 1;
  s[0][1] = 5;
  s[0][2] = 9;
  s[0][3] = 13;
  s[1][0] = 2;
  s[1][1] = 6;
  s[1][2] = 10;
  s[1][3] = 14;
  s[2][0] = 3;
  s[2][1] = 7;
  s[2][2] = 11;
  s[2][3] = 15;
  s[3][0] = 4;
  s[3][1] = 8;
  s[3][2] = 12;
  s[3][3] = 16;

  cMatrix m(s);
  std::cout << m << "\n";

  m = cMatrix::TranslationOnly(m);
  std::cout << m << "\n";

  ASSERT_EQ(m[0][0], 1);
  ASSERT_EQ(m[0][1], 0);
  ASSERT_EQ(m[0][2], 0);
  ASSERT_EQ(m[0][3], s[0][3]);
  ASSERT_EQ(m[1][0], 0);
  ASSERT_EQ(m[1][1], 1);
  ASSERT_EQ(m[1][2], 0);
  ASSERT_EQ(m[1][3], s[1][3]);
  ASSERT_EQ(m[2][0], 0);
  ASSERT_EQ(m[2][1], 0);
  ASSERT_EQ(m[2][2], 1);
  ASSERT_EQ(m[2][3], s[2][3]);
  ASSERT_EQ(m[3][0], 0);
  ASSERT_EQ(m[3][1], 0);
  ASSERT_EQ(m[3][2], 0);
  ASSERT_EQ(m[3][3], 1);
}