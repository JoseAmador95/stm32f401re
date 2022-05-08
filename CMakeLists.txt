include("cmake/toolchain-arm-none-eabi.cmake")
cmake_minimum_required(VERSION 3.15)
project(stm32f401-hal)
enable_language(C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_DIR src)

include_directories(include)

set(MCU_SOURCES
    ${SOURCE_DIR}/cortex-m4.c
    ${SOURCE_DIR}/stm32f401-gpio-driver.c
    ${SOURCE_DIR}/stm32f401-spi-driver.c
    ${SOURCE_DIR}/stm32f401-i2c-driver.c
    ${SOURCE_DIR}/stm32f401-rcc.c
)

set(MCU_STARTUP startup/startup_stm32f401xe.s)
set(MCU_SYSTEM ${SOURCE_DIR}/system-stm32f4xx.c)
set(BSP_SOURCE ${SOURCE_DIR}/nucleo-f401.c)
set(MAIN ${SOURCE_DIR}/main.c)

set(LINKER_SCRIPT ${CMAKE_HOME_DIRECTORY}/linker/stm32f401re_linker.ld)

add_compile_definitions(STM32F401xE)

add_compile_options(
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
)

add_link_options(
    -T${LINKER_SCRIPT}
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
)

set(SOURCES ${MCU_SOURCES} ${MCU_STARTUP} ${MCU_SYSTEM} ${BSP_SOURCE})
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${MAIN})
link_libraries(${CPU_OPTIONS} -T${LINKER_SCRIPT})
set_property(TARGET ${PROJECT_NAME}.elf PROPERTY LINK_DEPENDS ${LINKER_SCRIPT})
