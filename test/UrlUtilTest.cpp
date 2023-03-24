#include "UrlUtil.h"

#include "gtest/gtest.h"

#include <utility>

using namespace WebServer;

using PathAndBase = std::pair<std::string, std::string>;

//TODO rename
class UrlUtilPositiveTest : public testing::TestWithParam<PathAndBase> {
};

//TODO rename
class UrlUtilNegativeTest : public testing::TestWithParam<PathAndBase> {
};

//TODO rename
class RemoveQueryStringTest : public testing::TestWithParam<std::string> {
};

INSTANTIATE_TEST_SUITE_P(UrlUtilTestSuit, UrlUtilPositiveTest, testing::Values(
    PathAndBase("/file.html", "/"),
    PathAndBase("/base/dir/a/b/file.html", "/"),
    PathAndBase("/base/dir/a/b/file.html", "/base"),
    PathAndBase("/base/dir/a/b/file.html", "/base/dir"),
    PathAndBase("/base/dir/a/b/file.html", "/base/dir/")
));

TEST_P(UrlUtilPositiveTest, positive) {
    //given
    auto param = GetParam();

    //when
    auto result = checkIfPathStartsWithBase(param.first, param.second);

    //then
    ASSERT_TRUE(result);
}

INSTANTIATE_TEST_SUITE_P(UrlUtilTestSuit, UrlUtilNegativeTest, testing::Values(
    PathAndBase("/base/dir/a/b/file.html", "/a"),
    PathAndBase("/base/dir/a/b/file.html", "/base/a")
));

TEST_P(UrlUtilNegativeTest, checkIfPathStartsWithBase_negative) {
    //given
    auto param = GetParam();

    //when
    auto result = checkIfPathStartsWithBase(param.first, param.second);

    //then
    ASSERT_FALSE(result);
}

INSTANTIATE_TEST_SUITE_P(UrlUtilTestSuit, RemoveQueryStringTest, testing::Values(
    "/file.html",
    "/file.html?key=value"
));

TEST_P(RemoveQueryStringTest, removeQueryString) {
    //given
    auto param = GetParam();

    //when
    auto result = removeQueryString(param);

    //then
    ASSERT_EQ("/file.html", result);
}
