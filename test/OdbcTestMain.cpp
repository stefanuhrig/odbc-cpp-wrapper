#include <cstdlib>
#include "GoogleTest.h"
#include "PretestChecklist.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    if (!odbc::test::PretestChecklist::executeChecks())
        return EXIT_FAILURE;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
