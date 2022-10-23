



#pragma once

#include <QString>
#include <QObject>
#include <string>
#include <qtextstream.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QProcess>

enum class WineyardField {
    Name,
    Type,
    Runner,
    AppPath,
    Versioning
};

enum class GamescopeField {
    FrameRate,
    FrameRateNoFocus,
    GameWidth,
    GamescopeWidth,
    GameHeight,
    GamescopeHeight,
    WindowType,
    IntegerScaling
};

struct WineYardRunnerParams {
  QString program;
  QWidget* widget;
  bool isInTerminal = false;  
  QStringList args;
  QString postLaunchScript;
  WineYardRunnerParams() = default;
  WineYardRunnerParams(const WineYardRunnerParams& other) = default;
};

struct WineYardProcess { 
  QString processName;
  QString threads;
  QString pid;
  QString parent;
};



class WineYard : public QObject {
  Q_OBJECT
public:
    WineYard(QObject* parent);
    ~WineYard();
public:
    const QString& getName();
    const QString& getYardType();
    const QString& getRunner();
    bool usesVersioning();
public:
    int getGameResolutionWidth() const;
    int getGameResolutionHeight() const;
    int getGamescopeResolutionHeight() const;
    int getGamescopeResolutionWidth() const;
    int getFrameRate() const;
    int getFrameRateNoScope() const;
    bool getIntegerScaling() const;
    const QString& getWindowType() const;
    QJsonArray getLoadedPrograms();
public:
    void setName(const QString& newName);
    void setYardType(const QString& newYardType);
    void setRunner(const QString& newRunner);
    void setVersioning(bool useVersions);
public:
    void setGameResolutionWidth(int grw);
    void setGameResolutionHeight(int grh);
    void setGamescopeResolutionHeight(int grhs);
    void setGamescopeResolutionWidth(int grws);
    void setFrameRate(int fr);
    void setFrameRateNoScope(int frns);
    void setWindowType(QString windowTypeNew);
    void setIntegerScaling(bool intScaled);
public:
    void addProgram(const QString& fileName, const QString& filePath);
public:
    std::string slugifyName();
    std::string slugifyPrevName();
    void writeToConfig(QTextStream& fileStream, WineyardField field);
    void writeToConfig(QTextStream& fileStream, GamescopeField field);
    void writeGeneralHeader(QTextStream& fileStream);
    void writeGamescopeHeader(QTextStream& fileStream);
public:
    void run(const WineYardRunnerParams& params, bool useKonsole = false);
public:
    void setupYard();
    void save(bool replaceFile = false);
    void load(const QUrl& url);
    void getProcesses();
    void terminateProgram(const QString& programName, QWidget* widget);
private:
    QString name;
    QString prevName;
    QString yardType;
    bool useVersioning;
    QString runner;    
private:
    int gameResolutionWidth;
    int gameResolutionHeight;
    int gameResolutionHeightScope;
    int gameResolutionWidthScope;
    int frameRate;
    int frameRateNoFocus;
    bool integerScaling;
    QString windowType;
    QJsonDocument programListDoc;
    QList<WineYardProcess> m_Processes;
};
