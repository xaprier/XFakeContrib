if(WIN32)
    install(FILES XFakeContrib.png DESTINATION . COMPONENT desktop)
    install(FILES XFakeContrib.ico DESTINATION . COMPONENT desktop)
else()
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}/share/applications/XFakeContrib.desktop")
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}/share/icons/hicolor/256x256/apps/XFakeContrib.png")
    install(FILES XFakeContrib.desktop DESTINATION share/applications/ COMPONENT desktop)
    install(FILES XFakeContrib.png DESTINATION share/icons/hicolor/256x256/apps COMPONENT desktop)
endif()