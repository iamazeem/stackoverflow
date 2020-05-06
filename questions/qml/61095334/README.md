## Qt (C++): QJSEngine, global and script, what is causing the syntax error?

### Evaluat JavaScript Object using [QJSEngine](https://doc.qt.io/qt-5/qjsengine.html) and make it available with [QJSEngine::globalObject()](https://doc.qt.io/qt-5/qjsengine.html#globalObject)

Link: https://stackoverflow.com/questions/61095334/

### Prequisites

- Qt/QML (Tested with Qt 5.14.0)

### JSON Object:

```
{
    "db": "test",
    "host": "localhost",
    "usr": "root",
    "pass": "123456"
}
```

### Output

```
js: ---------------
js: db: test
js: host: localhost
js: usr: root
js: pass: 123456
js: ---------------
```
