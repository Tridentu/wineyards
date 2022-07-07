

#include "wineyards_drives.h"
#include "ui_wineyards_drives.h"


WineyardDrivesManager::WineyardDrivesManager(QWidget* parent, WineYard* yard) : QDialog(parent), m_Yard(yard), m_Ui(new Ui::WineyardsDriveDialog)
{
    m_Ui->setupUi(this);
}

