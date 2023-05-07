include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_md5 md5.cpp)
add_test(NAME test_md5 COMMAND $<TARGET_FILE:test_mixed>)
target_link_libraries(test_md5 PRIVATE md5 GTest::gtest_main)
target_include_directories(test_md5 PRIVATE ../)