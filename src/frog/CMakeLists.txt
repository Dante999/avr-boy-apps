cmake_minimum_required(VERSION 3.10)

project(frog)

add_executable(
        ${PROJECT_NAME}
        main.cpp #
	fly.cpp #
	frog.cpp #
	bird.cpp #
)

target_include_directories(${PROJECT_NAME} PUBLIC ../../include)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC project_options #
               project_warnings #
               avr_boy_core #
               CONAN_PKG::spdlog #
)
