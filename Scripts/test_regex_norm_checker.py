#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: test_regex_norm_checker.py
# Author: MasterLaplace
# Created on: 2023-10-12

import re

# # Define your regex pattern
# keyword_regex = r"^([a-z]+\([A-Za-z_.]+\)|^[a-z]+): "

# # List of sample commit messages
# commit_messages = [
#     "fix(readme): fix link about the wiki",
#     "fix(.github): move funding script",
#     "feat(main): add new feature",
#     "style: fix linting issues",
# ]

# # Test the regex pattern on each commit message
# for message in commit_messages:
#     match = re.search(keyword_regex, message)
#     if match:
#         print(f"Match found in '{message}': {match.group()}")
#     else:
#         print(f"No match found in '{message}'")


# Define regex for release date
realease_date_regex = r"- Release Date: \*\*([JFMASOND][a-z]+ \d+, \d+)\*\*"

# List of sample release notes
release_notes = """
> :clipboard: [Change Log](CHANGELOG.md).

- [![Latest Release](https://img.shields.io/github/v/release/MasterLaplace/Engine-3D.svg?label=version)](https://github.com/MasterLaplace/Engine-3D/releases/latest/)
- Release Date: **October 13, 2023**


<div id='license'/>
"""

# Test the regex pattern on each release note
match = re.search(realease_date_regex, release_notes)
if match:
    print(f"Match found in '{release_notes}': {match.group(1)}")
else:
    print(f"No match found in '{release_notes}'")
