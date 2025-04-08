cmake_minimum_required(VERSION 3.16)
project(nanoMQ_attempt LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_EXECUTABLE ON)

if(WIN32)
    add_library(nanomq STATIC IMPORTED)
    set_target_properties(nanomq PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nanomq/Release/nanomq.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nanomq/Debug/nanomq.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/nanomq/include"
    )

    add_library(nng STATIC IMPORTED)
    set_target_properties(nng PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nng/Release/nng.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nng/Debug/nng.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/nng/include"
    )
elseif(UNIX AND NOT APPLE)  # Linux
    add_library(nanomq STATIC IMPORTED)
    set_target_properties(nanomq PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build_UNIX/nanomq/libnanomq.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/nanomq/include"
    )

    add_library(nng STATIC IMPORTED)
    set_target_properties(nng PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build_UNIX/nng/libnng.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/nng/include"
    )
endif()

add_executable(nanoMQ_attempt main.cpp)

# Platform-specific linking
if(WIN32)
    target_link_libraries(nanoMQ_attempt
        nanomq
        nng
        ws2_32
        crypt32
        bcrypt
    )
elseif(UNIX AND NOT APPLE)  # Linux
    target_link_libraries(nanoMQ_attempt
        nanomq
        nng
        pthread
        dl
        rt
        m
    )
    # Add pthread compiler flag
    target_compile_options(nanoMQ_attempt PRIVATE -pthread)
endif()
