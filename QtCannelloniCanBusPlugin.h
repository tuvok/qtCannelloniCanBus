#ifndef QTCANNELLONICANBUSPLUGIN_H_
#define QTCANNELLONICANBUSPLUGIN_H_

#include <CannelloniCanBackend.h>

#include <QtSerialBus/QCanBusFactory>
#include <QObject>
#include <QStringList>

#include <iostream>

class QtCannelloniCanBusPlugin : public QObject, public QCanBusFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactory)

public:
    QCanBusDevice *createDevice(const QString &interfaceName, QString *errorMessage) const override
    {
        Q_UNUSED(errorMessage);
        QStringList urls = interfaceName.split(QChar::Null);

        if (urls.size() != 2)
            return nullptr;

        std::cout << "URL1: " << urls[0].toStdString() << std::endl;
        std::cout << "URL2: " << urls[1].toStdString() << std::endl;

        auto device = new CannelloniCanBackend(urls[0], urls[1]);
        return device;
    }
};

#endif /* QTCANNELLONICANBUSPLUGIN_H_ */
