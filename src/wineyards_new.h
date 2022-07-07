
#pragma once

#include <QDialog>
#include "wineyard_struct.h"


namespace Ui {
    class NewWineYardDialog;
}

class NewWineYardDialog : public QDialog {
public:
    NewWineYardDialog(QWidget* parent);
    ~NewWineYardDialog();
private:
    void createWineyard(bool checked = false);
    void setName(const QString& newName);
    void setYardType(const QString& newType);
    void setRunner(const QString& newRunner);
    void setVersioningEnabled(bool enabled);
    QScopedPointer<Ui::NewWineYardDialog> m_ui;
    WineYard* m_Yard;
};
