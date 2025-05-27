#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client {
public:
    Client(const QString& name, const QString& surname, const QString& email, const QString& tel);

    Client(const QString& name, const QString& surname, const QString& id, const QString& email, const QString& tel);
    Client() = default;

    QString getName() const;
    QString getSurname() const;
    QString getId() const;
    QString getEmail() const;
    QString getTel() const;

    void setName(const QString& newName);
    void setSurname(const QString& newSurname);
    void setId(const QString& newId);
    void setEmail(const QString& newEmail);
    void setTel(const QString& newTel);

private:
    QString name;
    QString surname;
    QString id;
    QString email;
    QString tel;
    static int ostatnieId;
};

#endif // CLIENT_H
