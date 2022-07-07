#include "ui_wineyards_program.h"

#include "wineyards_program.h"

WineyardsProgramEntry::WineyardsProgramEntry(QWidget* parent) : QWidget(parent), m_Ui(new Ui::WineYardsProgramEntry)
{
    m_Ui->setupUi(this);
    m_Ui->loadingIndicator->setVisible(false);
    m_Ui->runningIndicator->off();
}


WineyardsProgramEntry::~WineyardsProgramEntry()
{
    
}


void WineyardsProgramEntry::setProgramName(const QString& name)
{
    m_Name = name;
    m_Ui->programTitle->setComment(m_Name);
}


void WineyardsProgramEntry::setProgramTitle(const QString& title)
{
    m_Title = title;
    m_Ui->programTitle->setText(m_Title);
}

