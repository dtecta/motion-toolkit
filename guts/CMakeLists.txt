add_executable(guts
  Allocator.hpp
  Array.hpp
  Endian.hpp
  HashTable.hpp	
  Invariant.hpp
  List.hpp
  Log.hpp
  Map.hpp
  MemAlloc.hpp	
  Memory.hpp
  MemAllocLog.hpp
  Meta.hpp
  PriorityQueue.hpp
  RefPtr.hpp
  RuntimeError.hpp
  Set.hpp
  SharedPtr.hpp
  SpatialHash.hpp
  SStream.hpp
  StaticAssert.hpp 
  String.hpp
  Vector.hpp
  UnitTest.cpp
)

add_dependencies(guts consolid)
set_target_properties(guts PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(guts consolid)

