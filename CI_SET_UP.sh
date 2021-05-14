#!/bin/bash

apk add --update --no-cache python3 wget unzip py3-pip chromium python3-dev py-numpy-dev && ln -sf python3 /usr/bin/python
python -m ensurepip
pip3 install --no-cache --upgrade pip setuptools wheel
wget https://chromedriver.storage.googleapis.com/90.0.4430.24/chromedriver_linux64.zip
unzip chromedriver_linux64.zip
pip3 install selenium matplotlib

