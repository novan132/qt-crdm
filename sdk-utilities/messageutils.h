#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#endif // MESSAGEUTILS_H

#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>

#include "message.h"

namespace MessageUtils {
    inline void sendMessage(QTcpSocket& socket,
                            Message::Type messageType,
                            QByteArray& data)
    {
        Message message(messageType, data);

        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << message;
        socket.write(message);

    }
    inline Message& readMessage(QDataStream& stream)
    {
        auto message = Message();

        stream.startTransaction();
        stream >> message;

        if (!stream.commitTransaction()){
            return;
        }
        return message;
    }
}
