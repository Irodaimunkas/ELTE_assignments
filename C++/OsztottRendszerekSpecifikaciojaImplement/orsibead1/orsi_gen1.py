from random import randrange
try:
    set
except NameError:
    from sets import Set as set
#python2/3 magic for imports 

x = randrange(1,21)
y = randrange(1,21)

output = open("world.map", "w")

output.write( str(x) + " " + str(y) + "\n" )

for i in range(x):
    for j in range(y):
        output.write( str(randrange(0,11)) + " " )
    output.write("\n")


civ_count = min(x,y)
civ_range = min(randrange(min(x,y)),4)

output.write( str(civ_count) + " " + str(civ_range) + "\n")

pos = set()

while len(pos) < civ_count:
    pos_x = randrange(1,x+1)
    pos_y = randrange(1,y+1)
    pos.add( (pos_x,pos_y) )
    
for p in pos:
    output.write(str(p[0]) + " " + str(p[1]) + "\n")

output.close()
