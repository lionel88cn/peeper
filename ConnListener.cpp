#include "ConnListener.h"

void ConnListener::onConnect()
{
    qDebug() << "ConnListener::onConnect()" << endl;
    ontls=1;
}

void ConnListener::onDisconnect(ConnectionError e)
{
    qDebug() << "ConnListener::onDisconnect() " << e << endl;
}

bool ConnListener::onTLSConnect(const CertInfo& info)
{
    qDebug() << "ConnListener::onTLSConnect()" << endl;
    return true;
}

void ConnListener::initFlag()
{
    ontls=0;
}

int ConnListener::checkFlag()
{
    return ontls;
}
