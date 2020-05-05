#include <QStringList>
#include <QDebug>
#include <QDir>
#include <cstdlib>

int main()
{
    const QString     root { "C:/Test" };
    const QStringList dirs { "A", "B" };

    QDir rootDir { root };
    qDebug() << "Root Path:" << rootDir.absolutePath();
    qDebug() << "Root List:" << rootDir.entryList( QDir::Dirs ) << '\n';

    for ( const auto& dir : dirs  )
    {
        if ( rootDir.cd( dir ) )
        {
            qDebug() << "Dir Path:" << rootDir.absolutePath();
            qDebug() << "Dir List:" << rootDir.entryList( QDir::Files ) << '\n';
        }

        rootDir.cdUp();
        qDebug() << "cding...";
        qDebug() << "Dir Path:" << rootDir.absolutePath() << '\n';
    }

    return EXIT_SUCCESS;
}
