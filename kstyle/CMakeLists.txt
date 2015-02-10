project(kstyle-carbon)

################# includes #################
include_directories(
    animations
    debug
    transitions
)

include_directories(${CMAKE_SOURCE_DIR}/libcarbon)
include_directories(${CMAKE_BINARY_DIR}/libcarbon)

########### next target ###############
set(carbon_PART_SRCS
    animations/carbonanimations.cpp
    animations/carbonanimationdata.cpp
    animations/carbonbaseengine.cpp
    animations/carbonbusyindicatordata.cpp
    animations/carbonbusyindicatorengine.cpp
    animations/carbondockseparatordata.cpp
    animations/carbondockseparatorengine.cpp
    animations/carbonenabledata.cpp
    animations/carbongenericdata.cpp
    animations/carbonheaderviewdata.cpp
    animations/carbonheaderviewengine.cpp
    animations/carbonmdiwindowdata.cpp
    animations/carbonmdiwindowengine.cpp
    animations/carbonmenubardata.cpp
    animations/carbonmenubarengine.cpp
    animations/carbonmenudata.cpp
    animations/carbonmenuengine.cpp
    animations/carbonprogressbardata.cpp
    animations/carbonprogressbarengine.cpp
    animations/carbonscrollbardata.cpp
    animations/carbonscrollbarengine.cpp
    animations/carbonspinboxdata.cpp
    animations/carbonspinboxengine.cpp
    animations/carbonsplitterengine.cpp
    animations/carbontabbardata.cpp
    animations/carbontabbarengine.cpp
    animations/carbontoolbardata.cpp
    animations/carbontoolbarengine.cpp
    animations/carbontoolboxengine.cpp
    animations/carbonwidgetstatedata.cpp
    animations/carbonwidgetstateengine.cpp
    debug/carbonwidgetexplorer.cpp
    transitions/carboncomboboxdata.cpp
    transitions/carboncomboboxengine.cpp
    transitions/carbonlabeldata.cpp
    transitions/carbonlabelengine.cpp
    transitions/carbonlineeditdata.cpp
    transitions/carbonlineeditengine.cpp
    transitions/carbonstackedwidgetdata.cpp
    transitions/carbonstackedwidgetengine.cpp
    transitions/carbontransitiondata.cpp
    transitions/carbontransitions.cpp
    transitions/carbontransitionwidget.cpp
    carbonblurhelper.cpp
    carbonframeshadow.cpp
    carbonmdiwindowshadow.cpp
    carbonmnemonics.cpp
    carbonpropertynames.cpp
    carbonshadowhelper.cpp
    carbonsplitterproxy.cpp
    carbonstyle.cpp
    carbonstylehelper.cpp
    carbonstyleplugin.cpp
    carbonwindowmanager.cpp
)

if(CARBON_USE_KDE4)

  kde4_add_kcfg_files(carbon_PART_SRCS carbonstyleconfigdata.kcfgc)
  kde4_add_plugin(carbon ${carbon_PART_SRCS})
  target_link_libraries(carbon ${KDE4_KDEUI_LIBS})
  target_link_libraries(carbon carbonstyle)

  if(CARBON_HAVE_X11)
    target_link_libraries(carbon ${X11_XCB_LIBRARIES})
    target_link_libraries(carbon ${XCB_LIBRARIES})
  endif()

  install(TARGETS carbon DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/styles/)

else()

  kconfig_add_kcfg_files(carbon_PART_SRCS carbonstyleconfigdata.kcfgc)
  add_library(carbon MODULE ${carbon_PART_SRCS})

  target_link_libraries(carbon Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(carbon KF5::GuiAddons KF5::Style KF5::WindowSystem)
  target_link_libraries(carbon carbonstyle5)

  if(CARBON_HAVE_X11)
    target_link_libraries(carbon XCB::XCB)
    target_link_libraries(carbon Qt5::X11Extras)
  endif()

  install(TARGETS carbon DESTINATION ${QT_PLUGIN_INSTALL_DIR}/styles/)

endif()

if(WIN32)
  # As stated in http://msdn.microsoft.com/en-us/library/4hwaceh6.aspx M_PI only gets defined
  # when using MSVC if _USE_MATH_DEFINES is defined (this is needed for angle.cpp)
  target_compile_definitions(carbon PRIVATE _USE_MATH_DEFINES _GNU_SOURCE)
endif()

########### install files ###############
install(FILES carbon.themerc  DESTINATION  ${DATA_INSTALL_DIR}/kstyle/themes)

########### subdirectories ###############
add_subdirectory(config)
add_subdirectory(demo)
