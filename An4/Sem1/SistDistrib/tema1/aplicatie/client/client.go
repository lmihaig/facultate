package main

import (
	"bufio"
	"context"
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

func makeRPCCall(client pb.ServicesClient, callType string, name string) string {
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	// sugar.Infof("Client %s a facut request cu datele: %v", name, callType)
	switch callType {
	case "JumbleLetters":
		r, err := client.JumbleLettersFromArray(ctx, &pb.StringArrayRequest{Strings: []string{"casa", "masa", "trei", "tanc", "4321"}})
		fatalError("Eroare in call", err)
		return fmt.Sprint(r.GetStrings())
	case "FindPerfectSquares":
		r, err := client.FindPerfectSquareCounts(ctx, &pb.StringArrayRequest{Strings: []string{"abd4g5", "1sdf6fd", "fd2fdsf5"}})
		fatalError("Eroare in call", err)
		return fmt.Sprint(r.GetValue())
	default:
		fatalError(fmt.Sprintf("Serviciu Invalid %s", callType), errors.New("N/A"))
		return "NA"
	}
}


func main() {
	
	sugar = util.InitLogger(false).Sugar()
	defer sugar.Sync()

	names, err := readNamesFile("client/names.txt")
	fatalError("Eroare citirea fisierului cu nume", err)
	name := genRandomName(names)

	conn, err := grpc.Dial(address, grpc.WithTransportCredentials(insecure.NewCredentials()), grpc.WithUserAgent(name))
	fatalError("Conexiunea nu s-a putut realiza", err)
	defer conn.Close()
	
	rpcCalls := []string{"JumbleLetters",
		// "FindPerfectSquares"
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
