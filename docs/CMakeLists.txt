FIND_PACKAGE( Doxygen REQUIRED )

Set( HTML_OUTPUT "FragviewDoc_Html" CACHE STRING "Output directory for generated HTML documentation. Defaults to FragviewDoc_Html." )

# Enable Microsoft CHM help style only on Windows
SET( MICROSOFT_HELP_WORKSHOP "NO")
IF( MSVC )
    SET( MICROSOFT_HELP_WORKSHOP "YES" )
ENDIF( MSVC )

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY
)

ADD_CUSTOM_TARGET(
    docs ALL
    DEPENDS docs.done
)

ADD_CUSTOM_TARGET(
    OUTPUT docs.done
    COMMAND ${DOXYGEN_EXECUTABLE}
    COMMAND ${CMAKE_COMMAND} -E touch docs.done
    COMMENT "Generating fragview documentation"
    VERBATIM
    )

IF( DEFINED CMAKE_INSTALL_DOCDIR )
    INSTALL(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${HTML_OUTPUT}
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
    )
    INSTALL(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/FragviewDoc_Html/FragViewOverview.png
        ${CMAKE_CURRENT_SOURCE_DIR}/FragviewDoc_Html/FragViewOverview.svg
        ${CMAKE_CURRENT_SOURCE_DIR}/FragviewDoc_Html/fragviewsplash.png
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/${HTML_OUTPUT}
    )
ENDIF( DEFINED CMAKE_INSTALL_DOCDIR )
