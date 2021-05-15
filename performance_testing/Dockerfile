##################################################
# Section 1: Build the application
FROM ubuntu:18.04 as builder
MAINTAINER Group-04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get dist-upgrade -y && \
    apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    wget \
    python3 \
    gnupg2 \
    python3-pip && \
    pip3 install matplotlib && \
    pip3 install pandas && \
    python3 -m pip install selenium

RUN apt-get update && \
    apt-get upgrade && \
    # https://medium.com/dot-debug/running-chrome-in-a-docker-container-a55e7f4da4a8
    wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add \
    && echo "deb http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google.list && \
    apt-get update && \
    apt-get -y install google-chrome-stable && \


#COPY  /tmp/report.pdf .
# This is the entrypoint when starting the Docker container; hence, this Docker image is automatically starting our software on its creation
ENTRYPOINT ["testSelenium.py"]