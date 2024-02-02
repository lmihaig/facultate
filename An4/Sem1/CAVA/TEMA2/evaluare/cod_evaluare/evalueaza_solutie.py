import numpy as np
import matplotlib.pyplot as plt
import pdb

def intersection_over_union(bbox_a, bbox_b):
    x_a = max(bbox_a[0], bbox_b[0])
    y_a = max(bbox_a[1], bbox_b[1])
    x_b = min(bbox_a[2], bbox_b[2])
    y_b = min(bbox_a[3], bbox_b[3])

    inter_area = max(0, x_b - x_a + 1) * max(0, y_b - y_a + 1)

    box_a_area = (bbox_a[2] - bbox_a[0] + 1) * (bbox_a[3] - bbox_a[1] + 1)
    box_b_area = (bbox_b[2] - bbox_b[0] + 1) * (bbox_b[3] - bbox_b[1] + 1)
    iou = inter_area / float(box_a_area + box_b_area - inter_area)

    return iou


def compute_average_precision(rec, prec):
    # functie adaptata din 2010 Pascal VOC development kit
    m_rec = np.concatenate(([0], rec, [1]))
    m_pre = np.concatenate(([0], prec, [0]))
    for i in range(len(m_pre) -  1, -1, 1):
        m_pre[i] = max(m_pre[i], m_pre[i + 1])
    m_rec = np.array(m_rec)
    i = np.where(m_rec[1:] != m_rec[:-1])[0] + 1
    average_precision = np.sum((m_rec[i] - m_rec[i - 1]) * m_pre[i])
    return average_precision


def eval_detections(detections, scores, file_names, ground_truth_path):
    ground_truth_file = np.loadtxt(ground_truth_path, dtype='str')
    ground_truth_file_names = np.array(ground_truth_file[:, 0])
    ground_truth_detections = np.array(ground_truth_file[:, 1:], np.int)

    num_gt_detections = len(ground_truth_detections)  # numar total de adevarat pozitive
    gt_exists_detection = np.zeros(num_gt_detections)
    # sorteazam detectiile dupa scorul lor
    sorted_indices = np.argsort(scores)[::-1]
    file_names = file_names[sorted_indices]
    scores = scores[sorted_indices]
    detections = detections[sorted_indices]

    num_detections = len(detections)
    true_positive = np.zeros(num_detections)
    false_positive = np.zeros(num_detections)
    duplicated_detections = np.zeros(num_detections)

    for detection_idx in range(num_detections):
        indices_detections_on_image = np.where(ground_truth_file_names == file_names[detection_idx])[0]

        gt_detections_on_image = ground_truth_detections[indices_detections_on_image]
        bbox = detections[detection_idx]
        max_overlap = -1
        index_max_overlap_bbox = -1
        for gt_idx, gt_bbox in enumerate(gt_detections_on_image):
            overlap = intersection_over_union(bbox, gt_bbox)
            if overlap > max_overlap:
                max_overlap = overlap
                index_max_overlap_bbox = indices_detections_on_image[gt_idx]

        # clasifica o detectie ca fiind adevarat pozitiva / fals pozitiva
        if max_overlap >= 0.3:
            if gt_exists_detection[index_max_overlap_bbox] == 0:
                true_positive[detection_idx] = 1
                gt_exists_detection[index_max_overlap_bbox] = 1
            else:
                false_positive[detection_idx] = 1
                duplicated_detections[detection_idx] = 1
        else:
            false_positive[detection_idx] = 1

    cum_false_positive = np.cumsum(false_positive)
    cum_true_positive = np.cumsum(true_positive)

    rec = cum_true_positive / num_gt_detections
    prec = cum_true_positive / (cum_true_positive + cum_false_positive)
    average_precision = compute_average_precision(rec, prec)
    plt.plot(rec, prec, '-')
    plt.xlabel('Recall')
    plt.ylabel('Precision')
    plt.title('All faces: average precision %.3f' % average_precision)
    plt.savefig('precizie_medie_all_faces.png')
    plt.show()

def eval_detections_character(detections, scores, file_names,ground_truth_path,character):
    ground_truth_file = np.loadtxt(ground_truth_path, dtype='str')
    ground_truth_file_names = np.array(ground_truth_file[:, 0])
    ground_truth_detections = np.array(ground_truth_file[:, 1:], np.int)

    num_gt_detections = len(ground_truth_detections)  # numar total de adevarat pozitive
    gt_exists_detection = np.zeros(num_gt_detections)
    # sorteazam detectiile dupa scorul lor
    sorted_indices = np.argsort(scores)[::-1]
    file_names = file_names[sorted_indices]
    scores = scores[sorted_indices]
    detections = detections[sorted_indices]

    num_detections = len(detections)
    true_positive = np.zeros(num_detections)
    false_positive = np.zeros(num_detections)
    duplicated_detections = np.zeros(num_detections)

    for detection_idx in range(num_detections):
        indices_detections_on_image = np.where(ground_truth_file_names == file_names[detection_idx])[0]

        gt_detections_on_image = ground_truth_detections[indices_detections_on_image]
        bbox = detections[detection_idx]
        max_overlap = -1
        index_max_overlap_bbox = -1
        for gt_idx, gt_bbox in enumerate(gt_detections_on_image):
            overlap = intersection_over_union(bbox, gt_bbox)
            if overlap > max_overlap:
                max_overlap = overlap
                index_max_overlap_bbox = indices_detections_on_image[gt_idx]

        # clasifica o detectie ca fiind adevarat pozitiva / fals pozitiva
        if max_overlap >= 0.3:
            if gt_exists_detection[index_max_overlap_bbox] == 0:
                true_positive[detection_idx] = 1
                gt_exists_detection[index_max_overlap_bbox] = 1
            else:
                false_positive[detection_idx] = 1
                duplicated_detections[detection_idx] = 1
        else:
            false_positive[detection_idx] = 1

    cum_false_positive = np.cumsum(false_positive)
    cum_true_positive = np.cumsum(true_positive)

    rec = cum_true_positive / num_gt_detections
    prec = cum_true_positive / (cum_true_positive + cum_false_positive)
    average_precision = compute_average_precision(rec, prec)
    plt.plot(rec, prec, '-')
    plt.xlabel('Recall')
    plt.ylabel('Precision')
    plt.title(character + ' faces: average precision %.3f' % average_precision)
    plt.savefig('precizie_medie_' + character + '.png')
    plt.show()

def evaluate_results_task1(solution_path,ground_truth_path,verbose = 0):

	#incarca detectiile + scorurile + numele de imagini	
	detections = np.load(solution_path + "detections_all_faces.npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(detections.shape)

	scores = np.load(solution_path + "scores_all_faces.npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(scores.shape)
	
	file_names = np.load(solution_path + "file_names_all_faces.npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(file_names.shape)

	eval_detections(detections, scores, file_names, ground_truth_path)

def evaluate_results_task2(solution_path,ground_truth_path,character, verbose = 0):

	#incarca detectiile + scorurile + numele de imagini	
	detections = np.load(solution_path + "detections_" + character + ".npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(detections.shape)

	scores = np.load(solution_path + "scores_"+ character + ".npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(scores.shape)
	
	file_names = np.load(solution_path + "file_names_"+ character + ".npy",allow_pickle=True,fix_imports=True,encoding='latin1')
	print(file_names.shape)

	eval_detections_character(detections, scores, file_names, ground_truth_path, character)
  
verbose = 0

#change this on your machine
solution_path_root = "../fisiere_solutie/331_Alexe_Bogdan/"
ground_truth_path_root = "../../validare/"


#task1
solution_path = solution_path_root + "task1/"
ground_truth_path = ground_truth_path_root + "task1_gt_validare.txt"
print(solution_path)
evaluate_results_task1(solution_path, ground_truth_path, verbose)

#pdb.set_trace()

#task2
solution_path = solution_path_root + "task2/"


ground_truth_path = ground_truth_path_root + "task2_fred_gt_validare.txt"
evaluate_results_task2(solution_path, ground_truth_path, "fred", verbose)

ground_truth_path = ground_truth_path_root + "task2_barney_gt_validare.txt"
evaluate_results_task2(solution_path, ground_truth_path, "barney", verbose)

ground_truth_path = ground_truth_path_root + "task2_betty_gt_validare.txt"
evaluate_results_task2(solution_path, ground_truth_path, "betty", verbose)

ground_truth_path = ground_truth_path_root + "task2_wilma_gt_validare.txt"
evaluate_results_task2(solution_path, ground_truth_path, "wilma", verbose)
