FIND_PACKAGE( Doxygen )
IF(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} -- ${DOXYGEN_VERSION}")
    SET( HTML_OUTPUT "FragEngineDoc_Html" CACHE STRING "Output directory for generated HTML documentation. Defaults to FragviewDoc_Html." )

    # Enable Microsoft CHM help style only on Windows
    SET( MICROSOFT_HELP_WORKSHOP "NO")
    IF( MSVC )
        SET( MICROSOFT_HELP_WORKSHOP "YES" )
    ENDIF( MSVC )

    # Generate doxygen file.
    CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        @ONLY
    )

    ADD_CUSTOM_TARGET(
        docs ALL
        DEPENDS docs.done
    )

    ADD_CUSTOM_COMMAND(
        OUTPUT docs.done
        COMMAND ${DOXYGEN_EXECUTABLE}
        COMMAND ${CMAKE_COMMAND} -E touch docs.done
        COMMENT "Generating frag documentation"
        VERBATIM
        )

    IF( DEFINED CMAKE_INSTALL_DOCDIR )
        INSTALL(
            DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${HTML_OUTPUT}
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
        )
        #TODO add 
        INSTALL(FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/FragviewDoc_Html/FragEngineOverview.png
            ${CMAKE_CURRENT_SOURCE_DIR}/FragviewDoc_Html/FragEnginesplash.png
            DESTINATION ${CMAKE_INSTALL_DOCDIR}/${HTML_OUTPUT}
        )
    ENDIF( DEFINED CMAKE_INSTALL_DOCDIR )

ENDIF()

# Generate design files.
FIND_PROGRAM(PLANTUML plantuml)
IF(PLANTUML_FOUND)
    #TODO improve the logic.
    FILE(GLOB PU_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.pu)
    ADD_CUSTOM_TARGET(Design
                ${PLANTUML} ${PU_FILES})
ENDIF()