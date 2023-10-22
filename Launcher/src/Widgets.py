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
    def CreateSlider(pos: list[int], size: list[int], min: int, max: int, step: int, value: int, func: object)-> QSlider:
        """_summary_ Creates a slider with the given parameters

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        slider = QSlider()
        slider.setGeometry(pos[0], pos[1], size[0], size[1])
        slider.setOrientation(Qt.Horizontal)
        slider.setMinimum(min)
        slider.setMaximum(max)
        slider.setValue(value)
        slider.setTickPosition(QSlider.TicksBelow)
        slider.setTickInterval(step)
        slider.valueChanged.connect(func)
        return slider

    @staticmethod
    def CreateButton(pos: list[int], size: list[int], text: str, func: object)-> QPushButton:
        """_summary_ Creates a button in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            text (str): _description_ text to show
            func (object): _description_ function to call when clicked
        """
        button = QPushButton(text)
        button.setGeometry(pos[0], pos[1], size[0], size[1])
        button.clicked.connect(func)
        return button

    @staticmethod
    def CreateLabel(pos: list[int], text: str)-> QLabel:
        """_summary_ Creates a label in the window

        Args:
            pos (list[int]): _description_ position
            t_ext (str): _description_ text to show
        """
        my_text = QLabel(text)
        my_text.move(pos[0], pos[1])
        my_text.setAlignment(Qt.AlignCenter)
        return my_text

    @staticmethod
    def CreateLineEdit(pos: list[int], size: list[int], func: object)-> QLineEdit:
        """_summary_ Creates a line edit in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            func (object): _description_ function to call when text changes

        Returns:
            _type_: _description_ text

        Examples:
            >>> def ChangeText(text):
            >>>     print(text)
            >>>
            >>> line_edit = Widgets.createLineEdit(0, 0, 100, 30, changeText)
        """
        line_edit = QLineEdit()
        line_edit.setGeometry(pos[0], pos[1], size[0], size[1])
        line_edit.textChanged.connect(func)
        return line_edit

    @staticmethod
    def CreateTable(pos: list[int], size: list[int], rows: int, columns: int, headers: list, items: list)-> QTableWidget:
        """_summary_ Creates a table in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            rows (int): _description_ rows
            columns (int): _description_ columns
            headers (list): _description_ headers
            items (list): _description_ items to show in the table
        """
        table_widget = QTableWidget()
        table_widget.setGeometry(pos[0], pos[1], size[0], size[1])
        table_widget.setRowCount(rows)
        table_widget.setColumnCount(columns)
        table_widget.setHorizontalHeaderLabels(headers)
        for i in range(rows):
            for j in range(columns):
                table_widget.setItem(i, j, QTableWidgetItem(items[i][j]))
        return table_widget

    @staticmethod
    def CreateComboBox(pos: list[int], size: list[int], items: list, func: object)-> QComboBox:
        """_summary_ Creates a combo box in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            items (list): _description_ items to show in the combo box
            func (object): _description_ function to call when item changes
        """
        combo_box = QComboBox()
        combo_box.setGeometry(pos[0], pos[1], size[0], size[1])
        combo_box.addItems(items)
        combo_box.currentTextChanged.connect(func)
        return combo_box

    @staticmethod
    def CreateCheckBox(pos: list[int], size: list[int], text: str, func: object)-> QCheckBox:
        """_summary_ Creates a check box in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            text (str): _description_ text to show
            func (object): _description_ function to call when checked
        """
        check_box = QCheckBox(text)
        check_box.setGeometry(pos[0], pos[1], size[0], size[1])
        check_box.stateChanged.connect(func)
        return check_box

    @staticmethod
    def CreateRadioButton(pos: list[int], size: list[int], text: str, func: object)-> QRadioButton:
        """_summary_ Creates a radio button in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            text (str): _description_ text to show
            func (object): _description_ function to call when checked
        """
        radio_button = QRadioButton(text, )
        radio_button.setGeometry(pos[0], pos[1], size[0], size[1])
        radio_button.toggled.connect(func)
        return radio_button

    @staticmethod
    def CreateProgressBar(pos: list[int], size: list[int], value: int)-> QProgressBar:
        """_summary_ Creates a progress bar in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            value (int): _description_ initial value
        """
        progress_bar = QProgressBar()
        progress_bar.setGeometry(pos[0], pos[1], size[0], size[1])
        progress_bar.setValue(value)
        return progress_bar

    @staticmethod
    def CreateSpinBox(pos: list[int], size: list[int], min: int, max: int, step: int, value: int, func: object)-> QSpinBox:
        """_summary_ Creates a spin box in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        spin_box = QSpinBox()
        spin_box.setGeometry(pos[0], pos[1], size[0], size[1])
        spin_box.setMinimum(min)
        spin_box.setMaximum(max)
        spin_box.setSingleStep(step)
        spin_box.setValue(value)
        spin_box.valueChanged.connect(func)
        return spin_box

    @staticmethod
    def CreateDial(pos: list[int], size: list[int], min: int, max: int, step: int, value: int, func: object)-> QDial:
        """_summary_ Creates a dial in the window

        Args:
            pos (list[int]): _description_ position
            size (list[int]): _description_ size
            min (int): _description_ minimum value
            max (int): _description_ maximum value
            step (int): _description_ step value
            value (int): _description_ initial value
            func (object): _description_ function to call when value changes
        """
        dial = QDial()
        dial.setGeometry(pos[0], pos[1], size[0], size[1])
        dial.setMinimum(min)
        dial.setMaximum(max)
        dial.setSingleStep(step)
        dial.setValue(value)
        dial.valueChanged.connect(func)
        return dial

    @staticmethod
    def CreateLCDNumber(pos: list[int], size: list[int], value: int)-> QLCDNumber:
        """_summary_ Creates a LCD number in the window

        Args:
            pos (list[int]): _description_ position
            a_w (int): _description_ width
          _  ah (int): _description_ height
        """
        lcd_number = QLCDNumber()
        lcd_number.setGeometry(pos[0], pos[1], size[0], size[1])
        lcd_number.display(value)
        return lcd_number

    @staticmethod
    def CreateMenuBar()-> QMenuBar:
        """_summary_ Creates a menu bar in the window
        """
        menu_bar = QMenuBar()
        menu_bar.setGeometry(0, 0, 600, 30)
        menu_bar.setNativeMenuBar(False)
        menu_bar.setStyleSheet("background-color: #333; color: #FFF;")
        return menu_bar
