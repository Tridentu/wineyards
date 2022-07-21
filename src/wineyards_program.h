#pragma once

#include <QWidget>
#include "wineyard_struct.h"


namespace Ui {
  class WineYardsProgramEntry;  
};

class WineyardsProgramEntry : public QWidget {
  
public:
    WineyardsProgramEntry(QWidget* parent, WineYard* yard);
    ~WineyardsProgramEntry();
public:
    void setProgramTitle(const QString& title);
    void setProgramName(const QString& name);
private:
    void runProg();
    void runProgTerm();

    void stopProg();
private:
    QScopedPointer<Ui::WineYardsProgramEntry> m_Ui;
    QString m_Name;
    QString m_Title;
    WineYard* m_Yard;
};
