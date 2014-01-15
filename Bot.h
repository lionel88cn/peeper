#ifndef BOT_H
#define BOT_H

#include <message.h>
#include <messagehandler.h>
#include <string>
#include <client.h>
#include "ConnListener.h"
#include "findWindowList.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "BuddyList.h"
using namespace std;
using namespace gloox;

//global variables. Obviously the best way is define a class for everything in the main()
//however for now using global variables is the way for sharing contents
//will change later
extern WindowList openedwindows;
extern WindowList buddyswindows;

//some function found on the web for converting int to string
#pragma comment(lib, "user32.lib")
inline string to_string(int _Val);

//**********Section gloox**********
//gloox is a xmpp library, most of the following functions are copied from its provided examples
//All I did is: modified handleMessage(), and added receiveMsg() and sendChecking()
ostream& operator<<(ostream& os, Message::MessageType type);
ostream& operator<<(ostream& os, const Message& stanza);
class Bot : public MessageHandler
{
public:
    Bot();
    ConnectionError receiveMsg();
    ~Bot();
    virtual void handleMessage( const Message& stanza, MessageSession* session = 0 );
    void sendChecking();
    void sendMessageToAll(string mymsg);
private:
    Client* client;
    ConnListener* connListener;
};

#endif // BOT_H
