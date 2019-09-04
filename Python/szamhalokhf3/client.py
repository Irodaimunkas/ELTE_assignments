import sys
import socket
import struct
import random
import time
import math

server_addr = sys.argv[1]
server_port = int(sys.argv[2])
lowerLimit = 1
upperLimit = 100
m = 0

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect( (server_addr, server_port) )

packer = struct.Struct('c i')
ops = ['>', '<']

L = lowerLimit
R = upperLimit

while(L <= R):
	if(L == R):
		break
	rand = random.randint(1,10) % len(ops)
	op = ops[rand]
	m = math.floor((L + R) / 2)
	msg = packer.pack(op.encode('utf-8'), m)
	print( "Sending: %c%i" % (op, m) )	
	sock.sendall( msg )

	msg = sock.recv(100)
	parsed_msg = packer.unpack( msg )
	print(parsed_msg[0], parsed_msg[1])
	if(parsed_msg[0] == b'V' or parsed_msg[0] == b'K'):
		break

	if(op == '<'): # T < A[m]
		if(parsed_msg[0] == b'I'):
			R = m - 1
		elif(parsed_msg[0] == b'N'):
			L = m
	elif(op == '>'): # T > A[m]
		if(parsed_msg[0] == b'I'):
			L = m + 1
		elif(parsed_msg[0] == b'N'):
			R = m
	
	time.sleep(random.randint(1,5))

if(parsed_msg[0] != b'V' and parsed_msg[0] != b'K'):
	msg = packer.pack('='.encode('utf-8'), m)
	print( "Sending: %c%i" % ('=', m) )	
	sock.sendall( msg )

	msg = sock.recv(100)
	parsed_msg = packer.unpack( msg )
	print(parsed_msg[0], parsed_msg[1])

sock.close()