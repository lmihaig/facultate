"""ENUNT:

Identificator: ex-cautare-informata-exemple-modificate
Se va implementa o problema asemanatoare cu a canibalilor si misionarilor,
 indeplinind urmatoare conditii:
Avem N1 canibali, N2 misionari si K unitati de hrana pe un mal (pe malul
 celalalt nu avem nimic) și o barcă cu M locuri. Ne intereseaza sa mutam toți
  canibalii si misionarii pe malul opus. Nu ne interesaza neaparat sa mutam si
   hrana.
In cazul in care intr-unul dintre locuri (barca sau maluri) avem mai multi
 canibali decat misionari, acestia o sa-i atace.
Totusi misionarii pot evita sa fie atacati, hrandin canibalii cu unitati de
 hrana. Astfel, daca sunt NM (NM > 0) misionari si NC canibali intr-o locatie
  si NC>NM, misionarii pot evita sa fie atacati de canibali hranindu-i cu
   (NC-NM)/2 unitati de hrana (practic un canibal se satura cu 0.5 unitati
    de hrana.
Hrana poate fi mutata cu barca (dar trebuie mereu sa fie un om care carmuieste
 barca; barca nu se poate deplasa fara oameni). O unitate de hrana ocupa loc
  cat un om (nu se pot deplasa decat unitati intregi de hrana, nu jumatati).
   Canibalii nu mananca din hrana daca sunt singuri (doar un misionar le poate
    da, si le da numai daca e nevoie, adica daca sunt canibali mai multi
     decat misionari).
In plus, barca se degradeaza in timp. La fiecare Nr deplasari cu barca (de la
 un mal la celalalt) un loc din barca se va degrada (adica numarul de locuri
  din barca scade cu 1). Se va preciza in afisarea solutiei, pentru fiecare
   tranziție si cate locuri au ramas in barca
    (adica locuri care nu s-au stricat).
Costul unei mutări e dat de numărul de oameni din barcă

Fișierul de input va conține toți parametrii problemei în formatul:
 "nume parametru=valoare". De exemplu:
N1=4
N2=4
K=2
M=2
# Nr=3
MalInitial=vest
MalFinal=est
Solutiile vor reprezenta secventele de mutari. Afisarea în fișierul de output
 se va face scriind la fiecare moment de timp:

indicele stării (nodului) în drum
informații despre starea curenta (cati canibali, misionari si unități de hrană
 sunt pe malul de vest, cati canibali, misionari si hrană sunt pe malul de est)
Se va afișa între stări de la care mal pornesc bărcile si către care se duc și
 detaliat ce conțin.
Între două soluții se va afișa un separator, de exemplu "===================".
"""
import cProfile
from collections import deque
import errno
import json
import multiprocessing
import os
import heapq
import sys
from typing import Self


def parse(path: str) -> dict[str, int | str]:
    """
    Args:
        path (str): Path to the file that contains the dict values

    Raises:
        FileNotFoundError: If the file path is invalid

    Returns:
        ParamDict | None: Dictionary containing key value pairs
        representing the parameters
    """
    file_type = path.split(".")[-1]
    if file_type.endswith("json"):
        return json.load(open(path))

    if file_type.endswith("txt"):
        with open(path, "r") as file:
            vals = [line.strip().split("=")[-1] for line in file.readlines()]
            keys = [
                "cannibals",
                "missionaries",
                "start_food",
                "boat_seats",
                "boat_degradation",
                "init_shore",
                "final_shore",
            ]

            if len(vals) != len(keys):
                raise Exception("Invalid number of inputs in inputfile")

            for i, val in enumerate(vals):
                if i in [5, 6]:
                    if val in ["left", "right"]:
                        continue
                else:
                    if val.isnumeric():
                        vals[i] = int(val)
                        continue

                raise Exception("Invalid param format")
            return {key: val for key, val in zip(keys, vals)}

    raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), path)


class Node:
    def __init__(
        self,
        left_cannibals: int,
        left_missionaries: int,
        left_food: float,
        right_cannibals: int,
        right_missionaries: int,
        right_food: float,
        eaten_food: float,
        boat_seats: int,
        boat_counter: int,
        boat_shore: str,
        parent: Self,
        g_score: int,
        h_score: int,
    ):
        """Each Node contains the information for a given state

        Args:
            left_cannibals (int): number of cannibals on the left shore
            left_missionaries (int): number of missionaries on the left shore
            left_food (float): number of food units on the left shore
            right_cannibals (int): number of cannibals on the right shore
            right_missionaries (int): number of missionaries on the right shore
            right_food (float): number of food units on the right shore
            eaten_food (float): number of food units that have been eaten
            boat_seats (int): number of seats in the boat
            boat_counter (int): boat degradation counter
            boat_shore (str): which shore is the boat on
            parent (Self): parent Node of this Node
            g_score (int): path cost from start_node to this node
            h_score (int): heuristic cost from this node to goal_node
        """

        self.left_cannibals = left_cannibals
        self.left_missionaries = left_missionaries
        self.left_food = left_food
        self.right_cannibals = right_cannibals
        self.right_missionaries = right_missionaries
        self.right_food = right_food
        self.eaten_food = eaten_food
        self.boat_seats = boat_seats
        self.boat_counter = boat_counter
        self.boat_shore = boat_shore

        self.parent = parent
        self.g_score = g_score
        self.h_score = h_score
        self.f_score = self.g_score + self.h_score

    def __str__(self) -> str:
        # very stupid printing, breaks for numbers > 9999 | 0.99 (int|float)
        if self.boat_shore == "left":
            return f"""boat seats: {self.boat_seats}
boat counter: {self.boat_counter}
eaten food: {self.eaten_food}
_\\/_                       _~                                _\\/_
/o\\\\                   _~ )_)_~                              //o\\
 |                     )_))_))_)                               |
 | {self.left_missionaries:04} {self.left_cannibals:04} {self.left_food:04}       _!__!__!___             {self.right_food:04} {self.right_cannibals:04} {self.right_missionaries:04} |
_|_M____C____F____    \\______t/               _____F____C____M_|__
                `~^~^~^~^~^~^~^~^~^~^~^~^~^~`"""  # noqa
        else:
            return f"""boat seats: {self.boat_seats}
boat counter: {self.boat_counter}
eaten food: {self.eaten_food}
_\\/_                               ~_                        _\\/_
/o\\\\                            ~_ (_(~_                     //o\\
 |                              (_((_((_(                      |
 | {self.left_missionaries:04} {self.left_cannibals:04} {self.left_food:04}             ___!__!__!_       {self.right_food:04} {self.right_cannibals:04} {self.right_missionaries:04} |
_|_M____C____F____               \\t______/    _____F____C____M_|__
                  `~^~^~^~^~^~^~^~^~^~^~^~^~^~`"""  # noqa

    def __lt__(self, other: Self) -> bool:
        return self.g_score < other.g_score if self.f_score == other.f_score else self.f_score < other.f_score

    def __eq__(self, other: Self) -> bool:
        return self.g_score == other.g_score if self.f_score == other.f_score else self.f_score == other.f_score

    def check_repeat(self, new_node: Self) -> bool:
        node = self
        while node:
            if node.check_eql_vals(new_node):
                return True
            node = node.parent

        return False

    def check_eql_vals(self, new_node: Self) -> bool:
        field_name = [
            "left_cannibals",
            "left_missionaries",
            "left_food",
            "right_cannibals",
            "right_missionaries",
            "right_food",
            "eaten_food",
            "boat_seats",
            "boat_counter",
            "boat_shore",
        ]

        return all([self.__getattribute__(field) == new_node.__getattribute__(field) for field in field_name])

    def get_path(self) -> deque[Self]:
        path = deque()
        node = self
        while node:
            path.appendleft(node)
            node = node.parent
        return path

    def print_path(self, file) -> int:
        path = self.get_path()
        for i, node in enumerate(path):
            print(f"Path index: {i}", file=file)
            print(str(node), file=file)

        return len(path)


class Graph:
    def __init__(
        self,
        cannibals: int,
        missionaries: int,
        start_food: float,
        boat_seats: int,
        boat_degradation: int,
        init_shore: str,
        final_shore: str,
    ):
        start_food = float(start_food)
        self.total_cannibals = cannibals
        self.total_missionaries = missionaries
        self.start_food = start_food
        self.start_boat_seats = boat_seats
        self.boat_degradation = boat_degradation
        self.init_shore = init_shore
        # self.final_shore = "right" if init_shore == "left" else "left"
        self.final_shore = final_shore

        if init_shore == "left":
            self.start = Node(cannibals, missionaries, start_food, 0, 0, 0.0, 0, boat_seats, 0, init_shore, None, 0, 0)
        else:
            self.start = Node(0, 0, 0, cannibals, missionaries, start_food, 0, boat_seats, 0, init_shore, None, 0, 0)

    def test_goal(self, node: Node) -> bool:
        if self.init_shore == "left":
            return node.right_cannibals == self.total_cannibals and node.right_missionaries == self.total_missionaries
        elif self.init_shore == "right":
            return node.left_cannibals == self.total_cannibals and node.left_missionaries == self.total_missionaries

    def util_comparison(self, can: int, mis: int, food: float) -> tuple[float, bool]:
        consumed_food = 0
        if can > mis > 0:
            consumed_food = (can - mis) / 2
        valid = consumed_food <= food
        return (consumed_food, valid)

    def valid_start(self, node: Node) -> bool:
        return (
            self.util_comparison(node.left_cannibals, node.left_missionaries, node.left_food)[1]
            and self.util_comparison(node.right_cannibals, node.right_missionaries, node.right_food)[1]
        )

    def valid_state(self, node: Node, boat_cannibals: int, boat_missionaries: int, boat_food: float) -> bool:
        node.boat_counter += 1
        if node.boat_counter >= self.boat_degradation:
            node.boat_counter = 0
            node.boat_seats -= 1

        # if not (boat_missionaries or boat_cannibals):
        #     return False

        consumed_left, valid_left = self.util_comparison(node.left_cannibals, node.left_missionaries, node.left_food)
        if not valid_left:
            return False

        consumed_right, valid_right = self.util_comparison(
            node.right_cannibals, node.right_missionaries, node.right_food
        )
        if not valid_right:
            return False

        # boat_cannibals = self.total_cannibals - (node.left_cannibals + node.right_cannibals)
        # boat_missionaries = self.total_missionaries - (node.left_missionaries + node.right_missionaries)
        # boat_food = self.start_food - node.eaten_food - (node.left_food + node.right_food)

        # if boat_cannibals + boat_missionaries + boat_food > node.boat_seats:
        #     return False

        consumed_boat, valid_boat = self.util_comparison(boat_cannibals, boat_missionaries, boat_food)
        if not valid_boat:
            return False

        node.eaten_food += consumed_left + consumed_right + consumed_boat

        leftover_food = (self.start_food - node.eaten_food) >= 0

        if leftover_food:
            # updating the food on both shores
            node.left_food -= consumed_left
            node.right_food -= consumed_right

            # transport of the leftover food from the boat (can be 0)
            if node.boat_shore == "right":
                node.right_food += boat_food - consumed_boat
            else:
                node.left_food += boat_food - consumed_boat
            return True
        return False

    def compute_h(
        self,
        heuristic: str,
        left_cannibals: int,
        left_missionaries: int,
        left_food: float,
        right_cannibals: int,
        right_missionaries: int,
        right_food: float,
        eaten_food: float,
        boat_seats: int,
        boat_counter: int,
        boat_shore: str,
    ) -> int:
        match heuristic:
            case "basic":
                if self.init_shore == "left":
                    return 1 if left_cannibals == left_missionaries == 0 and boat_shore == "right" else 0
                elif self.init_shore == "right":
                    return 1 if right_cannibals == right_missionaries == 0 and boat_shore == "left" else 0
        return 0

    def generate_children(self, node: Node, heuristic: str) -> list[Node]:
        children = []
        if node.boat_shore == "left":
            max_missionaries = min(node.left_missionaries, node.boat_seats)
            max_cannibals = min(node.left_cannibals, node.boat_seats)
            max_food = min(node.left_food, node.boat_seats)
            flag = -1
        else:
            max_missionaries = min(node.right_missionaries, node.boat_seats)
            max_cannibals = min(node.right_cannibals, node.boat_seats)
            max_food = min(node.right_food, node.boat_seats)
            flag = 1

        for boat_missionaries in range(max_missionaries + 1):
            max_food = min(node.boat_seats - boat_missionaries, max_food)
            for boat_food in range(int(max_food) + 1):

                max_cannibals = min(node.boat_seats - boat_missionaries - boat_food, max_cannibals)
                if boat_missionaries:
                    max_cannibals = min(boat_missionaries + boat_food * 2, max_cannibals)

                for boat_cannibals in range(max_cannibals + 1):
                    if not (boat_cannibals or boat_missionaries):
                        continue

                    new_node_params = [
                        node.left_cannibals + boat_cannibals * flag,
                        node.left_missionaries + boat_missionaries * flag,
                        node.left_food if flag == 1 else node.left_food - boat_food,
                        node.right_cannibals - boat_cannibals * flag,
                        node.right_missionaries - boat_missionaries * flag,
                        node.right_food if flag == -1 else node.right_food - boat_food,
                        node.eaten_food,
                        node.boat_seats,
                        node.boat_counter,
                        "right" if flag == -1 else "left",
                        node,
                        node.g_score + 1,
                    ]

                    new_node = Node(*new_node_params, self.compute_h(heuristic, *new_node_params[:-2]))

                    if self.valid_state(new_node, boat_cannibals, boat_missionaries, boat_food):
                        children.append(new_node)

        return children

    def breadth_first_search(self):
        return 0

    def depth_first_search(self):
        return 0

    def depth_first_iterative_deepening(self):
        return 0

    def uniform_cost_search(self):
        return 0

    def a_star(self, heuristic: str, number_solutions: int, output_file):
        if not self.valid_start(self.start):
            print("Invalid starting parameters")
            return False

        pq = []
        heapq.heappush(pq, self.start)
        file = open(output_file, "w")
        while len(pq):
            cur_node = heapq.heappop(pq)

            if self.test_goal(cur_node):
                path_len = cur_node.print_path(file=file)
                print(f"Path len: {path_len}", file=file)
                print("=" * 80, file=file)
                print("\n\n", file=file)
                number_solutions -= 1
                if number_solutions == 0:
                    return

            children = self.generate_children(cur_node, heuristic)
            for child in children:
                heapq.heappush(pq, child)

    def a_star_optimized(self):
        return 0

    def a_star_iterative_deepening(self):
        return 0


if __name__ == "__main__":
    if len(sys.argv) > 4:
        param_dicts = {
            path: parse(os.path.join(sys.argv[1], path))
            for path in os.listdir(sys.argv[1])
            if os.path.isfile(os.path.join(sys.argv[1], path))
        }
        output_path = sys.argv[2]
        number_solutions = int(sys.argv[3])
        timeout = int(sys.argv[4])
    else:
        print("Usage:python cautare_informata.py [INPUT_PATH] [OUTPUT_PATH] [NUM_SOL] [TIMEOUT]")
        param_dicts = {"basic": parse("./input/small.json")}
        output_path = "output"
        number_solutions = 2
        timeout = 1000

    for key, param_dict in param_dicts.items():

        key = key.split(".")[0]

        print(f"{key}: {param_dict}")
        graph = Graph(**param_dict)

        if not os.path.exists(output_path):
            os.mkdir(output_path)

        # python cautare_informata.py input output 2 10
        output_file = os.path.join(output_path, key + ".txt")
        p = multiprocessing.Process(target=graph.a_star, args=("basic", number_solutions, output_file))
        p.start()
        p.join(timeout)
        p.terminate()

        cProfile.run("graph.a_star(heuristic='basic', number_solutions=number_solutions)")
