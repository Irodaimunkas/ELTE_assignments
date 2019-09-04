import sys
import json

input = sys.argv[1]
eventIt = 1
with open(input) as json_file:
    data = json.load(json_file)
    links_map = data["links"]
    started = [False] * len(data["simulation"]["demands"])
    startedCnt = 0

    for i in range(1, data["simulation"]["duration"] + 1):
        startedCnt = 0
        for currData in data["simulation"]["demands"]:
            linkNum = 0
            circNum = 0
            if( i == currData["start-time"] ):
                #############################################
                print(links_map)
                circGood = True

                while(  
                        currData["end-points"][0] != data["possible-circuits"][circNum][0] and 
                        currData["end-points"][1] != data["possible-circuits"][circNum][-1]
                    ):
                    circNum += 1

                for k in range(1, len(data["possible-circuits"][circNum])):
                    while(
                        data["possible-circuits"][circNum][k-1] not in links_map[linkNum]["points"] and
                        data["possible-circuits"][circNum][k] not in links_map[linkNum]["points"]
                    ):
                        linkNum += 1
                    
                    if( links_map[linkNum]["capacity"] - currData["demand"] >= 0 and circGood):
                        circGood = True
                    else:
                        circGood = False
                
                if(circGood):
                    linkNum = 0
                    while(
                        data["possible-circuits"][circNum][k-1] not in links_map[linkNum]["points"] and
                        data["possible-circuits"][circNum][k] not in links_map[linkNum]["points"]
                    ):
                        linkNum += 1

                    for k in range(0, len(data["possible-circuits"][circNum])):
                        links_map[linkNum]["capacity"] = links_map[linkNum]["capacity"] - currData["demand"]
                    
                    print("%i. igény foglalás: %s<->%s st:%i - sikeres" % (eventIt, currData["end-points"][0], currData["end-points"][1], i))
                    eventIt += 1
                    started[startedCnt] = True
                else:
                    print("%i. igény foglalás: %s<->%s st:%i - sikertelen" % (eventIt, currData["end-points"][0], currData["end-points"][1], i))
                    eventIt += 1


            elif( i == currData["end-time"] ):
                #############################################
                print(links_map)
                if( started[startedCnt] == True ):
                    while(  
                            currData["end-points"][0] != data["possible-circuits"][circNum][0] and 
                            currData["end-points"][1] != data["possible-circuits"][circNum][-1]
                        ):
                        circNum += 1

                    for k in range(1, len(data["possible-circuits"][circNum])):
                        
                        while(
                            data["possible-circuits"][circNum][k-1] not in links_map[linkNum]["points"] and
                            data["possible-circuits"][circNum][k] not in links_map[linkNum]["points"]
                        ):
                            linkNum += 1
                    
                    for k in range(0, len(data["possible-circuits"][circNum])):
                        links_map[linkNum]["capacity"] = links_map[linkNum]["capacity"] + currData["demand"]
                    
                    print("%i. igény felszabadítás: %s<->%s st:%i" % (eventIt, currData["end-points"][0], currData["end-points"][1], i))
                    eventIt += 1
                    started[startedCnt] = False
            startedCnt += 1         
