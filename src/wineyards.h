#pragma once

#include <KXmlGuiWindow>
#include <QScopedPointer>
#include "wineyards_new.h"
#include "wineyards_panel.h"
#include <QMdiSubWindow>
#include <KStandardAction>
#include "wineyardssettings.h"

namespace Ui {
    class WineyardsWindow;
}

class WineYardsWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit WineYardsWindow(QWidget *parent = nullptr);
    ~WineYardsWindow() override;
private:
    void newWineyard();
    void openYard();
    void setupWineYardActions();
    void startRenameWineyard();
    void openRecentYard(const QUrl& url);
    void prepareSave();
    void openConfig();
    void saveYard();
    void loadSettings(const QString& dialogName);
private:
    QScopedPointer<Ui::WineyardsWindow> m_ui;
    NewWineYardDialog* m_dialog;
    WineYard* m_Yard;
    QList<WineyardsPanel*> m_YardPrefs;
    QMdiSubWindow* yardWin = nullptr;
    KRecentFilesAction* m_RecentFiles;
    WineyardsSettings* m_Config;
};


