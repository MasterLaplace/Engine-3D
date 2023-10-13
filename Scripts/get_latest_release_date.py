#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: get_latest_release_date.py
# Author: MasterLaplace
# Created on: 2023-10-12

import requests
import json

# Replace with your GitHub repository information
repo_owner = "MasterLaplace"
repo_name = "Engine-3D"

# Fetch the latest release information from GitHub API
response = requests.get(f"https://api.github.com/repos/{repo_owner}/{repo_name}/releases/latest")
data = json.loads(response.text)

# Extract the release date
latest_release_date = data['published_at']

# publish at this format: **October 13, 2023**

formatted_date = f"**{latest_release_date[8:10]} {latest_release_date[5:7]}, {latest_release_date[:4]}**"

# Print the formatted date (you can also save it to a file)
print(formatted_date)
