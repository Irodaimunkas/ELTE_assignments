import socket, sys, struct, select, zlib, time

netc_srv_ip = sys.argv[1]
netc_srv_port = int(sys.argv[2])
chsum_srv_ip = sys.argv[3]
chsum_srv_port = int(sys.argv[4])
file_id = sys.argv[5]
file_path = sys.argv[6]

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect( (netc_srv_ip, netc_srv_port) )

# hex(zlib.crc32(bytearray(test_string, 'utf8')) % (1 << 32))
# sys.getsizeof(object)

f = open(file_path, 'rb').read()

sock.send(f)
sock.close()

checksum_bytes = hex(zlib.crc32(f) % (1 << 32))

to_checksum = 'BE|' + str(file_id) + '|60|' + str(sys.getsizeof(checksum_bytes)) + '|' + str(checksum_bytes)
msg = to_checksum.encode('utf8')

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect( (chsum_srv_ip, chsum_srv_port) )
sock.send(msg)

msg = sock.recv(100)

print(msg)
time.sleep(1)

sock.close()