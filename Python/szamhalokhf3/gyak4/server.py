import sys
import socket
import struct
import select

server_addr = sys.argv[1]
server_port = int(sys.argv[2])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind( (server_addr, server_port) )

sock.listen(5)

ops = { '+': lambda x,y: x+y, 
	'-': lambda x,y: x-y,
	'*': lambda x,y: x*y,
	'/': lambda x,y: x/y,
	'%': lambda x,y: x%y}

packer = struct.Struct('i i c')

inputs = [ sock ]

try:
	while True:
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
				print("MESSAGE from client: %d %c %d" % (parsed_msg[0], parsed_msg[2], parsed_msg[1]))
				result = ops[parsed_msg[2]](parsed_msg[0], parsed_msg[1])
				msg = packer.pack(result, 0, 'R')
				s.sendall(msg)
				print("Result sent: %d" % result)
			
finally:
	sock.close()
