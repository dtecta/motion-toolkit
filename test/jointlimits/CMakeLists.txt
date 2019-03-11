add_executable(test_jointlimits
  main.cpp
  JointLimitsTests.cpp
)

set(JOINTLIMITS_DEPS jointlimits consolid gtest)
add_dependencies(${JOINTLIMITS_DEPS}) 
set_target_properties(test_jointlimits PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(test_jointlimits ${JOINTLIMITS_DEPS})
if(UNIX)
target_link_libraries(test_jointlimits pthread)
endif()
