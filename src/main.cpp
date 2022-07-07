#include <QApplication>
#include <QMainWindow>
#include <KAboutData>
#include <QCommandLineParser>
#include <KLocalizedString>
#include "ui_wineyards.h"
#include "wineyards.h"
int main(int argc, char** argv)
{
    

    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("WineYards");

    KAboutData aboutData(
            QStringLiteral("WineYards"),
            i18n("WineYards"),
            QStringLiteral("0.1"),
            i18n("Like Bottles, but for KDE."),
            KAboutLicense::GPL,
            i18n("(c) 2022"),
            i18n("This app is intended for use with wine and KDE"),
            QStringLiteral("https://tridentu.github.io/wineyards"),
            QStringLiteral("tridentuorg@protonmail.com")
    );
    aboutData.setDesktopFileName("wineyards.desktop");
    KAboutData::setApplicationData(aboutData);
    
    QCommandLineParser parser;

    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);
    WineYardsWindow w;
    w.show();

    return app.exec();
}
