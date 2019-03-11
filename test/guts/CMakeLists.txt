add_executable(test_guts
  main.cpp
  GenericTests.cpp
)

set(GUTS_DEPS consolid gtest)
add_dependencies(${GUTS_DEPS})
set_target_properties(test_guts PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(test_guts ${GUTS_DEPS})

