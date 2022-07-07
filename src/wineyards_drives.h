
#pragma once 


#include <QDialog>
#include <QScopedPointer>
#include "wineyard_struct.h"

namespace Ui {
    class WineyardsDriveDialog;
}

const QString WINEYARDS_DRIVES = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class WineyardDrivesManager : public QDialog {
public:
    WineyardDrivesManager(QWidget* parent, WineYard* yard);
private:
    QScopedPointer<Ui::WineyardsDriveDialog> m_Ui;  
    WineYard* m_Yard;
};
