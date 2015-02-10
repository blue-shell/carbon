set(cursors_folders
    Carbon_Black
    Carbon_Blue
    Carbon_White
    Carbon_Yellow
    Carbon_Zion
    KDE_Classic
   )

foreach(theme ${cursors_folders})
    install(DIRECTORY ${theme} DESTINATION ${ICON_INSTALL_DIR})
endforeach(theme)

