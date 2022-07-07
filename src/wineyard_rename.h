
#pragma once 

#include <QDialog>
#include <QScopedPointer>
#include <QWidget>
#include "wineyard_struct.h"

namespace Ui {
  class WineyardRenameDialog;   
}

class WineyardsRenameDialog : public QDialog {
public:
    WineyardsRenameDialog(QWidget* parent, WineYard* yard);
private:
    void renameConfirm();
private:
    QScopedPointer<Ui::WineyardRenameDialog> m_Ui;
    WineYard* m_Yard;
};



