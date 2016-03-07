cmake_minimum_required(VERSION 2.8.8)

project(motion-toolkit)

set(CMAKE_DEBUG_POSTFIX  "_d")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/3rdparty/googletest/include
)

if(MSVC) 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /fp:fast /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /GR- /fp:fast /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GS-") 
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GS-") 
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
  set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
  if(NOT CMAKE_CL_64)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
  endif(NOT CMAKE_CL_64)
endif(MSVC)

if(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ffast-math -msse -mfpmath=sse")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fno-rtti -ffast-math -msse -mfpmath=sse")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread") 
endif(UNIX)
  
add_subdirectory(3rdparty/googletest)
add_subdirectory(consolid)
add_subdirectory(guts)
add_subdirectory(moto)
add_subdirectory(jointlimits)
add_subdirectory(doc)