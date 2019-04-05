#!/usr/bin/env python
# coding: utf-8

import os
import time 
import parser
import checker
import numpy as np

class   Map_Exec() :
    def __init__(self) :
        self.output = "" 
        self.map_gen = "" 
        self.error_message = ""

    def generate_map(self, option = "--big-superposition", map_name = "map") :
        ret = os.popen("./truc/generator " + option + " > " + map_name).readlines()
        if (ret != []) :
            self.error_message = ret
            return (1)
        return (0)

    def exec_lem_in(self, exec_name = "lem_in", path_map = "map") :
        self.map_gen = os.popen("cat " + path_map).readlines()
        print(self.map_gen)
        if (self.map_gen == []) :
            self.error_message = self.map_gen
            return (1)
        self.output = os.popen("./" + exec_name + " < " + path_map).readlines()
        print(self.output)
        if ("No such file" in self.output[0]) :
            self.error_message = self.output[0]
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

#    def display_result() :

    def execute_generator(self, nb_exec = -1, gen_option = "") :
        nb_exec = self.nb_exec if nb_exec == -1 else nb_exec
        gen_option = self.gen_option if gen_option == "" else gen_option
        for i in range(int(nb_exec)) :
            print("------- Test {}/{} -------".format(i + 1, nb_exec))
            map_exec = Map_Exec()
            map_exec.generate_map(gen_option)
            map_exec.exec_lem_in()
            map_parser = parser.Map_Parser(map_exec.map_gen)
            if map_parser.parse_map() == 1 :
                print("Wrong map")
                return (1)
            output_checker = checker.Output_Checker(map_exec.output, map_parser)
            if (output_checker.split_output() != 1) :
                if output_checker.check_map_output() == 1 or\
                        output_checker.check_actions() == 1 :
                    os.system("mv map map_error")
                    print("\nThe map has been registered has map_error")
                    break 
            step = len(output_checker.actions)
            print("Nb steps :       " + str(step))
            if map_parser.steps_required != None :
                self.result.append(step - map_parser.steps_required)
                print("Steps required : " + str(map_parser.steps_required))
            
            print("Difference : " + str(self.result[i]))
            if self.result[i] > self.lim_diff :
                os.system("mv map map_hard_" + str(i))
                print("This map has been register has map_hard_" + str(i))
            print("--------------------------\n")
            time.sleep(1)
        if self.result != [] :
            self.display_generator_summary()

class   Custom_Executer() :
    def __init__(self, path = "") :
        self.path = path

    def display_result(self, steps = -1, steps_required = -1, error_message = "") :
        print("------- Map : {} ------".format(self.path))
        if (error_message == "") :
            print("steps : " + str(self.steps))
            if (self.steps_required != -1) :
                print("steps_required : " + str(self.steps_required))
        else :
            print(error_message)
        print("--------------------------\n")

    def execute_custom(self, path = "") :
        self.path = self.path if path == "" else path
        if (self.path == "") :
            print("No path")
            return (1)
        map_exec = Map_Exec()
#        map_exec.generate_map()
        map_exec.exec_lem_in(path)
        map_parser = parser.Map_Parser(map_exec.map_gen)
        map_parser.parse_map()
        output_checker = checker.Output_Checker(map_exec.output, map_parser)
        if (output_checker.split_output() or output_checker.check_actions()\
                or output_checker.check_map_output()) :
            self.display_result(error_message = output_checker.error_message)
        else :
            steps = len(output_checker.answer)
            steps_required = map_parser.steps_required
            self.display_result(steps, steps_required)
        return (0)

if __name__ == "__main__" :
#    executer = Executer(50)
#    executer.execute_generator(gen_option = "--big")
#    executer.execute_generator()
#    specific_map("maps/best_combinaison")
    custom_exec = Custom_Executer()
    custom_exec.execute_custom("maps/best_combinaison")
