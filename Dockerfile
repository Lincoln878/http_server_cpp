FROM ubuntu:latest AS build

RUN apt-get update && \
    apt-get install -y build-essential cmake

WORKDIR /app

COPY . .
RUN cmake .
RUN make

CMD ["./http"]
