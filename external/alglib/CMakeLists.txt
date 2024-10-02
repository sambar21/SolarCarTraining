add_library(alglib "")

target_sources(
	alglib
	PRIVATE
		alglibinternal.cpp
		alglibmisc.cpp
		ap.cpp
		dataanalysis.cpp
		diffequations.cpp
		fasttransforms.cpp
		integration.cpp
		interpolation.cpp
		kernels_avx2.cpp
		kernels_fma.cpp
		kernels_sse2.cpp
		linalg.cpp
		optimization.cpp
		solvers.cpp
		specialfunctions.cpp
		statistics.cpp
	PUBLIC
		alglibinternal.h
		alglibmisc.h
		ap.h
		dataanalysis.h
		diffequations.h
		fasttransforms.h
		integration.h
		interpolation.h
		kernels_avx2.h
		kernels_fma.h
		kernels_sse2.h
		linalg.h
		optimization.h
		solvers.h
		specialfunctions.h
		statistics.h
		stdafx.h
)

if(WIN32 OR MSVC)
	add_compile_definitions(AE_OS=AE_WINDOWS)
elseif(UNIX)
	add_compile_definitions(AE_OS=AE_POSIX)
	# When compiling on POSIX/Linux, link ALGLIB with libpthread library. This is needed for
	# multithreaded optimization.
	target_link_libraries(alglib PRIVATE pthread)
endif()

## if the processor is intel or amd, add flag AE_CPU=AE_INTEL
#if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$" OR CMAKE_SYSTEM_PROCESSOR MATCHES
#														 "^(i386|i686)$"
#)
#	add_compile_definitions(AE_MKL)
#	# add ${PROJECT_SOURCE_DIR}/external/addons-mkl to CMAKE_PREFIX_PATH
#	list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/external/addons-mkl)
#	add_compile_definitions(AE_CPU=AE_INTEL)
#endif ()

# check architecture and print it out: x86_64, i386, arm, arm64, etc.
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
#if (WIN32 OR MSVC)
#	message(STATUS "OS: Windows")
#	if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
#		find_library(MKL_LIB alglib400_64mkl.lib)
#		if (MKL_LIB STREQUAL "MKL_LIB-NOTFOUND")
#			set(MKL_LIB ${PROJECT_SOURCE_DIR}/external/alglib/addons-mkl/libalglib400_64mkl.lib)
#		endif ()
#		target_link_libraries(alglib PRIVATE ${MKL_LIB})
#		message(STATUS "USING MKL FOR ALGLIB ON WINDOWS x86_64")
#	elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(i386|i686)$")
#		find_library(MKL_LIB alglib400_32mkl.lib)
#		if (MKL_LIB STREQUAL "MKL_LIB-NOTFOUND")
#			set(MKL_LIB ${PROJECT_SOURCE_DIR}/external/alglib/addons-mkl/libalglib400_32mkl.lib)
#		endif ()
#		target_link_libraries(alglib PRIVATE ${MKL_LIB})
#		message(STATUS "USING MKL FOR ALGLIB ON WINDOWS i386")
#	endif ()
#elseif (UNIX)
#	message(STATUS "OS: Unix")
#	if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
#		find_library(MKL_LIB alglib400_64mkl.so)
#		if (MKL_LIB STREQUAL "MKL_LIB-NOTFOUND")
#			set(MKL_LIB ${PROJECT_SOURCE_DIR}/external/alglib/addons-mkl/libalglib400_64mkl.so)
#		endif ()
#		target_link_libraries(alglib PRIVATE ${MKL_LIB})
#		message(STATUS "USING MKL FOR ALGLIB ON LINUX x86_64")
#	endif ()
#endif ()

target_include_directories(alglib INTERFACE ${PROJECT_SOURCE_DIR}/external)

# Compile with no warnings and with -O3 (regardless of build type)
target_compile_options(
	alglib
	PRIVATE
		-w
		-O3
)
