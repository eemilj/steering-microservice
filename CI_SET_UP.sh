#!/bin/bash

apk add --update --no-cache tesseract-ocr python3 wget unzip py3-pip chromium && ln -sf python3 /usr/bin/python
python -m ensurepip
pip3 install --no-cache --upgrade pip setuptools wheel && \
apk add --no-cache --virtual .build-deps gcc g++ zlib-dev make python3-dev py-numpy-dev jpeg-dev && \
    pip3 install matplotlib && \
    apk del .build-deps
wget https://chromedriver.storage.googleapis.com/90.0.4430.24/chromedriver_linux64.zip
unzip chromedriver_linux64.zip
pip3 install selenium

