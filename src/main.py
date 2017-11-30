from Client import *

# ServerIp='192.168.1.2'
# ServerPort=7778
#
# AgentIp='192.168.1.3'
# AgentPort=7773

config_lines = []

with open("config.txt") as f:
    lines = f.readlines()

for line in lines:
    config_lines.append(line.strip())

for line in config_lines:
    print(line)

AgentPort = int(config_lines[1])
AgentIp = config_lines[2]
ServerPort = int(config_lines[3])
ServerIp = config_lines[4]

print(AgentPort)
print(AgentIp)
print(ServerPort)
print(ServerIp)

try:
    # create client object
    client = chess_client(ServerIp, ServerPort)
    client2= chess_client(AgentIp,AgentPort)  #AGENT CONNECTION
    # connect to sever
    client.srvconnect()
    client2.srvconnect()
    # wait for other player to connect to get intial board state ; blocks
    state=client.waitForPlayer()
    print '[+] other Player connected'
    print '=> Has first move : ' + str(client.has_first_move)
    print '=> Initial board : '+client.intial_string
    client2.send_mov(state)
    #print state
    flag = client.has_first_move

    i=555
    # Main Game loop
    while True :

        # start with sending if we got first play from server
        if (flag):
            flag = 0
            ##############################################################
            ################## SEND BLOCK ################################
            ##############################################################
            

            # While loop to repeat the operation if it failed
            MOVE_SENT= False

            try :

                #
                data=client2.waitformov(1)
                print ("data is", data)
               # x = raw_input('send new move ? ')
                  # check the existence of the other player before sending any move

                result = client.send_mov(data)
                print ("data is", data)
               # x = raw_input('send new move ? ')
                #send move = send all messages

                if result == 0 :
                    print '[-] server did not received the move => server is not reachable'
                    # code to connect again to server
                else:
                    print '[+] Move sent'
                    MOVE_SENT = True


               
            except :
                print '[-] connrction closed'
                sleep(1)
                continue
        # SEND BLOCK

        flag = 1


        ##############################################################
        ################## Receive BLOCK #############################
        ##############################################################
       


        # While loop to repeat the operation if it failed

            # waiting for move from the other player
        mov = client.waitformov(0)
        print(mov)
        client2.send_mov(mov)

                # It's up now continue to send again

        ##############################################################
        ################## Receive BLOCK #############################
        ##############################################################

        ##############################################################
        ################## Receive BLOCK #############################
        ##############################################################

except Exception, e:
    print e

