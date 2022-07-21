#include "ui_wineyards_program.h"

#include "wineyards_program.h"

WineyardsProgramEntry::WineyardsProgramEntry(QWidget* parent, WineYard* yard) : QWidget(parent), m_Ui(new Ui::WineYardsProgramEntry), m_Yard(yard)
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
    connect(m_Ui->runBtn, &QToolButton::clicked, this, &WineyardsProgramEntry::runProg);
    connect(m_Ui->stopBtn, &QToolButton::clicked, this, &WineyardsProgramEntry::stopProg);
    connect(m_Ui->terminalBtn, &QToolButton::clicked, this, &WineyardsProgramEntry::runProgTerm);

}


void WineyardsProgramEntry::runProg()
{
    WineYardRunnerParams params;
    params.program = m_Name;
    params.widget = this;
    m_Yard->run(params);
}

void WineyardsProgramEntry::runProgTerm()
{
    WineYardRunnerParams params;
    params.program = m_Name;
    params.widget = this;
    m_Yard->run(params, true);
}


void WineyardsProgramEntry::stopProg()
{
    m_Yard->terminateProgram(m_Name, this);

}


void WineyardsProgramEntry::setProgramTitle(const QString& title)
{
    m_Title = title;
    m_Ui->programTitle->setText(m_Title);
}

