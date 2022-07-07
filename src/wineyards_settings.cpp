#include "wineyards_settings.h"
#include "ui_general_form.h"
#include "ui_advanced_form.h"
#include "ui_runners_form.h"
#include "ui_dll_form.h"
#include <KLocalizedString>
#include <KConfigDialogManager>


WineyardsSettingsWindow::WineyardsSettingsWindow(QWidget* parent) : KConfigDialog(parent, QStringLiteral("settings"), WineyardsSettings::self())
{
        setFaceType(FaceType::List);
        pages.append(addPage(new GeneralForm(this), i18n("General"), QStringLiteral("settings"), i18n("General Options")));
        pages.append(addPage(new AdvancedForm(this), i18n("Advanced"), QStringLiteral("preferences"), i18n("Advanced Options")));
        m_Runners = new RunnersForm(this);
        pages.append(addPage(m_Runners, i18n("Runners"), QStringLiteral("start"), i18n("Manage Runners")));
        m_DLLForm = new DLLForm(this);
        pages.append(addPage(m_DLLForm, i18n("DLL Components"), QStringLiteral("distributor-logo-windows"), i18n("Manage DLL Components")));
        
}

void WineyardsSettingsWindow::OpenPage(uint pageNumber)
{
    KPageWidgetItem* item = pages[pageNumber];
    if(item){
        setCurrentPage(item);
    }
}

void WineyardsSettingsWindow::OpenDLLDXVKTab()
{
    m_DLLForm->openDXVKTab();
}

void WineyardsSettingsWindow::OpenDLLDXVKNVAPITab()
{
    m_DLLForm->openDXVKNVAPITab();
}

void WineyardsSettingsWindow::OpenLatencyFleXTab()
{
    m_DLLForm->openLatencyFleXTab();
}



WineyardsSettingsWindow::~WineyardsSettingsWindow()
{
    
}


GeneralForm::GeneralForm(QWidget* parent) : QWidget(parent), m_Ui(new Ui::GeneralForm)
{
    m_Ui->setupUi(this);
}

AdvancedForm::AdvancedForm(QWidget* parent) : QWidget(parent), m_Ui(new Ui::AdvancedForm)
{
    m_Ui->setupUi(this);
}

RunnersForm::RunnersForm(QWidget* parent) : QWidget(parent), m_Ui(new Ui::RunnersForm)
{
    m_Ui->setupUi(this);
}

KEditListWidget* RunnersForm::getRunnersListWidget()
{
    return m_Ui->kcfg_runnersList;
}


DLLForm::DLLForm(QWidget* parent) : QWidget(parent), m_Ui(new Ui::DLLForm)
{
    m_Ui->setupUi(this);
}

void DLLForm::openDXVKNVAPITab()
{
    m_Ui->componentsStack->setCurrentWidget(m_Ui->componentDXVKNVAPI);
}

void DLLForm::openLatencyFleXTab()
{
    m_Ui->componentsStack->setCurrentWidget(m_Ui->componentLatencyFleX);
}



void DLLForm::openDXVKTab()
{
   m_Ui->componentsStack->setCurrentWidget(m_Ui->componentDXVK);
}

void DLLForm::openVKD3DTab(){
    m_Ui->componentsStack->setCurrentWidget(m_Ui->componentVKD3D);;
}

void WineyardsSettingsWindow::OpenDLLVKD3DTab()
{
    m_DLLForm->openVKD3DTab();
}



GeneralForm::~GeneralForm()
{
    
}


AdvancedForm::~AdvancedForm()
{
    
}

RunnersForm::~RunnersForm()
{
    
}

DLLForm::~DLLForm()
{
    
}

