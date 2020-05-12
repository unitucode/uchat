#!/bin/sh

private_key="private_key.pem"
private_password=12345678

certificate="certificate.crt"
certificate_info="/C=NL/ST=Some-State/O=Lupo Corp./CN=Server"

openssl req -x509 -sha1 -newkey rsa:2048 -keyout "$private_key" -out "$certificate" -outform PEM -days 1825 -subj "$certificate_info" -passout pass:$private_password
