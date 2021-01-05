// Copyright 2020 Nikita Klimov nik179804@gmail.com

#include <gtest/gtest.h>

#include <Analysis.hpp>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(Analysis, testFuncPrint) {
  Analysis A("/home/starich/STARICHDED/SEM3/LAB34-REW/tests//TestID");
  ASSERT_EQ(A.printAccount(A.getPathToAccount(0), 1).str(),
            "broker: ib       account: 00100003 files: 1   lastdate: 20181017");
}

TEST(Analysis, testOverload) {
  std::ostringstream output;
  Analysis A("/home/starich/STARICHDED/SEM3/LAB34-REW/tests//TestID");
  output << A;
  EXPECT_EQ(
      output.str(),
      R"(broker: ib       account: 00100001 files: 3   lastdate: 20180903
broker: ib       account: 00100003 files: 3   lastdate: 20181017
broker: bcs      account: 00122223 files: 1   lastdate: 20180904
)");
}
