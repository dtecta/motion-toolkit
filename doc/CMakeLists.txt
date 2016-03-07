
find_package(Doxygen)
  
# Build and install API documentation if doxygen is available
if(DOXYGEN_FOUND)
	configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
	add_custom_target(doc     COMMAND 
    ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
    COMMENT "Building documentation" VERBATIM
  )
	file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/api)
	install(DIRECTORY ${PROJECT_BINARY_DIR}/api DESTINATION doc)
endif()
