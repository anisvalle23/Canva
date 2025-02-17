#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QDataStream>

struct Usuario {
    QString username;
    QString password;
    QString role;
};

// Operadores para serializar y deserializar
inline QDataStream& operator<<(QDataStream& out, const Usuario& usuario) {
    out << usuario.username << usuario.password << usuario.role;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Usuario& usuario) {
    in >> usuario.username >> usuario.password >> usuario.role;
    return in;
}

#endif // USUARIO_H
