#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T11:48:37
#
#-------------------------------------------------

QT += core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = invaders-GL
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    gl_widget.cpp \
    textured_rect.cpp

HEADERS  += \
    gl_widget.hpp \
    mainwindow.hpp \
    point2d.hpp \
    textured_rect.hpp \
    action_manager.hpp \
    alien_group.hpp \
    alien.hpp \
    box2d.hpp \
    bullet.hpp \
    game_entity.hpp \
    game.hpp \
    gun.hpp \
    log.hpp \
    obstacle.hpp \
    patterns.hpp \
    ray2d.hpp \
    renderer.hpp \
    settings.hpp \
    sound_manager.hpp \
    star.hpp \
    bonus.hpp \
    explosion.hpp

RESOURCES += data.qrc

DISTFILES +=
