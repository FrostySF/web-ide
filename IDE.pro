QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += s-lang/build/Default_Build_C_C-Release/release/libs-lang.a
#INCLUDEPATH += $$PWD/extstaticlibs

SOURCES += \
    main.cpp \
    mainide.cpp

HEADERS += \
    mainide.h

FORMS += \
    mainide.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/s-lang/build/Default_Build_C_C-Release/release/ -ls-lang
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/s-lang/build/Default_Build_C_C-Release/debug/ -ls-lang
else:unix: LIBS += -L$$PWD/s-lang/build/Default_Build_C_C-Release/ -ls-lang

INCLUDEPATH += $$PWD/s-lang/include
DEPENDPATH += $$PWD/s-lang/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/s-lang/build/Default_Build_C_C-Release/release/libs-lang.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/s-lang/build/Default_Build_C_C-Release/debug/libs-lang.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/s-lang/build/Default_Build_C_C-Release/release/s-lang.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/s-lang/build/Default_Build_C_C-Release/debug/s-lang.lib
else:unix: PRE_TARGETDEPS += $$PWD/s-lang/build/Default_Build_C_C-Release/libs-lang.a

# Static
QMAKE_LFLAGS += -static -static-libgcc
QMAKE_LFLAGS_RELEASE += -static -static-libgcc
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -Os -momit-leaf-frame-pointer
DEFINES += QT_STATIC_BUILD
CONFIG += static
# Static
