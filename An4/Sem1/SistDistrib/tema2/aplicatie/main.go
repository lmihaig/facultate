package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
	"sync"
	"unicode"
)

type MapReduce func(data []string) map[string]int

// Task 1

func IsVowel(char rune) bool {
	return strings.Contains("aeiouAEIOU", string(char))
}

func IsConsonant(char rune) bool {
	return strings.Contains("bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ", string(char))
}

func vocalePareMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		vowelCount := 0
		consonantCount := 0

		for _, char := range word {
			if IsVowel(char) {
				vowelCount++
			} else if IsConsonant(char) {
				consonantCount++
			}
		}

		if vowelCount%2 == 0 && consonantCount%3 == 0 {
			result[word]++
		}
	}

	return result
}

// Task 2
func isPalindrome(word string) bool {
	word = strings.ToLower(strings.ReplaceAll(word, " ", ""))

	for i, j := 0, len(word)-1; i < j; i, j = i+1, j-1 {
		if word[i] != word[j] {
			return false
		}
	}

	return true
}
func palindromMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {

		if isPalindrome(word) {
			result[word]++
		}
	}

	return result
}

// Task 3: Pasareasca
func pasareascaMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if isPasareasca(word) {
			result[word]++
		}
	}

	return result
}

func isPasareasca(word string) bool {
	for i, char := range word {
		if IsVowel(char) {
			if i < len(word)-1 && word[i+1] != 'p' {
				return false
			}
		}
	}
	return true
}

// Task 4: Incepe si se termina cu o vocala
func vocalaStartEndMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if startsAndEndsWithVowel(word) {
			result[word]++
		}
	}

	return result
}

func startsAndEndsWithVowel(word string) bool {
	return strings.Contains("aeiouAEIOU", string(word[0])) && strings.Contains("aeiouAEIOU", string(word[len(word)-1]))
}

// Task 5: Anagramele cuvantului "facultate"
func anagramaMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if isAnagram(word, "facultate") {
			result[word]++
		}
	}

	return result
}

func isAnagram(word, base string) bool {
	if len(word) != len(base) {
		return false
	}

	counts := make(map[rune]int)

	for _, char := range word {
		counts[char]++
	}

	for _, char := range base {
		if counts[char] != strings.Count(base, string(char)) {
			return false
		}
	}

	return true
}

// Task 6: Litere mare - mic, numar par litere mici
func literaMareMicaMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if capitalizedEndsAndEvenLowercase(word) {
			result[word]++
		}
	}

	return result
}

func capitalizedEndsAndEvenLowercase(word string) bool {
	lowercase := 0
	for i, char := range word {
		if i == 0 || i == len(word)-1 {
			if !unicode.IsUpper(char) {
				return false
			}
		} else {
			if unicode.IsLower(char) {
				lowercase++
			}
		}
	}
	return lowercase%2 == 0
}

// Task 7: Diacritice
func diacriticeMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if containsDiacritics(word) {
			result[word]++
		}
	}

	return result
}

func containsDiacritics(word string) bool {
	count := 0
	for _, char := range word {
		if char > unicode.MaxASCII {
			count++
		}
	}
	return count > 1
}

// Task 8: Substitutie

// Task 9: Rimeaza

// Task 10: Alternanta consoana - vocala
func alternantaConsoanaVocalaMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if hasAlternatingConsonantVowel(word) {
			result[word]++
		}
	}

	return result
}

func hasAlternatingConsonantVowel(word string) bool {
	if len(word) < 2 {
		return false
	}
	for i := 0; i < len(word)-1; i++ {
		if !(IsConsonant(rune(word[i])) != IsConsonant(rune(word[i+1]))) {
			return false
		}
	}
	return true
}

// Task 11: Parole puternice
func parolePuterniceMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if isStrongPassword(word) {
			result[word]++
		}
	}

	return result
}

func isStrongPassword(password string) bool {
	hasLowerCase := false
	hasUpperCase := false
	hasDigit := false
	hasSymbol := false

	for _, char := range password {
		if unicode.IsLower(char) {
			hasLowerCase = true
		} else if unicode.IsUpper(char) {
			hasUpperCase = true
		} else if unicode.IsDigit(char) {
			hasDigit = true
		} else if unicode.IsSymbol(char) || unicode.IsPunct(char) {
			hasSymbol = true
		}
	}

	return hasLowerCase && hasUpperCase && hasDigit && hasSymbol
}

// Task 12: Căi absolute și relative
func caiAbsoluteRelativeMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if strings.HasPrefix(word, "/") || strings.HasPrefix(word, "./") || strings.HasPrefix(word, "../") {
			result[word]++
		}
	}

	return result
}

// Task 13: Nume romanesti
func numeRomanestiMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if strings.HasSuffix(word, "escu") {
			result[word]++
		}
	}

	return result
}

// Task 14: Numere Fibonacci
func fibonacciMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if isFibonacciNumber(word) {
			result[word]++
		}
	}

	return result
}

func isFibonacciNumber(number string) bool {
	n, err := strconv.Atoi(number)
	if err != nil {
		return false
	}

	return isPerfectSquare(5*n*n+4) || isPerfectSquare(5*n*n-4)
}

func isPerfectSquare(num int) bool {
	root := int(math.Sqrt(float64(num)))
	return root*root == num
}

// Task 15: Numere cu trei biti de 1
func bitiUnuMap(words []string) map[string]int {
	result := make(map[string]int)

	for _, word := range words {
		if hasThreeSetBits(word) {
			result[word]++
		}
	}

	return result
}

func hasThreeSetBits(number string) bool {
	n, err := strconv.Atoi(number)
	if err != nil {
		return false
	}

	count := 0
	for n > 0 {
		count += n & 1
		n >>= 1
	}

	return count == 3
}

func averageWordsReduce(results []map[string]int) float64 {
	totalWords := 0
	totalArrays := len(results)

	for _, result := range results {
		totalWords += len(result)
	}

	if totalArrays == 0 {
		return 0
	}

	return float64(totalWords) / float64(totalArrays)
}

func performMapReduce(data [][]string, mapperFunc MapReduce, reducerFunc func([]map[string]int) float64) float64 {
	var wg sync.WaitGroup
	var results []map[string]int
	ch := make(chan map[string]int, len(data))

	for _, words := range data {
		wg.Add(1)

		go func(words []string) {
			defer wg.Done()
			ch <- mapperFunc(words)
		}(words)
	}

	go func() {
		wg.Wait()
		close(ch)
	}()

	for result := range ch {
		results = append(results, result)
	}

	return reducerFunc(results)
}

func runTestsWithParameters(input [][]string, mapper MapReduce, reducer func([]map[string]int) float64, testName string) {
	average := performMapReduce(input, mapper, reducer)
	fmt.Println(input)
	fmt.Printf("%s: %f\n\n", testName, average)
}

func runTests() {
	// 1
	runTestsWithParameters(
		[][]string{
			{"aabbb", "ebep", "blablablaa", "hijk", "wsww"},
			{"abba", "eeeppp", "cocor", "ppppppaa", "qwerty", "acasq"},
			{"lalala", "lalal", "papapa", "papap"},
		},
		vocalePareMap,
		averageWordsReduce,
		"1. Nr par vocale, consoane / 3",
	)

	// 2
	runTestsWithParameters(
		[][]string{
			{"a1551a", "parc", "ana", "minim", "1pcl3"},
			{"calabalac", "tivit", "leu", "zece10", "ploaie", "9ana9"},
			{"lalalal", "tema", "papa", "ger"},
		},
		palindromMap,
		averageWordsReduce,
		"2. Palindrom",
	)

	// 3
	runTestsWithParameters(
		[][]string{
			{"apap", "paprc", "apnap", "mipnipm", "copil"},
			{"cepr", "program", "lepu", "zepcep", "golang", "tema"},
			{"par", "impar", "papap", "gepr"},
		},
		pasareascaMap,
		averageWordsReduce,
		"3. Pasareasca",
	)

	// 4
	runTestsWithParameters(
		[][]string{
			{"ana", "parc", "impare", "era", "copil"},
			{"cer", "program", "leu", "alee", "golang", "info"},
			{"inima", "impar", "apa", "eleve"},
		},
		vocalaStartEndMap,
		averageWordsReduce,
		"4. Termina si incepe cu vocala",
	)

	// 5
	runTestsWithParameters(
		[][]string{
			{"acultatef", "parc", "cultateaf", "faculatet", "copil"},
			{"cer", "tatefacul", "leu", "alee", "golang", "ultatefac"},
			{"tefaculta", "impar", "apa", "eleve"},
		},
		anagramaMap,
		averageWordsReduce,
		"5. Anagrame",
	)

	// 6
	runTestsWithParameters(
		[][]string{
			{"AcasA", "CasA", "FacultatE", "SisTemE", "distribuite"},
			{"GolanG", "map", "reduce", "Problema", "TemA", "ProieCt"},
			{"LicentA", "semestru", "ALGORitM", "StuDent"},
		},
		literaMareMicaMap,
		averageWordsReduce,
		"6. Incep termina cu litera mare, nr par litere mici",
	)

	// 7
	runTestsWithParameters(
		[][]string{
			{"țânțar", "carte", "ulcior", "copac", "plante"},
			{"beci", "", "mlăștinos", "astronaut", "stele", "planete"},
			{"floare", "somn", "șosetă", "scârțar"},
		},
		diacriticeMap,
		averageWordsReduce,
		"7. Cel putin doua diacritice",
	)

	// // 8
	// runTestsWithParameters(
	// 	[][]string{
	// 		{"prajitura", "camion", "foaie", "liliac", "uezrv"},
	// 		{"carte", "trofeu", "xzigw", "laptop", "scris", "muzica"},
	// 		{"pictura", "telefon", "parapanta", "catel"},
	// 	},
	// 	averageWordsReduce,
	// )

	// 9
	// runTestsWithParameters(
	// 	[][]string{
	// 		{"stele", "mele", "borcan", "vajnic", "strașnic"},
	// 		{"crocodil", "garnisit", "mușețel", "făurit", "arhanghel", "noapte"},
	// 		{"lampă", "sine", "cine", "toriște"},
	// 	},
	// 	// Add the necessary parameters for test 9
	// 	averageWordsReduce,
	// )

	// 10
	runTestsWithParameters(
		[][]string{
			{"caracatiță", "ceva", "saar", "aaastrfb", ""},
			{"aaabbbccc", "caporal", "ddanube", "jahfjksgfjhs", "ajsdas", "urs"},
			{"scoica", "coral", "arac", "karnak"},
		},
		alternantaConsoanaVocalaMap,
		averageWordsReduce,
		"10. Alterneaza consoana vocala",
	)

	// 11
	runTestsWithParameters(
		[][]string{
			{"sadsa1@A", "cevaA!4", "saar", "aaastrfb", ""},
			{"aaabbbccc", "!Caporal1", "ddanube", "jahfjksgfjhs", "ajsdas", "urs"},
			{"scoica", "Coral!@12", "arac", "karnak"},
		},
		parolePuterniceMap,
		averageWordsReduce,
		"11. Parole puternice",
	)

	// 12
	runTestsWithParameters(
		[][]string{
			{"/dev/null", "/bin", "saar", "teme/scoala/2020", ""},
			{"proiect/tema", "/dev", "ddanube", "jahfjksgfjhs", "ajsdas", "urs"},
			{"scoica", "/teme/repos/git", "arac", "karnak"},
		},
		caiAbsoluteRelativeMap,
		averageWordsReduce,
		"12. Cai absolute si relative",
	)

	// 13
	runTestsWithParameters(
		[][]string{
			{"Popescu", "Ionescu", "Pop", "aaastrfb", ""},
			{"Nicolae", "Dumitrescu", "ddanube", "jahfjksgfjhs", "ajsdas", "urs"},
			{"Dumitru", "Angelescu", "arac", "karnak"},
		},
		numeRomanestiMap,
		averageWordsReduce,
		"13. Nume cu escu",
	)

	// 14
	runTestsWithParameters(
		[][]string{
			{"12", "5", "6", "13", "7"},
			{"21", "20", "42", "43", "8", "38"},
			{"54", "55", "34", "100"},
		},
		fibonacciMap,
		averageWordsReduce,
		"14. Numere Fibonacci",
	)

	// 15
	runTestsWithParameters(
		[][]string{
			{"1", "13", "6", "7", "9"},
			{"19", "20", "43", "43", "21", "53"},
			{"54", "55", "28", "101"},
		},
		bitiUnuMap,
		averageWordsReduce,
		"15. Numere pe cu trei biti de 1",
	)
}

func main() {
	runTests()
}
