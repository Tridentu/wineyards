
#include "wineyards_gamescope.h"
#include "ui_wineyards_gamescope.h"
#include <KLocalizedString>
#include <QSpinBox>
#include <QDialog>
#include <QDebug>
#include <QPushButton>

WineyardsGamescopeDialog::WineyardsGamescopeDialog(QWidget* parent, WineYard* yard) : QDialog(parent), m_Yard(yard), m_Ui(new Ui::WineyardsGamescopeDialog)
{
    m_Ui->setupUi(this);
    m_Ui->frameRate->setCurrentText(QString::number(yard->getFrameRate()));
    m_Ui->frameRateNoFocus->setCurrentText(QString::number(yard->getFrameRateNoScope()));
    m_Ui->widthBoxGR->setValue(yard->getGameResolutionWidth());
    m_Ui->heightBoxGR->setValue(yard->getGameResolutionHeight());
    m_Ui->heightBoxGSR->setValue(yard->getGamescopeResolutionHeight());
    m_Ui->widthBoxGSR->setValue(yard->getGamescopeResolutionWidth());
    m_Ui->windowType->setCurrentText(yard->getWindowType());
    m_Ui->integerScaling->setChecked(yard->getIntegerScaling());
    connect(m_Ui->saveButton, &QPushButton::clicked, this, &WineyardsGamescopeDialog::save);
}




void WineyardsGamescopeDialog::save(){
    qDebug() << m_Ui->frameRateNoFocus->currentText();
    int choice = std::stoi( m_Ui->frameRate->currentText().toStdString());
    m_Yard->setFrameRate(choice);
    qDebug() << m_Ui->frameRateNoFocus->currentText();
    int choice2 = std::stoi(m_Ui->frameRateNoFocus->currentText().toStdString());
    m_Yard->setFrameRateNoScope(choice2);
    m_Yard->setGameResolutionWidth(m_Ui->widthBoxGR->value());
    m_Yard->setGameResolutionHeight(m_Ui->heightBoxGR->value());
    m_Yard->setGamescopeResolutionHeight(m_Ui->heightBoxGSR->value());
    m_Yard->setGamescopeResolutionWidth(m_Ui->widthBoxGSR->value());
    m_Yard->setGameResolutionWidth(m_Ui->widthBoxGR->value());
    m_Yard->setWindowType(m_Ui->windowType->currentText());
    m_Yard->setIntegerScaling(m_Ui->integerScaling->isChecked());
    accept();
}

WineyardsGamescopeDialog::~WineyardsGamescopeDialog()
{
    
}



