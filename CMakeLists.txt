cmake_minimum_required(VERSION 3.16)
project(wineyards)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(GENERATE_MOC ON)
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(CaravelLib REQUIRED)

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
include(ECMQtDeclareLoggingCategory)


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
  src/wineyards_package.cpp
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
    CaravelLib
    INIReader
)

set(wineyards_kio_SRC
    winekio/kio_wineyards.cpp
)

add_library(kio_wineyards MODULE)



set_target_properties(kio_wineyards PROPERTIES
    OUTPUT_NAME "wineyards"
)

target_sources(kio_wineyards PRIVATE ${wineyards_kio_SRC})

target_link_libraries(kio_wineyards
   KF5::KIOCore KF5::I18n   KF5::KIOFileWidgets
)

ecm_qt_declare_logging_category(kio_wineyards
    HEADER kio_wineyards_debug.h
    IDENTIFIER LOG_KIO_WINEYARDS
    CATEGORY_NAME kf.kio.slaves.wineyards
    OLD_CATEGORY_NAMES kio_wineyards
    DESCRIPTION "KIO wineyards"
    EXPORT KIO_WINEYARDS
)


ecm_qt_install_logging_categories(
    EXPORT KIO_WINEYARDS
    FILE kio-wineyards.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)



# Install the executable
install(TARGETS wineyards DESTINATION bin)

install(FILES wineyards.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES src/wineyardsui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/wineyards)
install(FILES wineyardssettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES wineyards.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})
install(TARGETS kio_wineyards  DESTINATION /opt/kf5/plugins/kf${QT_MAJOR_VERSION}/kio )
