#!/usr/bin/python3
# -*- coding: utf-8 -*-
# File name : Launcher.py
# Author : MasterLaplace
# Created : 2023-10-15
# Description : Main file for the application

import sys

from ParseArgument import ParseArgument
from SceneManager import *

def main():
    parser = ParseArgument()
    args = parser.parse()
    app = QApplication(sys.argv)
    window = SceneManager(fullscreen=args.fullscreen)
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
