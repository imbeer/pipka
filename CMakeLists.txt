cmake_minimum_required(VERSION 3.21)

project(pipka VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

set(PROJECT_SOURCES
        src/main.cpp

        res/icons/icons.qrc
        res/shaders/shaders.qrc

        src/ui/window.h src/ui/window.cpp
        src/ui/canvaswidget.h src/ui/canvaswidget.cpp
        src/ui/eventhandler.h src/ui/eventhandler.cpp

        src/ui/menus/floatingwidget.h src/ui/menus/floatingwidget.cpp
        src/ui/menus/maintoolbar.h src/ui/menus/maintoolbar.cpp

        src/ui/palette.h
        src/ui/menus/lists/scrollbar.h  src/ui/menus/lists/scrollbar.cpp
        src/ui/menus/lists/toollist.h
        src/ui/menus/lists/layerlist.h src/ui/menus/lists/layerlist.cpp
        src/ui/menus/lists/layerlistmodel.h src/ui/menus/lists/layerlistmodel.cpp
        src/ui/menus/lists/listitemdelegate.h src/ui/menus/lists/listitemdelegate.cpp
        src/ui/menus/tools/colorselectorsquare.h src/ui/menus/tools/colorselectorsquare.cpp
        src/ui/menus/tools/colorselectorwidget.h src/ui/menus/tools/colorselectorwidget.cpp
        src/ui/menus/tools/colorselectorslider.h src/ui/menus/tools/colorselectorslider.cpp

        src/image/pixel-structure/rectangle.h

        src/image/pixel-structure/layer/layer.h
        src/image/pixel-structure/layer/chunkedlayer.h src/image/pixel-structure/layer/chunkedlayer.cpp
        src/image/pixel-structure/layer/unchunkedlayer.h src/image/pixel-structure/layer/unchunkedlayer.cpp

        src/image/pixel-structure/image.h src/image/pixel-structure/image.cpp
        src/image/pixel-structure/chunk.h src/image/pixel-structure/chunk.cpp
        src/image/pixel-structure/buffer/temporarypixelbuffer.h src/image/pixel-structure/buffer/temporarypixelbuffer.cpp
        src/image/color/color.h src/image/color/color.cpp
        src/image/color/blend.h src/image/color/blend.cpp

        src/control/tools/tool.h
        src/control/controller.h src/control/controller.cpp
        src/control/context/transform.h src/control/context/transform.cpp
        src/control/tools/rasterizer.h src/control/tools/rasterizer.cpp

        src/control/tools/brushes/brush.h src/control/tools/brushes/brush.cpp
        src/control/tools/brushes/squarebrush.h src/control/tools/brushes/squarebrush.cpp

        src/control/context/operations/versioncontrolsystem.h src/control/context/operations/versioncontrolsystem.cpp
        src/control/context/operations/operation.h
        src/control/context/operations/pixeloperation.h src/control/context/operations/pixeloperation.cpp

        src/control/repository/repository.h
        src/control/repository/brushrepository.h src/control/repository/brushrepository.cpp
        src/control/repository/blendrepository.h src/control/repository/blendrepository.cpp
        src/control/repository/toolrepository.h src/control/repository/toolrepository.cpp
        src/image/pixel-structure/buffer/layerversionbuffer.cpp
        src/image/pixel-structure/buffer/layerversionbuffer.h
        src/ui/menus/lists/brushlistmodel.cpp
        src/ui/menus/lists/brushlistmodel.h
        src/ui/menus/lists/brushitemdelegate.cpp
        src/ui/menus/lists/brushitemdelegate.h
        src/ui/menus/lists/brushlist.cpp
        src/ui/menus/lists/brushlist.h

)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pipka
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET pipka APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(pipka SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(pipka
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()

target_link_libraries(pipka PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.pipka)
endif ()
set_target_properties(pipka PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS pipka
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pipka)
endif ()
