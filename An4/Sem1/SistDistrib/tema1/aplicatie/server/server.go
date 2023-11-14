package main

import (
	"context"
	"log"
	"net"
	pb "tema1/server/services"
	util "tema1/util"

	"go.uber.org/zap"
	"google.golang.org/grpc"
	"google.golang.org/grpc/metadata"
)

type server struct {
	pb.UnimplementedServicesServer
}

func (s *server) JumbleLettersFromArray(ctx context.Context, in *pb.StringArrayRequest) (*pb.StringArrayResponse, error) {
    handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
        result, err := util.Jumble(input.GetStrings())
        return &pb.StringArrayResponse{Strings: result}, err
    }

    resp, err := handleRequest(ctx, sugar, "JumbleLettersFromArray", in, handlerFunc)
    if err != nil {
        return nil, err
    }
    return resp.(*pb.StringArrayResponse), nil
}

// func (s *server) FindPerfectSquareCounts(ctx context.Context, in *pb.StringArrayRequest) (*pb.UInt32Response, error) {
//     handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
//         count, err := util.FindPerfectSquareCounts(input.GetStrings())
//         return &pb.UInt32Response{Value: count}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "FindPerfectSquareCounts", in, handlerFunc)
//     return resp.(*pb.UInt32Response), err
// }

// func (s *server) SumOfReversedIntegers(ctx context.Context, in *pb.Int32ArrayRequest) (*pb.Int32Response, error) {
//     handlerFunc := func(input *pb.Int32ArrayRequest) (interface{}, error) {
//         sum, err := util.SumOfReversedIntegers(input.GetNumbers())
//         return &pb.Int32Response{Value: sum}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "SumOfReversedIntegers", in, handlerFunc)
//     return resp.(*pb.Int32Response), err
// }

// func (s *server) CalculateAverageWithinDigitSumRange(ctx context.Context, in *pb.AverageWithinRangeRequest) (*pb.DoubleResponse, error) {
//     handlerFunc := func(input *pb.AverageWithinRangeRequest) (interface{}, error) {
//         average, err := util.CalculateAverageWithinRange(input.GetLowerBound(), input.GetUpperBound(), input.GetNumbers())
//         return &pb.DoubleResponse{Value: average}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "CalculateAverageWithinDigitSumRange", in, handlerFunc)
//     return resp.(*pb.DoubleResponse), err
// }

// func (s *server) ValidateAndConvertBinaryStrings(ctx context.Context, in *pb.StringArrayRequest) (*pb.UInt32ArrayResponse, error) {
//     handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
//         converted, err := util.ValidateAndConvertBinaryStrings(input.GetStrings())
//         return &pb.UInt32ArrayResponse{Numbers: converted}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "ValidateAndConvertBinaryStrings", in, handlerFunc)
//     return resp.(*pb.UInt32ArrayResponse), err
// }

// func (s *server) ApplyCaesarCipher(ctx context.Context, in *pb.CaesarCipherRequest) (*pb.SingleStringResponse, error) {
//     handlerFunc := func(input *pb.CaesarCipherRequest) (interface{}, error) {
//         cipherText, err := util.ApplyCaesarCipher(input.GetText(), input.GetDirection(), input.GetShiftAmount())
//         return &pb.SingleStringResponse{Value: cipherText}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "ApplyCaesarCipher", in, handlerFunc)
//     return resp.(*pb.SingleStringResponse), err
// }

// func (s *server) DecodeRunLengthEncodedText(ctx context.Context, in *pb.SingleStringRequest) (*pb.SingleStringResponse, error) {
//     handlerFunc := func(input *pb.SingleStringRequest) (interface{}, error) {
//         decodedText, err := util.DecodeRunLengthEncodedText(input.GetValue())
//         return &pb.SingleStringResponse{Value: decodedText}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "DecodeRunLengthEncodedText", in, handlerFunc)
//     return resp.(*pb.SingleStringResponse), err
// }

// func (s *server) CountPrimeNumberDigits(ctx context.Context, in *pb.UInt32ArrayRequest) (*pb.UInt32Response, error) {
//     handlerFunc := func(input *pb.UInt32ArrayRequest) (interface{}, error) {
//         count, err := util.CountPrimeNumberDigits(input.GetNumbers())
//         return &pb.UInt32Response{Value: count}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "CountPrimeNumberDigits", in, handlerFunc)
//     return resp.(*pb.UInt32Response), err
// }

// func (s *server) CountWordsWithEvenParityVowels(ctx context.Context, in *pb.StringArrayRequest) (*pb.UInt32Response, error) {
//     handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
//         count, err := util.CountWordsWithEvenParityVowels(input.GetStrings())
//         return &pb.UInt32Response{Value: count}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "CountWordsWithEvenParityVowels", in, handlerFunc)
//     return resp.(*pb.UInt32Response), err
// }

// func (s *server) ComputeGreatestCommonDivisor(ctx context.Context, in *pb.StringArrayRequest) (*pb.UInt32Response, error) {
//     handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
//         gcd, err := util.ComputeGreatestCommonDivisor(input.GetStrings())
//         return &pb.UInt32Response{Value: gcd}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "ComputeGreatestCommonDivisor", in, handlerFunc)
//     return resp.(*pb.UInt32Response), err
// }

// func (s *server) FilterComplexNumbersOutsideRange(ctx context.Context, in *pb.ComplexNumberRangeRequest) (*pb.Int32ArrayResponse, error) {
//     handlerFunc := func(input *pb.ComplexNumberRangeRequest) (interface{}, error) {
//         filtered, err := util.FilterComplexNumbersOutsideRange(input.GetLowerBound(), input.GetUpperBound(), input.GetNumbers())
//         return &pb.Int32ArrayResponse{Numbers: filtered}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "FilterComplexNumbersOutsideRange", in, handlerFunc)
//     return resp.(*pb.Int32ArrayResponse), err
// }

// func (s *server) ValidatePotentialPasswords(ctx context.Context, in *pb.StringArrayRequest) (*pb.StringArrayResponse, error) {
//     handlerFunc := func(input *pb.StringArrayRequest) (interface{}, error) {
//         validated, err := util.ValidatePotentialPasswords(input.GetStrings())
//         return &pb.StringArrayResponse{Strings: validated}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "ValidatePotentialPasswords", in, handlerFunc)
//     return resp.(*pb.StringArrayResponse), err
// }

// func (s *server) GenerateRandomPasswords(ctx context.Context, in *pb.CharacterArrayRequest) (*pb.StringArrayResponse, error) {
//     handlerFunc := func(input *pb.CharacterArrayRequest) (interface{}, error) {
//         passwords, err := util.GenerateRandomPasswords(input.GetCharacters())
//         return &pb.StringArrayResponse{Strings: passwords}, err
//     }

//     resp, err := handleRequest(ctx, sugar, "GenerateRandomPasswords", in, handlerFunc)
//     return resp.(*pb.StringArrayResponse), err
// }



func logRequestResponse(sugar *zap.SugaredLogger, requestType string, stage string, additionalInfo ...interface{}) {
    sugar.Infof("Server %s a primit requestul: %s. %v", stage, requestType, additionalInfo)
}


func handleRequest[T any](ctx context.Context, sugar *zap.SugaredLogger, requestType string, input T, handlerFunc func(T) (interface{}, error)) (interface{}, error) {
	sugar.Infof("Server a primit requestul: %s", requestType)
    sugar.Info("Serverul proceseaza datele")
    response, err := handlerFunc(input)
    if err != nil {
        sugar.Error("Eroare la procesarea datelor: ", err)
        return nil, err
    }
	headers, _ := metadata.FromIncomingContext(ctx)
	sugar.Infof("Serverul trimite %v catre client %s", response, headers.Get("user-agent")[0])
    return response, nil
}



var sugar *zap.SugaredLogger

func main() {
	sugar = util.InitLogger(true).Sugar()
	// mute logger
	// sugar = zap.NewNop().Sugar()
	defer sugar.Sync()

	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatal("failed to listen: ", err)
	}

	s := grpc.NewServer()
	pb.RegisterServicesServer(s, &server{})

	log.Println("server listening at ", lis.Addr())

	if err := s.Serve(lis); err != nil {
		log.Fatal("failed to serve: ", err)
	}
}