#pragma once
#include <QString>

class Participant
{
public:
	Participant(const QString& name = "", int ini = 0, const QString& minute = "", const QString& second = "")
        : name(name), ini(ini), minute(minute), second(second)
    {

    }

    void incrementTime();
    void resetTime();

    QString name;
    int ini;
    QString minute;
    QString second;
};

