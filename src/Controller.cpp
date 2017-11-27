/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <string.h>

#include <bits/stdc++.h>
#include "Search.h"
#include "AlphaBeta.h"

using namespace std;
typedef unsigned char byte;


class name {
public:
    int sockfd, sockfd2, newsockfd, newsockfd2, portno, portno2;
    socklen_t clilen, clilen2;
    char buffer[256];
    struct sockaddr_in serv_addr, serv_addr2, cli_addr, cli_addr2;
    int n;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string port, port2;
    string ip;

    name(string port_1, string port_2, string ip_1) : port(port_1), port2(port_2), ip(ip_1) {
    };


    void connect2() {

        sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd2 < 0)
            error("ERROR opening socket");
        bzero((char *) &serv_addr2, sizeof(serv_addr2));
        portno2 = atoi(port2.c_str());
        const char *cp = ip.c_str();
        serv_addr2.sin_family = AF_INET;
        serv_addr2.sin_addr.s_addr = inet_addr(cp);
        serv_addr2.sin_port = htons(portno2);
        if (bind(sockfd2, (struct sockaddr *) &serv_addr2,
                 sizeof(serv_addr2)) < 0)
            error("ERROR on binding");
        //printf("2bl l listen");
        ////////////////////////////listen for GUI//////////////////////////

        listen(sockfd2, 5);
        printf("Listening to PYTHON. \n");
        clilen = sizeof(cli_addr2);
        //printf("heeeeeeeeeeeh");
        newsockfd2 = accept(sockfd2,
                            (struct sockaddr *) &cli_addr2,
                            &clilen2);

        if (newsockfd2 < 0)
            error("ERROR on accept GUI = ");
        else printf("PYTHON PORT  %d \n", newsockfd2);

        /////////////////////////////////listen for python////////////////////////////////////


        bzero(buffer, 256);
    }

    void connect() {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(port.c_str());
        const char *cp = ip.c_str();
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(cp);
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0)
            error("ERROR on binding");
        listen(sockfd, 5);
        printf("Listening to GUI. \n");
        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr,
                           &clilen);

        if (newsockfd < 0)
            error("ERROR on accept Python client");
        else printf("GUI PORT = %d", newsockfd);
    }

    void error(const char *msg) {
        perror(msg);
        exit(1);
    }


    int byte_to_Integer(char buffer[4]) {
        int Int32 = 0;

        Int32 = (Int32 << 8) + buffer[3];
        Int32 = (Int32 << 8) + buffer[2];
        Int32 = (Int32 << 8) + buffer[1];
        Int32 = (Int32 << 8) + buffer[0];
        return Int32;
    }

    string wait_for_intial_state() {
        n = read(newsockfd2, buffer, 4);
        //printf("n is %d",n);
        int size = byte_to_Integer(buffer);
        //printf("size %d",size);
        n = read(newsockfd2, buffer, size);
        //printf("buffer is %s",buffer);

        string s(buffer);
        clear();
        return s;

    }

    int wait_for_first_player() {

        n = read(newsockfd2, buffer, 4);
        int opcode = byte_to_Integer(buffer);
        n = read(newsockfd2, buffer, 4);
        int x = byte_to_Integer(buffer);
        printf("X is %d \n", x);
        bzero(buffer, 256);
        return x;
    }


    string wait_for_mov() {

        n = read(newsockfd2, buffer, 4);
        int opcode = byte_to_Integer(buffer);
        string s = "";
        //printf("op code  %d\n",opcode);

        if (opcode == 2)///single move
        {
            n = read(newsockfd2, buffer, 4);
            printf("buffer is %s \n", buffer);
            string str(buffer);
            s = '2' + str;

        } else if (opcode == 6)///promotion
        {
            n = read(newsockfd2, buffer, 5);
            string str(buffer);
            s = '6' + str;


        } else if (opcode == 3)///win or lose message
        {
            n = read(newsockfd2, buffer, 1);
            string str(buffer);
            s = '3' + str;


        }
        bzero(buffer, 256);
        printf("returned s at  wait for move %s", s.c_str());
        return s;
    }

    void send_move(string src, string dst) {
        string y = '2' + src + dst;
        n = write(newsockfd2, y.c_str(), 5);
        if (n < 0) error("ERROR writing to socket");
    }

    void send_promotion(string src, string dst, string promotion) {
        string y = '6' + src + dst + promotion;

        n = write(newsockfd2, y.c_str(), 6);
        if (n < 0) error("ERROR writing to socket");
    }

    void send_win() {

        n = write(newsockfd2, "3", 1);
        if (n < 0) error("ERROR writing to socket");
    }

    void clear() {
        bzero(buffer, 256);

    }

    string Receive_GUI() {
        n = read(newsockfd, buffer, 5);
        printf("buffer is %s \n", buffer);
        string str(buffer);
        clear();
        return str;
    }

    void Send_GUI(string y) {
        //y="abs";
        //int x=y.size();
        n = write(newsockfd, y.c_str(), y.size());
        //printf("sent to gui %s",y.c_str());
        printf("sent to gui %s", y.c_str());
        if (n < 0) error("ERROR writing to socket");

    }

};

int main(int argc, char *argv[]) {

    name temp = name("7770", "7771", "192.168.1.3");
    temp.connect();
    temp.connect2();

    int flag = temp.wait_for_first_player();
    string fff = temp.Receive_GUI();
    string F = "" + to_string(flag);
    temp.Send_GUI(F);
    string initial_state = temp.wait_for_intial_state();
    temp.Send_GUI(initial_state);


    Board *board = new Board();
    board->fenInterpreter(initial_state, flag);

    int maxDepth = 5;
    Evaluate *evaluate = new Evaluate(board);
    Search *baseline = new AlphaBeta(maxDepth, board, evaluate);

    int bestMoveId;
    if (board->whiteToMove) {
        baseline->GetBestMove();
        bestMoveId = (int)baseline->bestMove;
        board->doo(bestMoveId);
    }

    while (1) {
//////////////////////////////waiting for opponent to play


////////////////////////////////////////////I am playing(my turn)
        baseline->GetBestMove();
        bestMoveId = (int)baseline->bestMove;
        board->doo(bestMoveId);

        break;

    }
    //close(temp.newsockfd2);
    //close(temp.sockfd);
    return 0;
}

