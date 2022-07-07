#pragma once

#include <QWidget>


namespace Ui {
  class WineYardsProgramEntry;  
};

class WineyardsProgramEntry : public QWidget {
  
public:
    WineyardsProgramEntry(QWidget* parent);
    ~WineyardsProgramEntry();
public:
    void setProgramTitle(const QString& title);
    void setProgramName(const QString& name);
private:
    QScopedPointer<Ui::WineYardsProgramEntry> m_Ui;
    QString m_Name;
    QString m_Title;
};
