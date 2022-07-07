
#include "wineyard_rename.h"

#include "ui_wineyard_rename.h"

WineyardsRenameDialog::WineyardsRenameDialog(QWidget* parent, WineYard* yard) : QDialog(parent), m_Ui(new Ui::WineyardRenameDialog), m_Yard(yard)
{
    m_Ui->setupUi(this);
    connect(m_Ui->buttonBox, &QDialogButtonBox::accepted, this, &WineyardsRenameDialog::renameConfirm);
}


void WineyardsRenameDialog::renameConfirm()
{
    m_Yard->setName(m_Ui->newNameBox->text());
    m_Yard->save(true);
    delete this;
}

