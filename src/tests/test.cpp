#include <gtest/gtest.h>

#include "../Model/model.h"

TEST(TestList, test_calc_1) {
  std::string eq =
      "15.0/(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0))*15.0/"
      "(7.0-(200.0+1.0))*3.0-(2.0+(1.0+1.0))*(15.0/"
      "(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0))+15.0/"
      "(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0)))\0";
  double result = 15.0 / (7.0 - (1.0 + 1.0)) * 3.0 -
                  (2.0 + (1.0 + 1.0)) * 15.0 / (7.0 - (200.0 + 1.0)) * 3.0 -
                  (2.0 + (1.0 + 1.0)) *
                      (15.0 / (7.0 - (1.0 + 1.0)) * 3.0 - (2.0 + (1.0 + 1.0)) +
                       15.0 / (7.0 - (1.0 + 1.0)) * 3.0 - (2.0 + (1.0 + 1.0)));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_2) {
  std::string eq = "sqrt(3)-1/2*sin(3^2-2)\0";
  double result = sqrt(3.0) - 1.0 / 2.0 * sin(pow(3.0, 2.0) - 2.0);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_3) {
  std::string eq = "sqrt(3+2*(1-cos(77)^2))\0";
  double result = sqrt(3.0 + 2.0 * (1.0 - pow(cos(77.0), 2.0)));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_4) {
  std::string eq = "tan(0.0)\0";
  double result = tan(0.0);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_5) {
  std::string eq = "ln(-1.0)\0";
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::ERROR);
}

TEST(TestList, test_calc_6) {
  std::string eq = "20/0\0";
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::INF);
}

TEST(TestList, test_calc_7) {
  std::string eq = "sqrt(-1.0)\0";
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::ERROR);
}

TEST(TestList, test_calc_8) {
  std::string eq = "cos(3*pi*e)\0";
  double result = cos(3 * M_PI * M_E);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_9) {
  std::string eq = "asin(3*x/pi)\0";
  double result = asin(3 * 0.85 / M_PI);
  awfl::Model test(0.85, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_10) {
  std::string eq = "log(94%3.2321321)\0";
  double result = log10(fmod(94, 3.2321321));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_11) {
  std::string eq = "acos(3*x/pi)\0";
  double result = acos(3 * 0.85 / M_PI);
  awfl::Model test(0.85, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_12) {
  std::string eq = "atan(3*x/pi)\0";
  double result = atan(3 * 0.85 / M_PI);
  awfl::Model test(0.85, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_13) {
  std::string eq = "tan(pi/2)\0";
  double result = tan(M_PI / 2);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_14) {
  std::string eq = "pi+2.43243243232312312+cos(sin(tan(99)))";
  double result = M_PI + 2.43243243232312312 + cos(sin(tan(99.0)));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_15) {
  std::string eq = "sin(120)*cos(90) * atan(asin(acos(sqrt(231321.0))))";
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::ERROR);
}

TEST(TestList, test_calc_16) {
  std::string eq = "37.383682*sqrt(log(38.16))*cos(cos(128)*sin(90))";
  double result = 37.383682 * sqrt(log10(38.16)) * cos(cos(128.0) * sin(90.0));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_17) {
  std::string eq = "ln(ln(ln(ln(368291.0))))*sqrt(sqrt(sqrt(sqrt(17352936))))";
  double result =
      log(log(log(log(368291.0)))) * sqrt(sqrt(sqrt(sqrt(17352936.0))));
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_18) {
  std::string eq = "1/tan(100)/tan(75)/tan(50)/tan(25)";
  double result = 1.0 / tan(100.0) / tan(75.0) / tan(50.0) / tan(25.0);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_19) {
  std::string eq = "sin(29)/sin(29)";
  double result = sin(29.0) / sin(29.0);
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

TEST(TestList, test_calc_20) {
  std::string eq = "1.4543534e-3+2.4534543e+1";
  double result = 1.4543534e-3 + 2.4534543e+1;
  awfl::Model test(0.0, eq);
  std::pair<int, long double> res = test.calculateReversePN();
  ASSERT_EQ(res.first, awfl::OK);
  ASSERT_EQ(res.second, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
