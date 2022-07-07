
#pragma once

#include <QWidget>
#include <QDialog>
#include <QScopedPointer>
#include <KFileCustomDialog>
#include "wineyard_struct.h"


namespace Ui {
 class WineyardPreferencesPanel;   
}
class WineyardsPanel : public QDialog {
public:
    WineyardsPanel(QWidget* parent, WineYard* yard);
public:
    void openConfig(uint pageIndex);
private:
    void openLO();
    void openDrives();
    void openDXVKSettings();
    void openVKD3DSettings();
    void openDXVKNVAPISettings();
    void openLatencyFlexSettings();
    void openGamescopeDialog();
    void addProgram();
    void addProgramEntry();
    void addLoadedPrograms();
private:
    WineYard* m_Yard;
    KFileCustomDialog*  m_Dialog;
    QScopedPointer<Ui::WineyardPreferencesPanel> m_Ui;
};
