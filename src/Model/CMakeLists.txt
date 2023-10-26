cmake_minimum_required(VERSION 3.5)

project(model LANGUAGES C)

add_executable(model )

include(GNUInstallDirs)
install(TARGETS model
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
