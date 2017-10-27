#ifndef MESSAGE_H
#define MESSAGE_H

#include "sdk-utilities_global.h"

#include <QByteArray>

struct Message{
    enum class Type{
        STATUS_REQUEST,
        UPDATE_REQUEST,
        DATA_RESULT
    };
    Message(const Type type = Type::STATUS_REQUEST,
            const QByteArray& data = QByteArray()):
        type(type),
        data(data)
    {}
    Type type;
    QByteArray data;
};

#endif // MESSAGE_H
