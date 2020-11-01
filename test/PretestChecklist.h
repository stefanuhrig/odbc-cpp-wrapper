#ifndef TEST_PRETESTCHECKLIST_H_INCLUDED
#define TEST_PRETESTCHECKLIST_H_INCLUDED
//------------------------------------------------------------------------------
#include <string>
#include <utility>
#include <vector>
//------------------------------------------------------------------------------
#define ADD_PRETEST_CHECK(name, function)                                      \
    namespace {                                                                \
    struct PretestCheck_##function {                                           \
    PretestCheck_##function () {                                               \
        ::odbc::test::PretestChecklist::addCheck(name, function); }            \
    };                                                                         \
    static PretestCheck_##function pretestCheck_##function;                    \
    }
//------------------------------------------------------------------------------
namespace odbc {
namespace test {
//------------------------------------------------------------------------------
class PretestChecklist
{
public:
    typedef bool (*PretestCheck)();

private:
    PretestChecklist() = default;

public:
    static void addCheck(const char* name, PretestCheck check);
    static bool executeChecks();

private:
    static PretestChecklist& getInstance();

private:
    std::vector<std::pair<std::string, PretestCheck>> checks_;
};
//------------------------------------------------------------------------------
} // namespace test
} // namespace odbc
//------------------------------------------------------------------------------
#endif
