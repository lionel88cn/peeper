#ifndef CONNLISTENER_H
#define CONNLISTENER_H

#include <connectionlistener.h>
#include <QDebug>
#include <iostream>
using namespace std;
using namespace gloox;

class ConnListener : public ConnectionListener
{
public:
    int ontls;

    virtual void onConnect();
    virtual void onDisconnect(ConnectionError e);
    virtual bool onTLSConnect(const CertInfo& info);
    void initFlag();
    int checkFlag();
};

#endif // CONNLISTENER_H
