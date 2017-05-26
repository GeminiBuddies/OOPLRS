#ifndef GLOBAL_CONF
#define GLOBAL_CONF 1

#include <QtCore>
#include <QtNetwork>

typedef char *byteseq;

class _Conn;
typedef const _Conn *Conn;

class _Conn {
    friend QString GetName(Conn);
private :

};

inline QString GetName(Conn c) {

}

#endif
