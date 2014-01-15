#include "Bot.h"

WindowList openedwindows;
WindowList buddyswindows;

inline string to_string(int _Val)
{
    // convert long long to string
    char _Buf[2 * _MAX_INT_DIG];
    sprintf(_Buf, "%d", _Val);
    return (string(_Buf));
}

ostream& operator<<(ostream& os, Message::MessageType type)
{
    switch (type)
    {
        case Message::Chat:
            os << "Chat";
            break;
        case Message::Error:
            os << "Error";
            break;
        case Message::Groupchat:
            os << "Groupchat";
            break;
        case Message::Headline:
            os << "Headline";
            break;
        case Message::Normal:
            os << "Normal";
            break;
        case Message::Invalid:
            os << "Invalid";
            break;
        default:
            os << "unknown type";
            break;
    }
    return os;
}

ostream& operator<<(ostream& os, const Message& stanza)
{
    os << "type:'" << stanza.subtype() <<  "' from:'" << stanza.from().full() << "' body:'" << stanza.body() << "'";
    return os;
}

Bot::Bot()
{
    JID jid("buddytestinghang@gmail.com");
    client = new Client( jid, "wochuhang" );
    connListener = new ConnListener();
    connListener->initFlag();
    client->registerMessageHandler( this );
    client->registerConnectionListener(connListener);
    if (client->connect(false))
    {
        ConnectionError ce = ConnNoError;
        while( (connListener->checkFlag())==0 )
        {
            ce = client->recv();
        }
    }
}

ConnectionError Bot::receiveMsg()
{
    ConnectionError ce = client->recv(100);
    return ce;
}

void Bot::sendChecking()
{
    string tmp=mybuddylist.head->buddyJID;
    JID buddyjid(tmp);
    Message checkmsg(Message::Chat,buddyjid,"C");
    client->send(checkmsg);
    BuddyNode* p=mybuddylist.head;
    while (p->next)
    {
        p=p->next;
        tmp=p->buddyJID;
        JID buddyjid(tmp);
        Message checkmsg(Message::Chat,buddyjid,"C");
        client->send(checkmsg);
    }
}

void Bot::sendMessageToAll(string mymsg)
{
    string tmp=mybuddylist.head->buddyJID;
    JID buddyjid(tmp);
    Message checkmsg(Message::Chat,buddyjid,mymsg);
    client->send(checkmsg);
    BuddyNode* p=mybuddylist.head;
    while (p->next)
    {
        p=p->next;
        tmp=p->buddyJID;
        JID buddyjid(tmp);
        Message checkmsg(Message::Chat,buddyjid,mymsg);
        client->send(checkmsg);
    }
}

Bot::~Bot()
{
    delete client;
    delete connListener;
}

void Bot::handleMessage( const Message& stanza, MessageSession* session )
{
    //cout << "Received message (function handleMessage): " << stanza << endl;
	qDebug()<<QString::fromStdString(stanza.body());
    int inMsgType=0;
    string inMsg=stanza.body();
    if ((inMsg.length()>0) && (stanza.subtype()!=2))
    {
        if (inMsg[0]=='C')
        {
            inMsgType=1;
        }
        if (inMsg[0]=='T')
        {
            inMsgType=2;
        }
        if (inMsg[0]=='R')
        {
            inMsgType=3;
        }
    }
    if (inMsgType==1)
    {
        //openedwindows.initialize();
        //MyFunc();
        cout<<"win_num = "<<openedwindows.win_num<<endl;
        for (int i=0;i<openedwindows.win_num;i++)
        {
            Message newmsg(Message::Chat,stanza.from(),'T'+to_string(i)+": "+openedwindows.content[i]);
            cout<<"Message sent: "<<'T'+to_string(i)+": "+openedwindows.content[i]<<endl;
            client->send(newmsg);
        }
        Message msg(Message::Chat,stanza.from(),"R");
        client->send(msg);
    }
    if (inMsgType==2)
    {
        int inNum=inMsg[1]-'0';
        cout<<"Buddy is telling me something with inNum = "<<inNum<<endl;
        int buddyid=mybuddylist.inList(stanza.from().bare());
        cout<<"Which buddy is this? "<<buddyid<<endl;
        buddyswindows.addwindow_ind(inMsg,inNum);
        mybuddylist.addWindow_BuddyID(buddyid,inMsg,inNum);
    }
    if (inMsgType==3)
    {
        string uishow;
        uishow=uishow+"----------\n";
        if (mybuddylist.head!=mybuddylist.rear)
        {
            BuddyNode* p=mybuddylist.head;
            while (1)
            {
                uishow=uishow+(p->buddyJID)+'\n';
                for (int i=0;i<p->onebuddywindowlist.win_num;i++)
                {
                    uishow=uishow+(p->onebuddywindowlist.content[i])+'\n';
                }
                if (!p->next)
                {
                    break;
                }
                else
                {
                    p=p->next;
                }
                uishow=uishow+"----------\n";
            }
        }
        uishow=uishow+"----------\n";
        const char *uishowchar = uishow.c_str();
    }
}

