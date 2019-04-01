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
        self.ants_arrived = 0
        self.error_message = ""

    def check_unique_action(self, action, nb_line, actions = None) :
        if actions == None :
            actions = self.actions
        if self.map_parser.find_room(action[1]) == None :
            self.error_message = "Room : on line {} doesn'exist"\
                    .format(action[1], nb_line)
            return (1)
        if action[1] in map_parser.start.tab_link :
            return (0)
        for i in range(nb_line - 1, -1, -1) :
            index = np.where(actions[i][:, 0] == action[0])[0]
            if len(index) == 1 :
                room = actions[i][int(index)][1]
                room = map_parser.find_room(room)
                if map_parser.find_room(action[1]) not in room.tab_link :
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
                print(self.raw_actions[i])
                return (1)
        if self.ants_arrived != self.map_parser.ants :
            print("Wrong number of ants arrived : \nAnts arrived : {}\nMap ants : {}"\
                    .format(self.ants_arrived, self.map_parser.ants))
        return (0)

    def check_map_output(self, map_output = "") :
        if map_output == "" : 
            map_output = self.map_output

    def check_output(self) :
        self.output = [line.rstrip("\n") for line in self.output]
        print("\n".join(self.output))
        for i in range(len(self.output)) :
            if self.output[i] == "" :
                self.actions = self.output[i + 1 :]
                self.raw_actions = self.output[i + 1 :]
                return (self.check_actions())
        print("Wrong output format : No '\n' separator between map and actions")
        return (1)
        
class   Map_Exec() :
    def __init__(self, output = "", map_gen = "") :
        self.output = output
        self.map_gen = map_gen

    def generate_map(self, option = "--big-superposition", map_name = "map") :
        os.system("./maps/generator " + option + " > " + map_name)

    def exec_lem_in(self, path_map = "map") :
        self.map_gen = os.popen("cat " + path_map).readlines()
        self.output = os.popen("./lem-in < " + path_map).readlines()

if __name__ == "__main__" :
    map_exec = Map_Exec()
    map_exec.exec_lem_in("maps/best_path")
    map_parser = parser.Map_Parser(map_exec.map_gen)
    map_parser.parse_map()
    output_checker = Output_Checker(map_exec.output, map_parser)
    output_checker.check_output()
    print(map_parser)
