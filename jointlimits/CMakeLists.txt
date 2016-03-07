set(TARGET_NAME jointlimits)

add_executable(${TARGET_NAME}
  Ellipse.cpp
  Ellipse.hpp
  Ellipsoid.cpp
  Ellipsoid.hpp
  EllipsoidJointLimits.cpp
  EllipsoidJointLimits.hpp
  EllipticCylinderJointLimits.cpp
  EllipticCylinderJointLimits.hpp
  EulerAnglesJointLimits.cpp
  EulerAnglesJointLimits.hpp
  JointLimits.hpp
  SwingTwistJointLimits.cpp
  SwingTwistJointLimits.hpp
  UnitTest.cpp
)

set(${TARGET_NAME}_DEPS consolid gtest)
add_dependencies(${${TARGET_NAME}_DEPS}) 
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(${TARGET_NAME} ${${TARGET_NAME}_DEPS})
if(UNIX)
target_link_libraries(${TARGET_NAME} pthread)
endif()
