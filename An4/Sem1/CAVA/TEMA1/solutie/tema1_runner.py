import typer
from typing_extensions import Annotated
import os
import cv2 as cv
import json
from DDD import Game
import numpy as np

app = typer.Typer()


def run_games(input_dir: str, output_dir: str, task: str):
    files = os.listdir(input_dir)
    num_games = len(files) / 21
    config = json.load(open("./config.json"))
    base_image = cv.imread(config["base_image_path"])
    score_tracker = config["score_tracker"]
    board = np.array(config["board"], dtype=int)

    for game_id in range(1, int(num_games) + 1):
        if num_games == 1:
            game_id = files[0].split("_")[0]
        with open(input_dir + f"{game_id}_mutari.txt") as mutari_file:
            mutari = mutari_file.read().split("\n")
            mutari_file.close()

        game = Game(
            game_id=game_id,
            init_image=base_image.copy(),
            mutari=mutari,
            score_tracker=score_tracker,
            input_dir=input_dir,
            output_dir=output_dir,
            board=board.copy(),
        )
        game.loop()


def runner(
    task: Annotated[str, typer.Argument()] = "task3",
    input_dir: Annotated[str, typer.Argument()] = "../evaluare/fake_test/",
    output_dir: Annotated[str, typer.Argument()] = "./rezultate/task3/",
):
    if not os.path.isdir(output_dir) or not output_dir.endswith("/"):
        raise ValueError(f"Invalid output directory: {output_dir}")
    if task.lower() in ["task1", "task2", "task3"]:
        run_games(input_dir, output_dir, task.lower())
    else:
        typer.echo(f"Task {task} not found.")


if __name__ == "__main__":
    typer.run(runner)
