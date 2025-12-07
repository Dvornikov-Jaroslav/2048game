find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(game2048_test
    game2048_test/main.cpp
    game2048_test/game2048_test.cpp
    game2048_test/game2048_test.hpp
)

target_link_libraries(game2048_test Qt6::Test game2048_lib)

add_test(NAME Game2048Test COMMAND game2048_test)
