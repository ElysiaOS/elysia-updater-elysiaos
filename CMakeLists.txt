cmake_minimum_required(VERSION 3.16)
project(ElysiaUpdater)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt6 MOC (Meta Object Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    main.cpp
    ElysiaUpdater.cpp
    translations.cpp
)

set(HEADERS
    ElysiaUpdater.h
    translations.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install target
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)