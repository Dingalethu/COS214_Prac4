#lightweight Linux base image
FROM ubuntu:latest

# Install the required tools 
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    gdb \
    valgrind

# Set the working directory inside the container
WORKDIR /app