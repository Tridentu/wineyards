
#include "wineyards_new.h"
#include <QToolButton>
#include "ui_wineyards_new.h"



NewWineYardDialog::NewWineYardDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::NewWineYardDialog), m_Yard(new WineYard(parent))
{
    m_ui->setupUi(this);
    m_ui->progressBar->setVisible(false);
    connect(m_ui->createButton, &QToolButton::clicked, this, &NewWineYardDialog::createWineyard);
    connect(m_ui->discardButton, &QToolButton::clicked, this, &QDialog::reject);
    connect(m_ui->wineyardNameField, &KLineEdit::textChanged, this, &NewWineYardDialog::setName);
    connect(m_ui->wineyardTypeField, &KComboBox::currentTextChanged, this, &NewWineYardDialog::setYardType);
    connect(m_ui->runnerVersionField, &KHistoryComboBox::currentTextChanged, this, &NewWineYardDialog::setRunner);
    connect(m_ui->wineyardVersioningCB, &QCheckBox::toggled, this, &NewWineYardDialog::setVersioningEnabled);

}


NewWineYardDialog::~NewWineYardDialog()
{
    delete m_Yard;
}

void NewWineYardDialog::setRunner(const QString& newRunner)
{
    m_Yard->setRunner(newRunner);
}

void NewWineYardDialog::setName(const QString& newName)
{
    m_Yard->setName(newName);
    
}

void NewWineYardDialog::setYardType(const QString& newType)
{
    m_Yard->setYardType(newType);
}


void NewWineYardDialog::createWineyard(bool checked)
{     
     m_Yard->save();
     accept();
}

void NewWineYardDialog::setVersioningEnabled(bool enabled)
{
    m_Yard->setVersioning(enabled);
}

