cmake_minimum_required(VERSION 3.7)
project(BrainPad)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .vs/BrainPad/v15/Browse.VC.db
        .vs/ProjectSettings.json
        .vs/slnx.sqlite
        .vs/VSWorkspaceState.json
        About.png
        aboutdialog.cpp
        aboutdialog.h
        aboutdialog.ui
        accept.png
        answer.cpp
        answer.h
        answer.ui
        appresources.qrc
        brainfktoc.cpp
        brainfktoc.h
        BrainPad.pro
        BrainPad.pro.user
        BrainPad.pro.user.ac85f3d
        BrainPad.pro.user.b73c511
        C2-icon.png
        console.ui
        consoledialog.cpp
        consoledialog.h
        consoledialog.ui
        Copy.png
        Cut.png
        Dark.png
        Default.png
        Delete.png
        emoticon_tongue.png
        Exit.png
        Interperate.png
        interpreter.cpp
        lex.cpp
        lex.h
        main.cpp
        mainwindow.cpp
        mainwindow.cpp.K11184
        mainwindow.h
        mainwindow.ui
        New.png
        Open.png
        Paste.png
        Redo.png
        Save.png
        "Select All.png"
        syntaxhighlighter.cpp
        syntaxhighlighter.h
        syntaxhighlighterdark.cpp
        syntaxhighlighterdark.h
        tag_orange.png
        Undo.png)

add_executable(BrainPad ${SOURCE_FILES})