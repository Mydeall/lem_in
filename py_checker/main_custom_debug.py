#!/usr/bin/env python
# coding: utf-8

import executer
import parser
import checker

if __name__ == "__main__" :
    map_exec = executer.Map_Exec()
    if (map_exec.read_custom_map(path_map = "map_m")) :
        print(map_exec.error_message)
    if (map_exec.exec_lem_in(path_map = "map_m") == 1) :
        print(map_exec.error_message)
    print("map_gen :")
    print(map_exec.map_gen)
    print("output :")
    print(map_exec.output)
    map_parser = parser.Map_Parser(map_exec.map_gen)
    if (map_parser.parse_map() == 1) :
        print("error during parsing")
    checker = checker.Output_Checker(map_exec.output, map_parser)
    if (checker.split_output() == 1) :
        print("error during split")
    elif (checker.check_map_output() == 1) :
        print("error during check map")
        print(checker.error_message)
    elif (checker.check_actions() == 1) :
        print("error during check actions")
        print(checker.error_message)
    print("steps : " + str(len(checker.actions)))


