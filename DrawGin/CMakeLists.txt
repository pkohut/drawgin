cmake_minimum_required (VERSION 2.8)
project (DrawGin)

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

#set(Boost_USE_STATIC_LIBS        ON)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE (Boost REQUIRED)
FIND_PACKAGE (Glog REQUIRED)

set (LIBRARY_OUTPUT_PATH       "${PROJECT_BINARY_DIR}/lib")
set (EXECUTABLE_OUTPUT_PATH    "${PROJECT_BINARY_DIR}/bin")
add_definitions(-DGOOGLE_GLOG_DLL_DECL=)


set (EXTRA_LIBS ${EXTRA_LIBS} 
	libDrawGin
)
	
if(MSVC)
    # this needs check for 64 or 32 bit builds
    set (Boost_LIBRARY_DIRS "${Boost_LIBRARY_DIRS}/win32")	
	add_definitions(-D_UNICODE)
else(MSVC)
	# Linux/OS X builds
    set (EXTRA_LIBS ${EXTRA_LIBS}
	    libglog.a
	    libboost_program_options.a
	)
	# Linux needs libpthread.so (apple does not)
	if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set (EXTRA_LIBS ${EXTRA_LIBS}
			libpthread.so
		)
	endif()

endif(MSVC)

if(CMAKE_COMPILER_IS_GNUCXX)
	message("build type = " ${CMAKE_BUILD_TYPE})
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	list(APPEND CMAKE_CXX_FLAGS "-g")
    else(${CMAKE_BUILD_TYPE} STREQUAL Debug)	
	list (APPEND CMAKE_EXE_LINKER_FLAGS "-s")
    endif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
endif(CMAKE_COMPILER_IS_GNUCXX)

set (PROJECT_HEADER_FILES
	OcConfig.h
	stdafx.h
	targetver.h	
)

set (PROJECT_FILES
	DrawGin.cpp
	stdafx.cpp
)

# ensure projects are not built unless dependencies are found
if(Boost_FOUND AND GLOG_FOUND)
    if(MSVC)
        include_directories ("${Boost_INCLUDE_DIRS}" "${GLOG_INCLUDE_DIRS}/windows" "${GLOG_INCLUDE_DIRS}" "${PROJECT_SOURCE_DIR}/inc")
		link_directories ("${Boost_LIBRARY_DIRS}" "${GLOG_ROOT}")
	else(MSVC)
		# Linux/OS X builds
	    include_directories ("${Boost_INCLUDE_DIRS}" "${GLOG_INCLUDE_DIRS}" "${PROJECT_SOURCE_DIR}/inc")
		link_directories ("${Boost_LIBRARY_DIRS}" "${GLOG_LIBRARY_DIR}")
	endif(MSVC)

    add_subdirectory("${PROJECT_SOURCE_DIR}/src")
    add_executable (DrawGin ${PROJECT_FILES} ${PROJECT_HEADER_FILES})

	if(MSVC)
		target_link_libraries (DrawGin ${EXTRA_LIBS} debug "${GLOG_ROOT}/Debug/libglog_static.lib" optimized "${GLOG_ROOT}/Release/libglog_static.lib")
	else(MSVC)
		# Linux/OS X builds
        target_link_libraries (DrawGin ${EXTRA_LIBS})
	endif(MSVC)
endif()
