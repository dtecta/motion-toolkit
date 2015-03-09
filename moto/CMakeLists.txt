add_executable(moto
  Algebra.hpp
  BBox3.hpp
  BitMask4.hpp
  Diagonal2.hpp
  Diagonal3.hpp
  Dual.hpp
  DualMatrix3x3.hpp
  DualVector2.hpp
  DualVector3.hpp
  DualVector4.hpp
  ErrorTracer.hpp
  Interval.hpp
  Matrix2x2.hpp
  Matrix3x3.hpp
  Matrix3x4.hpp
  Matrix3x4_SSE.hpp
  Matrix4x4.hpp
  Matrix4x4_SSE.hpp
  Metric.hpp
  Promote.hpp
  Random.hpp
  Scalar.hpp
  ScalarTraits.hpp
  Trigonometric.hpp
  Vector2.hpp
  Vector3.hpp
  Vector4.hpp
  Vector4_SSE.hpp
  UnitTest.cpp
)

add_dependencies(moto consolid) 
set_target_properties(moto PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(moto consolid)
if(UNIX)
target_link_libraries(moto pthread)
endif()
