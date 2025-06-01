# A Learning project to learn development in C++

## Main goals
- Build a working web server that can process get requests
- Allow concurrent requests

## Implementation
Used libraries like `sys/socket.h` and `thread` to allow assign threads and process requests concurrently.

## How to use
Clone this repository with
```
git clone https://github.com/Lincoln878/http_server_cpp.git
```

Use Docker to build the container
```
docker compose up --build
```

After running the container, send a request to `0.0.0.0:8080`, `127.0.0.1:8080`, or `localhost:8080` to get a response from the server.