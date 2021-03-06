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
                            QByteArray& data,
                            int revision)
    {
        Message message(messageType, data, revision);

        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << message;
        socket.write(byteArray);

    }
    inline Message readMessage(QDataStream& stream)
    {
        auto message = Message();

        stream.startTransaction();
        stream >> message;

        if (!stream.commitTransaction()){
            return Message();
        }
        return message;
    }
}
