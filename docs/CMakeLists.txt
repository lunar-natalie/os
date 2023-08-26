# Documentation build configuration.

# Adds a Doxygen build-time command to generate documentation from the files in
# `file_list` into `output_dir`.
macro(add_doxygen_command file_list output_dir)
  list(LENGTH ${file_list} file_count)
  if(file_count GREATER 0)
    string(REPLACE ";" " " files "${${file_list}}")
    string(APPEND DOXYGEN_COMMANDS
      "run_doxygen(\"${files}\" \"${output_dir}\")\n")
  endif()
endmacro()

# Doxygen base configuration properties
set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
set(DOXYGEN_COMMAND_LINE "\"${DOXYGEN_EXECUTABLE}\" ARGS \"${DOXYFILE}\"")
set(DOXYGEN_ROOT_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/out")
set(DOXYGEN_PATH_LIST) # List of directories to strip from the include path
set(DOXYGEN_FILES) # List of files to add to the main build command

# Load include directory
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(INCLUDE_FILES ${${PROJECT_NAME}_ALL_SOURCE_FILES})
list(FILTER INCLUDE_FILES INCLUDE REGEX "${INCLUDE_DIR}/.*\.h")
list(APPEND DOXYGEN_PATH_LIST "${INCLUDE_DIR}")

# Load auxiliary documentation
if(${PROJECT_NAME}_ENABLE_DOCS_AUX)
  file(GLOB AUX_FILES
    "${CMAKE_SOURCE_DIR}/*.md"
  )
  set(DOXYGEN_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
endif()

# Add build commands
list(APPEND DOXYGEN_FILES ${INCLUDE_FILES} ${AUX_FILES})
add_doxygen_command(DOXYGEN_FILES
  "${DOXYGEN_ROOT_OUTPUT_DIRECTORY}")

# Configure remaining options for Doxyfile.in
string(REPLACE ";" " " DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_PATH_LIST}")

# Fetch external stylesheet if enabled
if(${PROJECT_NAME}_ENABLE_STYLED_DOCS)
  include(FetchContent)

  message("-- Fetching Doxygen stylesheet")
  FetchContent_Declare(doxygen-awesome-css
    GIT_REPOSITORY "https://github.com/jothepro/doxygen-awesome-css.git"
    GIT_TAG a7f7891706c656903326f79baf74beb2b711688d # release v2.2.0
  )

  FetchContent_MakeAvailable(doxygen-awesome-css)

  if(doxygen-awesome-css_POPULATED)
    set(DOXYGEN_STYLESHEET
      "${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css")

    string(REPLACE "." ";" VERSION_COMPONENTS "${DOXYGEN_VERSION}")
    list(LENGTH VERSION_COMPONENTS N_VERSION_COMPONENTS)

    # Minimum version to enable new Doxygen options.
    set(MIN_NEW_VERSION_MAJOR 1)
    set(MIN_NEW_VERSION_MINOR 9)
    set(MIN_NEW_VERSION_PATCH 5)

    if(N_VERSION_COMPONENTS GREATER_EQUAL 3)
      list(GET VERSION_COMPONENTS 0 MAJOR)
      list(GET VERSION_COMPONENTS 1 MINOR)
      list(GET VERSION_COMPONENTS 2 PATCH)
      if(MAJOR GREATER_EQUAL MIN_NEW_VERSION_MAJOR
          AND MINOR GREATER_EQUAL MIN_NEW_VERSION_MINOR
          AND PATCH GREATER_EQUAL MIN_NEW_VERSION_PATCH)
        set(DOXYGEN_NEW True)
      endif()
    else()
      set(DOXYGEN_NEW False)
    endif()

    if(EXISTS "${DOXYGEN_STYLESHEET}")
      set(DOXYGEN_STYLE_CONFIG "\
GENERATE_TREEVIEW = YES
DISABLE_INDEX = NO
HTML_EXTRA_STYLESHEET = ${DOXYGEN_STYLESHEET}\
")
      if(DOXYGEN_NEW)
        set(DOXYGEN_STYLE_CONFIG "\
${DOXYGEN_STYLE_CONFIG}
FULL_SIDEBAR = NO
HTML_COLORSTYLE = LIGHT\
")
      endif()
    else()
      message(WARNING "Unable to find Doxygen stylesheet")
      message("-- Using default Doxygen style")
    endif()
  else()
    message(WARNING "Failed to retrieve Doxygen stylesheet repository")
    message("-- Using default Doxygen style")
  endif()
endif()

# Configure build script
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenerateDocs.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/GenerateDocs.cmake"
  @ONLY)

# Add target
add_custom_target(Docs
  COMMAND
    "${CMAKE_COMMAND}"
      -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/GenerateDocs.cmake"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Generating documentation"
  VERBATIM)
