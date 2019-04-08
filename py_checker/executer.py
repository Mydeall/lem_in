#!/usr/bin/env python
# coding: utf-8

import os
import time 
import parser
import checker
import numpy as np
import subprocess

class   Map_Exec() :
    def __init__(self) :
        self.output = "" 
        self.map_gen = "" 
        self.error_message = ""

    def generate_map(self, option = "--big-superposition", map_name = "map") :
        pipe = subprocess.Popen(["maps/generator", str(option)],\
                stdout=subprocess.PIPE,\
                stderr=subprocess.PIPE,\
                universal_newlines=True)
        self.map_gen, self.error_message= pipe.communicate()
        if (self.error_message != "") :
            self.error_message = "Error during map generation.\n" + self.error_message
            return (1)
        f = open("map", "a")
        f.write(self.map_gen)
        f.close()
        return (0)

    def exec_lem_in(self, exec_name = "./lem-in", path_map = "map") :
        print(self.map_gen)
        output = subprocess.check_output([exec_name,  "< map"], stderr=subprocess.STDOUT)
#        pipe = subprocess.Popen([exec_name, self.map_gen],\
 #               stdout=subprocess.PIPE,\
  #              stderr=subprocess.PIPE)
   #     self.output, self.error_message = pipe.communicate()
        print(output)
        if (self.error_message != "") :
            self.error_message = "Error during execution of lem-in :\n"\
                    + self.error_message
            return (1)
        return (0)

class   Gen_Executer() :
    def __init__(self, nb_exec, gen_option = "--big-superposition", lim_diff = 15) :
        self.nb_exec = nb_exec
        self.gen_option = gen_option
        self.lim_diff = lim_diff 
        self.result = []

    def display_generator_summary(self) :
        self.result = sorted(self.result)
        dict_diff = dict.fromkeys(set(self.result), 0)
        total = sum(self.result)
        for value in list(self.result) :
            dict_diff[value] += 1
        print("\n------- SUMMARY ---------")
        print("Nb execution : " + str(self.nb_exec))
        print("Results : ", self.result)
        print("\nMin : ", min(self.result))
        print("Max : ", max(self.result))
        print("Moyenne des self.result : {} pour {} executions".format(\
                str(total / len(self.result)), str(len(self.result))))
        print("\nMAP : ")
        for key, value in dict_diff.items() :
            print("\t{} : {}".format(key, value))

    def display_result(steps = -1, steps_required = -1, error_message = "", warning = "") :
        if (warning != "") :
            print(warning)
        if (error_message != "") :
            print(error_message)
        else :
            print("Nb steps :       " + str(steps))
            print("Steps required : " + str(steps_required))
            print("Difference : " + str(steps_required - steps))
        print("--------------------------")

    def execute_generator(self, nb_exec = -1, gen_option = "") :
        nb_exec = self.nb_exec if nb_exec == -1 else nb_exec
        gen_option = self.gen_option if gen_option == "" else gen_option
        warning = ""
        for i in range(int(nb_exec)) :
            print("\n------- Test {}/{} -------".format(i + 1, nb_exec))
            map_exec = Map_Exec()
            if (map_exec.generate_map(gen_option) == 1) :
                self.display_result(error_message = str(map_exec.error_message))
                return (1)
            if (map_exec.exec_lem_in() == 1) :
                self.display_result(error_message = str(map_exec.error_message))
                return (1)
            map_parser = parser.Map_Parser(map_exec.map_gen)
            if (map_parser.parse_map() == 1) :
                warning = "WARNING : the map has not been read entirely"
            output_checker = checker.Output_Checker(map_exec.output, map_parser)
            if (output_checker.split_output() != 1) :
                if output_checker.check_map_output() == 1 or\
                        output_checker.check_actions() == 1 :
                    os.system("mv map map_error_" + str(i))
                    self.display_result(0, 0, output_checker.error_message +\
                            "\nThe map has been registered has map_error_" + str(i))
                    break 
            steps = len(output_checker.actions)
            if map_parser.steps_required != None :
                self.result.append(steps - map_parser.steps_required)
            if self.result[i] > self.lim_diff :
                os.system("mv map map_hard_" + str(i))
                warning += "This map has been register has map_hard_" + str(i)
            self.display_result(steps, int(map_parser.steps_required), "", warning)
            time.sleep(1)
        if self.result != [] :
            self.display_generator_summary()

class   Custom_Executer() :
    def __init__(self, path = "") :
        self.path = path

    def display_result(self, steps = -1, steps_required = -1, error_message = "") :
        print("\n------- Map : {} ------".format(self.path))
        if (error_message == "") :
            print("Actions are valid\n")
            print("steps : " + str(steps))
            if (steps_required != -1) :
                print("steps_required : " + str(steps_required))
        else :
            print(error_message)
        print("--------------------------")

    def execute_custom(self, path = "") :
        self.path = self.path if path == "" else path
        if (self.path == "") :
            print("No path")
            return (1)
        map_exec = Map_Exec()
        if (map_exec.exec_lem_in(path_map = path) == 1) :
            print(map_exec.error_message)
            return (1)
        map_parser = parser.Map_Parser(map_exec.map_gen)
        map_parser.parse_map()
        output_checker = checker.Output_Checker(map_exec.output, map_parser)
        if (output_checker.split_output() or output_checker.check_actions()\
                or output_checker.check_map_output()) :
            self.display_result(error_message = output_checker.error_message)
        else :
            steps = len(output_checker.actions)
            steps_required = map_parser.steps_required
            self.display_result(steps, steps_required)
        return (0)
