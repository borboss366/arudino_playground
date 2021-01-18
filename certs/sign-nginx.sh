######################
# Create CA-signed certs
######################

NAME=nginx # Use your own domain name

# Create a certificate-signing request
sudo openssl req -new -key /etc/ssl/private/nginx.pem -out $NAME.csr

# Create a config file for the extensions
>$NAME.ext cat <<-EOF
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName = @alt_names
[alt_names]
DNS.1 = localhost
IP.1 = 192.168.31.76
EOF
# Create the signed certificate
sudo openssl x509 -req -in $NAME.csr -CA /etc/ssl/certs/arduino-playground.pem -CAkey /etc/ssl/private/arduino.key -CAcreateserial -out $NAME.crt -days 825 -sha256 -extfile $NAME.ext
sudo cp $NAME.crt /etc/ssl/certs/nginx-selfsigned-cert.pem
sudo systemctl restart nginx