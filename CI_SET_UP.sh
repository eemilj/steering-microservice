#!/bin/bash

apk add --update py-pip python3-dev libffi-dev openssl-dev gcc libc-dev rust cargo make
curl -o /usr/local/bin/docker-compose -L "https://github.com/docker/compose/releases/download/1.27.4/docker-compose-$(uname -s)-$(uname -m)"
chmod +x /usr/local/bin/docker-compose
ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
chmod +x /usr/bin/docker-compose