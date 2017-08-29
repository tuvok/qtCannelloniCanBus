#include "CannelloniCanBackend.h"

#include "UdpServer.h"

#include "cannelloni/parser.h"

#include <QVector>

CannelloniCanBackend::CannelloniCanBackend(QUrl local_, QUrl remote_)
    : local(local_), remote(remote_)
{
}

CannelloniCanBackend::~CannelloniCanBackend()
{
}

bool CannelloniCanBackend::writeFrame(const QCanBusFrame& frame)
{
    return true; // FIXME: implement
}

QString
CannelloniCanBackend::interpretErrorFrame(const QCanBusFrame& errorFrame)
{
    return "Error frame received";
}

bool CannelloniCanBackend::open()
{
    if (t.joinable())
        return false;

    t = std::thread([this]() {
        try
        {
            auto handler = [this](std::array<uint8_t, 1500> buffer,
                                  std::size_t len) {
                handlePacket(buffer, len);
            };

            UdpServer udps(io_service, handler, local.port());
            io_service.run();
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    });

    return true;
}

void CannelloniCanBackend::close()
{
    if (!io_service.stopped())
        io_service.stop();

    t.join();
}

void CannelloniCanBackend::handlePacket(std::array<uint8_t, 1500> buffer,
                                        std::size_t len)
{
    auto allocator = []() {
        return new canfd_frame; // FIXME: preallocate some buffer for frames
    };

    QVector<QCanBusFrame> newFrames;
    auto receiver = [&](canfd_frame* frame, bool success) {
        QCanBusFrame f;
        if (frame->can_id & CAN_ERR_FLAG)
            f.setFrameType(QCanBusFrame::ErrorFrame);
        else if (frame->can_id & CAN_RTR_FLAG)
            f.setFrameType(QCanBusFrame::RemoteRequestFrame);

        if (frame->can_id & CAN_EFF_FLAG)
            f.setExtendedFrameFormat(true);
        else
            f.setExtendedFrameFormat(false);

        f.setFrameId(frame->can_id);
        f.setFlexibleDataRateFormat(true);

        QByteArray a;
        a.append(reinterpret_cast<char*>(frame->data), frame->len);
        f.setPayload(a);

        newFrames.push_back(f);
        delete frame;
    };

    parseFrames(len, buffer.data(), allocator, receiver);
    enqueueReceivedFrames(newFrames);
}
