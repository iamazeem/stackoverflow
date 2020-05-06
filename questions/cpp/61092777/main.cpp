#include <iostream>
#include "student.pb.h"

int main()
{
    // Serailization

    student::Student s1;
    s1.set_name("XYZ");
    s1.set_age(20);

    const auto serializedData = s1.SerializeAsString();

    // Send/Store Serialized Data

    // Deserialization

    student::Student s2;
    if ( !s2.ParseFromString( serializedData ) )
    {
        std::cerr << "Deserialzation failed!\n";
        return -1;
    }

    std::cout << "Name: " << s2.name() << '\n';
    std::cout << "Age : " << s2.age() << '\n';

    return 0;
}
