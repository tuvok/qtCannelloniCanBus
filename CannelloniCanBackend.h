#ifndef CANNELLONICANBACKEND_H_
#define CANNELLONICANBACKEND_H_

#include <QCanBusDevice>
#include <QUdpSocket>

class CannelloniCanBackend : public QCanBusDevice
{
    Q_OBJECT
public:
    CannelloniCanBackend(quint16 localPort, const QHostAddress& remoteAddr,
                         quint16 remotePort);

    bool writeFrame(const QCanBusFrame& frame) override;
    QString interpretErrorFrame(const QCanBusFrame& errorFrame) override;

protected:
    bool open() override;
    void close() override;
    void timerEvent(QTimerEvent*) override;

private:
    quint16 localPort_;
    QHostAddress remoteAddr_;
    quint16 remotePort_;
    QUdpSocket sock_;
    int timerId_;
    void handlePacket(const QByteArray& data);

private slots:
    void dataAvailable();
    void outQueueTimer();
};

#endif /* CANNELLONICANBACKEND_H_ */
