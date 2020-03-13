include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB SOURCE_FILES "*.cpp")
add_executable(GasSimulation ${SOURCE_FILES})