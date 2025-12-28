#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "devicemanager.h"
#include "devicesmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DeviceManager manager;
    DevicesModel devicesModel(&manager);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("deviceManager", &manager);
    engine.rootContext()->setContextProperty("devicesModel", &devicesModel);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
