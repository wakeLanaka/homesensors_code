include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_library(SQLITE3_LIB sqlite3 REQUIRED)

add_executable(AirLogTests
        test_main.cpp
        AirQualityTest.cpp
        HistoryServiceTest.cpp
        SqlStorageTest.cpp
        mock/MockSensor.h
        mock/MockService.h
        ../src/app/AirQualityController.cpp
        ../src/domain/HistoryService.cpp
        ../src/domain/EnvironmentalMetric.cpp
        ../src/drivers/SqlStorage.cpp
)

target_include_directories(AirLogTests PRIVATE ../include)
target_link_libraries(AirLogTests
        PRIVATE
        GTest::gtest_main
        GTest::gmock
        ${SQLITE3_LIB}
)

include(GoogleTest)
gtest_discover_tests(AirLogTests)