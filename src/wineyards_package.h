#pragma once


#include <QWidget>
#include <caravel/CaravelDBContext.h>



namespace Ui {
 class PackageEntry;   
}

class WineyardsPackageUI : public QWidget {
public:
    WineyardsPackageUI(QWidget* parent, CaravelPM::CaravelPackageInfo info);
public:
    void Install();
public:
    static void InitDB();
private:
    Ui::PackageEntry* m_Ui;
    QString packageName;
};
