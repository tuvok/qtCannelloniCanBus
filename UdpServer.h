#ifndef UDPSERVER_H_
#define UDPSERVER_H_

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Code for this class was initially taken from boost tutorial:
// http://www.boost.org/doc/libs/1_35_0/doc/html/boost_asio/tutorial/tutdaytime6/src.html

#include <array>
#include <ctime>
#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UdpServer
{
public:
    UdpServer(boost::asio::io_service& io_service,
            std::function<void(std::array<uint8_t, 1500>, std::size_t)> handlePacket_,
            unsigned int port) :
                socket_(io_service, udp::endpoint(udp::v4(), port))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&UdpServer::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error, std::size_t len)
    {
        if (error && error != boost::asio::error::message_size)
            return;

        handlePacket(recv_buffer_, len);

        start_receive();
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<uint8_t, 1500> recv_buffer_;
    std::function<void(std::array<uint8_t, 1500>, std::size_t)> handlePacket;
};


#endif /* UDPSERVER_H_ */
