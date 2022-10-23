
#include "ui_wineyards_package.h"
#include "wineyards_package.h"
#include <KNotification>
#include <QProcess>
#include <QDebug>
#include <KLocalizedString>

WineyardsPackageUI::WineyardsPackageUI(QWidget* parent, CaravelPM::CaravelPackageInfo info) : QWidget(parent), m_Ui(new Ui::PackageEntry)
{
    m_Ui->setupUi(this);
    m_Ui->packageTitle->setText(QString::fromStdString((info.PackageName)));
    m_Ui->packageTitle->setComment(QString::fromStdString((info.Description)));
    m_Ui->category->setText(QString("Category: ") + QString::fromStdString(info.PackageCategory));
    connect(m_Ui->installButton, &QToolButton::clicked, this, &WineyardsPackageUI::Install);
    packageName = QString::fromStdString((info.PackageName));
}

void WineyardsPackageUI::Install()
{
   auto packages = CaravelPM::CaravelDBContext::GetDB()->GetInstalledPackages();
   bool isInstalled;
   for (auto pack : packages) {
     if(QString::fromStdString(pack.name) == packageName ){
         isInstalled = true;
     }
    }
    if(!isInstalled){
      QString prog = "caravel-pm";
      QStringList args;
      args << "install-package";
      args << packageName;
      QProcess* proc = new QProcess(this);
      proc->start(prog, args);
      proc->waitForFinished();
      qDebug() << QString::fromUtf8(proc->readAllStandardError());
      if(proc->exitStatus() == QProcess::NormalExit) {
           KNotification* note = KNotification::event("packageInstalled",i18n("Wine Package Installed"), i18n("A Wine package (") + packageName + i18n(") has been installed"),QStringLiteral("wine"),this,KNotification::CloseOnTimeout,"wineyards");
        note->sendEvent();
      } else {
             KNotification* note = KNotification::event("packageInstallFailed",i18n("Wine Package Install Failed"), i18n("A Wine package (") + packageName + i18n(") failed to install"),QStringLiteral("wine"),this,KNotification::CloseOnTimeout,"wineyards");
        note->sendEvent();
      }
    } else {
        KNotification* note = KNotification::event("packageIsInstalled",i18n("Wine Package Already Installed"), i18n("A Wine package (") + packageName + i18n(") has already been installed"),QStringLiteral("wine"),this,KNotification::CloseOnTimeout,"wineyards");
        note->sendEvent();
    }
}



void WineyardsPackageUI::InitDB()
{
      CaravelPM::CaravelDBContext::GetDB()->InitDB("https://tridentu.github.io/acquirium/pman.caraveldb", false);
}
