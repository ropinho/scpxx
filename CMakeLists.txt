cmake_minimum_required( VERSION 3.5 )
project( ORReader VERSION 0.1 LANGUAGES CXX )

include(GNUInstallDirs)
set(INSTALL_CMAKE_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/orlib)

add_subdirectory(src)
