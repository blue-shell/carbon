add_definitions(-DTRANSLATION_DOMAIN=\"carbon_style_demo\")

include_directories(${CMAKE_BINARY_DIR}/libcarbon)

########### next target ###############
set(carbon_demo_SOURCES
    carbonbenchmarkwidget.cpp
    carbonbuttondemowidget.cpp
    carbondemodialog.cpp
    carbondemowidget.cpp
    carbonframedemowidget.cpp
    carboninputdemowidget.cpp
    carbonlistdemowidget.cpp
    carbonmdidemowidget.cpp
    carbonsimulator.cpp
    carbonsliderdemowidget.cpp
    carbontabdemowidget.cpp
    carbontabwidget.cpp
    main.cpp)

set(carbon_demo_FORMS
    ui/carbonbenchmarkwidget.ui
    ui/carbonbuttondemowidget.ui
    ui/carbondemodialog.ui
    ui/carbonframedemowidget.ui
    ui/carboninputdemowidget.ui
    ui/carbonlistdemowidget.ui
    ui/carbonmdidemowidget.ui
    ui/carbonsliderdemowidget.ui
    ui/carbontabdemowidget.ui
)

if(CARBON_USE_KDE4)

  kde4_add_ui_files(carbon_demo_FORMS_HEADERS ${carbon_demo_FORMS})

  kde4_add_executable(carbon-demo
      ${carbon_demo_SOURCES}
      ${carbon_demo_FORMS_HEADERS}
 )

  target_link_libraries(carbon-demo ${KDE4_KDEUI_LIBS})

  ########### install files ###############
  install(TARGETS carbon-demo ${INSTALL_TARGETS_DEFAULT_ARGS})

else()

  ki18n_wrap_ui(carbon_demo_FORMS_HEADERS ${carbon_demo_FORMS})

  add_executable(carbon-demo5
      ${carbon_demo_SOURCES}
      ${carbon_demo_FORMS_HEADERS}
 )

  target_link_libraries(carbon-demo5 Qt5::Core Qt5::Gui Qt5::Widgets)
  target_link_libraries(carbon-demo5 KF5::Completion KF5::ConfigGui KF5::WidgetsAddons KF5::I18n)

  ########### install files ###############
  install(TARGETS carbon-demo5 ${INSTALL_TARGETS_DEFAULT_ARGS})

endif()
