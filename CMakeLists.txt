cmake_minimum_required(VERSION 3.16)
project(wineyards)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(GENERATE_MOC ON)
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

find_package(KF5 "5.86.0" REQUIRED COMPONENTS
    CoreAddons
    I18n
    XmlGui
    Completion
    ItemModels
    ItemViews
    Service
    ConfigWidgets
    Config
    TextWidgets
    KIO
    WidgetsAddons
    Notifications
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)



set(wineyards_SRC
  src/main.cpp
  src/wineyards.cpp  
  src/wineyard_struct.cpp
  src/wineyards_new.cpp
  src/wineyards_panel.cpp
  src/wineyards_lo.cpp
  src/wineyards_drives.cpp
  src/wineyard_rename.cpp
  src/wineyards_settings.cpp
  src/wineyards_gamescope.cpp
  src/wineyards_program.cpp
)
kconfig_add_kcfg_files(wineyards_SRC GENERATE_MOC  wineyardssettings.kcfgc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# Tell CMake to create the helloworld executable
add_executable(wineyards ${wineyards_SRC})
# Use the Widgets module from Qt 5.
target_link_libraries(wineyards  
    Qt5::Widgets 
    KF5::XmlGui 
    KF5::I18n 
    KF5::CoreAddons 
    KF5::Completion 
    KF5::TextWidgets 
    KF5::ItemModels 
    KF5::ItemViews
    KF5::ConfigWidgets
    KF5::ConfigCore
    KF5::KIOCore 
    KF5::KIOFileWidgets 
    KF5::KIOWidgets 
    KF5::KIONTLM
    KF5::ConfigGui
    KF5::WidgetsAddons
    KF5::Notifications
    INIReader
)

# Install the executable
install(TARGETS wineyards DESTINATION bin)

install(FILES wineyards.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES src/wineyardsui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/wineyards)
install(FILES wineyardssettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES wineyards.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})
