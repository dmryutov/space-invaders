#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T15:58:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = invaders-Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gl_widget.cpp \
    textured_rect.cpp

HEADERS  += \
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
    point2d.hpp \
    ray2d.hpp \
    renderer.hpp \
    settings.hpp \
    gl_widget.hpp \
    textured_rect.hpp \
    mainwindow.hpp
