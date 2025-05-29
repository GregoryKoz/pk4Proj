cmake_minimum_required(VERSION 3.19)
project(Salon-projekt LANGUAGES CXX)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-std=c++20)
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Salon-projekt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    klient.h
    klient.cpp
    Salon.h
    Salon.cpp
    pojazd.h
    pojazd.cpp
    osobowy.h osobowy.cpp
    motocykl.h motocykl.cpp
    ciezarowy.h ciezarowy.cpp
    dodajklientadialog.h dodajklientadialog.cpp dodajklientadialog.ui
    resources.qrc
    dodajpojazddialog.h
    dodajosobowydialog.h dodajosobowydialog.cpp dodajosobowydialog.ui
    dodajciezarowydialog.h dodajciezarowydialog.cpp dodajciezarowydialog.ui
    dodajmotocykldialog.h dodajmotocykldialog.cpp dodajmotocykldialog.ui







)

target_link_libraries(Salon-projekt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Salon-projekt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Salon-projekt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
