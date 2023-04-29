# Base image with C compiler and libcurl installed
FROM ubuntu:latest
RUN apt-get update && apt-get install -y build-essential curl gcc libcurl4-gnutls-dev libmicrohttpd-dev

# Set the working directory to /app
WORKDIR /app

# Copy the bot.c file to the container
COPY bot.c .
COPY bot.h .

# Compile bot.c and create the bot executable
RUN gcc -o bot bot.c -lmicrohttpd -lcurl 

# Run the bot executable
CMD ["./bot"]