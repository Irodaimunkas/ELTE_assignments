import csv
import sys
import json
import subprocess
import platform
import datetime

input = sys.argv[1]
urls = []
os = platform.system()
date = datetime.datetime.today().strftime('%Y%m%d')

pingOut = {
    "date": date,
    "system": os,
    "pings": [],
}

tracerouteOut = {
    "date": date,
    "system": os,
    "traces": [],
}

with open(input) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    urls1 = []
    urls2 = []
    
    for row in list(csv_reader):
        if(line_count < 10):
            urls1.append(row[1])
            line_count += 1

    csv_file.seek(0)
    line_count = 0

    for row in reversed(list(csv_reader)):
        if(line_count < 10):
            urls2.append(row[1])
            line_count += 1

    urls = urls1 + urls2

print("Processing...")

for row in urls:
    ping = subprocess.Popen(['ping', '-n', '10', row], stdout=subprocess.PIPE)

    pingOut["pings"].append({
        "target": row,
        "output": str(ping.communicate()[0])
    })

    ping.stdout.close()

    if(os == "Windows"):
        traceroute = subprocess.Popen(['tracert', '-h', '30', row], stdout=subprocess.PIPE)
    else:
        traceroute = subprocess.Popen(['traceroute', '-h', '30', row], stdout=subprocess.PIPE)

    tracerouteOut["traces"].append({
        "target": row,
        "output":str(traceroute.communicate()[0])
    })

    traceroute.stdout.close()

    print(row)

with open("ping.json", "w") as write_file:
    json.dump(pingOut, write_file)

with open("traceroute.json", "w") as write_file:
    json.dump(tracerouteOut, write_file)