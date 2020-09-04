#define _CRT_SECURE_NO_WARNINGS
#include "ClientSocket.h"
#include "ServerSocket.h"
#include <iostream>
#include <string>
#include "TicTacToe.h"

void runAsClient();
void runAsServer();
void takeTurn(TicTacToe&, const char&);

int main()
{
    std::string input = "";
    std::cout << "Would you like to run as Server or Client?\n> " << std::endl;
    
    while (input != "Server" and input != "Client") {
        std::getline(std::cin, input);
        if (input == "Server")
            runAsServer();
        else if (input == "Client")
            runAsClient();
    }

    return 0;
}

void runAsClient() {
    //create game
    TicTacToe game;
    char board[10];

    //Setup client socket
    ClientSocket client;
    client.startClient();

    //Get sever info to resolve server
    std::string input;
    std::cout << "Server ip?\n> " << std::endl;
    std::getline(std::cin, input);
    client.resolveServer(input.c_str());

    client.connect();
    //Recieve 'who goes first' data
    char* received = strcat(client.receive().recvbuf, "\0");
    bool isFirst = strcmp(received, "s") == 0;
    std::cout << (isFirst ? "You are first." : "You are second.") << std::endl;
    
    if(!isFirst) {
        //receive board info
        received = client.receive().recvbuf;
        game.setBoard(received);
        game.getBoard(board);
        game.display(board);
    }
    takeTurn(game, 'O');
    game.getBoard(board);
    game.display(board);
    client.send(board);

    client.shutdown();
}

void runAsServer() {
    char* received;
    //Create game
    TicTacToe game;
    char board[10];
    //game.getBoard(board);
    //game.display(board);
    bool isFirst = game.choosePlayer1();

    //setup server socket
    ServerSocket server;
    server.startServer();
    server.resolveServer();
    server.createListeningSocket();
    server.setupListeningSocket();
    std::cout << "Waiting for client to connect" << std::endl;
    server.acceptClient();
    std::cout << "Connected" << std::endl;

    std::cout << (isFirst ? "You are first." : "You are second.") << std::endl;
    server.send(isFirst ? "f" : "s");

    if (isFirst) {
        takeTurn(game, 'X');
        game.getBoard(board);
        game.display(board);
        server.send(board);
    }
    received = server.receive().recvbuf;
    game.setBoard(received);
    game.getBoard(board);
    game.display(board);


    //std::cout << server.receive().recvbuf << std::endl;
    //std::string input;
    //std::getline(std::cin, input);
    //server.send(input.c_str(), true);

    server.closeListeningSocket();
    server.shutdown();
}

void takeTurn(TicTacToe& game, const char& piece) {
    int position;

    std::cout << "Choose a position(1-9)" << std::endl;
    std::cin >> position;  
    while (!game.makePlay(position, piece)) {
        std::cout << "Invalid position, try again.(1-9)" << std::endl;
        std::cin >> position;
    }
}