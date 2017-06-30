include(RegexUtils)
test_escape_string_as_regex()

file(GLOB Sphinx_directory_files "*")

escape_string_as_regex(ESCAPED_CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

foreach(f ${Sphinx_directory_files})
    if(NOT f MATCHES "\\.txt" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/[.].+" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/src")
        list(APPEND Eigen_directory_files_to_install ${f})
    endif()
endforeach(f ${Sphinx_directory_files})

install(FILES
        ${Sphinx_directory_files_to_install}
        DESTINATION ${INCLUDE_INSTALL_DIR}/libSphinx COMPONENT Devel
        )

install(DIRECTORY src DESTINATION ${INCLUDE_INSTALL_DIR}/libSphinx COMPONENT Devel FILES_MATCHING PATTERN "*.h")