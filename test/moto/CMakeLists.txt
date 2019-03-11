add_executable(test_moto
  main.cpp
  DualNumberTests.cpp
  MatrixTests.cpp
  NumericalTests.cpp
  TestHelpers.hpp
  TrigonometryTests.cpp
  Types.hpp
)

set(MOTO_DEPS consolid gtest)
add_dependencies(${MOTO_DEPS}) 
set_target_properties(test_moto PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(test_moto ${MOTO_DEPS})
if(UNIX)
target_link_libraries(test_moto pthread)
endif()
