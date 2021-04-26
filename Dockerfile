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
    build-essential \
    libopencv-dev \
    lcov \
    htmldoc

ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && make install && make test && \
    cd .. && \
    lcov --directory . --capture --no-external --output-file coverage.info && \
    lcov --remove coverage.info '*.hpp' -o coverage.info && \
    lcov --list coverage.info && \
    genhtml coverage.info --output-directory coverage && \
    htmldoc --webpage $(find coverage/test/ -type f \( -iname \index-sort-f.html -o -iname \*gcov.html \)) --outfile  report.pdf && \
    cp -R build/ report.pdf /tmp

# Second stage for packaging the software into a software bundle:
FROM ubuntu:18.04
MAINTAINER Group-04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get dist-upgrade -y

RUN apt-get install -y --no-install-recommends \
    libopencv-core3.2 \
    libopencv-highgui3.2 \
    libopencv-imgproc3.2

WORKDIR /usr/bin
COPY --from=builder /tmp/build/SteeringMicroservice .
WORKDIR /opt
COPY --from=builder /tmp/report.pdf .
# This is the entrypoint when starting the Docker container; hence, this Docker image is automatically starting our software on its creation
ENTRYPOINT ["/usr/bin/SteeringMicroservice"]