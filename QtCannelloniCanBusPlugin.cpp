#include "CannelloniCanBackend.h"

#include <QCanBusFactory>
#include <QObject>
#include <QStringList>

#include <iostream>

class QtCannelloniCanBusPlugin : public QObject, public QCanBusFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactory)

public:
    QCanBusDevice* createDevice(const QString& interfaceName,
                                QString* errorMessage) const override
    {
        Q_UNUSED(errorMessage);
        Q_UNUSED(interfaceName);
        return new CannelloniCanBackend(49999, QHostAddress::LocalHost, 50000);
    }
};

#include "QtCannelloniCanBusPlugin.moc"
