cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
 project(10_homework VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
 project(10_homework VERSION 0.0.3)
endif()

#SET(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc/HEAD-f2787da/bin/c++-HEAD)

find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(bulkmt main.cpp)
add_executable(gtests tests.cpp)
add_library(library commands.cpp consumer.cpp topic.cpp consumer_out.cpp consumer_file.cpp producer.cpp)


set_target_properties(bulkmt library gtests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(bulkmt PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(bulkmt PRIVATE ${CMAKE_THREAD_LIBS_INIT} library)
target_link_libraries(gtests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} library)
    
target_compile_options(bulkmt PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(library PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(gtests PRIVATE -Wall -Wextra -pedantic -Werror  )


install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ddzuba@yandex.ru)
include(CPack)

enable_testing()
add_test(gtests gtests)