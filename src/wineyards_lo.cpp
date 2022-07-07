

#include "wineyards_lo.h"
#include "ui_wineyards_launch_options.h"


WineyardsLODialog::WineyardsLODialog(QWidget* parent, WineYard* yard) : QDialog(parent), m_Ui(new Ui::WineyardsLaunchOptionsDialog), m_Yard(yard)
{
    m_Ui->setupUi(this);
}


