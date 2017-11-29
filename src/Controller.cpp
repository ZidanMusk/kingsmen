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

    string wait_for_mode() {
        n = read(newsockfd2, buffer, 1);
        string str(buffer);
        return str;


    }
};

int main(int argc, char *argv[]) {

    ifstream config_file;
    config_file.open("config.txt");

    string gui_port;
    string agent_port;
    string my_ip;
    config_file >> gui_port >> agent_port >> my_ip;
    config_file.close();

    cout<<gui_port<<endl;
    cout<<agent_port<<endl;
    cout<<my_ip<<endl;


//    name temp = name("7772", "7779", "192.168.1.3");
    name temp = name(gui_port, agent_port, my_ip);

    boared _b;

    temp.connect();
    temp.connect2();
    int flag = -1;
    flag = temp.wait_for_first_player();
    string F = "" + to_string(flag);
    string intial_state = temp.wait_for_intial_state();
    string mode = temp.wait_for_mode();
    temp.Send_GUI(mode);
    _b.fenIntrpreter(intial_state, flag);
    string color = "";
    if (_b.me == 'w')
        color = "White";
    else
        color = "Black";
    temp.Send_GUI(color);
    string fff = temp.Receive_GUI();
    temp.Send_GUI(F);
    fff = temp.Receive_GUI();
    temp.Send_GUI(intial_state);
    fff = temp.Receive_GUI();
    if (mode == "0")
        mode = "human";
    else
        mode = "AI";
    temp.Send_GUI(mode);
    fff = temp.Receive_GUI();


    Board *board = new Board();
    board->fenInterpreter(initial_state, flag);

    int maxDepth = 5;
    Evaluate *evaluate = new Evaluate(board);
    Search *baseline = new AlphaBeta(maxDepth, board, evaluate);

    int bestMoveId;
    if (board->whiteToMove) {
    }

    if (mode == "human") {
        while (1) {
            if (board->whiteToMove) {
                baseline->GetBestMove();
                bestMoveId = (int) baseline->bestMove;
                string move = board->moveInterpret(bestMoveId);
                Send_GUI(move);
                string ACK = Recieve_GUI();
                string src;
                string dst;
                while (1) {
                    move = Recieve_GUI();
                    printf("Your move is", move.c_str());
                    src = move.substr(0, 2);
                    dst = move.substr(2, 2);

                    if (board->gui_isValid(src, dst, (int) (move[4] - '0')) == 'V') {
                        string msg = "V" + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Recieve_GUI();
                        break;
                    } else {
                        string msg = "I" + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Recieve_GUI();
                    }
                }
                if (move[4] == '0') {
                    send_move(src, dst);
                } else // promotion
                {
                    string prom = "";

                    if ((move[4]) == '4')prom = 'N';
                    if ((move[4]) == '5')prom = 'B';
                    if ((move[4]) == '6')prom = 'R';
                    if ((move[4]) == '7')prom = 'Q';

                    if (board->me == 'b')prom = to_lower(prom);
                    send_promotion(src, dst, prom);

                }
            } else {
                string move = wait_for_mov();
                if (move[0] == '2')//single move
                {
                    string src = move.substr(1, 2);
                    string dst = move.substr(3, 2);
                    if (board->gui_isValid(src, dst, 0) == 'V') {
                        string msg = src + dst + "0" + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }

                } else if (move[0] == '6')//promotion
                {

                    string src = move.substr(1, 2);
                    string dst = move.substr(3, 2);
                    int prom = 0;
                    if (to_upper(move[5]) == 'N')prom = 4;
                    if (to_upper(move[5]) == 'B')prom = 5;
                    if (to_upper(move[5]) == 'R')prom = 6;
                    if (to_upper(move[5]) == 'Q')prom = 7;

                    if (board->gui_isValid(src, dst, prom) == 'V') {
                        string msg = src + dst + to_string(prom) + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }


                } else if (move[0] == '3')//w/l timeout
                {
                    if (to_upper(move[1]) == 'W') {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'l' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }
                }
            }


            break;

        }
    } else {
//AAAAAAAAAAAAAAAAAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
        while (1) {
            if (board->whiteToMove) {
                baseline->GetBestMove();
                bestMoveId = (int) baseline->bestMove;
                string move = board->moveInterpret(bestMoveId);
                Send_GUI(move);
                string ACK = Recieve_GUI();
                string src = move.substr(0, 2);
                string dst = move.substr(2, 2);

                if (move[4] == '0') {
                    send_move(src, dst);
                } else // promotion
                {
                    string prom = "";

                    if ((move[4]) == '4')prom = 'N';
                    if ((move[4]) == '5')prom = 'B';
                    if ((move[4]) == '6')prom = 'R';
                    if ((move[4]) == '7')prom = 'Q';

                    if (board->me == 'b')prom = to_lower(prom);
                    send_promotion(src, dst, prom);

                }
            } else {
                string move = wait_for_mov();
                if (move[0] == '2')//single move
                {
                    string src = move.substr(1, 2);
                    string dst = move.substr(3, 2);
                    if (board->gui_isValid(src, dst, 0) == 'V') {
                        string msg = src + dst + "0" + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }

                } else if (move[0] == '6')//promotion
                {

                    string src = move.substr(1, 2);
                    string dst = move.substr(3, 2);
                    int prom = 0;
                    if (to_upper(move[5]) == 'N')prom = 4;
                    if (to_upper(move[5]) == 'B')prom = 5;
                    if (to_upper(move[5]) == 'R')prom = 6;
                    if (to_upper(move[5]) == 'Q')prom = 7;

                    if (board->gui_isValid(src, dst, prom) == 'V') {
                        string msg = src + dst + to_string(prom) + board->gui_gameState() + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }


                } else if (move[0] == '3')//w/l timeout
                {
                    if (to_upper(move[1]) == 'W') {
                        string msg = "a1" + "a1" + "0" + 'w' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();
                    } else {
                        string msg = "a1" + "a1" + "0" + 'l' + board->toFen();
                        Send_GUI(msg);
                        Ack = Receive_GUI();

                    }
                }
            }


        }

    }
    //close(temp.newsockfd2);
    //close(temp.sockfd);
    return 0;
}

