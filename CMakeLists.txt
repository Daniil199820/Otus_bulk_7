cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})

set(INSTALL_GTEST OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/GTest_module" 
"googletest")


add_executable(bulk Model.cpp Controller.cpp main.cpp)
add_executable(tests_ tests_.cpp )

set_target_properties(bulk tests_ PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


target_include_directories(
    tests_ PRIVATE
   ${GTEST_INCLUDE_DIRS}
)



target_include_directories(
    bulk PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tests_ PRIVATE
    gtest gtest_main
)

if (MSVC)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(bulk PRIVATE
        /W4
    )
   
    target_compile_options(tests_ PRIVATE
        /W4
    )

else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic 
    )
   
    target_compile_options(tests_ PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(tests_ tests_)