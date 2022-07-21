
#include "kio_wineyards.h"
#include "kio_wineyards_debug.h"
#include <KIO/SlaveBase>
#include <qprocess.h>
#include <QtGui/qguiapplication.h>

class KIOPluginForMetadata : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.wineyards" FILE "wineyardsp.json")
};

WineYardsProtocol::WineYardsProtocol(const QByteArray& pool_socket, const QByteArray& app_socket) : KIO::SlaveBase("wineyards", pool_socket, app_socket)
{
    qCDebug(LOG_KIO_WINEYARDS);
    
}


void WineYardsProtocol::open(const QUrl& url, QIODevice::OpenMode mode)
{
    
}



void WineYardsProtocol::get(const QUrl& url)
{
    if(url.host().isEmpty()){
        QProcess* proc = new QProcess();
        proc->startDetached("wineyards", QStringList());
        finished();
        return;
    }
    qCDebug(LOG_KIO_WINEYARDS) << "Host:" << url.host();
     if (url.host().isEmpty()) {
        QUrl newURL(url);
        newURL.setPath(url.host()+url.path());
        newURL.setHost(("apps.reg"));
        redirection(newURL);
        finished();
        return;
    }
    
    if (url.path().contains('<'))
    {
        error(KIO::ERR_MALFORMED_URL, url.url());
        return;
    }
    if(url.host() == QStringLiteral("apps.tridentu")) {
         mimeType("application/x-ms-dos-executable");
         QProcess* proc = new QProcess();
         QStringList argList = QStringList();
         {
             argList << "start";
            argList << "/unix";
            argList << url.path();
         }
         proc->startDetached("wine", argList);
         finished();
         return;
    } else if (url.host() == QStringLiteral("apps.reg")){
        mimeType("application/x-ms-dos-executable");
        QProcess* proc = new QProcess();
        QStringList argList = QStringList();
         {
            argList << "start";
            argList << QStringLiteral("C:\\") + url.path();
         }
         proc->startDetached("wine", argList);
         finished();
         return;
    }
   
    
    



}

void WineYardsProtocol::listDir(const QUrl& url)
{
    
    
}

void WineYardsProtocol::mimetype(const QUrl& url)
{
    qCDebug(LOG_KIO_WINEYARDS);
    
   if(url.fileName().contains(".exe")){
       mimeType("application/x-ms-dos-executable");
   } else if(url.host().isEmpty()){

       
}
    
    finished();
}

WineYardsProtocol::~WineYardsProtocol()
{
    
}

extern "C" int Q_DECL_EXPORT kdemain(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QLatin1String("kio_wineyards"));

    if (argc != 4) {
        qCritical() << "Usage: kio_wineyards protocol domain-socket1 domain-socket2";
        exit(-1);
    }

    WineYardsProtocol slave(argv[2], argv[3]);
    slave.dispatchLoop();

    return 0;
}

#include "kio_wineyards.moc"



