## C++: Calling the setter and getter method based on the proto file

### Serialization and Deserialization using [Google's Protocol Buffers](https://developers.google.com/protocol-buffers)

Link: https://stackoverflow.com/questions/61092777/

### Prerequisites

- C++11 compilant compiler (at least)
- Protocol Buffers Compiler (`protoc`). Follow [Installation Instructions](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md) for C++.

You should be able to compile `student.proto` for C++ like this:
```
$ protoc --cpp_out=. student.proto
```

`student.pb.h` and `student.pb.cc` will be generated.

For convenience, the generated files are already included.

### Compile and Run

With `g++`:
```
$ g++ -std=c++11 student.pb.cc main.cpp -o student -lprotobuf
$ ./student
```

#### Output
```
Name: XYZ
Age : 20
```
