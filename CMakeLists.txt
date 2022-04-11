cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(run_artemis)

# ROOT 6 installation
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/ CACHE PATH "install dir" FORCE)

# Build options
#option(BUILD_IDAQ2ROOT "Build and install Isobe DAQ data to ROOT converter" ON)

# path definitions
set(YAML_CPP_INSTALL_DIR $ENV{YAML_CPP_DIR} )
set(ARTEMIS_INSTALL_DIR /opt/local/artemis/ CACHE STRING "path to artemis install")
set(YAML_CPP_DIR ${YAML_CPP_INSTALL_DIR} CACHE STRING "path to artemis install")
set(CAT_LIB_DIR /home/ota/repos/artemis-cat-src/ CACHE STRING "path to artemis-cat-src")
set(OEDO_LIB_DIR ${CMAKE_SOURCE_DIR}/src-oedo CACHE STRING "path to artemis src-oedo")
set(SHARE_LIB_DIR ${CMAKE_SOURCE_DIR}/share/src CACHE STRING "path to artemis share src")
set(GET_LIB_DIR /opt/local/GETDecoder CACHE STRING "path to get decoder lib")
#configure_file( anamerger/include/LibraryConfig.h.in ${CMAKE_BINARY_DIR}/generated/LibraryConfig.h)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Physics Minuit2)
#find_package(LibXml2 REQUIRED)
#find_package(yaml-cpp)
set(YAML_CPP_INCLUDE_DIR ${YAML_CPP_DIR}/include CACHE PATH "yaml-cpp include dir")
set(YAML_CPP_LIB_DIR ${YAML_CPP_DIR}/lib CACHE PATH "yaml-cpp lib dir")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# include directories
include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories(${ARTEMIS_INSTALL_DIR}/include)
include_directories(${CAT_LIB_DIR})
include_directories(${OEDO_LIB_DIR})
include_directories(${SHARE_LIB_DIR})
include_directories(${GET_LIB_DIR}/include)
#include_directories(${CMAKE_BINARY_DIR}/generated)

# link directories
link_directories(${YAML_CPP_LIB_DIR})
link_directories(${YAML_CPP_INCLUDE_DIR})
link_directories(${ARTEMIS_INSTALL_DIR}/lib)
link_directories(${CAT_LIB_DIR})
link_directories(${OEDO_LIB_DIR})
link_directories(${SHARE_LIB_DIR})
link_directories(${GET_LIB_DIR}/lib)
link_directories(${ROOTSYS}/lib)

add_executable(run_artemis run_artemis.cpp)
target_link_libraries(run_artemis ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    catcmd catloop catcore artcont catmc
    artdecoder artridf artrdf arthist
    artparam GETDecoder
    Minuit Genetic
    user CAT oedo
    )