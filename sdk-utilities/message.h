#ifndef MESSAGE_H
#define MESSAGE_H

#include "sdk-utilities_global.h"

#include <QByteArray>

// message is used to exchange infromation between client and server
struct SDKUTILITIESSHARED_EXPORT Message{
    enum class Type{
        STATUS_REQUEST, // type for requesting list of radar and relay, no field data, send regularly
        RADAR_DELETE,   // type for requesting to delete radar, data: radar id
        RADAR_UPDATE,   // type for requesting to update radar, data: radar id
        RADAR_ADD,      // type for requesting to add radar, data: Radar
        RELAY_COMMAND,  // type for commanding relay to on, off, or reset
        DATA_RESULT,    // type for returning radar and relay status, data: list of radar and relay
    };
    Message(const Type type = Type::STATUS_REQUEST,
            const QByteArray& data = QByteArray(),
            int revision):
        type(type),
        data(data),
        revision(revision)
    {}
    int revision;
    Type type;
    QByteArray data;
};

#endif // MESSAGE_H
