#!/usr/bin/env python
# coding: utf-8

import os
import time 
import parser
import numpy as np

class   Output_Checker() :
    def __init__(self, output, map_parser) :
        self.output = output 
        self.map_parser = map_parser
        self.actions = None 
        self.raw_actions = "" 
        self.map_output = "" 
        self.ants_arrived = 0
        self.error_message = ""

    def check_unique_action(self, action, nb_line, actions = None) :
        if actions == None :
            actions = self.actions
        if self.map_parser.find_room(action[1]) == None :
            self.error_message = "Room : on line {} doesn'exist"\
                    .format(action[1], nb_line)
            return (1)
        if action[1] in self.map_parser.start.tab_link :
            return (0)
        for i in range(nb_line - 1, -1, -1) :
            index = np.where(actions[i][:, 0] == action[0])[0]
            if len(index) == 1 :
                room = actions[i][int(index)][1]
                room = self.map_parser.find_room(room)
                if self.map_parser.find_room(action[1]) not in room.tab_link :
                    self.error_message = "No link existing between {} (line : {}) and {} (line {})"\
                            .format(action[1], nb_line, room, i)
                    return (1)
                return (0)
            if i == 0 :
                self.error_message = "Ant {} in room {} come frome nowhere (line : {})"\
                        .format(action[0], action[1], nb_line)
        return (0)

    def check_step(self, nb_line, actions = None) :
        if (actions == None) :
            actions = self.actions
        lst_line = actions[nb_line]
        if (min(map(len, lst_line)) < 2) :
            self.error_message = "Wrong action format : line " + str(nb_line)
            return (1)
        uniques, counts = np.unique(lst_line[:, 0], return_counts=True)
        ants_error = [(key, value) for key, value in zip(uniques, counts)
                if value > 1]
        uniques, counts = np.unique(lst_line[:, 1], return_counts=True)
        nb_occur_room = dict(zip(uniques, counts))
        room_error = [(key, value) for key, value in nb_occur_room.items()\
                if value > 1 and key != self.map_parser.end.name]
        if len(ants_error) > 0 :
            self.error_message = "Ant in multiple room (" + str(ants_error)\
                    + "): line " + str(nb_line)
            return (1)
        if len(room_error) > 0 :
            self.error_message = "Multiple ants in a room (" + str(room_error)\
                    + "): line " + str(nb_line)
            return (1)
        if self.map_parser.end.name in nb_occur_room.keys() :
            self.ants_arrived += nb_occur_room[self.map_parser.end.name]
        for action in lst_line :
            if self.check_unique_action(action, nb_line) == 1 :
                return (1)
        return (0)

    def check_actions(self, actions = None) :
        if (actions == None) :
            actions = self.actions
        for i in range(len(self.actions)) :
            actions[i] = actions[i].replace("L", "", 1)
            actions[i] = actions[i].split(" L")
            actions[i] = np.array(\
                    [action.split("-", 1) for action in actions[i]])
            if (self.check_step(i, actions) == 1) :
                print(self.error_message)
                print("line : '{}'".format(self.raw_actions[i]))
#                f = open("output_error", "a")
 #               f.write("\n".join(list(actions)))
 #               f.close()
                return (1)
        if self.ants_arrived != self.map_parser.ants :
            print("Wrong number of ants arrived : \nAnts arrived : {}\nMap ants : {}"\
                    .format(self.ants_arrived, self.map_parser.ants))
            return (1)
        return (0)

    def check_map_output(self, map_output = "") :
        if map_output == "" : 
            map_output = self.map_output
        for i in range(len(map_output)) :
            if map_output[i] != self.map_parser.map_gen[i].rstrip("\n") :
                self.error_message = "The output map is not the same on line " + str(i)
                print(self.error_message)
                print("|" + str(map_output[i]) + "|")
                print("|" + str(self.map_parser.map_gen[i]) + "|")
                return (1)
        return (0)

    def split_output(self) :
        self.output = [line.rstrip("\n") for line in self.output]
#        print("\n".join(self.output))
        for i in range(len(self.output)) :
            if self.output[i] == "" :
                self.actions = self.output[i + 1 :]
                self.raw_actions = self.output[i + 1 :]
                self.map_output = self.output[:i - 1]
                return (0)
        print("Wrong output format : No '\n' separator between map and actions")
        return (1)
        
class   Map_Exec() :
    def __init__(self) :
        self.output = "" 
        self.map_gen = "" 

    def generate_map(self, option = "--big-superposition", map_name = "map") :
        os.system("./maps/generator " + option + " > " + map_name)

    def exec_lem_in(self, path_map = "map") :
        self.map_gen = os.popen("cat " + path_map).readlines()
        self.output = os.popen("./lem-in < " + path_map).readlines()

class   Executer() :
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
            output_checker = Output_Checker(map_exec.output, map_parser)
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

def specific_map(map_path) :
    map_exec = Map_Exec()
    map_exec.exec_lem_in(map_path)
    map_parser = parser.Map_Parser(map_exec.map_gen)
    map_parser.parse_map()
    output_checker = Output_Checker(map_exec.output, map_parser)
    output_checker.split_output()
    output_checker.check_actions()
    print(output_checker.ants_arrived)

if __name__ == "__main__" :
    executer = Executer(50)
 #   executer.execute_generator(gen_option = "--big")
    executer.execute_generator()
#    specific_map("maps/best_combinaison")

    
