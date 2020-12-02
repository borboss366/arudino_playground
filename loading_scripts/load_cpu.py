import random
import time 
import subprocess
import psutil
import socket
from influxdb import InfluxDBClient

client = InfluxDBClient(host='46.101.189.187', port=8086, database='sandbox')

for i in range(10000):
    value = psutil.cpu_percent()
    now = int(time.time())
    host = socket.gethostname()
    data = "cpu_real,host={host} value={value} {ts}".format(value=value, ts=now, host=host)
    client.write_points([data], time_precision='s', protocol='line')
    print("written" + data)
