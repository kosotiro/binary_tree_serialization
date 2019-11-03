cmake_minimum_required(VERSION 3.5)
project(serdeser VERSION 1.0.0 LANGUAGES C)

add_library(serdeser src/serialize.c)

target_include_directories(serdeser
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS serdeser EXPORT MySerDeserLibraryConfig 
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/build)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MySerDeserLibraryConfig DESTINATION share/MySerDeserLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS serdeser FILE MySerDeserLibraryConfig.cmake)
