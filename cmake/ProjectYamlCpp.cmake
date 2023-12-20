#------------------------------------------------------------------------------
# install yaml cpp from git
# @ ${YAMLCPP_INCLUDE_DIR}: yamlcpp include path
# @ ${YAMLCPP_LIBRARY}: yamlcpp libbrary path
# ------------------------------------------------------------------------------

include(ExternalProject)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(YAMLCPP_CMAKE_COMMAND emcmake cmake)
else()
    set(YAMLCPP_CMAKE_COMMAND ${CMAKE_COMMAND})
endif()

ExternalProject_Add(yaml-cpp
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NAME yaml-cpp-0.8.0.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    URL https://github.com/jbeder/yaml-cpp/archive/0.8.0.tar.gz
    URL_HASH SHA256=fbe74bbdcee21d656715688706da3c8becfd946d92cd44705cc6098bb23b3a16
    CMAKE_COMMAND ${YAMLCPP_CMAKE_COMMAND}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               # Build static lib but suitable to be included in a shared lib.
               -DCMAKE_POSITION_INDEPENDENT_CODE=${BUILD_SHARED_LIBS}
               ${_only_release_configuration}
               -DYAMLCPP_WITH_TESTS=OFF
               -DYAMLCPP_WITH_PKGCONFIG_SUPPORT=OFF
               	# -DCMAKE_C_FLAGS=-Wa,-march=generic64
               	# -DCMAKE_CXX_FLAGS=-Wa,-march=generic64
               	-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -Wno-error
        		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -Wno-error
    LOG_CONFIGURE 1
    LOG_BUILD 1
    BUILD_COMMAND ""
    ${_overwrite_install_command}
    LOG_INSTALL 0
    BUILD_BYPRODUCTS <INSTALL_DIR>/lib/libyamlcpp.a
)

# Create yamlcpp imported library
ExternalProject_Get_Property(yaml-cpp INSTALL_DIR)
add_library(YamlCpp STATIC IMPORTED)
set(YAMLCPP_LIBRARY ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}yaml-cpp${CMAKE_STATIC_LIBRARY_SUFFIX})
set(YAMLCPP_INCLUDE_DIR ${INSTALL_DIR}/include)
file(MAKE_DIRECTORY ${YAMLCPP_INCLUDE_DIR})  # Must exist.
set_property(TARGET YamlCpp PROPERTY IMPORTED_LOCATION ${YAMLCPP_LIBRARY})
set_property(TARGET YamlCpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${YAMLCPP_INCLUDE_DIR})
add_dependencies(YamlCpp yaml-cpp)
unset(INSTALL_DIR)
