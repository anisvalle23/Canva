QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check

# Definir el nombre del ejecutable
TARGET = MiniCanvas

# Archivos fuente
SOURCES += \
    alumnos.cpp \
    clases.cpp \
    estructuras.cpp \
    maestros.cpp \
    main.cpp \
    mainwindow.cpp \
    registro.cpp

# Archivos de encabezado
HEADERS += \
    alumnos.h \
    clases.h \
    estructuras.h \
    maestros.h \
    mainwindow.h \
    registro.h

# Archivos de diseño UI
FORMS += \
    alumnos.ui \
    maestros.ui \
    mainwindow.ui \
    registro.ui

# Archivos de recursos
RESOURCES += \
    resources.qrc

# Archivos adicionales para la distribución
DISTFILES += \
    resources/Inicio.png

# Configuración de destino en diferentes plataformas
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
