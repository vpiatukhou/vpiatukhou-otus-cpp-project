#include "UrlUtil.h"

#include "gtest/gtest.h"

#include <utility>

using namespace WebServer;

using PathAndRoot = std::pair<std::string, std::string>;

//TODO rename
class UrlUtilPositiveTest : public testing::TestWithParam<PathAndRoot> {
};

//TODO rename
class UrlUtilNegativeTest : public testing::TestWithParam<PathAndRoot> {
};

//TODO rename
class RemoveQueryStringTest : public testing::TestWithParam<std::string> {
};

INSTANTIATE_TEST_SUITE_P(UrlUtilTestSuit, UrlUtilPositiveTest, testing::Values(
    PathAndRoot("/file.html", "/"),
    PathAndRoot("/root/dir/a/b/file.html", "/"),
    PathAndRoot("/root/dir/a/b/file.html", "/root"),
    PathAndRoot("/root/dir/a/b/file.html", "/root/dir"),
    PathAndRoot("/root/dir/a/b/file.html", "/root/dir/")
));

TEST_P(UrlUtilPositiveTest, positive) {
    //given
    auto param = GetParam();

    //when
    auto result = checkIfPathStartsWithRoot(param.first, param.second);

    //then
    ASSERT_TRUE(result);
}

INSTANTIATE_TEST_SUITE_P(UrlUtilTestSuit, UrlUtilNegativeTest, testing::Values(
    PathAndRoot("/root/dir/a/b/file.html", "/a"),
    PathAndRoot("/root/dir/a/b/file.html", "/root/a")
));

TEST_P(UrlUtilNegativeTest, checkIfPathStartsWithRoot_negative) {
    //given
    auto param = GetParam();

    //when
    auto result = checkIfPathStartsWithRoot(param.first, param.second);

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
