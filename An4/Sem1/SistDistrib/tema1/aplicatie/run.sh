#!/bin/bash

protoc --go_out=./server --go-grpc_out=./server ./server/services.proto
echo "Compiling Server..."
go build -o grpcServer.exe ./server/server.go
echo "Server compiled"

echo "Compiling Client..."
go build -o grpcClient.exe ./client/client.go
echo "Client compiled"

echo "Starting Server..."
./grpcServer.exe &
SERVER_PID=$!
echo "Server started with PID $SERVER_PID"
sleep 2

# Function to start clients in the background
start_clients() {
    echo "Starting 5 gRPC Clients..."
    for i in {1..5}; do
       ./grpcClient.exe & 
    done
}

# Start clients in the background
start_clients &

# Display the message immediately
echo -e "\nPress any key to stop the server ..."
read -r -n1 -s

kill "$SERVER_PID"
echo "Server stopped"
