#include "klient.h"
int Client::ostatnieId = 1;

Client::Client(const QString& name, const QString& surname)
    : name(name), surname(surname)
{
    id = QString::number(ostatnieId++);
}

Client::Client(const QString& name, const QString& surname, const QString& id)
    : name(name), surname(surname), id(id)
{
    bool ok;
    int idVal = id.toInt(&ok);
    if (ok && idVal >= ostatnieId) {
        ostatnieId = idVal + 1;
    }
}
QString Client::getName() const {
    return name;
}

QString Client::getSurname() const {
    return surname;
}

QString Client::getId() const {
    return id;
}
QString Client::getEmail() const{
    return email;
}
QString Client::getTel() const{
    return tel;
}

void Client::setName(const QString& newName) {
    name = newName;
}

void Client::setSurname(const QString& newSurname) {
    surname = newSurname;
}

void Client::setId(const QString& newId) {
    id = newId;
}
void Client::setTel(const QString &newTel){
    tel= newTel;
}
void Client::setEmail(const QString &newEmail){
    email=newEmail;
}
