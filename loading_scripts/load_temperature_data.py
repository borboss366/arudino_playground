
import argparse
import subprocess
import psutil
import socket
import random
import time 
import sys
import re

from influxdb import InfluxDBClient

ap = argparse.ArgumentParser()

# Add the arguments to the parser
ap.add_argument("-db", "--database", help="Influx database name")
ap.add_argument("-url", "--url", help="Host URL")
ap.add_argument("-p", "--port", help="Port")

args = ap.parse_args()

database = args.database if args.database is not None else "sandbox"
url = args.url if  args.url is not None else "localhost"
port = args.port if args.port is not None else 8086

client = InfluxDBClient(host=url, port=port)

def parse_measurement(name, line):
    regex = re.compile(f'{name}: (\d+(\.\d+)?)')
    match = regex.match(line)

    if match:
        return match.group(1)

    return None


def load_measurement(name, value):
    now = int(time.time())

    data = "{name} value={value} {ts}".format(value=value, ts=now, name=name)
    client.write_points([data], database='sandbox', time_precision='s', protocol='line')
    print("written " + data)

measurements = ['Moisture', 'Humidity', 'Temperature']

for line in sys.stdin:
    for measurement in measurements:
        value = parse_measurement(measurement, line)

        if  value:
            load_measurement(measurement, value)
