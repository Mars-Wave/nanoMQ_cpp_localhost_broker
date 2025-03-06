cmake_minimum_required(VERSION 3.16)
project(nanoMQ_attempt LANGUAGES CXX)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)


if(WIN32)
  # Windows-specific settingsset(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(your_target PRIVATE Threads::Threads)
endif()

# Import the static nanomq library
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
# add_library(nanomq_cli STATIC IMPORTED)
# set_target_properties(nanomq_cli PROPERTIES
#     IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nanomq_cli/Release/nanomq_cli.lib"
#     IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/build/nanomq_cli/Debug/nanomq_cli.lib"
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nanomq/nanomq_cli/include"
# )

add_executable(nanoMQ_attempt main.cpp)

# Link libraries and system dependencies
target_link_libraries(nanoMQ_attempt
  # nanomq_cli
  nanomq
  nng
  ws2_32       # For Windows socket functions (htons, etc.)
  crypt32      # For Windows crypto functions
  bcrypt       # For cryptographic primitives
)
