#include <iostream>
#include "newShape.pb.h"

int main()
{
    // Serailization

    ::myProject::protobuf::NewShape newShape1;

    auto shape1 = newShape1.add_shape();
    auto polygon1 = shape1->add_polygon();
    polygon1->add_point(1);
    polygon1->add_point(2);

    auto shape2 = newShape1.add_shape();
    auto polygon2 = shape2->add_polygon();
    polygon2->add_point(3);
    polygon2->add_point(4);

    const auto serializedData = newShape1.SerializeAsString();

    std::cout << "Serialized Data Size: " << serializedData.size() << "\n\n";

    // Send/Store Serialized Data

    // Deserialization

    ::myProject::protobuf::NewShape newShape2;

    if ( !newShape2.ParseFromString( serializedData ) )
    {
        std::cerr << "Deserialization failed!\n";
        return -1;
    }

    std::cout << "Deserialized Data Size: " << newShape2.ByteSize() << "\n\n";

    std::cout << "NewShape [Shapes: " << newShape2.shape_size() << "]\n";

    for ( int i {0}; i < newShape2.shape_size(); ++i )
    {
        std::cout << " Shape # " << i << '\n';

        const auto& shape = newShape2.shape( i );
        for ( int j {0}; j < shape.polygon_size(); ++j )
        {
            std::cout << "  Polygon # " << j << '\n';

            const auto& polygon = shape.polygon( j );
            for ( int k {0}; k < polygon.point_size(); ++k )
            {
                const auto& point = polygon.point( k );
                std::cout << "   Point # " << k << ": " << point << '\n';
            }
        }
    }

    return 0;
}
