#include "wineyards.h"
#include "ui_wineyards.h"
#include <QApplication>
#include <QAction>
#include <KActionCollection>
#include <KLocalizedString>
#include <QFileDialog>
#include <QDebug>
#include "wineyard_rename.h"
#include "wineyards_settings.h"



WineYardsWindow::WineYardsWindow(QWidget *parent) :
    KXmlGuiWindow(parent),
    m_ui(new Ui::WineyardsWindow),
    m_Yard(new WineYard(this)),
    m_Config(WineyardsSettings::self())
{
    m_ui->setupUi(this);
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());
    KStandardAction::openNew(this, &WineYardsWindow::newWineyard, actionCollection());
    KStandardAction::open(this, &WineYardsWindow::openYard, actionCollection());
    m_RecentFiles = KStandardAction::openRecent(this, &WineYardsWindow::openRecentYard, actionCollection());
    KStandardAction::preferences(this, &WineYardsWindow::openConfig, actionCollection());
    KStandardAction::save(this, &WineYardsWindow::saveYard, actionCollection());

    setupWineYardActions();
    m_dialog = new NewWineYardDialog(this);
    setupGUI(StandardWindowOption::Default, "/usr/share/kxmlgui5/wineyards/wineyardsui.rc");
    connect(qApp, &QApplication::aboutToQuit, this, &WineYardsWindow::prepareSave);
    m_RecentFiles->loadEntries(m_Config->config()->group("RecentFiles"));

}

void WineYardsWindow::newWineyard()
{
    m_dialog->show();
}

void WineYardsWindow::openYard(){
    QUrl url(QDir::homePath().append(QDir::separator()).append(".wineyards"));
    const QUrl yardFile = QFileDialog::getOpenFileUrl(this, i18n("Open Existing Wineyard..."), url, i18n("WineYards (*.wineyard.ini)"));
    m_Yard->load(yardFile);
    WineyardsPanel* panel = new WineyardsPanel(this, m_Yard);
    m_RecentFiles->addUrl(yardFile, m_Yard->getName());
    panel->open();
}

void WineYardsWindow::prepareSave()
{
    m_RecentFiles->saveEntries(m_Config->config()->group("RecentFiles"));
}


void WineYardsWindow::saveYard()
{
    m_Yard->save();
}

void WineYardsWindow::setupWineYardActions()
{
    QAction* wineyardRenameAction = new QAction(this);
    wineyardRenameAction->setText(i18n("Rename Wineyard"));
    wineyardRenameAction->setIcon(QIcon::fromTheme("edit"));
    actionCollection()->setDefaultShortcut(wineyardRenameAction, Qt::CTRL + Qt::SHIFT + Qt::Key_R);
    actionCollection()->addAction("wineyardRename", wineyardRenameAction);
    connect(wineyardRenameAction, &QAction::triggered, this, &WineYardsWindow::startRenameWineyard);
}


void WineYardsWindow::startRenameWineyard()
{
    qDebug() << "Starting rename process...";
    WineyardsRenameDialog* newNameDialog = new WineyardsRenameDialog(this, m_Yard);
    newNameDialog->open();
}

void WineYardsWindow::openRecentYard(const QUrl& url)
{
    m_Yard->load(url);
    WineyardsPanel* panel = new WineyardsPanel(this, m_Yard);
    panel->open();
}

void WineYardsWindow::openConfig()
{
   if (KConfigDialog::showDialog(QStringLiteral("settings")))
        return;
   WineyardsSettingsWindow* dialog = new WineyardsSettingsWindow(this);
   connect(dialog, &WineyardsSettingsWindow::settingsChanged, this, &WineYardsWindow::loadSettings);
   dialog->show();
}


void WineYardsWindow::loadSettings(const QString& dialogName)
{
    
}






WineYardsWindow::~WineYardsWindow() = default;

