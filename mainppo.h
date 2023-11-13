#ifndef MAINPPO_H
#define MAINPPO_H

// Include the PatientProfile header here
#include "patientprofile.h"

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <string>

namespace Ui

{
class MainPPO;
}

class MainPPO : public QMainWindow

{
    Q_OBJECT

public:

    explicit MainPPO(QWidget *parent = nullptr);
    ~MainPPO();

private slots:

    void on_generateDataButton_clicked();
    void on_saveToCSVButton_clicked();
    void calculateAverageValues();
    void calculateMaxMinValues();
    void healthOverview();
    void on_LoadData_clicked();
    void switchTheme();
    void selectDefaultDirectory();
    void on_actionExit_triggered();
    void on_analyzeDataButton_clicked();
    void on_actionSet_Default_Directory_triggered();

private:
    Ui::MainPPO *ui;
    bool isDarkMode = false;  // To keep track of the current theme
    QString loadStyleSheet(const QString &styleSheetFile);  // Load QSS files
    QPushButton *themeSwitchButton;
    void updateThemeButtonIcon();
    QString defaultDirectory;
    std::vector<std::vector<QString>> patientDataForCSV;
    std::vector<PatientProfile> profiles;
};

#endif // MAINPPO_H
