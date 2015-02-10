add_definitions(-DTRANSLATION_DOMAIN=\"libcarbonstyleconfig\")

################# configuration #################
configure_file(config-libcarbon.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-libcarbon.h)

################# libcarbonstyle #################
set(carbonstyle_LIB_SRCS
    carbonanimation.cpp
    carbonhelper.cpp
    carbonitemmodel.cpp
    carbonshadowcache.cpp
    carbontileset.cpp
    carbonutil.cpp)

if(CARBON_USE_KDE4)

  kde4_add_kcfg_files(carbonstyle_LIB_SRCS
    carbonactiveshadowconfiguration.kcfgc
    carboninactiveshadowconfiguration.kcfgc
 )

  kde4_add_library(carbonstyle SHARED ${carbonstyle_LIB_SRCS})

  generate_export_header(carbonstyle BASE_NAME carbon EXPORT_FILE_NAME carbon_export.h)

  target_link_libraries(carbonstyle ${KDE4_KDEUI_LIBS})

  if(CARBON_HAVE_X11)
    target_link_libraries(carbonstyle ${X11_XCB_LIBRARIES})
    target_link_libraries(carbonstyle ${XCB_LIBRARIES})
  endif()

  set_target_properties(carbonstyle PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

 if(WIN32)
      # As stated in http://msdn.microsoft.com/en-us/library/4hwaceh6.aspx M_PI only gets defined
      # when using MSVC if _USE_MATH_DEFINES is defined (this is needed for angle.cpp)
      target_compile_definitions(carbonstyle PRIVATE _USE_MATH_DEFINES _GNU_SOURCE)
  endif()
  install(TARGETS carbonstyle ${INSTALL_TARGETS_DEFAULT_ARGS})

else()

  kconfig_add_kcfg_files(carbonstyle_LIB_SRCS
    carbonactiveshadowconfiguration.kcfgc
    carboninactiveshadowconfiguration.kcfgc
 )

  add_library(carbonstyle5 ${carbonstyle_LIB_SRCS})

  generate_export_header(carbonstyle5 BASE_NAME carbon EXPORT_FILE_NAME carbon_export.h)

  # NB: although we install no headers, we still need to have a link
  #     interface, since other Carbon targets link to this library
  target_link_libraries(carbonstyle5
      PUBLIC
          Qt5::Core
          Qt5::Gui
          Qt5::Widgets
          KF5::ConfigCore
          KF5::ConfigWidgets
      PRIVATE
          KF5::GuiAddons
 )

  target_include_directories(carbonstyle5 PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

  if(CARBON_HAVE_X11)
      target_link_libraries(carbonstyle5 PRIVATE XCB::XCB Qt5::X11Extras)
  endif()

  set_target_properties(carbonstyle5 PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
  if(WIN32)
      # As stated in http://msdn.microsoft.com/en-us/library/4hwaceh6.aspx M_PI only gets defined
      # when using MSVC if _USE_MATH_DEFINES is defined (this is needed for angle.cpp)
      target_compile_definitions(carbonstyle5 PRIVATE _USE_MATH_DEFINES _GNU_SOURCE)
  endif()
  install(TARGETS carbonstyle5 ${INSTALL_TARGETS_DEFAULT_ARGS})

endif()

################# libcarbonstyleconfig #################
set(carbonstyleconfig_LIB_SRCS
    carbonanimationconfigitem.cpp
    carbonbaseanimationconfigwidget.cpp
    carbongenericanimationconfigitem.cpp
    carbonshadowconfigwidget.cpp
)

set(carbonstyleconfig_LIB_FORMS
    ui/carbonanimationconfigitem.ui
    ui/carbonanimationconfigwidget.ui
    ui/carbongenericanimationconfigbox.ui
    ui/carbonshadowconfigurationui.ui
)

if(CARBON_USE_KDE4)

  kde4_add_ui_files(carbonstyleconfig_LIB_FORMS_HEADERS ${carbonstyleconfig_LIB_FORMS})
  kde4_add_kcfg_files(carbonstyleconfig_LIB_SRCS
      carbonactiveshadowconfiguration.kcfgc
      carboninactiveshadowconfiguration.kcfgc
 )

  kde4_add_library(carbonstyleconfig SHARED
      ${carbonstyleconfig_LIB_SRCS}
      ${carbonstyleconfig_LIB_FORMS_HEADERS})

  generate_export_header(carbonstyleconfig BASE_NAME carbon_config EXPORT_FILE_NAME carbon_config_export.h)

  target_link_libraries(carbonstyleconfig ${KDE4_KDEUI_LIBS})

  set_target_properties(carbonstyleconfig PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
  install(TARGETS carbonstyleconfig ${INSTALL_TARGETS_DEFAULT_ARGS})

  # NB: although we install no headers, we still need to have a link
  #     interface, since other Carbon targets link to this library
  target_link_libraries(carbonstyleconfig carbonstyle)

else()

  ki18n_wrap_ui(carbonstyleconfig_LIB_FORMS_HEADERS ${carbonstyleconfig_LIB_FORMS})

  kconfig_add_kcfg_files(carbonstyleconfig_LIB_SRCS
      carbonactiveshadowconfiguration.kcfgc
      carboninactiveshadowconfiguration.kcfgc
 )

  add_library(carbonstyleconfig5 SHARED
      ${carbonstyleconfig_LIB_SRCS}
      ${carbonstyleconfig_LIB_FORMS_HEADERS})

  generate_export_header(carbonstyleconfig5 BASE_NAME carbon_config EXPORT_FILE_NAME carbon_config_export.h)

  # NB: although we install no headers, we still need to have a link
  #     interface, since other Carbon targets link to this library
  target_link_libraries(carbonstyleconfig5
       PUBLIC
          carbonstyle5
          Qt5::Core
          Qt5::Gui
          Qt5::Widgets
      PRIVATE
          KF5::I18n
 )

  set_target_properties(carbonstyleconfig5 PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
  install(TARGETS carbonstyleconfig5 ${INSTALL_TARGETS_DEFAULT_ARGS})
  # Note: no headers installed

endif()
