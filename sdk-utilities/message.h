#ifndef MESSAGE_H
#define MESSAGE_H

#include "sdk-utilities_global.h"

#include <QByteArray>

// message is used to exchange infromation between client and server
struct SDKUTILITIESSHARED_EXPORT Message{
    enum class Type{
        INVALID_REQUEST,
        STATUS_REQUEST, // type for requesting list of radar and relay, no field data, send regularly
        RADAR_DELETE,   // type for requesting to delete radar, data: radar id
        RADAR_UPDATE,   // type for requesting to update radar, data: Radar
        RADAR_ADD,      // type for requesting to add radar, data: Radar
        RELAY_COMMAND,  // type for commanding relay to on, off, or reset
        DATA_RESULT,    // type for returning radar and relay status, data: list of radar and relay
    };
    Message(const Type type = Type::INVALID_REQUEST,
            const QByteArray& data = QByteArray(),
            int revision = -1):
        type(type),
        data(data),
        revision(revision)
    {}

    Type type;
    QByteArray data;
    int revision;
};

inline QDataStream& operator<<(QDataStream& out, const Message& message)
{
    out << static_cast<qint8>(message.type)
        << message.data
        << message.revision;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Message& message)
{
    qint8 type;
    in >> type
       >> message.data
       >> message.revision;

    message.type = static_cast<Message::Type>(type);

    return in;
}

#endif // MESSAGE_H
