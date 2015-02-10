add_definitions(-DTRANSLATION_DOMAIN=\"carbon_style_config\")
set(kstyle_carbon_config_PART_SRCS
    carbonanimationconfigwidget.cpp
    carbonfollowmouseanimationconfigitem.cpp
    carbonstyleconfig.cpp
)

set(kstyle_carbon_config_PART_FORMS
    ui/carbonfollowmouseanimationconfigbox.ui
    ui/carbonstyleconfig.ui
)

if(CARBON_USE_KDE4)

  kde4_add_kcfg_files(kstyle_carbon_config_PART_SRCS ../carbonstyleconfigdata.kcfgc)

  kde4_add_ui_files(kstyle_carbon_config_PART_FORMS_HEADERS ${kstyle_carbon_config_PART_FORMS})

  kde4_add_plugin(kstyle_carbon_config
      ${kstyle_carbon_config_PART_SRCS}
      ${kstyle_carbon_config_PART_FORMS_HEADERS}
 )

  target_link_libraries(kstyle_carbon_config ${KDE4_KDEUI_LIBS})
  target_link_libraries(kstyle_carbon_config carbonstyleconfig)
  install(TARGETS kstyle_carbon_config DESTINATION ${PLUGIN_INSTALL_DIR}/)

else()

  set(kstyle_carbon_config_PART_SRCS ${kstyle_carbon_config_PART_SRCS} carbonstyleconfigmodule.cpp)

  kconfig_add_kcfg_files(kstyle_carbon_config_PART_SRCS ../carbonstyleconfigdata.kcfgc)

  set(kstyle_carbon_config_PART_FORMS
    ui/carbonfollowmouseanimationconfigbox.ui
    ui/carbonstyleconfig.ui
 )

  ki18n_wrap_ui(kstyle_carbon_config_PART_FORMS_HEADERS ${kstyle_carbon_config_PART_FORMS})

  add_library(kstyle_carbon_config MODULE
      ${kstyle_carbon_config_PART_SRCS}
      ${kstyle_carbon_config_PART_FORMS_HEADERS}
 )

  target_link_libraries(kstyle_carbon_config Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(kstyle_carbon_config KF5::Completion KF5::I18n)
  target_link_libraries(kstyle_carbon_config carbonstyleconfig5)

  install(TARGETS kstyle_carbon_config DESTINATION ${QT_PLUGIN_INSTALL_DIR})
  install(FILES carbonstyleconfig.desktop DESTINATION  ${SERVICES_INSTALL_DIR})

endif()

########### next target ###############
set(carbon_settings_SOURCES
    carbonconfigdialog.cpp
    main.cpp)

set(carbon_settings_FORMS ui/carbonconfigdialog.ui)

if(CARBON_USE_KDE4)

  kde4_add_ui_files(carbon_settings_SOURCES ${carbon_settings_FORMS})
  kde4_add_executable(carbon-settings ${carbon_settings_SOURCES})
  target_link_libraries(carbon-settings ${KDE4_KDEUI_LIBS})
  target_link_libraries(carbon-settings ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

  install(TARGETS carbon-settings ${INSTALL_TARGETS_DEFAULT_ARGS})

else()

  ki18n_wrap_ui(carbon_settings_FORMS_HEADERS ${carbon_settings_FORMS})

  add_executable(carbon-settings5
      ${carbon_settings_SOURCES}
      ${carbon_settings_FORMS_HEADERS}
 )

  target_link_libraries(carbon-settings5 Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(carbon-settings5 KF5::I18n KF5::WidgetsAddons KF5::ConfigCore KF5::ConfigGui KF5::Service)

  install(TARGETS carbon-settings5 ${INSTALL_TARGETS_DEFAULT_ARGS})

endif()
