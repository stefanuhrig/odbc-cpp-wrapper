#include <iostream>
#include "PretestChecklist.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
namespace odbc {
namespace test {
//------------------------------------------------------------------------------
void PretestChecklist::addCheck(const char* name, PretestCheck check)
{
    getInstance().checks_.emplace_back(name, check);
}
//------------------------------------------------------------------------------
PretestChecklist& PretestChecklist::getInstance()
{
    static PretestChecklist instance;
    return instance;
}
//------------------------------------------------------------------------------
bool PretestChecklist::executeChecks()
{
    for (const auto& check : getInstance().checks_)
    {
        cout << "Executing pretest check " << check.first << "..." << endl;
        try {
            if (!(*check.second)()) {
                return false;
            }
        } catch (...) {
            return false;
        }
    }
    return true;
}
//------------------------------------------------------------------------------
} // namespace test
} // namespace odbc
