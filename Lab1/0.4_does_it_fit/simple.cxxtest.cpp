#include <cxxtest/TestSuite.h>

#include "count_if_followed_by.h"


class MyTestSuite : public CxxTest::TestSuite {
  public:
    void test1 () {
      char const  data[6] = {'G','G','X','G','X','G'};
      int  const test_len = 4;

      int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

      // SYNOPSIS:
      //   result should be 1 since the length specified is 4,
      //   and only one pair of [X, G] is present in that range!

      TS_ASSERT_EQUALS(result, 1);
    }

    void test2 () {
      char const  data[4] = {'G','G','X','G'};
      int  const test_len = 3;

      int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

      // SYNOPSIS:
      //   result should be 0 since the length specified is 3,
      //   and no pairs of [X, G] are present in that range!

      TS_ASSERT_EQUALS(result, 0);
    }

    void test3 () {
      char const  data[4] = {'X','G','X','G'};
      int  const test_len = 4;

      int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

      // SYNOPSIS:
      //   result should be 2 since the length specified is 4,
      //   and two pairs of [X, G] are present in that range!

      TS_ASSERT_EQUALS(result, 2);
    }

    void test4 () {
      char const  data[4] = {'X','G','X','G'};
      int  const test_len = 2;

      int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

      // SYNOPSIS:
      //   result should be 1 since the length specified is 2,
      //   and one pair of [X, G] is present in that range!

      TS_ASSERT_EQUALS(result, 1);
    }
};
