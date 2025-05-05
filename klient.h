#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client {
public:
    Client(const QString& name, const QString& surname);

    Client(const QString& name, const QString& surname, const QString& id);


    QString getName() const;
    QString getSurname() const;
    QString getId() const;

    void setName(const QString& newName);
    void setSurname(const QString& newSurname);
    void setId(const QString& newId);

private:
    QString name;
    QString surname;
    QString id;
    static int ostatnieId; // unikalny licznik ID
};

#endif // CLIENT_H
