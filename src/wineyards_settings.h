
#pragma once

#include <KConfigDialog>
#include <QWidget>
#include "wineyardssettings.h"
#include <QScopedPointer>
#include <KEditListWidget>

namespace Ui {
    class GeneralForm;
    class AdvancedForm;
    class RunnersForm;
    class DLLForm;
}

class GeneralForm : public QWidget {
public:
    GeneralForm(QWidget* parent);
    ~GeneralForm();
private:
    QScopedPointer<Ui::GeneralForm> m_Ui;
};

class AdvancedForm : public QWidget {
public:
    AdvancedForm(QWidget* parent);
    ~AdvancedForm();
private:
    QScopedPointer<Ui::AdvancedForm> m_Ui;
};

class RunnersForm : public QWidget {
public:
    RunnersForm(QWidget* parent);
    ~RunnersForm();
    KEditListWidget* getRunnersListWidget();
private:
    QScopedPointer<Ui::RunnersForm> m_Ui;
};

class DLLForm : public QWidget {
public:
    DLLForm(QWidget* parent);
    void openDXVKTab();
    void openVKD3DTab();
    void openDXVKNVAPITab();
    void openLatencyFleXTab();
    ~DLLForm();
private:
    QScopedPointer<Ui::DLLForm> m_Ui;
};


class WineyardsSettingsWindow : public KConfigDialog {
public:
    WineyardsSettingsWindow(QWidget* parent);
    ~WineyardsSettingsWindow();
public:
    void OpenPage(uint pageNumber);
    void OpenDLLDXVKTab();
    void OpenDLLVKD3DTab();
    void OpenDLLDXVKNVAPITab();
    void OpenLatencyFleXTab();

private:
    WineyardsSettings* m_Config;
    RunnersForm* m_Runners;
    DLLForm* m_DLLForm;
    QList<KPageWidgetItem*> pages;
};
