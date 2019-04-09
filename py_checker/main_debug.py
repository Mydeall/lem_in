#!/usr/bin/env python
# coding: utf-8

import executer
import parser
import checker
import sys

if __name__ == "__main__" :
    map_exec = executer.Map_Exec()
    if (map_exec.generate_map() == 1) :
        print(map_exec.error_message)
        sys.exit()
    if (map_exec.exec_lem_in() == 1) :
        print(map_exec.error_message)
        sys.exit()
    map_parser = parser.Map_Parser(map_exec.map_gen)
    if (map_parser.parse_map() == 1) :
        print("error during parsing")
        sys.exit()
    checker = checker.Output_Checker(map_exec.output, map_parser)
    if (checker.split_output() == 1) :
        print("error during split")
        sys.exit()
    elif (checker.check_map_output() == 1) :
        print("error during check map")
        print(checker.error_message)
        sys.exit()
    elif (checker.check_actions() == 1) :
        print("error during check actions")
        print(checker.error_message)
        sys.exit()
    print("steps : " + str(len(checker.actions)))
    print("steps required : " + str(map_parser.steps_required))
