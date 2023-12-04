class Square:
    def __init__(self, value: int, position: tuple):
        self.value = value
        self.position = position


class Piece:
    def __init__(self, orientation: str, first_val: Square, second_val: Square):
        self.orientation = orientation
        self.first = first_val
        self.second = second_val


def identify_board(new_board):
    pass


def find_new_piece(prev_board, new_board) -> Piece:
    pass
