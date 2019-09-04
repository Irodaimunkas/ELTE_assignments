import binascii
import zlib
import sys

test_string = "FeketeRetek a rettenetes"

# print("Input: {}".format(test_string))
f = open("test.txt", "rb").read()
print(f)
print(hex(binascii.crc32(f) % (1 << 32)))
print(hex(zlib.crc32(f) % (1 << 32)))
print( sys.getsizeof(hex(zlib.crc32(f) % (1 << 32)) ))
