
#pragma once

#include <QUrl>
#include <QByteArray>
#include <KIO/Global>
#include <KIO/ForwardingSlaveBase>
#include <QDir>



class WineYardsProtocol : public KIO::SlaveBase {
public:
    WineYardsProtocol(const QByteArray& pool_socket, const QByteArray& app_socket);
    virtual ~WineYardsProtocol() override;
    
    virtual void mimetype(const QUrl& url) override;
    virtual void open(const QUrl& url, QIODevice::OpenMode mode) override;
    virtual void get(const QUrl & url) override;
    virtual void listDir(const QUrl & url) override;
private:
    QString m_WineMethod;
    QDir m_ActionPath;
};
