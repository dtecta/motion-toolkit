#include <gtest/gtest.h>


GTEST_API_ int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  
  int result = RUN_ALL_TESTS();
  return result;
}
