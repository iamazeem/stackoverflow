#include <QCoreApplication>
#include <QJSEngine>
#include <QJSValue>
#include <QDebug>

int main( int argc, char** argv )
{
    QCoreApplication app{ argc, argv };

    const auto raw_config =
    R"json((
    {
        "db": "test",
        "host": "localhost",
        "usr": "root",
        "pass": "123456"
    }
    ))json";

    QJSEngine engine;
    engine.installExtensions( QJSEngine::ConsoleExtension );

    const auto json_config = engine.evaluate( raw_config );
    if ( json_config.isError() )
    {
        qDebug() << "Uncaught exception at line"
                 << json_config.property("lineNumber").toInt()
                 << ":" << json_config.toString();
        return -1;
    }

    engine.globalObject().setProperty( "db", json_config );

    const auto test_script =
    R"javascript((
    function test() {
        try{
            console.info("---------------");

            if ( db === undefined ) {
                console.info("db is undefined");
                return;
            }
            else if ( typeof db === "object" ) {
                for( k in db ) {
                    console.info( k + ": " + db[k] );
                }
            }
            console.info("---------------");
        } catch( e ) {
            console.warn( "test() WARNING: " + e );
        }
    }
    ))javascript";

    auto test_func = engine.evaluate( test_script );
    if ( test_func.isError() )
    {
        qDebug() << "Uncaught exception at line"
                 << test_func.property("lineNumber").toInt()
                 << ":" << test_func.toString();
        return -1;
    }

    const auto result = test_func.call();
    if ( result.isError() )
    {
        qDebug() << "Uncaught exception at line"
                 << result.property("lineNumber").toInt()
                 << ":" << result.toString();
        return -1;
    }

    return 0;
}
