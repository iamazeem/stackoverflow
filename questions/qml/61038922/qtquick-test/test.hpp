#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>
#include <QString>

class Test : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString get1_RetByValue_NonConstLocalString()
    {
        QString s { __func__ };
        return s;
    }

    Q_INVOKABLE const QString get2_RetByConstValue_ConstLocalString()
    {
        const QString s { __func__ };
        return s;
    }

    Q_INVOKABLE const QString get3_RetByConstValue_StaticString()
    {
        static QString s { __func__ };
        return s;
    }

    Q_INVOKABLE const QString& get4_RetByConstRef_LocalString()
    {
        QString s { __func__ };
        return s;
    }

    Q_INVOKABLE static const QString& get5_RetByStaticConstRef_StaticString()
    {
        static QString s { __func__ };
        return s;
    }
};

#endif // TEST_HPP
