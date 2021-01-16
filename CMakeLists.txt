cmake_minimum_required(VERSION 3.15)

project(avr_boy_apps CXX)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(
        project_options INTERFACE
)
target_compile_features(project_options INTERFACE cxx_std_17)

# standard compiler warnings
add_library(
        project_warnings INTERFACE
)
include(cmake/compiler-warnings.cmake)
set_project_warnings(project_warnings)
include(cmake/standard-project-settings.cmake)

# ------------------------------------------------------------------------------
# setup conan
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} 
                         gtest/1.10.0
                         spdlog/1.8.2
)

if(NOT CONAN_INITIALIZED)
        set(CONAN_INITIALIZED TRUE)
        include(cmake/conan.cmake)
        run_conan()
endif()

include_directories(PUBLIC extern/avr-boy-emulator/include)

#add_subdirectory(extern/avr-boy-emulator)
add_subdirectory(extern/avr-boy-core)
add_subdirectory(src)
