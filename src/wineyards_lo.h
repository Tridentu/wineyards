#pragma once

#include <QDialog>
#include "wineyard_struct.h"
#include <QScopedPointer>


namespace Ui {
    class WineyardsLaunchOptionsDialog;
}

class WineyardsLODialog : public QDialog {
public:
    WineyardsLODialog(QWidget* parent, WineYard* yard);
private:
    WineYard* m_Yard;
    QScopedPointer<Ui::WineyardsLaunchOptionsDialog> m_Ui;
};
