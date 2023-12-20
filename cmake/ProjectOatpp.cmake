#------------------------------------------------------------------------------
# install oatpp from git
# @ ${OATPP_INCLUDE_DIR}: oatpp include path
# @ ${OATPP_LIBRARY}: oatpp libbrary path
# ------------------------------------------------------------------------------

include(ExternalProject)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(OATPP_CMAKE_COMMAND emcmake cmake)
else()
    set(OATPP_CMAKE_COMMAND ${CMAKE_COMMAND})
endif()

ExternalProject_Add(oatpp
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NAME oatpp-1.3.0.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    URL https://github.com/oatpp/oatpp/archive/1.3.0.tar.gz
    URL_HASH SHA256=e1f80fa8fd7a74da6737e7fee1a4db68b4d7085a3f40e7d550752d6ff5714583
    CMAKE_COMMAND ${OATPP_CMAKE_COMMAND}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               # Build static lib but suitable to be included in a shared lib.
               -DCMAKE_POSITION_INDEPENDENT_CODE=${BUILD_SHARED_LIBS}
               ${_only_release_configuration}
               -DOATPP_WITH_TESTS=OFF
               -DOATPP_WITH_PKGCONFIG_SUPPORT=OFF
               	# -DCMAKE_C_FLAGS=-Wa,-march=generic64
               	# -DCMAKE_CXX_FLAGS=-Wa,-march=generic64
               	-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -Wno-error
        		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -Wno-error
    LOG_CONFIGURE 1
    LOG_BUILD 1
    BUILD_COMMAND ""
    ${_overwrite_install_command}
    LOG_INSTALL 0
    BUILD_BYPRODUCTS <INSTALL_DIR>/lib/oatpp-1.3.0/liboatpp.a
)

# Create oatpp imported library
ExternalProject_Get_Property(oatpp INSTALL_DIR)
add_library(Oatpp STATIC IMPORTED)
set(OATPP_LIBRARY ${INSTALL_DIR}/lib/oatpp-1.3.0/${CMAKE_STATIC_LIBRARY_PREFIX}oatpp${CMAKE_STATIC_LIBRARY_SUFFIX})
set(OATPP_INCLUDE_DIR ${INSTALL_DIR}/include/oatpp-1.3.0/oatpp)
file(MAKE_DIRECTORY ${OATPP_INCLUDE_DIR})  # Must exist.
set_property(TARGET Oatpp PROPERTY IMPORTED_LOCATION ${OATPP_LIBRARY})
set_property(TARGET Oatpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OATPP_INCLUDE_DIR})
add_dependencies(Oatpp oatpp)
unset(INSTALL_DIR)
