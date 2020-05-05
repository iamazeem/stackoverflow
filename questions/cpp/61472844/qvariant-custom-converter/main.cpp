#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMetaType>

struct FQString final : QString
{
    using QString::operator=;

    static QString convert( const float f )
    {
        return QString::number( f );
    }
};

Q_DECLARE_METATYPE( FQString );

int main()
{
    QMetaType::registerConverter<float, FQString>( FQString::convert );

    const float f = 0.0001;
    const QVariant v( f );

    const QString s = v.value<FQString>();
    qDebug() << "Value:" << s;

    return 0;
}
