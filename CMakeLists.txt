cmake_minimum_required(VERSION 3.10)

project(FlappyBird LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Szukamy allegro-config
find_program(ALLEGRO_CONFIG allegro-config REQUIRED)

# Pobranie flag
execute_process(
        COMMAND ${ALLEGRO_CONFIG} --cflags
        OUTPUT_VARIABLE ALLEGRO_CFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND ${ALLEGRO_CONFIG} --libs
        OUTPUT_VARIABLE ALLEGRO_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Rozbij stringi na listy
separate_arguments(ALLEGRO_CFLAGS_LIST NATIVE_COMMAND ${ALLEGRO_CFLAGS})
separate_arguments(ALLEGRO_LIBS_LIST NATIVE_COMMAND ${ALLEGRO_LIBS})

file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_compile_options(${PROJECT_NAME} PRIVATE ${ALLEGRO_CFLAGS_LIST})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_LIBS_LIST})
