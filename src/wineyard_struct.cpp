
#include "wineyard_struct.h"

#include <QDir>
#include <slugify.hpp>
#include <QDebug>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <INIReader.h>
#include <KNotification>
#include <KLocalizedString>
#include <qprocess.h>

void WineYard::setupYard()
{
    
}


bool WineYard::usesVersioning()
{
    return useVersioning;
}

const QString & WineYard::getName()
{
    return name;
}

const  QString & WineYard::getRunner()
{
    return runner;
}

const  QString & WineYard::getYardType()
{
    return yardType;
}

WineYard::WineYard(QObject* parent) : QObject(parent),  name("Untitled WineYard"), yardType("Application"), useVersioning(false), prevName(name)
{
    gameResolutionWidth = 1280;
    gameResolutionHeight = 720;
    gameResolutionHeightScope = 720;
    gameResolutionWidthScope = 1280;
    frameRate = 60;
    frameRateNoFocus = 30;
    windowType = "Borderless";
}

std::string WineYard::slugifyName()
{
    return slugify(name.toStdString());
}

std::string WineYard::slugifyPrevName(){
    return slugify(prevName.toStdString());
}

void WineYard::save(bool replaceFile)
{
    QString fileName((slugifyName() + ".wineyard.ini").c_str());
    if(replaceFile){
        QString prevFileName((slugifyPrevName() + ".wineyard.ini").c_str());
        QString prevPathStr(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).append(prevFileName).toStdString().c_str());
        QFile oldConfig(prevPathStr);
        oldConfig.rename(fileName);
        
    }
    QString pathStr(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).append(fileName).toStdString().c_str());
    QFile newConfig(pathStr);
    if(newConfig.open(QIODevice::ReadWrite)){
        QTextStream stream(&newConfig);
        writeGeneralHeader(stream);
        writeToConfig(stream,WineyardField::Name);
        writeToConfig(stream,WineyardField::Type);
        writeToConfig(stream,WineyardField::Runner);
        writeToConfig(stream,WineyardField::AppPath);
        writeToConfig(stream,WineyardField::Versioning);
        writeGamescopeHeader(stream);
        writeToConfig(stream,GamescopeField::FrameRate);
        writeToConfig(stream,GamescopeField::FrameRateNoFocus);
        writeToConfig(stream,GamescopeField::GameHeight);
        writeToConfig(stream,GamescopeField::GameWidth);
        writeToConfig(stream,GamescopeField::GamescopeWidth);
        writeToConfig(stream,GamescopeField::GamescopeHeight);
        writeToConfig(stream,GamescopeField::WindowType);
        writeToConfig(stream,GamescopeField::IntegerScaling);

        newConfig.close();
        QString pathStr2(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).toStdString().c_str());
        QDir wineyardDir(pathStr2);
        wineyardDir.mkdir(QString::fromStdString(slugifyName()));
        {
            QString pathStr2(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).toStdString().c_str());
            wineyardDir = QDir(pathStr2);
            wineyardDir.cd(QString::fromStdString(slugifyName()));
            wineyardDir.setPath(wineyardDir.path() + QStringLiteral("/programs.json"));
            QFile jsonFile(wineyardDir.path());
            if(!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
                return;
            QTextStream stream(&jsonFile);
            stream.setCodec("utf-8");
            stream << programListDoc.toJson();
            jsonFile.close();
        }
        qDebug() << "WineYard " << pathStr << " saved successfully.";
    } else {
        qDebug() << "WineYard " << pathStr << " was not saved.";   
    }
}

void WineYard::writeGamescopeHeader(QTextStream& fileStream)
{
    fileStream << "\n";
    fileStream << "[gamescope]\n";
}


void WineYard::writeGeneralHeader(QTextStream& fileStream)
{
    fileStream << "[general]\n";
}
void WineYard::writeToConfig(QTextStream& fileStream, GamescopeField field)
{
    switch(field){
        case GamescopeField::FrameRate:
            fileStream << "frameRate=" << QString::number(frameRate);
            break;
        case GamescopeField::FrameRateNoFocus:
            fileStream << "frameRateNoFocus=" << QString::number(frameRateNoFocus);
            break;
        case GamescopeField::GameWidth:
            fileStream << "width=" << QString::number(gameResolutionWidth);
            break;
        case GamescopeField::GameHeight:
            fileStream << "height=" << QString::number(gameResolutionHeight);
            break;
        case GamescopeField::GamescopeWidth:
            fileStream << "gamescopeWidth=" << QString::number(gameResolutionWidthScope);
            break;
        case GamescopeField::GamescopeHeight:
            fileStream << "gamescopeHeight=" << QString::number(gameResolutionHeightScope);
            break;
        case GamescopeField::WindowType:
            fileStream << "windowType=" << windowType;
            break;
        case GamescopeField::IntegerScaling:
            fileStream << "integerScaling=" << ((integerScaling) ? "y" : "n");
            break;
    }
    fileStream << "\n";
}

QJsonArray WineYard::getLoadedPrograms()
{
    return programListDoc.array();
}


void WineYard::writeToConfig(QTextStream& fileStream, WineyardField field)
{
    switch(field){
        case WineyardField::Name:
            fileStream << "name=" << name;
            break;
        case WineyardField::Type:
            fileStream << "type=" << yardType;
            break;
        case WineyardField::Runner:
            fileStream << "runner=" << runner;
            break;
        case WineyardField::Versioning:
            fileStream << "versioning=" << ((useVersioning) ? "y" : "n");
            break;
        case WineyardField::AppPath:
            QDir wineyardDir;
            QString pathStr2(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).toStdString().c_str());
            wineyardDir = QDir(pathStr2);
            wineyardDir.cd(QString::fromStdString(slugifyName()));
            wineyardDir.cd("apps");
            fileStream << "appPath=" << pathStr2 + QDir::separator() +  QString::fromStdString(slugifyName()) + QDir::separator() + QStringLiteral("apps");
            break;
      
    }
    fileStream << "\n";
}

void WineYard::setName(const QString& newName)
{
    prevName = name;
    name = newName;
}

void WineYard::setRunner(const QString& newRunner)
{
    runner = newRunner;
}

void WineYard::setVersioning(bool useVersions)
{
    useVersioning = useVersions;
}

void WineYard::setYardType(const QString& newYardType)
{
    yardType = newYardType;
}

void WineYard::addProgram(const QString& fileName, const QString& filePath)
{
    QJsonArray arr = programListDoc.array();
    QJsonObject progObj;
    progObj["name"] = fileName;
    progObj["path"] = filePath;
    arr.append(progObj);
    programListDoc.setArray(arr);
}


void WineYard::load(const QUrl& url){
    QString pathStr = url.path();
    INIReader reader(pathStr.toStdString());
    if(reader.ParseError() < 0){
     qDebug() << "Can't load WineYard file " << pathStr;
     return;
    }
    setName(QString(reader.GetString("general","name","Untitled").c_str()));
    setYardType(QString(reader.GetString("general","type","Application").c_str()));
    setRunner(QString(reader.GetString("general","runner","").c_str()));
    setVersioning(reader.GetString("general","versioning","n") == "y");
    setFrameRate(reader.GetInteger("gamescope","frameRate",60));
    setFrameRateNoScope(reader.GetInteger("gamescope","frameRateNoFocus",60));
    setGameResolutionWidth(reader.GetInteger("gamescope","width",1280));
    setGameResolutionHeight(reader.GetInteger("gamescope","height",720));
    setGamescopeResolutionWidth(reader.GetInteger("gamescope","gamescopeWidth",1280));
    setGamescopeResolutionHeight(reader.GetInteger("gamescope","gamescopeHeight",720));
    setIntegerScaling(reader.GetString("gamescope","integerScaling","n") == "y");
    setWindowType(QString::fromStdString(reader.GetString("gamescope","windowType","Borderless")));
    {
        QString pathStr2(QDir::homePath().append(QDir::separator()).append(".wineyards").append(QDir::separator()).toStdString().c_str());
        QDir wineyardDir(pathStr2);
        wineyardDir.cd(QString::fromStdString(slugifyName()));
        wineyardDir.setPath(wineyardDir.path() + QStringLiteral("/programs.json"));
        QFile jsonFile(wineyardDir.path());
        if(!jsonFile.open(QIODevice::ReadOnly))
            return;
        QTextStream stream(&jsonFile);
        programListDoc = QJsonDocument::fromJson(stream.readAll().toLocal8Bit());
        jsonFile.close();
    }
    setenv("CURRENT_WIY_DIR", reader.GetString("general","runner","appPath").c_str(), 1);
}

int WineYard::getGameResolutionWidth() const
{
    return gameResolutionWidth;
}

int WineYard::getGameResolutionHeight() const 
{
    return gameResolutionHeight;
}

int WineYard::getGamescopeResolutionWidth() const
{
    return gameResolutionWidthScope;
}

int WineYard::getGamescopeResolutionHeight() const
{
    return gameResolutionHeightScope;
}

int WineYard::getFrameRate() const
{
    return frameRate;
}

int WineYard::getFrameRateNoScope() const
{
    return frameRateNoFocus;
}

const QString & WineYard::getWindowType() const
{
    return windowType;
}

void WineYard::setFrameRate(int fr)
{
    frameRate = fr;
}

void WineYard::setFrameRateNoScope(int frns)
{
    frameRateNoFocus = frns;
}

void WineYard::setGameResolutionHeight(int grh)
{
    gameResolutionHeight = grh;
}

void WineYard::setGameResolutionWidth(int grw)
{
    gameResolutionWidth = grw;
}


void WineYard::setGamescopeResolutionHeight(int grhs)
{
    gameResolutionHeightScope = grhs;
}

void WineYard::setGamescopeResolutionWidth(int grws)
{
    gameResolutionWidthScope = grws;
}

void WineYard::setWindowType(QString windowTypeNew)
{
    windowType = windowTypeNew;
}


bool WineYard::getIntegerScaling() const
{
    return integerScaling;
}

void WineYard::setIntegerScaling(bool intScaled)
{
    integerScaling = intScaled;
}


void WineYard::run(const WineYardRunnerParams& params, bool useKonsole)
{
    QProcess* proc = new QProcess();
    QStringList args;
   
    if(useKonsole){
        args << "-e";
        args  << QStringLiteral("wine").append(" start /unix ").append(params.program);
        proc->startDetached("konsole", args);
    } else {
         args << "start";
        args << "/unix" << params.program;
        proc->startDetached("wine", args);
         KNotification* note = KNotification::event("programStarted",i18n("Wine Program Started"), i18n("A Wine program (") + params.program + i18n(") has started"),QStringLiteral("wine"),params.widget,KNotification::CloseOnTimeout,"wineyards");
        note->sendEvent();
    }
   
}

void WineYard::terminateProgram(const QString& programName,  QWidget* widget)
{
        getProcesses();
        qDebug() << m_Processes.length();
        QUrl url("file:///" + programName);
        QString finalUrl((url.isValid()) ? url.fileName() : programName);
        for (auto& procWine: m_Processes){
            if (procWine.processName == finalUrl){
                {
                    QProcess* dbgProc = new QProcess();
                    QStringList args;
                    QStringList cmd;
                    cmd  << QStringLiteral("attach 0x").append(procWine.pid) << "kill" << "quit" ;
                    for (auto cmdlet : cmd){
                        qDebug() << cmdlet;
                        args << QStringLiteral("--command") << cmdlet;
                        dbgProc->start("winedbg", args);
                        dbgProc->waitForFinished();
                        qDebug() << dbgProc->readAllStandardOutput();
                        if(dbgProc->exitStatus() == QProcess::CrashExit){
                            KNotification* noteFail = KNotification::event("programExitFailed",i18n("Wine Program Failed to Abort"), i18n("A Wine program (") + programName + i18n(") has failed to terminate."),QStringLiteral("wine"),widget,KNotification::CloseOnTimeout,"wineyards");
                            noteFail->sendEvent();
                        }
                        args.clear();
                    }
                    
                }
                break;
            }
        }
}


void WineYard::getProcesses()
{
 QString parent;
 {
   QString result;
   QProcess* dbgProc = new QProcess();
   QStringList args;
   args << "--command" << "info proc";
   dbgProc->start("winedbg", args);
   dbgProc->waitForFinished();
   result = dbgProc->readAllStandardOutput();
   if(result.isEmpty())
       return;
   QStringList splitResult = result.split('\n');
   splitResult.removeAt(0);
   for(auto& w: splitResult){
      
       QString wNew = w.replace("'", " ");
       wNew = wNew.remove(0,1);
       if(wNew.contains(QStringLiteral("\\_"))){
           wNew = wNew.replace(QStringLiteral("\\_"), "");
           wNew += "child";
       }
        wNew = wNew.replace(QRegExp("(\\s{2,})"), " ");

       {
        QStringList newWR2 = wNew.split(" ");
        QString w_parent;
        QRegExp digit("\\d*");
        if (newWR2.length() >= 3 && digit.exactMatch(newWR2[0])){
            QString processId = newWR2[0];
            QString threads = newWR2[1];
            QString processName = newWR2[2];
            if (newWR2.length() == 3){
                parent = processId;
            } else {
                w_parent = parent;
            }
            WineYardProcess procStub;
            procStub.pid = processId;
            procStub.processName = processName;
            procStub.parent = w_parent;
            procStub.threads = threads;
            m_Processes.append(procStub);
        }
      }
   }
 }
}




WineYard::~WineYard(){

}
