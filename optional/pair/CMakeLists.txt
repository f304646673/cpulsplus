# Collect all source files in this directory
file(GLOB SOURCES "*.cpp")

# Add the executable target
add_executable(PairExecutable ${SOURCES})