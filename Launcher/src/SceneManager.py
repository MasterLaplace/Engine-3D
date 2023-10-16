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
    def __init__(self, fullscreen=False):
        super().__init__()
        self.fullscreen = fullscreen
        self.WIN_X = 600
        self.WIN_Y = 400
        self.initUI()
        if self.fullscreen:
            self.setWindowState(Qt.WindowFullScreen)

    def initUI(self):
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.stacked_widget = QStackedWidget()

        self.stacked_widget.addWidget(self.HomePage())
        self.stacked_widget.addWidget(self.SettingsPage())
        self.stacked_widget.addWidget(self.CreditsPage())

        self.central_layout = QVBoxLayout()
        self.central_layout.addWidget(self.stacked_widget)
        self.central_widget.setLayout(self.central_layout)

        self.setGeometry(int(self.WIN_X/2), int(self.WIN_Y/2), self.WIN_X, self.WIN_Y)
        self.setWindowTitle('Engine-3D Launcher')
        self.setWindowIcon(QIcon('./Image/Logo_1.png'))
        # Create system tray icon
        self.createSystemTrayIcon()

    def HomePage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.createLabel(0, 0, 'Welcome to Engine-3D Launcher'))
        layout.addWidget(Widgets.createButton(0, 0, 0, 0, 'Open a project (config.xml)', self.showFileDialog))
        self.xml_text = QTextEdit(self)
        self.xml_text.setReadOnly(True)
        layout.addWidget(self.xml_text)
        self.run_button = Widgets.createButton(0, 0, 0, 0, 'Launch project', self.showRunProject)
        self.run_button.setEnabled(False)
        layout.addWidget(self.run_button)
        layout.addWidget(Widgets.createButton(0, 0, 0, 0, 'Credits', self.showCredits))

        return Widgets(layout)

    def SettingsPage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.createLabel(0, 0, 'Engine-3D Settings:'))
        layout.addWidget(Widgets.createButton(0, 0, 50, 50, 'Home', self.showHome))

        return Widgets(layout)

    def CreditsPage(self)-> Widgets:
        layout = QVBoxLayout()

        layout.addWidget(Widgets.createLabel(0, 0, 'Engine-3D Credits:'))
        layout.addWidget(Widgets.createLabel(0, 0, __CREDITS__))
        layout.addWidget(Widgets.createLabel(0, 0, 'Engine-3D Launcher version: ' + __VERSION__))
        layout.addWidget(Widgets.createButton(0, 0, 50, 50, 'Home', self.showHome))

        return Widgets(layout)

    def createSystemTrayIcon(self):
        self.tray_icon = QSystemTrayIcon(QIcon('./Image/Logo_1.png'), self)
        self.tray_icon.show()

        tray_menu = QMenu(self)

        about_action = QAction('About', self)
        about_action.triggered.connect(self.showCredits)
        tray_menu.addAction(about_action)
        reopen_action = QAction('Open', self)
        reopen_action.triggered.connect(self.show)
        tray_menu.addAction(reopen_action)
        exit_action = QAction('Exit', self)
        exit_action.triggered.connect(self.closeApplication)
        tray_menu.addAction(exit_action)

        self.tray_icon.setContextMenu(tray_menu)

    def showHome(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(0)

    def showSettings(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(1)

    def showCredits(self):
        if not self.isActiveWindow():
            self.show()
        self.stacked_widget.setCurrentIndex(2)

    def showRunProject(self):
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

    def showFileDialog(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly

        self.file_name, _ = QFileDialog.getOpenFileName(self, 'Open XML File', '', 'XML Files (*.xml)', options=options)

        if self.file_name:
            with open(self.file_name, 'r', encoding='utf-8') as file:
                self.xml_content = file.read()
                self.xml_text.setPlainText(self.xml_content)
                self.run_button.setEnabled(True)

    def closeApplication(self):
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
