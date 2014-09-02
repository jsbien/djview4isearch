# #####################################################################
# Automatically generated by qmake (2.01a) czw. sie 27 19:06:01 2009
# #####################################################################
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += network xml opengl
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
RESOURCES = resources.qrc

TRANSLATIONS = i18n/pl.ts

win32 {
  RC_FILE = windows.rc
  LIBS = /home/michal/programming/build/djvulibre-windows/libdjvulibre.dll.a
}

macx {
  ICON = images/application.icns
  LIBS += /usr/local/lib/libdjvulibre.dylib
}

unix:!macx {
  LIBS = -ldjvulibre
  GID = $$system(hg id -n)
  DEFINES += HGID=\\\"$$HGID\\\"

  versiontarget.target = version.o
  versiontarget.depends = FORCE
  PRE_TARGETDEPS += version.o
  QMAKE_EXTRA_TARGETS += versiontarget
}

# Input
HEADERS += recentfiles.h \
	 mainwindow.h \
	 qdjvuwidget.h \
	 qdjvunet.h \
	 qdjvu.h \
	 messagedialog.h \
	 poliqarpwidget.h \
	 poliqarp.h \
	 djvulink.h \
	 preferencesdialog.h \
	 djvuitemlist.h \
	 version.h \
	 djvupreview.h \
	 djvuwidget.h \
	 logdialog.h \
	 replyparser.h \
	 poliqarpsettingsdialog.h \
	 helpdialog.h \
    aligneditemdelegate.h \
    textresultwidget.h \
    indexwidget.h \
    fileindex.h \
    entryindexdialog.h \
    log.h \
    entry.h
SOURCES += recentfiles.cpp \
	 mainwindow.cpp \
	 main.cpp \
	 qdjvuwidget.cpp \
	 qdjvunet.cpp \
	 qdjvu.cpp \
	 messagedialog.cpp \
	 poliqarpwidget.cpp \
	 poliqarp.cpp \
	 djvulink.cpp \
	 preferencesdialog.cpp \
	 djvuitemlist.cpp \
	 version.cpp \
	 djvupreview.cpp \
	 djvuwidget.cpp \
	 logdialog.cpp \
	 replyparser.cpp \
	 poliqarpsettingsdialog.cpp \
	 helpdialog.cpp \
    aligneditemdelegate.cpp \
    textresultwidget.cpp \
    indexwidget.cpp \
    fileindex.cpp \
    entryindexdialog.cpp \
    log.cpp \
    entry.cpp
FORMS = mainwindow.ui \
	 poliqarpwidget.ui \
	 preferencesdialog.ui \
	 logdialog.ui \
	 poliqarpsettingsdialog.ui \
	 helpdialog.ui \
    indexwidget.ui \
    entryindexdialog.ui

