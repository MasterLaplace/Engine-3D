#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: increment_version.py
# Author: MasterLaplace
# Created on: 2023-10-12

import re

def increment_version(current_version: str):
    match = re.search(r'v(\d+\.\d+\.\d+)', current_version)
    if match:
        current_version_number = match.group(1)
        major, minor, patch = map(int, current_version_number.split('.'))
        return f"Engine-3D v{major}.{minor}.{patch + 1}"

    return current_version

if __name__ == "__main__":
    # Read the current version from the VERSION file
    with open("VERSION", "r") as version_file:
        current_version = version_file.read().strip()

    new_version = increment_version(current_version)

    # Update the VERSION file with the new version
    with open("VERSION", "w") as version_file:
        version_file.write(new_version)
