cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME RV_Remake)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# set FreeRTOS
set(FREERTOS_PORT GCC_ARM_CM4F)
set(FREERTOS_HEAP 4)

# add freeRTOS config
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_SOURCE_DIR}/Core/Inc)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})
message("CXX_std: " ${CMAKE_CXX_STANDARD})

# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Drivers/Peripherals/Inc/USART.h
        Drivers/Peripherals/Inc/CAN.h
        Drivers/Peripherals/Inc/DMA.h
        Drivers/Peripherals/Inc/TIM.h
        Drivers/Peripherals/Inc/IIC.h
        Drivers/Peripherals/Src/USART.cpp)

#
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/Drivers/APP/Src/*.cpp
        ${CMAKE_SOURCE_DIR}/Drivers/Peripherals/Src/*.cpp
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Add freeRTOS
add_subdirectory(Libraries/FreeRTOS-Kernel)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${SOURCES}
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Drivers/APP/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/Peripherals/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    freertos_config
    freertos_kernel
    # Add user defined libraries
)
