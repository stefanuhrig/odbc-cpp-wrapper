#include <odbc/Connection.h>
#include <odbc/Environment.h>
#include <odbc/Exception.h>
#include <odbc/Statement.h>
#include <odbc/Util.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "PretestChecklist.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
namespace odbc {
namespace test {
//------------------------------------------------------------------------------
static bool postgresPretestCheck()
{
    const char* connstring = getenv("POSTGRES_CONNSTRING");
    if (!connstring) {
        cerr << "Environment variable POSTGRES_CONNSTRING is not set" << endl;
        return false;
    }
    const char* schema = getenv("POSTGRES_SCHEMA");
    if (!schema) {
        cerr << "Environment variable POSTGRES_SCHEMA is not set" << endl;
        return false;
    }

    ostringstream dropSchema;
    dropSchema << "DROP SCHEMA IF EXISTS " << Util::quote(schema) << " CASCADE";
    
    ostringstream createSchema;
    createSchema << "CREATE SCHEMA " << Util::quote(schema);

    try {
        EnvironmentRef env = Environment::create();
        ConnectionRef conn = env->createConnection();
        conn->connect(connstring);
        StatementRef stmt = conn->createStatement();
        
        stmt->execute(dropSchema.str().c_str());
        stmt->execute(createSchema.str().c_str());
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------
ADD_PRETEST_CHECK("postgres", postgresPretestCheck);
//------------------------------------------------------------------------------
} // namespace test
} // namespace odbc
