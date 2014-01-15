#include "WindowList.h"

WindowList::WindowList()
{
    win_num=0;
    content=new string[10];
}

void WindowList::initialize()
{
    win_num=0;
}

void WindowList::addwindow(string newwindow)
{
    content[win_num]=newwindow;
    win_num++;
    if (win_num==10)
    {
        win_num=0;
    }
}

void WindowList::addwindow_ind(string newwindow,int ind)
{
    if ((ind<10)&&(ind>=0))
    {
        content[ind]=newwindow;
        if ((ind+1)>win_num)
        {
            win_num=(ind+1);
        }
    }
}

void WindowList::copy(WindowList* origin)
{
    win_num=origin->win_num;
    if (win_num>0)
    {
        for (int i=0;i<win_num;i++)
        {
            content[i]=origin->content[i];
        }
    }
}

bool WindowList::compare(WindowList* p,int* whichchanges)
{
    if (win_num==0)
    {
        return true;
    }
    else
    {
        for (int i=0;i<10;i++)
        {
            whichchanges[i]=0;
        }
        bool changeflag=false;
        for (int i=0;i<win_num;i++)
        {
            if (!(content[i]==p->content[i]))
            {
                changeflag=true;
                whichchanges[i]=1;
            }
        }
        if (changeflag)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
