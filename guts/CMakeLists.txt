add_executable(guts
  Allocator.hpp
  Array.hpp
  Deque.hpp
  Endian.hpp
  FileUtils.hpp
  HashTable.hpp	
  Invariant.hpp
  List.hpp
  Log.hpp
  Map.hpp
  MemAlloc.hpp	
  MemAllocLog.hpp
  Memory.hpp
  Meta.hpp
  PriorityQueue.hpp
  Queue.hpp
  RefPtr.hpp
  RuntimeError.hpp
  SStream.hpp
  Set.hpp
  SharedPtr.hpp
  Singleton.hpp
  SpatialHash.hpp
  StaticAssert.hpp 
  String.hpp
  UniquePtr.hpp
  UnitTest.cpp
  Vector.hpp
)

set(GUTS_DEPS consolid gtest)
add_dependencies(${GUTS_DEPS})
set_target_properties(guts PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(guts ${GUTS_DEPS})

