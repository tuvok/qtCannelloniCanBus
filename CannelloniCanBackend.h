#ifndef CANNELLONICANBACKEND_H_
#define CANNELLONICANBACKEND_H_

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QUrl>
#include <QVector>

#include <boost/asio/io_service.hpp>

#include <thread>

class CannelloniCanBackend : public QCanBusDevice
{
    Q_OBJECT
public:
    CannelloniCanBackend(QUrl local_, QUrl remote_);
    virtual ~CannelloniCanBackend();

    virtual bool writeFrame(const QCanBusFrame& frame);
    virtual QString interpretErrorFrame(const QCanBusFrame& errorFrame);

protected:
    virtual bool open();
    virtual void close();

private:
    QUrl local;
    QUrl remote;
    boost::asio::io_service io_service;
    std::thread t;

    void handlePacket(std::array<uint8_t, 1500> buffer, std::size_t len);
};

#endif /* CANNELLONICANBACKEND_H_ */
