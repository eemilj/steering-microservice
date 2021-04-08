##################################################
# Section 1: Build the application
FROM ubuntu:18.04 as builder
MAINTAINER Christian Berger christian.berger@gu.se
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get dist-upgrade -y
RUN apt-get install -y --no-install-recommends \
    cmake \
    build-essential \
    lcov \
    htmldoc

ADD src/ /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make test &&\
    ./helloworld && \
    cd .. && \
    lcov --directory . --capture --no-external --output-file coverage.info && \
    lcov --remove coverage.info '*.hpp' -o coverage.info && \
    lcov --list coverage.info && \
    genhtml coverage.info --output-directory coverage && \
    htmldoc --webpage $(find coverage/sources/ -type f \( -iname \index-sort-f.html -o -iname \*gcov.html \)) --outfile  report.pdf && \
    cp -R build/helloworld report.pdf /tmp

##################################################
# Section 2: Bundle the application.
FROM ubuntu:18.04
MAINTAINER Christian Berger christian.berger@gu.se
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get dist-upgrade -y

WORKDIR /opt
COPY --from=builder /tmp .
ENTRYPOINT ["/opt/helloworld"]