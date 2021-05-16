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
    apt-transport-https \
    software-properties-common \
    curl \
    wget \
    git \
    build-essential \
    python3 \
    gnupg2 \
    unzip \
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
    mkdir selenium-drivers && \
    wget https://chromedriver.storage.googleapis.com/90.0.4430.24/chromedriver_linux64.zip && \
    unzip chromedriver_linux64.zip -d selenium-drivers && \
    chmod 0755 /selenium-drivers/chromedriver && \
    # https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-18-04
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | apt-key add - && \
    add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable" && \
    apt update && \
    apt install -y docker-ce && \
    pwd && \
    mkdir recordings

ADD scripts/* /
RUN chmod +x *.sh && \
    mkdir testCSV && \
    mkdir csv_files
# This is the entrypoint when starting the Docker container; hence, this Docker image is automatically starting our software on its creation
CMD ["/runScripts.sh"]
ENTRYPOINT ["bash"]