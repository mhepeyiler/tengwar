FROM ubuntu:22.04 as build

RUN apt-get update 
RUN apt-get -y install build-essential
RUN apt-get -y install gcc
RUN apt-get -y install gdb
RUN apt-get -y install cmake 
RUN apt-get -y install python3
RUN apt-get -y install python3-pip
RUN pip3 install conan

WORKDIR /tengwar

COPY . .

RUN conan profile detect --force 

RUN chmod +x bootstrap.sh

CMD ["bash", "bootstrap.sh"]