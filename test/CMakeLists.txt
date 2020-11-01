INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

SET(OdbcCppTest_sources
    offline/EnvironmentTest.cpp
    offline/ParameterDataTest.cpp
    offline/TypesTest.cpp
    offline/UtilInternalTest.cpp
    OdbcTestMain.cpp
    PretestChecklist.cpp
)

IF (POSTGRES_TESTS)
    SET(OdbcCppTest_sources
        ${OdbcCppTest_sources}
        postgres/PostgresPretestCheck.cpp
        postgres/PostgresConnectionTest.cpp
    )
ENDIF()

ADD_EXECUTABLE(
    OdbcCppTest
    ${OdbcCppTest_sources}
)

TARGET_LINK_LIBRARIES(
    OdbcCppTest
    odbccpp_static
    GTest::gmock
    ${ODBC_LIBRARIES}
)

TARGET_COMPILE_DEFINITIONS(OdbcCppTest
    PUBLIC
        ODBC_STATIC
        _CRT_SECURE_NO_WARNINGS
)

ADD_TEST(AllTests OdbcCppTest)
