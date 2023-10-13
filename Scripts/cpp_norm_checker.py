#!/usr/bin/env python3
# # -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: cpp_norm_checker.py
# Author: MasterLaplace
# Created on: 2023-10-12

import os
import re

class NormChecker:
    def __init__(self):
        self.nb_errors = 0

    def check_End_Of_File(self, file_name: str, content: str):
        """_summary_
        * The file must end with a new line
        * The EOF must be alone on its line
        """
        lines = content.split('\n')

        last_line = lines[-1]
        if last_line.strip() != '':
            raise AssertionError(f"The file \"{file_name}\" does not end with an empty line.")


    def check_structure_name(self, file_name: str, content: str):
        """_summary_
        * All the structure names must start with a capital letter and end with _s
        """
        pattern = r'struct\s+(\w+)\s*{'
        incorrect_structures = []

        matches = re.findall(pattern, content)
        for struct_name in matches:
            if not struct_name[0].isupper() or not struct_name.endswith('_s'):
                incorrect_structures.append(struct_name)

        if incorrect_structures:
            print(f"Incorrect structure names found in file '{file_name}':")
            for struct_name in incorrect_structures:
                print(struct_name)
            raise AssertionError(f"The file \"{file_name}\" contains structures with incorrect names.")

    def check_namespace_name(self, file_name: str, content: str):
        """_summary_
        * All the namespace names must start with a capital letter
        """
        pattern = r'namespace\s+(\w+)\s*{'
        incorrect_namespaces = []

        matches = re.findall(pattern, content)
        for struct_name in matches:
            if not struct_name[0].isupper():
                incorrect_namespaces.append(struct_name)

        if incorrect_namespaces:
            print(f"Incorrect namespace names found in file '{file_name}':")
            for struct_name in incorrect_namespaces:
                print(struct_name)
            raise AssertionError(f"The file \"{file_name}\" contains namespaces with incorrect names.")

    def check_tab_size(self, file_name: str, content: str):
        """_summary_
        * All the lines must be indented with 4 spaces
        """
        lines_incorrect = []

        for i, ligne in enumerate(content.split('\n')):
            # Check if the line is a Doxygen documentation
            if ligne.strip().startswith('/**') or ligne.strip().startswith('*') or ligne.strip().startswith('*/'):
                continue

            # Check if the line contains comments
            if ligne.strip().startswith('#') or ligne.strip().startswith('//'):
                continue

            # Check line indentation
            indentation = len(ligne) - len(ligne.lstrip())
            if indentation % 4 != 0:
                lines_incorrect.append(i + 1)

        if lines_incorrect:
            raise AssertionError(f"The file \"{file_name}\" contains lines with incorrect indentation on the lines:", lines_incorrect)

    def call_all_checks(self, file_name: str, content: str):
        self.check_tab_size(file_name, content)
        self.check_structure_name(file_name, content)
        self.check_namespace_name(file_name, content)
        self.check_End_Of_File(file_name, content)


FOLDER_SRC = 'Engine/Plugins/'

def main():
    check_norm = NormChecker()

    for directory, subdirectories, files in os.walk(FOLDER_SRC):
        for file in files:
            file_path = os.path.join(directory, file)

            try:
                # We're only interested in C++ files
                if file_path.endswith('.cpp'):
                    if file != 'main.cpp' and not file[0].isupper() or file[0].isdigit():
                        raise AssertionError("The name of the file \"" + file_path + "\" does not start with a capital letter")
                    with open(file_path, 'r', encoding='latin-1') as f:
                        check_norm.call_all_checks(file_path, f.read())

                 # We're only interested in C++ Header files
                elif file_path.endswith('.hpp'):
                    if not file[0].isupper() or file[0].isdigit():
                        raise AssertionError("The name of the file \"" + file_path + "\" does not start with a capital letter")
                    with open(file_path, 'r', encoding='latin-1') as f:
                        check_norm.call_all_checks(file_path, f.read())
                else:
                    raise AssertionError("Unknow file detected in the Plugin: " + file_path)
            except AssertionError as e:
                check_norm.nb_errors += 1
                print(e)

    if check_norm.nb_errors > 0:
        raise AssertionError(f"\033[1;31mThere are {check_norm.nb_errors} error(s) in the plugins source code\033[0m")
    else:
        print("\033[1;32m► The plugins source code complies with C++ coding standards!\033[0m")

if __name__ == '__main__':
    main()
