## C++: How to get information from your ProtoBuf in C++?

### Serialization and Deserialization using [Google's Protocol Buffers](https://developers.google.com/protocol-buffers)

Link: https://stackoverflow.com/questions/61039095/

### Prerequisites

- C++11 compilant compiler (at least)
- Protocol Buffers Compiler (`protoc`). Follow [Installation Instructions](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md) for C++.

You should be able to compile `newShape.proto` for C++ like this:
```
$ protoc --cpp_out=. newShape.proto
```

`newShape.pb.h` and `newShape.pb.cc` will be generated.

For convenience, the generated files are already included.

### Compile and Run

With `g++`:
```
$ g++ -std=c++11 newShape.pb.cc main.cpp -o newShape -lprotobuf
$ ./newShape
```

#### Output
```
Serialized Data Size: 16

Deserialized Data Size: 16

NewShape [Shapes: 2]
 Shape # 0
  Polygon # 0
   Point # 0: 1
   Point # 1: 2
 Shape # 1
  Polygon # 0
   Point # 0: 3
   Point # 1: 4
```
