
#include "wineyards_panel.h"
#include "ui_wineyards_panel.h"
#include "wineyards_lo.h"
#include "wineyards_drives.h"
#include "wineyards_settings.h"
#include "wineyards_gamescope.h"
#include <KFileCustomDialog>
#include "wineyards_program.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "wineyards_package.h"

WineyardsPanel::WineyardsPanel(QWidget* parent, WineYard* yard) : QDialog(parent), m_Yard(yard), m_Ui(new Ui::WineyardPreferencesPanel)
{
    m_Ui->setupUi(this);
    connect(m_Ui->launchOptionsButton, &QToolButton::clicked, this, &WineyardsPanel::openLO);
    connect(m_Ui->drivesManage, &QToolButton::clicked, this, &WineyardsPanel::openDrives);
    connect(m_Ui->dxvkManage, &QToolButton::clicked, this, &WineyardsPanel::openDXVKSettings);
    connect(m_Ui->vkd3dManage, &QToolButton::clicked, this, &WineyardsPanel::openVKD3DSettings);
    connect(m_Ui->dxvkNVAPIManage, &QToolButton::clicked, this, &WineyardsPanel::openDXVKNVAPISettings);
    connect(m_Ui->latencyFlexManage, &QToolButton::clicked, this, &WineyardsPanel::openLatencyFlexSettings);
    connect(m_Ui->gamescopeManage, &QToolButton::clicked, this, &WineyardsPanel::openGamescopeDialog);
    connect(m_Ui->addPathButton, &QToolButton::clicked, this, &WineyardsPanel::addProgram);
    m_Dialog = new KFileCustomDialog();
    m_Dialog->setWindowTitle(QString("Choose an executable path"));
    m_Dialog->setOperationMode(KFileWidget::Opening);
    addLoadedPrograms();
    addPackages();
}

void WineyardsPanel::addPackages()
{
    WineyardsPackageUI::InitDB();
    auto packages = CaravelPM::CaravelDBContext::GetDB()->FindPackagesInCategory("wine");
    if (!packages.empty()){
        for (auto pack : packages) {
            auto ui = new WineyardsPackageUI(this, pack);
             QListWidgetItem* item = new QListWidgetItem(QString());
            item->setSizeHint(ui->size());
            m_Ui->packageView->addItem(item);
            m_Ui->packageView->setItemWidget(item, ui);
        }
    }
}


void WineyardsPanel::openLO()
{
    WineyardsLODialog* dialog = new WineyardsLODialog(this, m_Yard);
    dialog->open();
}

void WineyardsPanel::openVKD3DSettings()
{
    auto dialogE =KConfigDialog::exists(QStringLiteral("settings"));
    if (dialogE){
        delete dialogE;
    }
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   dialog->OpenPage(3);
   dialog->show();
   dialog->OpenDLLVKD3DTab();
}


void WineyardsPanel::openDrives()
{
    WineyardDrivesManager* dm = new WineyardDrivesManager(this, m_Yard);
    dm->open();
}

void WineyardsPanel::openConfig(uint pageIndex)
{
    if (KConfigDialog::showDialog(QStringLiteral("settings")))
        return;
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   dialog->OpenPage(pageIndex);
   dialog->show();
}

void WineyardsPanel::addLoadedPrograms()
{
    auto arr = m_Yard->getLoadedPrograms();
    for (int i = 0; i < arr.size(); i++) {
        auto arrObj = arr[i];
        WineyardsProgramEntry* entry = new WineyardsProgramEntry(this, m_Yard);
        entry->setProgramName(arrObj.toObject().take("path").toString());
        QFile file(arrObj.toObject().take("path").toString());
        QFileInfo fileInfo(file);
        entry->setProgramTitle(arrObj.toObject().take("name").toString());
        QListWidgetItem* item = new QListWidgetItem(QString());
        item->setSizeHint(entry->sizeHint());
        m_Ui->programList->addItem(item);
        m_Ui->programList->setItemWidget(item, entry);
    }
}


void WineyardsPanel::openDXVKSettings()
{
    auto dialogE =KConfigDialog::exists(QStringLiteral("settings"));
    if (dialogE){
        delete dialogE;
    }
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   dialog->OpenPage(3);
   dialog->show();
   dialog->OpenDLLDXVKTab();

}

void WineyardsPanel::openGamescopeDialog(){
   WineyardsGamescopeDialog* dialog = new WineyardsGamescopeDialog(this, m_Yard);
   dialog->show();
}

void WineyardsPanel::openLatencyFlexSettings()
{
    auto dialogE =KConfigDialog::exists(QStringLiteral("settings"));
    if (dialogE){
        delete dialogE;
    }
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   dialog->OpenPage(3);
   dialog->show();
   dialog->OpenLatencyFleXTab();
}

void WineyardsPanel::openDXVKNVAPISettings()
{
    auto dialogE =KConfigDialog::exists(QStringLiteral("settings"));
    if (dialogE){
        delete dialogE;
    }
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   dialog->OpenPage(3);
   dialog->show();
   dialog->OpenDLLDXVKNVAPITab();
}

void WineyardsPanel::addProgram()
{   if(!m_Dialog)
        return;
    m_Dialog->show();
    connect(m_Dialog->fileWidget(), &KFileWidget::accepted, this, &WineyardsPanel::addProgramEntry);
}

void WineyardsPanel::addProgramEntry()
{
   QString result =  m_Dialog->fileWidget()->selectedFile();
   
   WineyardsProgramEntry* entry = new WineyardsProgramEntry(this, m_Yard);
   entry->setProgramName(result);
   QFile file(result);
   QFileInfo fileInfo(file);
   entry->setProgramTitle(fileInfo.baseName());
   m_Yard->addProgram(fileInfo.baseName(), result);
   QListWidgetItem* item = new QListWidgetItem(QString());
   item->setSizeHint(entry->sizeHint());
   m_Ui->programList->addItem(item);
   m_Ui->programList->setItemWidget(item, entry);

}

