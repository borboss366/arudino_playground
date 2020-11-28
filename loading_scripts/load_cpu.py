import random
import time 
import subprocess
import psutil
import socket

# gives a single float value

# import requests
from influxdb import InfluxDBClient
client = InfluxDBClient(host='192.168.31.76', port=8086)

for i in range(10000):
    value = psutil.cpu_percent()
    now = int(time.time())
    host = socket.gethostname()
    # command = "curl -X POST http://192.168.31.76:8086/write?db=mydb --data-binary cpu_load_short,host=server01,region=us-west value={value} {ts}".format(value=value, ts=now)
    data = "cpu_real,host={host} value={value} {ts}".format(value=value, ts=now, host=host)
    client.write_points([data], database='mydb', time_precision='s', protocol='line')
    print("written" + data)
