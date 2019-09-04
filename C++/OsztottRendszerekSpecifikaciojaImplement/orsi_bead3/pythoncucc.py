from random import randrange
try:
    set
except NameError:
    from sets import Set as set
    
x = 20
y = 20

output = open("world.map", "w")

output.write( str(x) + " " + str(y) + "\n" )

for i in range(x):
    for j in range(y):
        output.write( str(randrange(0,12)) + " " )
    output.write("\n")


trader_count = 1000

output.write( str(trader_count) +  "\n")
   
for p in range(trader_count):
    for item in range(5):
        output.write(str(randrange(0,6)) + " ")
    output.write(str(randrange(1,5)) + "\n")

output.close()