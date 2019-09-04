import socket, sys, struct, zlib

netc_srv_ip = sys.argv[1]
netc_srv_port = int(sys.argv[2])
chsum_srv_ip = sys.argv[3]
chsum_srv_port = int(sys.argv[4])
file_id = sys.argv[5]
file_path = sys.argv[6]

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind( (netc_srv_ip, netc_srv_port) )

sock.listen(5)

connection, client_info = sock.accept()

msg = connection.recv(100)

f = open(file_path, "w")
f.write( str(msg) )
f.close()
sock.close()

checksum_bytes = hex(zlib.crc32(msg) % (1 << 32))
to_checksum = 'KI|' + file_id

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect( (chsum_srv_ip, chsum_srv_port) )
msg = to_checksum.encode("utf8")
sock.send(msg)
msg = sock.recv(100)
things = str(msg).split("|")
things[0] = things[0][2:]
things[1] = things[1][:-1]
print(things)
print(checksum_bytes)
print(sys.getsizeof(checksum_bytes))
if(checksum_bytes == things[1] and sys.getsizeof(checksum_bytes) == int(things[0])):
    print("CSUM OK")
else:
    print("CSUM CORRUPTED")
sock.close()

