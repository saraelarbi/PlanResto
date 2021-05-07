#include "DuMessengerServer.h"
#include "DuMessengerSocket.h"
#include <QTextStream>
#include <QDebug>
namespace DuarteCorporation
{


DuMessengerServer::DuMessengerServer(QObject *parent)
    : QTcpServer(parent)
{

}
bool DuMessengerServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}
void DuMessengerServer::incomingConnection(qintptr handle)
{
    qDebug() << "Clien conneced with handle:" << handle;
    auto socket = new DuMessengerSocket(handle, this);
    mSockets << socket;

    for (auto i : mSockets){
        QTextStream T(i);
        T << "Server : connecter:" << handle;
        i->flush();
    }

    connect(socket, &DuMessengerSocket::DuReadyRead, [&](DuMessengerSocket *S)
    {
        qDebug() << "DuReadyRead";
        QTextStream T(S);
        auto text = T.readAll();

     for (auto i : mSockets) {
         QTextStream K(i);
         K << text;
         i->flush();

     }
    });
    connect(socket, &DuMessengerSocket::DuStateChanged,
            [&](DuMessengerSocket *S, int ST)
    {qDebug()<< "DuStateChanged with handle:"
                << S->socketDescriptor();
        if (ST == QTcpSocket::UnconnectedState){
            qDebug()<< "Unconnected state with handle:"
             << S->socketDescriptor();
        mSockets.removeOne(S);
        for (auto i : mSockets) {
            QTextStream K(i);
            K << "Server: El cliente"
              << S->socketDescriptor()
              << "Se ha desconnectado...";
              i->flush();
        }
    }
});
}
}
