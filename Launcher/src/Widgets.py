#!/usr/bin/python3
# -*- coding: utf-8 -*-
# File name : Widget.py
# Author : MasterLaplace
# Created : 2023-10-15
# Description : Widget for the application

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *

class Widgets(QWidget):
    """_summary_ Widget for the application

    Methods:
        - clear: _summary_ Clears the window
        - createSlider: _summary_ Creates a slider with the given parameters
        - createButton: _summary_ Creates a button in the window
        - createLabel: _summary_ Creates a label in the window
        - createLineEdit: _summary_ Creates a line edit in the window
        - createTable: _summary_ Creates a table in the window
        - createComboBox: _summary_ Creates a combo box in the window
        - createCheckBox: _summary_ Creates a check box in the window
        - createRadioButton: _summary_ Creates a radio button in the window
        - createProgressBar: _summary_ Creates a progress bar in the window
        - createSpinBox: _summary_ Creates a spin box in the window
        - createDial: _summary_ Creates a dial in the window
        - createLCDNumber: _summary_ Creates a LCD number in the window
        - createMenuBar: _summary_ Creates a menu bar in the window
        - keyPressEvent: _summary_ Handles key press events in the window
    """
    def __init__(self, layout: QVBoxLayout):
        super().__init__()
        self.setLayout(layout)

    @staticmethod
    def createSlider(ax: int, ay: int, aw: int, ah: int, min: int, max: int, step: int, value: int, func: object)-> QSlider:
        """_summary_ Creates a slider with the given parameters

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        slider = QSlider()
        slider.setGeometry(ax, ay, aw, ah)
        slider.setOrientation(Qt.Horizontal)
        slider.setMinimum(min)
        slider.setMaximum(max)
        slider.setValue(value)
        slider.setTickPosition(QSlider.TicksBelow)
        slider.setTickInterval(step)
        slider.valueChanged.connect(func)
        return slider

    @staticmethod
    def createButton(ax: int, ay: int, aw: int, ah: int, text: str, func: object)-> QPushButton:
        """_summary_ Creates a button in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            text (str): _description_ text to show
            func (object): _description_ function to call when clicked
        """
        button = QPushButton(text)
        button.setGeometry(ax, ay, aw, ah)
        button.clicked.connect(func)
        return button

    @staticmethod
    def createLabel(ax: int, ay: int, text: str)-> QLabel:
        """_summary_ Creates a label in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            text (str): _description_ text to show
        """
        my_text = QLabel(text)
        my_text.move(ax, ay)
        my_text.setAlignment(Qt.AlignCenter)
        return my_text

    @staticmethod
    def createLineEdit( ax: int, ay: int, aw: int, ah: int, func: object)-> QLineEdit:
        """_summary_ Creates a line edit in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            func (object): _description_ function to call when text changes

        Returns:
            _type_: _description_ text

        Examples:
            >>> def changeText(text):
            >>>     print(text)
            >>>
            >>> line_edit = Widgets.createLineEdit(0, 0, 100, 30, changeText)
        """
        line_edit = QLineEdit()
        line_edit.setGeometry(ax, ay, aw, ah)
        line_edit.textChanged.connect(func)
        return line_edit

    @staticmethod
    def createTable(ax: int, ay: int, aw: int, ah: int, rows: int, columns: int, headers: list, items: list)-> QTableWidget:
        """_summary_ Creates a table in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            rows (int): _description_ rows
            columns (int): _description_ columns
            headers (list): _description_ headers
            items (list): _description_ items to show in the table
        """
        table_widget = QTableWidget()
        table_widget.setGeometry(ax, ay, aw, ah)
        table_widget.setRowCount(rows)
        table_widget.setColumnCount(columns)
        table_widget.setHorizontalHeaderLabels(headers)
        for i in range(rows):
            for j in range(columns):
                table_widget.setItem(i, j, QTableWidgetItem(items[i][j]))
        return table_widget

    @staticmethod
    def createComboBox(ax: int, ay: int, aw: int, ah: int, items: list, func: object)-> QComboBox:
        """_summary_ Creates a combo box in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            items (list): _description_ items to show in the combo box
            func (object): _description_ function to call when item changes
        """
        combo_box = QComboBox()
        combo_box.setGeometry(ax, ay, aw, ah)
        combo_box.addItems(items)
        combo_box.currentTextChanged.connect(func)
        return combo_box

    @staticmethod
    def createCheckBox(ax: int, ay: int, aw: int, ah: int, text: str, func: object)-> QCheckBox:
        """_summary_ Creates a check box in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            text (str): _description_ text to show
            func (object): _description_ function to call when checked
        """
        check_box = QCheckBox(text, )
        check_box.setGeometry(ax, ay, aw, ah)
        check_box.stateChanged.connect(func)
        return check_box

    @staticmethod
    def createRadioButton(ax: int, ay: int, aw: int, ah: int, text: str, func: object)-> QRadioButton:
        """_summary_ Creates a radio button in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            text (str): _description_ text to show
            func (object): _description_ function to call when checked
        """
        radio_button = QRadioButton(text, )
        radio_button.setGeometry(ax, ay, aw, ah)
        radio_button.toggled.connect(func)
        return radio_button

    @staticmethod
    def createProgressBar(ax: int, ay: int, aw: int, ah: int, value: int)-> QProgressBar:
        """_summary_ Creates a progress bar in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            value (int): _description_ initial value
        """
        progress_bar = QProgressBar()
        progress_bar.setGeometry(ax, ay, aw, ah)
        progress_bar.setValue(value)
        return progress_bar

    @staticmethod
    def createSpinBox(ax: int, ay: int, aw: int, ah: int, min: int, max: int, step: int, value: int, func: object)-> QSpinBox:
        """_summary_ Creates a spin box in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        spin_box = QSpinBox()
        spin_box.setGeometry(ax, ay, aw, ah)
        spin_box.setMinimum(min)
        spin_box.setMaximum(max)
        spin_box.setSingleStep(step)
        spin_box.setValue(value)
        spin_box.valueChanged.connect(func)
        return spin_box

    @staticmethod
    def createDial(ax: int, ay: int, aw: int, ah: int, min: int, max: int, step: int, value: int, func: object)-> QDial:
        """_summary_ Creates a dial in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        dial = QDial()
        dial.setGeometry(ax, ay, aw, ah)
        dial.setMinimum(min)
        dial.setMaximum(max)
        dial.setSingleStep(step)
        dial.setValue(value)
        dial.valueChanged.connect(func)
        return dial

    @staticmethod
    def createLCDNumber(ax: int, ay: int, aw: int, ah: int, value: int)-> QLCDNumber:
        """_summary_ Creates a LCD number in the window

        Args:
            ax (int): _description_ x position
            ay (int): _description_ y position
            aw (int): _description_ width
            ah (int): _description_ height
        """
        lcd_number = QLCDNumber()
        lcd_number.setGeometry(ax, ay, aw, ah)
        lcd_number.display(value)
        return lcd_number

    @staticmethod
    def createMenuBar()-> QMenuBar:
        """_summary_ Creates a menu bar in the window
        """
        menu_bar = QMenuBar()
        menu_bar.setGeometry(0, 0, 600, 30)
        menu_bar.setNativeMenuBar(False)
        menu_bar.setStyleSheet("background-color: #333; color: #FFF;")
        return menu_bar
