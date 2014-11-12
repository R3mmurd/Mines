QMAKE_CXXFLAGS += -std=c++11

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
