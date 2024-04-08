cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0015 NEW)
project(compile C)

set(EDK_INCLUDE "../../../c_api" CACHE PATH "Path to Eduction SDK header files")
set(EDK_LIBS "../../../bin" CACHE PATH "Path to Eduction SDK library files")
set(EDK_LICENSE "../../../licensekey.dat" CACHE PATH "Path to Eduction license key file")
set(EDK_VERSION "../../../versionkey.dat" CACHE PATH "Path to Eduction version key file")

file(READ ${EDK_LICENSE} EDK_LICENSE_KEY HEX)
string(REGEX REPLACE "([0-9A-Fa-f][0-9A-Fa-f])" "0x\\1," EDK_LICENSE_KEY_BYTES ${EDK_LICENSE_KEY})
file(READ ${EDK_VERSION} EDK_VERSION_KEY HEX)
string(REGEX REPLACE "([0-9A-Fa-f][0-9A-Fa-f])" "0x\\1," EDK_VERSION_KEY_BYTES ${EDK_VERSION_KEY})
file(WRITE license_key.h "static const unsigned char EDK_LICENSE_KEY[] = {${EDK_LICENSE_KEY_BYTES}0x3b,${EDK_VERSION_KEY_BYTES}0x00};\n")

include_directories(${EDK_INCLUDE})
link_directories(${EDK_LIBS})

add_executable(compile compile.c)
target_link_libraries(compile edk)
