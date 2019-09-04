import socket, sys, struct, select, time

ip = sys.argv[1]
port = int(sys.argv[2])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = (ip, port)

sock.bind(server_address)

sock.listen(5)

myInputs = []

clients = [ sock ]

readable, _, _ = select.select(clients, [], [])

running = True
oneSec = False

try:
    while (running):
        try:
            readable, _, _ = select.select(clients, [], [])
            for s in readable:
                if(s is sock):
                    connection, client_info = sock.accept()
                    print('New client from %s:%d' % client_info)
                    clients.append(connection)
                else:
                    msg = s.recv(100)
                    if not msg:
                        s.close()
                        print('Client has closed the connection')
                        clients.remove(s)
                        continue
                    myInput = str(msg).split('|')
                    myInput[0] = myInput[0][2:]
                    myInput[-1] = myInput[-1][:-1]

                    print('Clien message: ' + str(msg))
                    print(myInput[0])
                    if(myInput[0] == "BE"):
                        myInputs.append(myInput)
                        myInputs[-1][2] = int(myInputs[-1][2])
                        msg = 'OK'.encode('utf8')
                        print('Sending: OK - to %s:%d' % client_info)

                    elif(myInput[0] == "KI"):
                        l = False
                        for i in range(len(myInputs)):
                            print(myInputs[i][1] + " " + myInput[1])
                            if(myInputs[i][1] == myInput[1]):
                                msg = (myInputs[i][3] + '|' + myInputs[i][4]).encode('utf8')
                                print('Sending %s to %s:%d' % (myInputs[i][3] + '|' + myInputs[i][4], client_info[0], client_info[1]) )
                                l = True
                        if(l == False):
                            msg = '0|'.encode('utf8')
                            print('Sending 0| to %s:%d' % client_info)
                    s.send(msg)
            time.sleep(1)
            for i in range(len(myInputs)):
                myInputs[i][2] = myInputs[i][2] - 1
                if(myInputs[i][2] <= 0):
                    myInputs.pop(i)
        except KeyboardInterrupt:
            running = False
finally:
	sock.close()