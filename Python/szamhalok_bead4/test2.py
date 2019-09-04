import hashlib, sys

m = hashlib.md5()
m.update("FeketeRetek".encode("utf8"))
m.update(" a rettenetes".encode("utf8"))
print("Digest: {}".format(m.digest()))
print("Digest in hex: 0x{}".format(m.hexdigest()))
print("Digest size: {}".format(m.digest_size))