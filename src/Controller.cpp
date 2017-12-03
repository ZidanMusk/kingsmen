/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>
#include "Search.h"
#include "Evaluate.h"
#include "AlphaBeta.h"
#include "PVS.h"
#include "MTDF.h"


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
        else printf("GUI PORT = %d\n", newsockfd);
        bzero(buffer, 256);
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
        printf("returned s at  wait for move %s\n", s.c_str());
        return s;
    }

    void send_move(string src, string dst) {
        string y = '2' + src + dst;
        printf("Sending");
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
        printf("sent to gui %s\n", y.c_str());
        if (n < 0) error("ERROR writing to socket");

    }

    string wait_for_mode() {
        n = read(newsockfd2, buffer, 4);
        int g = byte_to_Integer(buffer);
        string sh = "" + to_string(g);
        clear();
        return sh;


    }
    void run() {
        
        Board *board = new Board();
        Board *boardMTDF = new Board(false);
        Evaluate *evaluate = new Evaluate(board);

        this->connect();
        this->connect2();
        int flag = -1;
        flag = this->wait_for_first_player();
        string F = "" + to_string(flag);
        string initial_state = this->wait_for_intial_state();
        string mode = this->wait_for_mode();
        //this->Send_GUI(mode);
        board->fenInterpreter(initial_state, flag);
        string color = "";
        if (board->me == 'w')
            color = "White";
        else
            color = "Black";
        this->Send_GUI(color);
        string fff = this->Receive_GUI();
        this->Send_GUI(F);
        fff = this->Receive_GUI();
        this->Send_GUI(initial_state);
        fff = this->Receive_GUI();
        cout << mode;
        if (mode == "1")
            mode = "human";
        else
            mode = "AI";
        this->Send_GUI(mode);
        fff = this->Receive_GUI();



        int maxDepth = 10;
        int timeL = 20;
//    Search *baseline = new AlphaBeta(maxDepth, board, evaluate);
        Search *baseline = new PVS(maxDepth,board,evaluate,true,timeL);
//    Search *mtdf = new MTDF(maxDepth,boardMTDF,evaluate, true, true, true,timeL);

        int bestMoveId;

        string Ack;

        if (mode == "human") {
            while (1) {
                if (board->isOver())
                    break;
                if (board->whiteToMove) {
                    baseline->GetBestMove();
                    bestMoveId = (int) baseline->bestMove;
                    string move = board->moveInterpret(bestMoveId);
                    this->Send_GUI(move);
                    Ack = this->Receive_GUI();
                    string src;
                    string dst;
                    while (1) {
                        //move = this->Receive_GUI();
                        cin>>move;
                        printf("Your move is %s\n", move.c_str());
                        src = move.substr(0, 2);
                        dst = move.substr(2, 2);

                        if (board->gui_isValid(src, dst, (int) (move[4] - '0')) == 'V') {
                            string msg = "V";
                            msg += board->gui_gameState();
                            msg += board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                            cout << evaluate->evaluate() << endl;
                            break;
                        } else {
                            string msg = "I";
                            msg += board->gui_gameState();
                            msg += board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        }
                    }
                    if (move[4] == '0') {
                        this->send_move(src, dst);
                    } else // promotion
                    {
                        string prom = "";

                        if ((move[4]) == '4')prom = 'N';
                        if ((move[4]) == '5')prom = 'B';
                        if ((move[4]) == '6')prom = 'R';
                        if ((move[4]) == '7')prom = 'Q';

                        if (board->me == 'b')prom[0] = tolower(prom[0]);
                        this->send_promotion(src, dst, prom);

                    }
                } else {
                    string move = this->wait_for_mov();
                    if (move[0] == '2')//single move
                    {
                        string src = move.substr(1, 2);
                        string dst = move.substr(3, 2);
                        if (board->gui_isValid(src, dst, 0) == 'V') {
                            string msg = src + dst + "0";
                            msg += board->gui_gameState();
                            msg += board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                            cout << evaluate->evaluate() << endl;

                        } else {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();

                        }

                    } else if (move[0] == '6')//promotion
                    {

                        string src = move.substr(1, 2);
                        string dst = move.substr(3, 2);
                        int prom = 0;
                        if (toupper(move[5]) == 'N')prom = 4;
                        if (toupper(move[5]) == 'B')prom = 5;
                        if (toupper(move[5]) == 'R')prom = 6;
                        if (toupper(move[5]) == 'Q')prom = 7;

                        if (board->gui_isValid(src, dst, prom) == 'V') {
                            string msg = src + dst + to_string(prom) + board->gui_gameState() + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                            cout << evaluate->evaluate() << endl;

                        } else {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();

                        }


                    } else if (move[0] == '3')//w/l timeout
                    {
                        if (toupper(move[1]) == 'W') {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        } else {
                            string msg = board->getLosingKing() + "l" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();

                        }
                    }
                }

            }
        } else {

            while (1) {
                if (board->isOver())
                    break;
                if (board->whiteToMove) {
                    //baseline->GetBestMove();
                    //bestMoveId = (int) baseline->bestMove;
                    //string move = board->moveInterpret(bestMoveId);
                    string move;
                    cin >> move;
                    cout << "OUR FUCKIN MOVE " << move << endl;
                    string src = move.substr(0, 2);
                    string dst = move.substr(2, 2);
                    board->gui_isValid(src, dst, (int) (move[4] - '0'));
                    this->Send_GUI(move + board->gui_gameState() + board->toFen());
                    string ACK = this->Receive_GUI();
                    cout << evaluate->evaluate() << endl;

                    if (move[4] == '0') {
                        this->send_move(src, dst);
                    } else // promotion
                    {
                        string prom = "";

                        if ((move[4]) == '4')prom = 'N';
                        if ((move[4]) == '5')prom = 'B';
                        if ((move[4]) == '6')prom = 'R';
                        if ((move[4]) == '7')prom = 'Q';

                        if (board->me == 'b')prom[0] = tolower(prom[0]);
                        this->send_promotion(src, dst, prom);

                    }
                } else {
                    string move = this->wait_for_mov();
                    if (move[0] == '2')//single move
                    {
                        string src = move.substr(1, 2);
                        string dst = move.substr(3, 2);
                        if (board->gui_isValid(src, dst, 0) == 'V') {
                            string msg = src + dst + "0" + board->gui_gameState() + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                            cout << evaluate->evaluate() << endl;

                        } else {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        }

                    } else if (move[0] == '6')//promotion
                    {

                        string src = move.substr(1, 2);
                        string dst = move.substr(3, 2);
                        int prom = 0;
                        if (toupper(move[5]) == 'N')prom = 4;
                        if (toupper(move[5]) == 'B')prom = 5;
                        if (toupper(move[5]) == 'R')prom = 6;
                        if (toupper(move[5]) == 'Q')prom = 7;

                        if (board->gui_isValid(src, dst, prom) == 'V') {
                            string msg = src + dst + to_string(prom) + board->gui_gameState() + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                            cout << evaluate->evaluate() << endl;

                        } else {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        }


                    } else if (move[0] == '3')//w/l timeout
                    {
                        if (toupper(move[1]) == 'W') {
                            string msg = board->getLosingKing() + "w" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        } else {
                            string msg = board->getLosingKing() + "l" + board->toFen();
                            this->Send_GUI(msg);
                            Ack = this->Receive_GUI();
                        }
                    }
                }


            }

        }
        close(this->newsockfd2);
        close(this->sockfd);

    }
};