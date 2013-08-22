CONFIG += warn_off

QMAKE_CXXFLAGS += -std=c++0x

LIBS += \
    -lgsl \
    -lgslcblas

HEADERS += \
    matrix.H \
    game_panel.H \
    game_frame.H \
    face.H

SOURCES += \
    matrix.C \
    main.C \
    game_panel.C \
    game_frame.C \
    face.C

RESOURCES += \
    images.qrc
