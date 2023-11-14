package util

import "errors"

func Jumble(words []string) ([]string, error) {
	if len(words) == 0 {
		return nil, errors.New("no words provided")
	}

	jumbled := make([]string, len(words[0]))

	for i := range jumbled {
		for _, word := range words {
			if len(word) > i {
				jumbled[i] += string(word[i])
			}
		}
	}

	return jumbled, nil
}

// func FindPerfectSquares(words []string) uint32 {
// 	var count uint32

// 	for _, word := range words {
// 		if isPerfectSquare(len(word)) {
// 			count++
// 		}
// 	}

// 	return count
// }