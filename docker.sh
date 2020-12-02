docker run -d \
  --name docker-influxdb-grafana \
  -p 3003:3003 \
  -p 3004:8083 \
  -p 8086:8086 \
  -v /timeseries/influxdb:/var/lib/influxdb \
  -v /timeseries/grafana:/var/lib/grafana \
  philhawthorne/docker-influxdb-grafana:latest