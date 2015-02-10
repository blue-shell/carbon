add_definitions(-DTRANSLATION_DOMAIN=\"carbon_decoration_config\")

set(kwin_carbon_config_PART_SRCS
    carbonanimationconfigwidget.cpp
    carbonconfig.cpp
    carbonconfigwidget.cpp
    carbondetectwidget.cpp
    carbonexceptiondialog.cpp
    carbonexceptionlistwidget.cpp
    carbonexceptionmodel.cpp
    ../carbonexceptionlist.cpp
 )

set(kwin_carbon_config_PART_FORMS
   ui/carbonconfigurationui.ui
   ui/carbondetectwidget.ui
   ui/carbonexceptiondialog.ui
   ui/carbonexceptionlistwidget.ui
)

if(CARBON_USE_KDE4)
  kde4_add_kcfg_files(kwin_carbon_config_PART_SRCS ../carbonconfiguration.kcfgc)
  kde4_add_ui_files(kwin_carbon_config_PART_FORMS_HEADERS ${kwin_carbon_config_PART_FORMS})
  kde4_add_plugin(kwin_carbon_config
      ${kwin_carbon_config_PART_SRCS}
      ${kwin_carbon_config_PART_FORMS_HEADERS})

  target_link_libraries(
      kwin_carbon_config
      ${KDE4_KDEUI_LIBS}
      ${KDE4WORKSPACE_KDECORATIONS_LIBS}
      carbonstyle carbonstyleconfig
 )

  if(CARBON_HAVE_X11)
    target_link_libraries(kwin_carbon_config ${X11_XCB_LIBRARIES})
    target_link_libraries(kwin_carbon_config ${XCB_LIBRARIES})
  endif()

  install(TARGETS kwin_carbon_config DESTINATION ${PLUGIN_INSTALL_DIR})

else()
  kconfig_add_kcfg_files(kwin_carbon_config_PART_SRCS ../carbonconfiguration.kcfgc)

  ki18n_wrap_ui(kwin_carbon_config_PART_FORMS_HEADERS ${kwin_carbon_config_PART_FORMS})
  add_library(kwin_carbon_config MODULE
      ${kwin_carbon_config_PART_SRCS}
      ${kwin_carbon_config_PART_FORMS_HEADERS})

  target_link_libraries(kwin_carbon_config Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(kwin_carbon_config KF5::I18n KF5::WindowSystem KF5::Completion)
  target_link_libraries(kwin_carbon_config kdecorations carbonstyle5  carbonstyleconfig5)

  if(CARBON_HAVE_X11)
    target_link_libraries(kwin_carbon_config XCB::XCB)
    target_link_libraries(kwin_carbon_config Qt5::X11Extras)
  endif()

  install(TARGETS kwin_carbon_config DESTINATION ${PLUGIN_INSTALL_DIR}/kwin/kdecorations/config)
endif()
