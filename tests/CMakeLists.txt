project(funktions_tests LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.12.4
)
FetchContent_MakeAvailable(catch)

add_executable(${PROJECT_NAME}
    fnwrapper_test.cpp
    logical_test.cpp
    main.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra -Werror -ansi -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /Wall /W4
    )
else()
    message("Unknown compiler... skipping configuration for warnings")
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        rvarago::funktions
        Catch2::Catch2
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
