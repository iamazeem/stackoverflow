#include <iostream>
#include <fstream>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

int main()
{
    using namespace rapidjson;

    std::ifstream ifs { R"(test.json)" };
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        return EXIT_FAILURE;
    }

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );

    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    if ( doc.HasParseError() )
    {
        std::cout << "Error  : " << doc.GetParseError()  << '\n'
                  << "Offset : " << doc.GetErrorOffset() << '\n';
        return EXIT_FAILURE;
    }

    const std::string jsonStr { buffer.GetString() };

    std::cout << jsonStr << '\n';

    doc[ "ip" ] = "127.0.0.1";

    std::ofstream ofs { R"(C:\Test\NewTest.json)" };
    if ( !ofs.is_open() )
    {
        std::cerr << "Could not open file for writing!\n";
        return EXIT_FAILURE;
    }

    OStreamWrapper osw { ofs };
    Writer<OStreamWrapper> writer2 { osw };
    doc.Accept( writer2 );

    return EXIT_SUCCESS;
}