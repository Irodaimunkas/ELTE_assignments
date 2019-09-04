import sys
import socket
import random
import struct
import time

server_addr = sys.argv[1]
server_port = int(sys.argv[2])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect( (server_addr, server_port) )

ops = ['+', '-', '*', '/', '%']

packer = struct.Struct('i i c')

for nrnd in range(10):
	oper1 = random.randint(1,100)
	oper2 = random.randint(1,100)
	op = ops[nrnd % len(ops)]

	msg = packer.pack(oper1, oper2, op)
	print( "MESSAGE: %d %c %d" % (oper1, op, oper2) )	
	sock.sendall( msg )

	msg = sock.recv(100)
	parsed_msg = packer.unpack( msg )
	print( "MESSAGE RECEIVED - RESULT: %d" % parsed_msg[0])
	time.sleep(2)
sock.close()


