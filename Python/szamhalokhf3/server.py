import sys
import socket
import struct
import select
import random

server_addr = sys.argv[1]
server_port = int(sys.argv[2])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind( (server_addr, server_port) )

sock.listen(5)

packer = struct.Struct('c i')

inputs = [ sock ]

randNum = 0
finalCount = 0
gameEnded = False

try:
	while True:
		if(randNum == 0):
			randNum = random.randint(1,100)
			print("Number is: %i" % randNum)

		if(finalCount == 1):
			gameEnded = False

		readables, _, _ = select.select( inputs, [], [] )
		
		for s in readables:
			if s is sock:
				connection, client_info = sock.accept()
				print("Client connected from %s:%d" % client_info )
				inputs.append(connection)
			else:
				msg = s.recv(100)
				if not msg:
					s.close()
					print("Client has closed the connection")
					inputs.remove(s)
					continue

				parsed_msg = packer.unpack(msg)
				print(parsed_msg[0], parsed_msg[1])
				if(gameEnded == False):
					if(parsed_msg[0] == b'<'):
						if(parsed_msg[1] > randNum):
							msg = packer.pack('I'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('I', 10))
						elif(parsed_msg[1] <= randNum):
							msg = packer.pack('N'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('N', 10))
					elif(parsed_msg[0] == b'>'):
						if(parsed_msg[1] >= randNum):
							msg = packer.pack('N'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('N', 10))
						elif(parsed_msg[1] < randNum):
							msg = packer.pack('I'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('I', 10))
					else:
						if(parsed_msg[1] == randNum):
							finalCount = len(inputs) - 1
							msg = packer.pack('Y'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('Y', 10))
							gameEnded = True
							randNum = random.randint(1,100)
							print("Number is: %i" % randNum)
						else:
							msg = packer.pack('K'.encode('utf-8'), 10)
							print("Sending: %c%i" % ('K', 10))
				else:
					msg = packer.pack('V'.encode('utf-8'), 10)
					print("Sending: %c%i" % ('V', 10))
					finalCount = finalCount - 1
				s.sendall(msg)
			
finally:
	sock.close()