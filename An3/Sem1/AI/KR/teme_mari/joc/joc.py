"""ENUNT:
Se va implementa urmatorul joc:
Jocul se desfasoara pe un grid NxN, cu 10≥N≥4 (utilizatorul va fi întrebat la începutul jocului
pe ce dimensiune de grid dorește să joace).
Este un joc turn based
Un jucator foloseste simbolul x si celalalt 0 ( o sa ii numim pe scurt jucatorii x si 0)
Jucatorul x pune simbolul primul pe tabla
Prima mutare, pentru fiecare dintre jucători nu are nicio restricție. De la a doua mutare încolo jucatorii pot
pune simboluri doar pe linii care sunt la distanță mai mică sau egala cu K1 de o linie pe care se află deja un simbol
al jucătorului care tocmai mută și distanță mai mică sau egala cu K2 față de o coloană pe care se află deja un simbol
al jucătorului. Valorile pentru K1 și K2 se vor citi de la tastatură.

Scopul jocului este sa se creeze un numar cat mai mare de linii de câte 3 simboluri pe rand, coloana sau diagonala.
Jocul se termina cand nu mai sunt spatii libere in grid. Castiga jucatorul care are cel mai mare numar de secvente
(acest număr reprezentând și scorul) de 3 simboluri vecine in linie pe rand, coloana sau diagonala.
Observație: secvențele de simboluri se pot intersecta (dacă sunt 4 simboluri vecine în linie, se vor însuma la scor ca
două secvențe de câte 3). De exemplu, mai jos ambele seturi de câte 3 simboluri "0" se adună la punctaj.
La afișarea gridului în consolă, se vor afișa în dreptul liniilor și coloanelor și numerele lor
(indicii începând de la 0) ca să poată identifica utilizatorul mai ușor coordonatele locului în care vrea să mute.

"""
import copy
import itertools
import random
import time
import numpy as np
import pygame
import sys
from itertools import cycle
from typing import Self
import colorsys

# WINDOW SETINGS
WIDTH = 800
HEIGHT = 800

# COLOURS
BLUE = (2, 117, 216)
L_BLUE = (91, 192, 222)
GREEN = (92, 184, 92)
YELLOW = (240, 173, 78)
RED = (217, 83, 79)
BLACK = (41, 43, 44)
WHITE = (247, 247, 247)

# COLOUR ASSIGNMENTS
BACKGROUND_CLR = L_BLUE
BOARD_CLR = BLACK
X_CLR = RED
O_CLR = GREEN
TEXT_CLR = WHITE
HIGHLIGHT_CLR = YELLOW
TOP_BUTTON_CLR = BLUE
BOT_BUTTON_CLR = BLACK
HOVER_BUTTON_CLR = RED

# GAME SETTINGS
MENU = True
BOARD_SIZE = 4
ROW_DIST = 1
COL_DIST = 1
MODE = "PvP"
PLAYER_SYM = "X"
AI_ONE_DIFF = "easy"
AI_TWO_DIFF = "easy"
AI_ONE_ALGO = "minimax"
AI_TWO_ALGO = "minimax"

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("lmihaig - x si 0")
menu_font = pygame.font.Font("./m6x11.ttf", 32)
game_font = pygame.font.Font("./m6x11.ttf", 80)
clock = pygame.time.Clock()
pygame.mixer.init()
sound_x = pygame.mixer.Sound("./sound_one.wav")
sound_o = pygame.mixer.Sound("./sound_two.mp3")
sound_final = pygame.mixer.Sound("./final.wav")


class Button:
    def __init__(self, name: str, width: int, height: int, pos: int, elevation: int, options: list[str] = None):
        # Core attributes
        self.name = name
        self.pressed = False
        self.elevation = elevation
        self.dynamic_elevation = elevation
        self.original_y_pos = pos[1]
        self.options = cycle(options) if options else None

        # top rectangle
        self.top_rect = pygame.Rect(pos, (width, height))
        self.top_color = TOP_BUTTON_CLR

        # bottom rectangle
        self.bottom_rect = pygame.Rect(pos, (width, height))
        self.bottom_color = BOT_BUTTON_CLR

        self.text = self.name + ": " + next(self.options) if self.name else next(self.options)

    def draw(self):
        # text
        self.text_surf = menu_font.render(self.text, True, TEXT_CLR)
        self.text_rect = self.text_surf.get_rect(center=self.top_rect.center)
        # elevation logic
        self.top_rect.y = self.original_y_pos - self.dynamic_elevation
        self.text_rect.center = self.top_rect.center

        self.bottom_rect.midtop = self.top_rect.midtop
        self.bottom_rect.height = self.top_rect.height + self.dynamic_elevation

        pygame.draw.rect(screen, self.bottom_color, self.bottom_rect, border_radius=12)
        pygame.draw.rect(screen, self.top_color, self.top_rect, border_radius=12)
        screen.blit(self.text_surf, self.text_rect)
        return self.check_click()

    def check_click(self):
        mouse_pos = pygame.mouse.get_pos()
        if self.top_rect.collidepoint(mouse_pos):
            self.top_color = HOVER_BUTTON_CLR
            if pygame.mouse.get_pressed()[0]:
                self.dynamic_elevation = 0
                self.pressed = True
                if self.options:
                    val = next(self.options)
                    self.text = self.name + ": " + val
                    pygame.time.wait(100)
                    return val
            else:
                self.dynamic_elevation = self.elevation
                if self.pressed:
                    self.pressed = False
        else:
            self.dynamic_elevation = self.elevation
            self.top_color = TOP_BUTTON_CLR


class Cell:
    def __init__(self, rect: pygame.rect, x: int, y: int, symbol: str = " "):
        self.rect = rect
        self.symbol = symbol
        self.x = x
        self.y = y

    def check_click(self):
        mouse_pos = pygame.mouse.get_pos()
        if self.rect.collidepoint(mouse_pos):
            if pygame.mouse.get_pressed()[0]:
                return True
        return False

    def highlight(self, clr: tuple[int]):
        pygame.draw.rect(screen, clr, self.rect)

    def set_symbol(self, symbol):
        if self.symbol == " ":
            self.symbol = symbol
            return True
        return False

    def draw_symbol(self):
        if self.symbol != " ":
            match self.symbol:
                case "X":
                    sym_col = X_CLR
                case "0":
                    sym_col = O_CLR

            text_surf = game_font.render(self.symbol, True, sym_col)

            # 4, 8 hardcoded to center symbol
            text_rect = text_surf.get_rect(center=increment_tuple(self.rect.center, [4, 8]))
            screen.blit(text_surf, text_rect)
            return True


class Node:
    def __init__(self, board: list[list[Cell]], to_move: str, depth: int, parent: Self, estimation: int = None):
        self.board = board
        self.to_move = to_move
        self.depth = depth
        self.parent = parent
        self.valid_moves = set()
        self.estimation = estimation

    def __repr__(self):
        res = [" |" + " | ".join([str(index) for index in range(BOARD_SIZE)])]
        i = 0
        for row in self.board:
            res.append(f"{i}|" + " | ".join(cell.symbol for cell in row) + " |")
            res.append("-" * (BOARD_SIZE - 1) * 5)
            i += 1
        return "\n".join(res)

    def draw_state(self):
        for row in self.board:
            for elem in row:
                pygame.draw.rect(screen, BACKGROUND_CLR, elem.rect)
                elem.draw_symbol()

    def display_to_move(self):
        text = menu_font.render(f"{self.to_move} to move", True, TEXT_CLR, BOARD_CLR)
        text_rect = text.get_rect(center=(WIDTH / 2, 50))
        screen.blit(text, text_rect)

    def get_valid_moves(self):
        if self.depth < 2:
            self.valid_moves = set(cell for row in self.board for cell in row if cell.symbol == " ")
        else:
            val_moves = set()
            for cell in set(cell for row in self.board for cell in row if cell.symbol == self.to_move):
                for new_x in range(cell.x - COL_DIST, cell.x + COL_DIST + 1):
                    for new_y in range(cell.y - ROW_DIST, cell.y + ROW_DIST + 1):
                        if 0 <= new_x < BOARD_SIZE and 0 <= new_y < BOARD_SIZE:
                            elem = self.board[new_x][new_y]
                            if elem.symbol == " ":
                                val_moves.add(self.board[new_x][new_y])

            self.valid_moves = val_moves

        return self.valid_moves

    def estimate_score(self):
        pass


class Graph:
    def __init__(self, start: Node, player_one, player_two):
        self.start = start
        self.cur_node = start
        self.player_one = player_one
        self.player_two = player_two

    def minimax(self, node: Node, max_depth: int):
        if node.depth >= max_depth or not node.get_valid_moves():
            node.estimation = node.estimate_score()
            return node

    def move_player(self, player):
        new_node = copy.deepcopy(self.cur_node)
        max_depth = 0
        match player:
            case "Human":
                for row in new_node.board:
                    for cell in row:
                        if cell in new_node.valid_moves:
                            if cell.check_click() and cell.set_symbol(new_node.to_move):
                                cell.draw_symbol()
                                return new_node.board
            case "AI", algo, diff:
                match diff:
                    case "Easy":
                        max_depth = 2
                    case "Medium":
                        max_depth = 5
                    case "Hard":
                        max_depth = 10
                match algo:
                    case "minimax":
                        return self.minimax(new_node, new_node.depth + max_depth).board
                    case "alpha-beta":
                        return self.alpha_beta(new_node, new_node.depth + max_depth).board
        return None

    def next_move(self):
        if self.cur_node.to_move == "X":
            new_board = self.move_player(self.player_one)
            if new_board:
                self.cur_node = Node(new_board, "0", self.cur_node.depth + 1, self.cur_node)
                self.cur_node.draw_state()
                sound_x.play()
                pygame.display.update()
                print(self.cur_node)
        else:
            new_board = self.move_player(self.player_two)
            if new_board:
                self.cur_node = Node(new_board, "X", self.cur_node.depth + 1, self.cur_node)
                self.cur_node.draw_state()
                sound_o.play()
                pygame.display.update()
                print(self.cur_node)

    def draw_line(self, start_cell: Cell, end_cell: Cell):
        random_start_offset = random.randint(0, 20)
        random_end_offset = random.randint(0, 20)
        # # color = tuple(np.random.random(size=3) * 256)
        # if start_cell.symbol == "X":
        #     color = hsv2rgb(80 + random.randint(-5, 5), random.randint(100, 260), random.randint(100, 260))
        # else:
        #     color = hsv2rgb(5 + random.randint(-5, 5), random.randint(100, 260), random.randint(100, 260))
        color = hsv2rgb(60 + random.randint(-5, 5), random.randint(180, 360), random.randint(300, 360))
        pygame.draw.line(
            screen,
            color,
            increment_tuple(start_cell.rect.center, [random_start_offset, random_start_offset]),
            increment_tuple(end_cell.rect.center, [random_end_offset, random_end_offset]),
            width=8,
        )

    def draw_end_screen(self):
        def check_valid(cell, new_x, new_y):
            if 0 <= new_x < BOARD_SIZE and 0 <= new_y < BOARD_SIZE:
                if cell.symbol == self.cur_node.board[new_x][new_y].symbol:
                    return True
            return False

        scor_x, scor_o = 0, 0
        for row in self.cur_node.board:
            for cell in row:
                if cell.symbol == " ":
                    continue
                for dir in [(0, 1), (1, 1), (1, 0), (1, -1)]:
                    if not check_valid(cell, cell.x + dir[0], cell.y + dir[1]):
                        continue
                    if not check_valid(cell, cell.x + dir[0] * 2, cell.y + dir[1] * 2):
                        continue
                    self.draw_line(cell, self.cur_node.board[cell.x + dir[0] * 2][cell.y + dir[1] * 2])
                    if cell.symbol == "X":
                        scor_x += 1
                    else:
                        scor_o += 1
        if scor_x == scor_o:
            text = "TIE?!"
        else:
            text = "X WINS!" if scor_x > scor_o else "0 WINS!"
        text = game_font.render(text, True, TEXT_CLR, BOARD_CLR)
        text_rect = text.get_rect(center=(WIDTH / 2, HEIGHT / 2 - 50))

        subtext = game_font.render(f"X:{scor_x} 0:{scor_o}", True, TEXT_CLR, BOARD_CLR)
        subtext_rect = text.get_rect(center=(WIDTH / 2, HEIGHT / 2 + 50))
        screen.blit(text, text_rect)
        screen.blit(subtext, subtext_rect)


def increment_tuple(tup: tuple[int], nums: list[int]):
    ree = tuple(tup[i] + nums[i] for i in range(len(tup)))
    return ree


def hsv2rgb(h, s, v):
    return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h / 360, s / 360, v / 360))


# BUTTONS FOR MENU
play_btn = Button("", 200, 40, (550, 700), 5, options=["Play"])

board_size_btn = Button("Board size", 200, 40, (25, 50), 5, options=[str(i) for i in range(4, 11)])
col_dist_btn = Button("Column distance", 300, 40, (50, 100), 5, options=[str(i) for i in range(BOARD_SIZE + 1)])
row_dist_btn = Button("Row distance", 300, 40, (375, 100), 5, options=[str(i) for i in range(BOARD_SIZE + 1)])

game_mode_btn = Button("Game Mode", 300, 40, (25, 200), 5, options=["PvP", "AIvP", "AIvAI"])
algo_ai_one_btn = Button("AI_1 Algorithm", 350, 40, (50, 250), 5, options=["minimax", "alpha-beta"])
diff_ai_one_btn = Button("AI_1 Difficulty", 350, 40, (50, 300), 5, options=["Easy", "Medium", "Hard"])

algo_ai_two_btn = Button("AI_2 Algorithm", 350, 40, (425, 250), 5, options=["minimax", "alpha-beta"])
diff_ai_two_btn = Button("AI_2 Difficulty", 350, 40, (425, 300), 5, options=["Easy", "Medium", "Hard"])

player_symbol_Btn = Button("Player Symbol", 250, 40, (425, 250), 5, options=["X", "0"])


def draw_menu():
    screen.fill(BACKGROUND_CLR)
    global MENU, BOARD_SIZE, ROW_DIST, COL_DIST, MODE, PLAYER_SYM, AI_ONE_DIFF, AI_TWO_DIFF, AI_ONE_ALGO, AI_TWO_ALGO
    play = play_btn.draw()
    board_size = board_size_btn.draw()

    if board_size:
        BOARD_SIZE = int(board_size)
        col_dist_btn.options = cycle([str(i) for i in range(BOARD_SIZE + 1)])
        row_dist_btn.options = cycle([str(i) for i in range(BOARD_SIZE + 1)])
        COL_DIST = min(COL_DIST, BOARD_SIZE)
        ROW_DIST = min(ROW_DIST, BOARD_SIZE)

    col = col_dist_btn.draw()

    COL_DIST = int(col) if col else COL_DIST

    row = row_dist_btn.draw()
    ROW_DIST = min(int(row), BOARD_SIZE) if row else ROW_DIST

    game_mode = game_mode_btn.draw()
    MODE = game_mode if game_mode else MODE

    if MODE == "AIvP":
        sym = player_symbol_Btn.draw()
        PLAYER_SYM = sym if sym else PLAYER_SYM

    if MODE == "AIvAI":
        diff_ai_two = diff_ai_two_btn.draw()
        algo_ai_two = algo_ai_two_btn.draw()
        AI_TWO_DIFF = diff_ai_two if diff_ai_two else AI_TWO_DIFF
        AI_TWO_ALGO = algo_ai_two if algo_ai_two else AI_TWO_ALGO

    if MODE != "PvP":
        diff_ai_one = diff_ai_one_btn.draw()
        algo_ai_one = algo_ai_one_btn.draw()
        AI_ONE_DIFF = diff_ai_one if diff_ai_one else AI_ONE_DIFF
        AI_ONE_ALGO = algo_ai_one if algo_ai_one else AI_ONE_ALGO

    if play:
        print(
            MENU,
            BOARD_SIZE,
            ROW_DIST,
            COL_DIST,
            MODE,
            PLAYER_SYM,
            AI_ONE_DIFF,
            AI_TWO_DIFF,
            AI_ONE_ALGO,
            AI_TWO_ALGO,
        )
        MENU = False


def play_game(graph: Graph):
    valid_moves = graph.cur_node.get_valid_moves()
    if valid_moves:
        for cell in valid_moves:
            cell.highlight(HIGHLIGHT_CLR)

        graph.cur_node.display_to_move()

        pygame.display.update()

        graph.next_move()

        return False
    else:
        graph.draw_end_screen()
        sound_final.play()
        return True


def init_game():
    screen.fill(BOARD_CLR)
    block_size = (HEIGHT - (3 * (BOARD_SIZE - 1))) // BOARD_SIZE
    cells: list[list[Cell]] = [[" " for i in range(BOARD_SIZE)] for j in range(BOARD_SIZE)]
    for y in range(BOARD_SIZE):
        for x in range(BOARD_SIZE):
            cells[x][y] = Cell(pygame.Rect(x * (block_size + 3), y * (block_size + 3), block_size, block_size), x, y)
            pygame.draw.rect(screen, BACKGROUND_CLR, cells[x][y].rect)
    start_node = Node(cells, "X", 0, None)
    match MODE, PLAYER_SYM, AI_ONE_ALGO, AI_ONE_DIFF, AI_TWO_ALGO, AI_TWO_DIFF:
        case "PvP", _, _, _, _, _:
            player_one, player_two = "Human", "Human"
        case "AIvP", "X", algo, diff, _, _:
            player_one, player_two = "Human", ("AI", algo, diff)
        case "AIvP", "0", algo, diff, _, _:
            player_one, player_two = ("AI", algo, diff), "Human"
        case "AIvAI", _, algo_one, diff_one, algo_two, diff_two:
            player_one, player_two = ("AI", algo_one, diff_one), ("AI", algo_two, diff_two)
    return Graph(start_node, player_one, player_two)


def check_quit():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()


if __name__ == "__main__":
    initgame = True
    while True:
        if MENU:
            draw_menu()
        else:
            if initgame:
                graph = init_game()
                initgame = False
            if play_game(graph):
                pygame.display.update()
                while True:
                    check_quit()
        check_quit()
        pygame.display.update()
