add_library(md5 STATIC)
enable_testing()

add_subdirectory(tests)

target_sources(md5 PRIVATE
    md5.cpp
    md5.h
)

