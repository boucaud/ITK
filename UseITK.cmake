#
# This module add the VTK include paths to a project
# It should be included after the FindVTK module
#
IF (ITK_BINARY_PATH)
  LOAD_CACHE(${ITK_BINARY_PATH} 
  EXCLUDE
    BUILD_SHARED_LIBS
    BUILD_TESTING
    BUILD_EXAMPLES
    LIBRARY_OUTPUT_PATH
    EXECUTABLE_OUTPUT_PATH
    MAKECOMMAND 
    SITE
    BUILDNAME
    CVS_UPDATE_OPTIONS
    DART_TESTING_TIMEOUT
    INCLUDE_INTERNALS
    ITK_BINARY_DIR
    ITK_LIBRARY_PATH
    ITK_BUILD_SHARED_LIBS
    )
    INCLUDE (${ITK_SOURCE_DIR}/itkCMakeOptions.cmake)
    INCLUDE_DIRECTORIES(${ITK_SOURCE_DIR}/Code/BasicFilters)
    INCLUDE_DIRECTORIES(${ITK_SOURCE_DIR}/Code/Algorithms)
    LINK_DIRECTORIES(${ITK_LIBRARY_PATH})
ENDIF (ITK_BINARY_PATH)

IF (UNIX)
  LINK_LIBRARIES(${THREAD_LIBS} ${DL_LIBS} -lm)
ENDIF (UNIX)
