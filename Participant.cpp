#include "Participant.h"

void Participant::incrementTime()
{
    int sec = second.toInt();
    int min = minute.toInt();

    sec++;
    if (sec == 60)
    {
        sec = 0;
        min++;
    }

    second = QString::number(sec);
    minute = QString::number(min);
}

void Participant::resetTime()
{
    minute = "0";
    second = "0";
}

