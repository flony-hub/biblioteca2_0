cmake_minimum_required(VERSION 3.16)

project(BibliotecaApp1_0 VERSION 0.1 LANGUAGES CXX)

# Habilitar soporte para UIC, MOC, y RCC de Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar los módulos de Qt necesarios (Widgets y Sql)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets AxContainer)

# Lista de archivos fuente y cabecera
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    libro.cpp
    libro.h
    usuario.cpp
    usuario.h
    prestamo.cpp
    prestamo.h
    databasemanager.cpp
    databasemanager.h
    dialogolibro.cpp
    dialogolibro.h
    dialogousuario.cpp
    dialogousuario.h
    dialogoprestamo.cpp
    dialogoprestamo.h
    dialogobusquedalibro.h
    dialogobusquedalibro.cpp

)

# Archivos UI (interfaces gráficas) y recursos
set(PROJECT_UI
    mainwindow.ui
    dialogolibro.ui
    dialogousuario.ui
    dialogoprestamo.ui
    dialogobusquedalibro.ui
)

set(PROJECT_RESOURCES
    resources.qrc
)

# Crear el ejecutable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BibliotecaApp1_0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_UI}
        ${PROJECT_RESOURCES}
        dialogobusquedalibro.h dialogobusquedalibro.cpp dialogobusquedalibro.ui
    )
else()
    add_executable(BibliotecaApp1_0
        ${PROJECT_SOURCES}
        ${PROJECT_UI}
        ${PROJECT_RESOURCES}
    )
endif()

# Enlazar las bibliotecas de Qt
target_link_libraries(BibliotecaApp1_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(BibliotecaApp1_0 PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::AxContainer)

# Configuraciones adicionales para macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BibliotecaApp1_0)
endif()
set_target_properties(BibliotecaApp1_0 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Instalación del ejecutable
include(GNUInstallDirs)
install(TARGETS BibliotecaApp1_0
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalización del ejecutable (solo para Qt 6)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BibliotecaApp1_0)
endif()
