
#pragma once

#include <QDialog>
#include "wineyard_struct.h"

namespace Ui {
   class WineyardsGamescopeDialog;  
};

class WineyardsGamescopeDialog : public QDialog {
public:
    WineyardsGamescopeDialog(QWidget* parent, WineYard* yard);
    ~WineyardsGamescopeDialog();
private:
    void setCurrentFrameRate(QString rateChoice);
    void setCurrentFrameRateNF(QString rateChoice);
    void setGameResWidth(int i);
    void setGameResHeight(int i);
    void setGameResScopeHeight(int i);
    void setGameResScopeWidth(int i);
    void save();
private:
    QScopedPointer<Ui::WineyardsGamescopeDialog> m_Ui;
    QScopedPointer<WineYard> m_Yard;
};
