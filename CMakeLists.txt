cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(moto)

set(CMAKE_DEBUG_POSTFIX  "_d")

include_directories(
  ${moto_SOURCE_DIR}
)

if(MSVC) 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS /fp:fast /arch:SSE ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS /GR- /fp:fast /arch:SSE ")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GS-") 
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GS-") 
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
  set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
endif(MSVC)

if(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ffast-math -msse -mfpmath=sse")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -ffast-math -msse -mfpmath=sse")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")
endif(UNIX)

if(UNIX AND NOT WIN32 AND NOT APPLE)
  if(CMAKE_SIZEOF_VOID_P MATCHES "8")
      set(LIB_POSTFIX "64" CACHE STRING "suffix for 32/64 dir placement")
      mark_as_advanced(LIB_POSTFIX)
  endif(CMAKE_SIZEOF_VOID_P MATCHES "8")
endif(UNIX AND NOT WIN32 AND NOT APPLE)
if(NOT DEFINED LIB_POSTFIX)
    set(LIB_POSTFIX "")
endif(NOT DEFINED LIB_POSTFIX)

add_subdirectory(consolid)
add_subdirectory(guts)
add_subdirectory(moto)
