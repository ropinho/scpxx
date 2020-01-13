cmake_minimum_required( VERSION 3.5 )
project( SCPxx VERSION 1.0.0 LANGUAGES CXX )

include(GNUInstallDirs)
set(INSTALL_CMAKE_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/scpxx)

add_subdirectory(src)
