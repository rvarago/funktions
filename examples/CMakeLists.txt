project(funktions_examples LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    device_validation.cpp
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
)

add_custom_target(${PROJECT_NAME}_run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
)