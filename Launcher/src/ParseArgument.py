#!/usr/bin/python3
# -*- coding: utf-8 -*-
# File name : ParseArgument.py
# Author : MasterLaplace
# Created : 2023-10-15
# Description : Parse arguments for the application

from sys import exit
from argparse import ArgumentParser

__VERSION__ = "Launcher v0.1.0"

__COPYRIGHT__ = """\
Copyright (c) 2022-2023 Master_Laplace.  All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.\
"""

__CREDITS__ = """\
Engine-3D Credits:

Website:
https://github.com/MasterLaplace/Engine-3D

Developer:
Master_Laplace - Creator and maintainer of the project -

Publicher:
ME.inc - Publisher of the project -\
"""

class ParseArgument:
    """_summary_ ParseArgument class for the application

    Args:
        object (_type_): _description_ Object class
    """
    def __init__(self):
        self.parser = ArgumentParser(description='Engine-3D Launcher')
        self.parser.add_argument('-v', '--version', action='version', version=__VERSION__)
        self.parser.add_argument('-s', '--scene', type=int, help='Scene to show')
        self.parser.add_argument('-f', '--fullscreen', action='store_true', help='Fullscreen mode')
        self.parser.add_argument('-c', '--copyright', action='store_true', help='Display copyright')
        self.parser.add_argument('-C', '--credits', action='store_true', help='Display credits')

    def parse(self):
        """_summary_ Parse arguments

        Args:
            self (_type_): _description_ self

        Returns:
            _type_: _description_ _return_
        """
        args = self.parser.parse_args()

        if args.copyright:
            print(__COPYRIGHT__)
            exit()

        if args.credits:
            print(__CREDITS__)
            exit()
        return args
