package util

import (
	"errors"
	"math"
	"math/cmplx"
	"math/rand"
	"regexp"
	"strconv"
	"strings"
	"unicode"
)

func JumbleWords(words []string) ([]string, error) {
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

func isPerfectSquare(num int) bool {
    if num < 0 {
        return false
    }
    
    sqrt := math.Sqrt(float64(num))
    return sqrt == math.Floor(sqrt)
}

func FindPerfectSquaresCount(words []string) uint32 {
	var count uint32 = 0
    for _, s := range words {
        for _, word := range strings.FieldsFunc(s, func(r rune) bool {
            return !unicode.IsDigit(r)
        }) {
			num, err := strconv.Atoi(word);
            if  err == nil && isPerfectSquare(num) {
                count++
            }
        }
    }
    return count
}

func SumOfReversedIntegers(numbers []int32) int32 {
	var sum int32 = 0
	for _, num := range numbers {
		var reversed int32 = 0
		for num > 0 {
			reversed = reversed * 10 + num % 10
			num /= 10
		}
		sum += reversed
	}
	return sum
}

func sumOfDigits(n int32) int32 {
    var sum int32 = 0
    for n > 0 {
        sum += n % 10
        n /= 10
    }
    return sum
}

func CalculateAverageWithinRange(lowerBound int32, upperBound int32, numbers []int32) float64 {
	var sum int32 = 0
	var count int32 = 0
	for _, num := range numbers {
		if sumOfDigits(num) >= lowerBound && sumOfDigits(num) <= upperBound {
			sum += num
			count++
		}
	}
	if count == 0 {
		return 0
	}
	return float64(sum) / float64(count)
}

func ValidateAndConvertBinaryStrings(strings []string) ([]uint32, error) {
	var nums []uint32
	for _, str := range strings {
		num, err := strconv.ParseUint(str, 2, 32)
		if err != nil {
			continue
		}
		nums = append(nums, uint32(num))
	} 
	return nums, nil
}

func ApplyCaesarCipher(text string, direction string, shift uint32) (string, error) {
	if strings.ToLower(direction) != "left" && strings.ToLower(direction) != "right" {
		return "", errors.New("invalid direction")
	}

	var shifted string
	for _, c := range text {
		if !unicode.IsLetter(c) {
			shifted += string(c)
			continue
		}
		if direction == "left" {
			shifted += string((c - 'a' + 26 - rune(shift)) % 26 + 'a')
		} else {
			shifted += string((c - 'a' + rune(shift)) % 26 + 'a')
		}
	}
	return shifted, nil
}


func DecodeRunLengthEncodedText(encoded string) (string, error){
	var decoded string
	for i := 0; i < len(encoded); i++ {
		if unicode.IsDigit(rune(encoded[i])) {
			var count int
			for unicode.IsDigit(rune(encoded[i])) {
				count = count * 10 + int(encoded[i] - '0')
				i++
			}
			if count == 0 {
				return "", errors.New("invalid input")
			}
			for j := 0; j < count; j++ {
				decoded += string(encoded[i])
			}
		} else {
			return "", errors.New("invalid input")
		}
	}
	return decoded, nil
} 


func isPrime(num int32) bool {
	if num < 2 {
		return false
	}
	for i := int32(2); i <= int32(math.Sqrt(float64(num))); i++ {
		if num % i == 0 {
			return false
		}
	}
	return true
}

func CountDigits(num int32) uint32 {
    return uint32(len(strconv.Itoa(int(num))))
}

func CountPrimeNumberDigits(numbers []int32) (uint32, error){
	var digits uint32 = 0

	for _, num := range numbers {
		if isPrime(num) {
			digits += CountDigits(num)
		}
	}
	return digits, nil
}

func CountWordsWithEvenParityVowels(words []string) (uint32, error){
	var count uint32 = 0
	for _, word := range words {
		var vowels uint32 = 0
		for i, c := range word {
			if strings.ContainsRune("aeiou", c) && i % 2 == 0 {
				vowels++
			}
		}
		if vowels % 2 == 0 {
			count++
		}
	}
	return count, nil
}


func computeGCD(a uint32, b uint32) uint32 {
	for b != 0 {
		a, b = b, a % b
	}
	return a
}


func ComputeGreatestCommonDivisor(numbers []string) (uint32, error){
	var gcd uint32 = 0
	for _, num := range numbers {
		n, err := strconv.Atoi(num)
		if err != nil {
			continue
		}
		if gcd == 0 {
			gcd = uint32(n)
		} else {
			gcd = computeGCD(gcd, uint32(n))
		}
	}
	return gcd, nil
}

func permuteNum(num int32, steps int32) int32 {
	var permuted int32 = 0
	for i := 0; i < int(steps); i++ {
		permuted = permuted * 10 + num % 10
		num /= 10
	}
	return permuted
}


func SumNumbersAfterRightPerm(numbers []int32, shift int32) (int32, error){
	var sum int32 = 0
	for _, num := range numbers {
		sum += permuteNum(num, shift)
	}

	return sum, nil
}



func SumAfterDoublingFirstDigit(numbers []int32) (int32, error) {
    var sum int32 = 0
    for _, num := range numbers {
        numStr := strconv.Itoa(int(num))
        doubledNumStr := string(numStr[0]) + numStr
        doubledNum, err := strconv.Atoi(doubledNumStr)
        if err != nil {
            return 0, err
        }
        sum += int32(doubledNum)
    }
    return sum, nil
}


func FilterComplexNumbersOutsideRange(lowerBound int32, upperBound int32, nums []int32) ([]int32, error){
	var filtered []int32
	for i := 0; i < len(nums); i+=2 {
		complexNumAbs := int32(cmplx.Abs(complex(float64(nums[i]), float64(nums[i+1]))))
		if lowerBound >= complexNumAbs || upperBound < complexNumAbs {
			filtered = append(filtered, complexNumAbs)
		}
	}

	return filtered, nil
}


func ValidatePotentialPasswords(passwords []string) ([]string, error) {
    var validated []string

    hasLower := regexp.MustCompile(`[a-z]`)
    hasUpper := regexp.MustCompile(`[A-Z]`)
    hasDigit := regexp.MustCompile(`\d`)
    hasSymbol := regexp.MustCompile(`[\W_]`)

    for _, password := range passwords {
        if hasLower.MatchString(password) &&
           hasUpper.MatchString(password) &&
           hasDigit.MatchString(password) &&
           hasSymbol.MatchString(password) {

            validated = append(validated, password)
        }
    }

    return validated, nil
}


func GenerateRandomPasswords(characters string) ([]string, error) {
    hasLower := regexp.MustCompile(`[a-z]`).MatchString(characters)
    hasUpper := regexp.MustCompile(`[A-Z]`).MatchString(characters)
    hasDigit := regexp.MustCompile(`\d`).MatchString(characters)
    hasSymbol := regexp.MustCompile(`[\W_]`).MatchString(characters)

    if !(hasLower && hasUpper && hasDigit && hasSymbol) {
        return nil, errors.New("input string must contain at least one lowercase, one uppercase, one digit, and one symbol")
    }

    var passwords []string
    numPasswords := rand.Intn(10) + 1

    for i := 0; i < numPasswords; i++ {
        passwordLength := rand.Intn(11) + 5 
        password := make([]byte, passwordLength)

        for j := 0; j < passwordLength; j++ {
            password[j] = characters[rand.Intn(len(characters))]
        }

        passwords = append(passwords, string(password))
    }

    return passwords, nil
}