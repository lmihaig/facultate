import numpy as np
import cv2 as cv
from util import (
    crop_board,
    grid_mask,
    print_image,
    denoise,
    sharpen,
    edge_detect,
    get_piece,
    index_to_board_notation,
)

from colorama import Fore, Style


class Square:
    def __init__(self, value: int, position: tuple):
        self.value = value
        self.position = position


class Piece:
    def __init__(self, orientation: str, first_square: Square, second_square: Square):
        self.orientation = orientation
        self.first_square = first_square
        self.second_square = second_square

    def is_double(self) -> bool:
        if self.first_square.value == self.second_square.value:
            return True
        return False


class Game:
    def __init__(
        self,
        game_id: int,
        init_image: np.ndarray,
        mutari: list[str],
        score_tracker: list[int],
        input_dir: str,
        output_dir: str,
        board: np.ndarray,
    ):
        self.game_id = game_id
        self.mutari = mutari
        self.prev_image = crop_board(init_image)
        self.cur_image = None
        # actually a dictionary of horizontal and vertical lines
        self.grid = None
        # board[0][x][y] value of domino piece in position (x, y)
        # board[1][x][y] value of special diamond in position (x, y)
        self.board = board
        self.score_tracker = score_tracker
        self.players_score = {"player1": None, "player2": None}
        self.input_dir = input_dir
        self.output_dir = output_dir
        self.mask = None

    def get_grid(self, image: np.ndarray) -> np.ndarray:
        image = denoise(image)
        image = sharpen(image)
        image = edge_detect(image)
        mask, lines = grid_mask(image)
        self.mask = mask
        return lines

    def detect_piece(self) -> Piece:
        (
            orientation,
            first_square_position,
            first_square_value,
            second_square_position,
            second_square_value,
        ) = get_piece(
            self.prev_image.copy(),
            self.cur_image.copy(),
            self.grid.copy(),
            self.mask.copy(),
        )

        first_square = Square(first_square_value, first_square_position)
        second_square = Square(second_square_value, second_square_position)
        piece = Piece(orientation, first_square, second_square)
        return piece
    def place(self, piece: Piece, player: str, move_num: int) -> int:
        # print(f"{Fore.YELLOW}Move number: {move_num}{Style.RESET_ALL}")
        # print(f"{Fore.GREEN}Player: {player}{Style.RESET_ALL}")
        # print(f"Score is: {self.players_score}")
        # print(f"Piece Orientation: {piece.orientation}")
        # print(f"Piece Values: {piece.first_square.value}, {piece.second_square.value}")
        # print(
        #     "Piece Positions: ",
        #     index_to_board_notation(piece.first_square.position),
        #     index_to_board_notation(piece.second_square.position),
        # )

        x1, y1, x2, y2 = (
            piece.first_square.position[0],
            piece.first_square.position[1],
            piece.second_square.position[0],
            piece.second_square.position[1],
        )
        self.board[0][x1][y1] = piece.first_square.value
        self.board[0][x2][y2] = piece.second_square.value

        points = 0
        if move_num in (1, 2):
            return points

        # try:
        #     print(
        #         "Player1 tile: ", self.score_tracker[self.players_score["player1"] - 1]
        #     )
        #     print(
        #         "Player2 tile: ", self.score_tracker[self.players_score["player2"] - 1]
        #     )

        # except Exception:
        #     pass

        bonus1, bonus2 = (
            self.board[1][x1][y1],
            self.board[1][x2][y2],
        )
        extrapoints = 0
        if bonus1 != 0 or bonus2 != 0:
            points = max(bonus1, bonus2)
            if piece.is_double():
                points *= 2
            # print("Board points are: ", points)
        if self.players_score["player1"]:
            if self.score_tracker[self.players_score["player1"] - 1] in (
                piece.first_square.value,
                piece.second_square.value,
            ):
                # print(
                #     self.players_score,
                #     self.score_tracker[self.players_score["player1"] - 1],
                #     piece.first_square.value,
                #     piece.second_square.value,
                # )
                self.players_score["player1"] += 3
                if player == "player1":
                    extrapoints = 3

        if self.players_score["player2"]:
            if self.score_tracker[self.players_score["player2"] - 1] in (
                piece.first_square.value,
                piece.second_square.value,
            ):
                # print(
                #     self.score_tracker[self.players_score["player2"] - 1],
                #     piece.first_square.value,
                #     piece.second_square.value,
                # )
                self.players_score["player2"] += 3
                if player == "player2":
                    extrapoints = 3

        if self.players_score[player] is None:
            self.players_score[player] = points
        else:
            self.players_score[player] += points
        return points + extrapoints

    def print_move_info(self, piece: Piece, points: int, move_num: int):
        fsq = piece.first_square
        ssq = piece.second_square

        filename = f"{self.output_dir}{self.game_id}_{move_num:02d}.txt"
        with open(filename, "w") as file:
            print(f"{index_to_board_notation(fsq.position)} {fsq.value}", file=file)
            print(f"{index_to_board_notation(ssq.position)} {ssq.value}", file=file)
            print(f"{points}", file=file)

    def loop(self):
        self.grid = self.get_grid(self.prev_image.copy())
        for move_num in range(1, 21):
            jpg_path, player = self.mutari[move_num - 1].split()

            image_path = self.input_dir + jpg_path
            self.cur_image = crop_board(cv.imread(image_path))
            piece = self.detect_piece()
            points = self.place(piece, player, move_num)
            self.print_move_info(piece, points, move_num)
            self.prev_image = self.cur_image.copy()
