# to be written
def compare_annotations(filename_predicted, filename_gt, verbose=0):
    p = open(filename_predicted, "rt")
    gt = open(filename_gt, "rt")
    all_lines_p = p.readlines()
    all_lines_gt = gt.readlines()

    # ANSI escape code for red text
    RED_TEXT = "\033[91m"
    RESET_TEXT = "\033[0m"  # Resets the text color to default

    number_lines_gt = len(all_lines_gt)

    match_positions = 1
    match_values = 1
    match_score = 1

    for i in range(number_lines_gt - 1):
        current_pos_gt, current_value_gt = all_lines_gt[i].split()

        if verbose:
            print(i)
            print(current_pos_gt, current_value_gt)

        try:
            current_pos_p, current_value_p = all_lines_p[i].split()

            if verbose:
                print(current_pos_p, current_value_p)

            if current_pos_p != current_pos_gt or current_value_p != current_value_gt:
                print(
                    RED_TEXT
                    + f"Prediction Error at line {i}: GT({current_pos_gt}, {current_value_gt}) vs P({current_pos_p}, {current_value_p})"
                    + RESET_TEXT
                )
                match_positions = (
                    0 if current_pos_p != current_pos_gt else match_positions
                )
                match_values = (
                    0 if current_value_p != current_value_gt else match_values
                )

        except Exception:
            print(RED_TEXT + f"Error reading predicted data at line {i}" + RESET_TEXT)
            match_positions = 0
            match_values = 0

    try:
        current_pos_p, current_value_p = all_lines_p[i + 1].split()
        match_positions = 0
        match_values = 0

        if verbose:
            print("EXTRA LINE:")
            print(current_pos_p, current_value_p)

    except Exception:
        pass

    points_positions = 0.05 * match_positions
    points_values = 0.02 * match_values

    last_line_p = all_lines_p[-1]
    score_p = last_line_p.split()
    last_line_gt = all_lines_gt[-1]
    score_gt = last_line_gt.split()

    if verbose:
        print(score_p, score_gt)

    if score_p != score_gt:
        print(RED_TEXT + f"Score Mismatch: GT({score_gt}) vs P({score_p})" + RESET_TEXT)
        match_score = 0

    points_score = 0.02 * match_score

    return points_positions, points_values, points_score


# change this on your machine pointing to your results (txt files)
# predictions_path_root = "/Users/bogdan/Desktop/CAVA_2024_Tema1_evaluare/fisiere_solutie/331_Alexe_Bogdan/"
predictions_path_root = "D:/facultate/An4/Sem1/CAVA/TEMA1/solutie/rezultate/task3/"


# change this on your machine to point to the ground-truth test
# gt_path_root = "/Users/bogdan/Desktop/CAVA_2024_Tema1_evaluare/ground-truth/"
gt_path_root = (
    "D:/facultate/An4/Sem1/CAVA/TEMA1/evaluare/fisiere_solutie/331_Alexe_Bogdan/"
)


# change this to 1 if you want to print results at each turn
verbose = 1
total_points = 0
for game in range(
    1, 2
):  # for one game change this to range(1,2), otherwise put range(1,6)
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
