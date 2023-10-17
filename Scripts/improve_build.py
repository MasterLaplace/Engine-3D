#/usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: get_latest_release_date.py
# Author: MasterLaplace
# Created on: 2023-10-13

from time import sleep
import sys


bold = '\033[1m'
normal = '\033[0m'
red = '\033[31m\033[1m'
yellow = '\033[33m\033[1m'
green = '\033[32m\033[1m'

spaces = " "*50
sys.stdout.write('\r')
sys.stdout.write(spaces * 2)
sys.stdout.write('\r')

file = sys.argv[1]
nb = sys.argv[2]
all = sys.argv[3]

if nb > all:
    nb = all

place = 30
if int(all) == 0:
    percentage = 0
else:
    percentage = int(nb) * 100 / int(all)

display = bold + file
if len(file) < place:
    display += " " * (place - len(file))
display += "["
sys.stdout.write(display)

if percentage > 67:
    color = green
elif percentage > 33:
    color = yellow
else:
    color = red
sys.stdout.write(color)

sys.stdout.write(u"\u25AE" * int(int(percentage) * place / 100))
sys.stdout.write(" " * int(place - (percentage * place / 100)))

sys.stdout.write(normal + bold + "]" + "\t" + str(int(percentage)) + '%' + normal + "\t" +"(" + nb + '/' + all +")" + spaces )
sys.stdout.flush()
sleep(0.01)
