package main

import (
	"bufio"
	"context"
	"flag"
	"fmt"
	"math/rand"
	"os"
	"sync"
	pb "tema1/server/services"
	util "tema1/util"
	"time"

	"errors"

	"go.uber.org/zap"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

const (
	address = "localhost:50051"
)

var sugar *zap.SugaredLogger

func genRandomName(names []string) string {
	return fmt.Sprintf("%s#%04d", names[rand.Intn(len(names))], 1000+rand.Intn(9999))
}

func readNamesFile(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var names []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		names = append(names, scanner.Text())
	}

	return names, scanner.Err()
}

func fatalError(str string, err error) {
	if err != nil {
		sugar.Error(str, zap.Error(err))
		os.Exit(1)
	}
}

func manualRPCCall(conn *grpc.ClientConn, name string) {
	c := pb.NewServicesClient(conn)

	for {
		fmt.Println("Select RPC call:")
		fmt.Println("1. JumbleLetters")
		fmt.Println("2. FindPerfectSquareCount")
		fmt.Println("3. SumOfReversedIntegers")
		fmt.Println("4. CalculateAverageWithinDigitSumRange")
		fmt.Println("5. ValidateAndConvertBinaryStrings")
		fmt.Println("6. ApplyCaesarCipher")
		fmt.Println("7. DecodeRunLengthEncodedText")
		fmt.Println("8. CountPrimeNumberDigits")
		fmt.Println("9. CountWordsWithEvenParityVowels")
		fmt.Println("10. ComputeGreatestCommonDivisor")
		fmt.Println("11. SumNumbersAfterRightPerm")
		fmt.Println("12. SumAfterDoublingFirstDigit")
		fmt.Println("13. FilterComplexNumbersOutsideRange")
		fmt.Println("14. ValidatePotentialPasswords")
		fmt.Println("15. GenerateRandomPasswords")
		fmt.Println("16. Exit")

		var choice int
		fmt.Scanln(&choice)

		var callType string
		switch choice {
		case 1:
			callType = "JumbleLetters"
		case 2:
			callType = "FindPerfectSquareCount"
		case 3:
			callType = "SumOfReversedIntegers"
		case 4:
			callType = "CalculateAverageWithinDigitSumRange"
		case 5:
			callType = "ValidateAndConvertBinaryStrings"
		case 6:
			callType = "ApplyCaesarCipher"
		case 7:
			callType = "DecodeRunLengthEncodedText"
		case 8:
			callType = "CountPrimeNumberDigits"
		case 9:
			callType = "CountWordsWithEvenParityVowels"
		case 10:
			callType = "ComputeGreatestCommonDivisor"
		case 11:
			callType = "SumNumbersAfterRightPerm"
		case 12:
			callType = "SumAfterDoublingFirstDigit"
		case 13:
			callType = "FilterComplexNumbersOutsideRange"
		case 14:
			callType = "ValidatePotentialPasswords"
		case 15:
			callType = "GenerateRandomPasswords"
		case 16:
			fmt.Println("Exiting manual mode.")
			return
		default:
			fmt.Println("Invalid choice.")
			continue
		}

		r := makeRPCCall(c, callType, name)
		fmt.Printf("Response: %v\n", r)
	}
}

func makeRPCCall(client pb.ServicesClient, callType string, name string) string {
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	// sugar.Infof("Client %s a facut request cu datele: %v", name, callType)
	switch callType {
	case "JumbleLetters":
		r, err := client.JumbleLettersFromArray(ctx, &pb.StringArrayRequest{Strings: []string{"casa", "masa", "trei", "tanc", "4321"}})
		fatalError("Eroare in call", err)
		return fmt.Sprint(r.GetStrings())
	case "FindPerfectSquareCount":
		r, err := client.FindPerfectSquareCount(ctx, &pb.StringArrayRequest{Strings: []string{"abd4g5", "1sdf6fd", "fd2fdsf5"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "SumOfReversedIntegers":
		r, err := client.SumOfReversedIntegers(ctx, &pb.Int32ArrayRequest{Numbers: []int32{12, 13, 14}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "CalculateAverageWithinDigitSumRange":
		r, err := client.CalculateAverageWithinDigitSumRange(ctx, &pb.AverageWithinRangeRequest{
			LowerBound: 2, UpperBound: 10, Numbers: []int32{11, 39, 32, 80, 84}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "ValidateAndConvertBinaryStrings":
		r, err := client.ValidateAndConvertBinaryStrings(ctx, &pb.StringArrayRequest{Strings: []string{"2dasdas", "12", "dasdas", "1010", "101"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetNumbers())

	case "ApplyCaesarCipher":
		r, err := client.ApplyCaesarCipher(ctx, &pb.CaesarCipherRequest{
			Text: "abcdef", Direction: "left", ShiftAmount: 3})
		fatalError("Error in call", err)
		return r.GetValue()

	case "DecodeRunLengthEncodedText":
		r, err := client.DecodeRunLengthEncodedText(ctx, &pb.SingleStringRequest{Value: "1G11o1L"})
		fatalError("Error in call", err)
		return r.GetValue()

	case "CountPrimeNumberDigits":
		r, err := client.CountPrimeNumberDigits(ctx, &pb.UInt32ArrayRequest{Numbers: []uint32{23, 17, 15, 3, 18}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "CountWordsWithEvenParityVowels":
		r, err := client.CountWordsWithEvenParityVowels(ctx, &pb.StringArrayRequest{Strings: []string{"mama", "iris", "bunica", "ala"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "ComputeGreatestCommonDivisor":
		r, err := client.ComputeGreatestCommonDivisor(ctx, &pb.StringArrayRequest{Strings: []string{"24", "16", "aaa", "bbb"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "SumNumbersAfterRightPerm":
		r, err := client.SumNumbersAfterRightPerm(ctx, &pb.RightShiftSumRequest{
			Numbers: []int32{1234, 3456, 4567}, ShiftAmount: 2})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "SumAfterDoublingFirstDigit":
		r, err := client.SumAfterDoublingFirstDigit(ctx, &pb.Int32ArrayRequest{Numbers: []int32{23, 43, 26, 74}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetValue())

	case "FilterComplexNumbersOutsideRange":
		r, err := client.FilterComplexNumbersOutsideRange(ctx, &pb.ComplexNumberRangeRequest{
			LowerBound: 3, UpperBound: 10, Numbers: []int32{3, 4, 5, 6}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetNumbers())

	case "ValidatePotentialPasswords":
		r, err := client.ValidatePotentialPasswords(ctx, &pb.StringArrayRequest{Strings: []string{"Ceva12!@", "asa212", "dasdas"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetStrings())

	case "GenerateRandomPasswords":
		r, err := client.GenerateRandomPasswords(ctx, &pb.StringArrayRequest{Strings: []string{"a", "b", "e", "3", "!", "A", "_"}})
		fatalError("Error in call", err)
		return fmt.Sprint(r.GetStrings())

	default:
		fatalError(fmt.Sprintf("Invalid service %s", callType), errors.New("N/A"))
		return "NA"
	}
}

func main() {
	manualMode := flag.Bool("M", false, "Start in manual mode")
	flag.Parse()

	sugar = util.InitLogger(false).Sugar()
	defer sugar.Sync()

	names, err := readNamesFile("client/names.txt")
	fatalError("Eroare citirea fisierului cu nume", err)
	name := genRandomName(names)

	conn, err := grpc.Dial(address, grpc.WithTransportCredentials(insecure.NewCredentials()), grpc.WithUserAgent(name))
	fatalError("Conexiunea nu s-a putut realiza", err)
	defer conn.Close()

	if *manualMode {
		manualRPCCall(conn, name)
	} else {
		rpcCalls := []string{
			"JumbleLetters", "SumOfReversedIntegers",
			"CalculateAverageWithinDigitSumRange", "ValidateAndConvertBinaryStrings",
			"ApplyCaesarCipher", "DecodeRunLengthEncodedText", "CountPrimeNumberDigits",
			"CountWordsWithEvenParityVowels", "ComputeGreatestCommonDivisor",
			"SumNumbersAfterRightPerm", "SumAfterDoublingFirstDigit",
			"FilterComplexNumbersOutsideRange", "ValidatePotentialPasswords",
			"GenerateRandomPasswords",
		}

		var wg sync.WaitGroup

		for _, rpcCall := range rpcCalls {
			wg.Add(1)
			go func(callType string) {
				defer wg.Done()

				c := pb.NewServicesClient(conn)
				sugar.Infof("Client %s conectat la %s", name, address)

				r := makeRPCCall(c, callType, name)
				sugar.Infof("Client %s a primit raspunsul %v", name, r)

			}(rpcCall)
		}

		wg.Wait()
	}
}
