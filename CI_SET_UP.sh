#!/bin/bash

apk add --update py-pip python3-dev libffi-dev openssl-dev gcc libc-dev rust cargo make
curl -L "https://github.com/docker/compose/releases/download/1.27.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
chmod +x /usr/local/bin/docker-compose
docker-compose --version