#!/usr/bin/python3
# -*- coding: utf-8 -*-
# File name : Scene.py
# Author : MasterLaplace
# # Created : 2023-10-16
# Description : Scene for the application

import sys
import os
import re

from PyQt5.QtGui import QIcon

from ParseArgument import __CREDITS__, __VERSION__
from Widgets import *

class SceneManager(QMainWindow):
    def __init__(self, fullscreen: bool=False):
        super().__init__()
        self.fullscreen = fullscreen
        self.WIN_X = 600
        self.WIN_Y = 400
        self.project_graphycal = ''
        self.project_name = ''
        self.project_version = ''
        self.InitUI()
        if self.fullscreen:
            self.setWindowState(Qt.WindowFullScreen)

    def InitUI(self):
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.stacked_widget = QStackedWidget()

        self.stacked_widget.addWidget(self.HomePage())
        self.stacked_widget.addWidget(self.CreateProjectPage())
        self.stacked_widget.addWidget(self.SettingsPage())
        self.stacked_widget.addWidget(self.CreditsPage())

        self.central_layout = QVBoxLayout()
        self.central_layout.addWidget(self.stacked_widget)
        self.central_widget.setLayout(self.central_layout)

        self.setGeometry(int(self.WIN_X/2), int(self.WIN_Y/2), self.WIN_X, self.WIN_Y)
        self.setWindowTitle('Engine-3D Launcher')
        self.setWindowIcon(QIcon('./Image/Logo_1.png'))
        # Create system tray icon
        self.CreateSystemTrayIcon()

    def HomePage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.CreateLabel([0, 0], 'Welcome to Engine-3D Launcher'))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Create a new project', self.ShowCreateProject))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Open a project (config.xml)', self.ShowFileDialog))
        self.xml_text = QTextEdit(self)
        self.xml_text.setReadOnly(True)
        layout.addWidget(self.xml_text)
        self.run_button = Widgets.CreateButton([0, 0], [0, 0], 'Launch project', self.ShowRunProject)
        self.run_button.setEnabled(False)
        layout.addWidget(self.run_button)
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Credits', self.ShowCredits))

        return Widgets(layout)

    def CreateProjectPage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.CreateLabel([0, 0], 'Engine-3D Create Project:'))
        layout.addWidget(Widgets.CreateLabel([0, 0], 'Project name:'))
        layout.addWidget(Widgets.CreateLineEdit([0, 0], [0, 0], self.ChangeProjectName))
        layout.addWidget(Widgets.CreateLabel([0, 0], 'Graphycal API:'))
        layout.addWidget(Widgets.CreateComboBox([0, 0], [0, 0], ['sdl2', 'CSFML', 'SFML', 'OpenGL', 'Vulkan'], self.ChangeProjectGraphycal))
        layout.addWidget(Widgets.CreateLabel([0, 0], 'Engine-3D version:'))
        layout.addWidget(Widgets.CreateComboBox([0, 0], [0, 0], ['0.2.0', '0.1.0'], self.ChangeProjectVersion))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Create', self.CreateProject))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Home', self.ShowHome))

        return Widgets(layout)

    def SettingsPage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.CreateLabel([0, 0], 'Engine-3D Settings:'))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Home', self.ShowHome))

        return Widgets(layout)

    def CreditsPage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.CreateLabel([0, 0], 'Engine-3D Credits:'))
        layout.addWidget(Widgets.CreateLabel([0, 0], __CREDITS__))
        layout.addWidget(Widgets.CreateLabel([0, 0], 'Engine-3D Launcher version: ' + __VERSION__))
        layout.addWidget(Widgets.CreateButton([0, 0], [0, 0], 'Home', self.ShowHome))

        return Widgets(layout)

    def CreateSystemTrayIcon(self):
        self.tray_icon = QSystemTrayIcon(QIcon('./Image/Logo_1.png'), self)
        self.tray_icon.show()

        tray_menu = QMenu(self)

        about_action = QAction('About', self)
        about_action.triggered.connect(self.ShowCredits)
        tray_menu.addAction(about_action)
        reopen_action = QAction('Open', self)
        reopen_action.triggered.connect(self.show)
        tray_menu.addAction(reopen_action)
        exit_action = QAction('Exit', self)
        exit_action.triggered.connect(self.CloseApplication)
        tray_menu.addAction(exit_action)

        self.tray_icon.setContextMenu(tray_menu)

    def CreateProject(self):
        if self.project_name == '':
            self.project_name = 'NewProject'
        if self.project_graphycal == '':
            self.project_graphycal = 'CSFML'
        if self.project_version == '':
            self.project_version = '0.2.0'

        __XML_TEMPLATE__ = f"""\
<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
    <Info name="{self.project_name}" graphycal="{self.project_graphycal.lower()}" version="{self.project_version}"/>
</sbml>
"""

        filename = f'Projects/{self.project_name}/config.xml'
        os.makedirs(os.path.dirname(filename), exist_ok=True)
        with open(filename, "w", encoding='utf-8') as file:
            file.write(__XML_TEMPLATE__)

        self.project_graphycal = ''
        self.project_name = ''
        self.project_version = ''
        self.ShowHome()

    def ShowHome(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(0)

    def ShowSettings(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(2)

    def ShowCredits(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(3)

    def ShowCreateProject(self):
        if not self.isActiveWindow():
            self.hide()
        self.stacked_widget.setCurrentIndex(1)

    def ShowRunProject(self):
        if self.isActiveWindow():
            self.hide()
        self.run_button.setEnabled(False)
        self.stacked_widget.setCurrentIndex(0)

        info_pattern = r'<Info\s+name="([^"]+)"\s+graphycal="([^"]+)"'
        match = re.search(info_pattern, self.xml_content)

        if match:
            name = match.group(1)
            graphycal = match.group(2)
            os.system(f'make run {name} {graphycal} -s')

    def ShowFileDialog(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly

        self.file_name, _ = QFileDialog.getOpenFileName(self, 'Open XML File', '', 'XML Files (*.xml)', options=options)

        if self.file_name:
            with open(self.file_name, 'r', encoding='utf-8') as file:
                self.xml_content = file.read()
                self.xml_text.setPlainText(self.xml_content)
                self.run_button.setEnabled(True)

    def ChangeProjectName(self, name):
        self.project_name = name
    def ChangeProjectGraphycal(self, graphycal):
        self.project_graphycal = graphycal
    def ChangeProjectVersion(self, version):
        self.project_version = version

    def CloseApplication(self):
        self.tray_icon.hide()
        sys.exit()

    def keyPressEvent(self, e):
        """_summary_ Handles key press events in the window

        Args:
            e (_type_): _description_ event to handle
        """
        if e.key() == Qt.Key_Escape:
            self.close()
        elif e.key() == Qt.Key_F12:
            if not self.isFullScreen():
                self.setWindowState(Qt.WindowFullScreen)
            else:
                self.setWindowState(Qt.WindowNoState)
        elif e.key() == Qt.Key_F11:
            if not self.isMaximized():
                self.setWindowState(Qt.WindowMaximized)
            else:
                self.setWindowState(Qt.WindowNoState)
