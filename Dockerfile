# Use an official image as a parent image
FROM ubuntu:20.04

# Set the working directory
WORKDIR /app

# Install necessary libraries and tools
RUN apt-get update && apt-get install -y gcc libcsfml-dev make

# Copy your source code to the container
COPY . .

# Compile your C project
RUN make

# Set the entry point for your application
CMD ["./bin/engine.out"]
