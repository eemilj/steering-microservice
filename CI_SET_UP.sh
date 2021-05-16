#!/bin/bash

apk add --update --no-cache py-pip python3-dev libffi-dev openssl-dev gcc libc-dev rust cargo make

pip install docker-compose
docker-compose  --version