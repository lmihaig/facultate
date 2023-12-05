import sys


import sys


def compare_annotations(filename_predicted, filename_gt, verbose=0):
    with open(filename_predicted, "rt") as p, open(filename_gt, "rt") as gt:
        all_lines_p = p.readlines()
        all_lines_gt = gt.readlines()

    # ANSI escape codes for colored text
    RED_TEXT = "\033[91m"
    GREEN_TEXT = "\033[92m"
    YELLOW_TEXT = "\033[93m"
    RESET_TEXT = "\033[0m"

    match_positions, match_values, match_score = 1, 1, 1

    for i in range(min(len(all_lines_gt), len(all_lines_p)) - 1):
        try:
            current_pos_gt, current_value_gt = all_lines_gt[i].strip().split()
            current_pos_p, current_value_p = all_lines_p[i].strip().split()

            pos_color = RED_TEXT if current_pos_p != current_pos_gt else GREEN_TEXT
            val_color = RED_TEXT if current_value_p != current_value_gt else GREEN_TEXT

            if (
                verbose
                or current_pos_p != current_pos_gt
                or current_value_p != current_value_gt
            ):
                print(
                    f"Line {i}: GT({pos_color}{current_pos_gt}{RESET_TEXT}, {val_color}{current_value_gt}{RESET_TEXT}) | "
                    f"Pred({pos_color}{current_pos_p}{RESET_TEXT}, {val_color}{current_value_p}{RESET_TEXT})"
                )
                match_positions = (
                    0 if current_pos_p != current_pos_gt else match_positions
                )
                match_values = (
                    0 if current_value_p != current_value_gt else match_values
                )

        except ValueError as e:
            print(
                YELLOW_TEXT + f"Warning: Line {i} formatting issue - {e}" + RESET_TEXT
            )
            match_positions = 0
            match_values = 0

        except IndexError as e:
            print(YELLOW_TEXT + f"Warning: Line {i} index error - {e}" + RESET_TEXT)
            match_positions = 0
            match_values = 0
            break

    # Additional checks for file length discrepancies
    if len(all_lines_p) > len(all_lines_gt):
        print(YELLOW_TEXT + "Warning: Prediction file has extra lines" + RESET_TEXT)
    elif len(all_lines_p) < len(all_lines_gt):
        print(YELLOW_TEXT + "Warning: Prediction file has fewer lines" + RESET_TEXT)

    # Score comparison
    score_p = all_lines_p[-1].strip().split() if all_lines_p else ["0"]
    score_gt = all_lines_gt[-1].strip().split() if all_lines_gt else ["0"]

    if score_p != score_gt:
        print(
            RED_TEXT + f"Score Mismatch: GT({score_gt}) vs Pred({score_p})" + RESET_TEXT
        )
        match_score = 0

    points_positions = 0.05 * match_positions
    points_values = 0.02 * match_values
    points_score = 0.02 * match_score

    return points_positions, points_values, points_score


# # change this on your machine pointing to your results (txt files)
# # predictions_path_root = "/Users/bogdan/Desktop/CAVA_2024_Tema1_evaluare/fisiere_solutie/331_Alexe_Bogdan/"
# predictions_path_root = "D:/facultate/An4/Sem1/CAVA/TEMA1/solutie/rezultate/task3/"


# # change this on your machine to point to the ground-truth test
# # gt_path_root = "/Users/bogdan/Desktop/CAVA_2024_Tema1_evaluare/ground-truth/"
# gt_path_root = (
#     "D:/facultate/An4/Sem1/CAVA/TEMA1/evaluare/fisiere_solutie/331_Alexe_Bogdan/"
# )


if len(sys.argv) < 3:
    print("Usage: script.py [predictions_path] [gt_path]")
    sys.exit(1)

predictions_path_root = sys.argv[1]
gt_path_root = sys.argv[2]

verbose = 1
total_points = 0
for game in range(1, 6):
    for turn in range(1, 21):
        name_turn = str(turn)
        if turn < 10:
            name_turn = "0" + str(turn)

        filename_predicted = (
            predictions_path_root + str(game) + "_" + name_turn + ".txt"
        )
        filename_gt = gt_path_root + str(game) + "_" + name_turn + ".txt"

        game_turn = str(game) + "_" + name_turn
        points_position = 0
        points_values = 0
        points_score = 0

        try:
            points_position, points_values, points_score = compare_annotations(
                filename_predicted, filename_gt, verbose
            )
        except Exception:
            print("For image: ", game_turn, " encountered an error")

        print(
            "Image: ",
            game_turn,
            "Points position: ",
            points_position,
            "Points values: ",
            points_values,
            "Points score: ",
            points_score,
        )
        total_points = total_points + points_position + points_values + points_score

print(total_points)
