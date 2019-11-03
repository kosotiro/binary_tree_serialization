cmake_minimum_required(VERSION 3.5)
project(mybtree VERSION 1.0.0 LANGUAGES C)

add_library(mybtree src/btree.c)

target_include_directories(mybtree
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS mybtree EXPORT MyBtreeLibraryConfig 
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}/build
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/build)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MyBtreeLibraryConfig DESTINATION share/MyBtreeLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS mybtree FILE MyBtreeLibraryConfig.cmake)


