#ifndef DOCXSHARED_H
#define DOCXSHARED_H

#include <QDomElement>
#include <QByteArray>
#include <QImage>
#include <QException>

namespace DocxUtils
{

QDomElement addOrAssignElement(QDomDocument *dom, QDomElement *parent, const QString &eleName, bool addToFirst = false);

QByteArray getFileHash(const QString &fileName);

QByteArray imageHash(const QImage &img);

QByteArray byteHash(const QByteArray &bytes);

class Parented
{
public:
    Parented();
    Parented* part();

    virtual ~Parented();

private:

};

class InvalidSpanError : public QException
{
public:
    InvalidSpanError(const QString &errorStr);
    void raise() const;
    QException *clone() const;

private:
    QString m_error;
};
}

#endif // SHARED_H
