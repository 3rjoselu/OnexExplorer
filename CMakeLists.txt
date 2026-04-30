cmake_minimum_required(VERSION 3.5)
project(OnexExplorer)

set(DTARGET_64 ON)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set(FREEGLUT_ROOT "C:/freeglut")
set(GLUT_INCLUDE_DIR "${FREEGLUT_ROOT}/include/GL")
set(GLUT_LIBRARIES "${FREEGLUT_ROOT}/lib/libfreeglut.dll.a")
include_directories(${GLUT_INCLUDE_DIR})

set(SOURCES
        Source/main.cpp
        Source/MainWindow.cpp
        Source/Converters/ImageConverter.cpp
        Source/Converters/LittleEndianConverter.cpp
        Source/Converters/NosModelConverter.cpp
        Source/Converters/ObjConverter.cpp
        Source/Decryptors/NosTextDatFileDecryptor.cpp
        Source/Decryptors/NosTextOthersFileDecryptor.cpp
        Source/Decryptors/NosZlibDecryptor.cpp
        Source/Openers/NosZlibOpener.cpp
        Source/Openers/NosCCInfOpener.cpp
        Source/Openers/NosTextOpener.cpp
        Source/Openers/INosFileOpener.cpp
        Source/Openers/JsonConfigOpener.cpp
        Source/Ui/OnexTreeItem.cpp
        Source/Ui/FileInfo.cpp
        Source/Ui/Settings.cpp
        Source/Ui/Previews/SingleTextFilePreview.cpp
        Source/Ui/Previews/SingleImagePreview.cpp
        Source/Ui/Previews/MultiImagePreview.cpp
        Source/Ui/Previews/SingleModelPreview.cpp
        Source/Ui/TreeItems/OnexTreeImage.cpp
        Source/Ui/TreeItems/OnexTreeText.cpp
        Source/Ui/TreeItems/OnexTreeZlibItem.cpp
        Source/Ui/TreeItems/OnexNSipData.cpp
        Source/Ui/TreeItems/OnexNS4BbData.cpp
        Source/Ui/TreeItems/OnexNStcData.cpp
        Source/Ui/TreeItems/OnexNStpData.cpp
        Source/Ui/TreeItems/OnexNStpMipMap.cpp
        Source/Ui/TreeItems/OnexNSmpData.cpp
        Source/Ui/TreeItems/OnexNSmpFrame.cpp
        Source/Ui/TreeItems/OnexNStgData.cpp
        Source/Ui/TreeItems/OnexNSmnData.cpp
        Source/Ui/TreeItems/OnexNSmcData.cpp
        )

set(MOC_HEADERS
        Source/MainWindow.h
        Source/NosEnumTypes.h
        Source/Converters/ImageConverter.h
        Source/Converters/LittleEndianConverter.h
        Source/Converters/IModelConverter.h
        Source/Converters/NosModelConverter.h
        Source/Converters/ObjConverter.h
        Source/Decryptors/NosTextDatFileDecryptor.h
        Source/Decryptors/NosTextOthersFileDecryptor.h
        Source/Decryptors/NosZlibDecryptor.h
        Source/Openers/NosZlibOpener.h
        Source/Openers/NosCCInfOpener.h
        Source/Openers/NosTextOpener.h
        Source/Openers/INosFileOpener.h
        Source/Openers/JsonConfigOpener.h
        Source/Ui/OnexTreeItem.h
        Source/Ui/FileInfo.h
        Source/Ui/Settings.h
        Source/Ui/Previews/SingleTextFilePreview.h
        Source/Ui/Previews/SingleImagePreview.h
        Source/Ui/Previews/MultiImagePreview.h
        Source/Ui/Previews/SingleModelPreview.h
        Source/Ui/TreeItems/OnexTreeImage.h
        Source/Ui/TreeItems/OnexTreeText.h
        Source/Ui/TreeItems/OnexTreeZlibItem.h
        Source/Ui/TreeItems/OnexNSipData.h
        Source/Ui/TreeItems/OnexNS4BbData.h
        Source/Ui/TreeItems/OnexNStcData.h
        Source/Ui/TreeItems/OnexNStpData.h
        Source/Ui/TreeItems/OnexNStpMipMap.h
        Source/Ui/TreeItems/OnexNSmpData.h
        Source/Ui/TreeItems/OnexNSmpFrame.h
        Source/Ui/TreeItems/OnexNStgData.h
        Source/Ui/TreeItems/OnexNSmnData.h
        Source/Ui/TreeItems/OnexNSmcData.h
        )

set(UIS
        Source/mainwindow.ui
        Source/Ui/Previews/SingleTextFilePreview.ui
        Source/Ui/Previews/SingleImagePreview.ui
        Source/Ui/Previews/MultiImagePreview.ui
        Source/Ui/Settings.ui
        )

set(RESOURCES
        resources.qrc
        )


# compile
#add_executable( PROJECT_NAME ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
# or use line below instead, if you using Windows ™ Operating System.
add_executable(OnexExplorer WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} ${RESOURCES})

# build it (link libraries)
target_link_libraries(OnexExplorer Qt5::Core)
target_link_libraries(OnexExplorer Qt5::Widgets)
target_link_libraries(OnexExplorer Qt5::Gui)
target_link_libraries(OnexExplorer ${GLUT_LIBRARIES} opengl32 glu32)

# post-build: deploy Qt DLLs and copy freeglut
get_target_property(QMAKE_EXE Qt5::qmake IMPORTED_LOCATION)
get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)
find_program(WINDEPLOYQT windeployqt HINTS "${QT_BIN_DIR}")

if(WINDEPLOYQT)
    add_custom_command(TARGET OnexExplorer POST_BUILD
        COMMAND "${WINDEPLOYQT}" $<TARGET_FILE:OnexExplorer>
        COMMENT "Deploying Qt DLLs..."
    )
endif()

add_custom_command(TARGET OnexExplorer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_ROOT}/bin/libfreeglut.dll"
        $<TARGET_FILE_DIR:OnexExplorer>
    COMMENT "Copying freeglut.dll..."
)
