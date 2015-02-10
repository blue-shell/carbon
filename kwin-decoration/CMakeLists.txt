########### add version number into compilation defines
add_definitions(-DTRANSLATION_DOMAIN=\"carbon_kwin_deco\")

if(CARBON_USE_KDE4)
  include_directories(${CMAKE_SOURCE_DIR}/libcarbon)
  include_directories(${CMAKE_BINARY_DIR}/libcarbon)
  include_directories(${KDE4WORKSPACE_INCLUDE_DIR})
endif()

add_subdirectory(config)

########### next target ###############
set(kwin_carbon_SRCS
     carbonbutton.cpp
     carbonclient.cpp
     carbonclientgroupitemdata.cpp
     carbondecohelper.cpp
     carbonexceptionlist.cpp
     carbonfactory.cpp
     carbonsizegrip.cpp
     carbontitleanimationdata.cpp
)

if(CARBON_USE_KDE4)

  kde4_add_kcfg_files(kwin_carbon_SRCS carbonconfiguration.kcfgc)
  kde4_add_plugin(kwin3_carbon ${kwin_carbon_SRCS})
  target_link_libraries(
      kwin3_carbon
      ${KDE4_KDEUI_LIBS}
      ${KDE4WORKSPACE_KDECORATIONS_LIBS}
      carbonstyle
)

  if(CARBON_HAVE_X11)
    target_link_libraries(kwin3_carbon ${X11_XCB_LIBRARIES})
    target_link_libraries(kwin3_carbon ${XCB_LIBRARIES})
  endif()

  install(TARGETS kwin3_carbon DESTINATION ${PLUGIN_INSTALL_DIR})
  install(FILES carbonclient.desktop  DESTINATION  ${DATA_INSTALL_DIR}/kwin/)

else()

  kconfig_add_kcfg_files(kwin_carbon_SRCS carbonconfiguration.kcfgc)

  add_library(kwin3_carbon MODULE ${kwin_carbon_SRCS})
  target_link_libraries(kwin3_carbon Qt5::Widgets)
  target_link_libraries(kwin3_carbon KF5::GuiAddons KF5::I18n KF5::WindowSystem KF5::Style KF5::Service)

  target_link_libraries(kwin3_carbon kdecorations)

  target_link_libraries(kwin3_carbon carbonstyle5)

  kservice_desktop_to_json(kwin3_carbon carbonclient.desktop)

  if(CARBON_HAVE_X11)
    target_link_libraries(kwin3_carbon XCB::XCB)
  endif()

  install(TARGETS kwin3_carbon  DESTINATION ${PLUGIN_INSTALL_DIR}/kwin/kdecorations)

endif()
