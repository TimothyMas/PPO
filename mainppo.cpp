#include "mainppo.h"
#include "ui_mainppo.h"
#include "patientprofile.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <limits>

#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QIcon>
#include <QProcess>
#include <QTextStream>
#include <utility>

// Enhanced Data Generation Functions
int mockHeartRate()

{
    int chance = rand() % 100;
    if (chance < 5)       // 5% chance for athletes or very fit individuals
        return rand() % 21 + 40;  // 40 to 60 BPM
    else if (chance < 85) // 80% chance for average adults
        return rand() % 41 + 60;  // 60 to 100 BPM
    else                  // 15% chance for older adults or those with conditions
        return rand() % 21 + 100; // 100 to 120 BPM
}

std::pair<int, int> mockBloodPressure()

{
    int chance = rand() % 100;
    if (chance < 50)

    {  // 50% chance for normal BP
        return {rand() % 10 + 110, rand() % 10 + 70};  // Systolic: 110-119, Diastolic: 70-79
    }

    else if (chance < 75)

    {  // 25% chance for elevated BP
        return {rand() % 10 + 120, rand() % 10 + 80};  // Systolic: 120-129, Diastolic: 80-89
    }

    else if (chance < 90)

    {  // 15% chance for stage 1 hypertension
        return {rand() % 10 + 130, rand() % 10 + 90};  // Systolic: 130-139, Diastolic: 90-99
    }

    else

    {  // 10% chance for stage 2 hypertension
        return {rand() % 11 + 140, rand() % 11 + 100}; // Systolic: 140-150, Diastolic: 100-110
    }
}

int mockGlucoseLevel()

{
    int chance = rand() % 100;
    if (chance < 70)      // 70% chance for normal glucose level
        return rand() % 30 + 70;  // 70 to 99 mg/dL
    else if (chance < 90) // 20% chance for prediabetes
        return rand() % 26 + 100; // 100 to 125 mg/dL
    else                  // 10% chance for diabetes
        return rand() % 25 + 126; // 126 to 150 mg/dL
}

// Constants for Heart Rate
const int HR_LOWER_LIMIT_ATHLETE = 40;
const int HR_UPPER_LIMIT_ATHLETE = 60;
const int HR_LOWER_LIMIT_ADULT = 60;
const int HR_UPPER_LIMIT_ADULT = 100;

// Constants for Blood Pressure
const int BP_SYSTOLIC_NORMAL = 120;
const int BP_DIASTOLIC_NORMAL = 80;

// Constants for Glucose Level
const int GLUCOSE_NORMAL_UPPER_LIMIT = 140;

// Health Check Functions
std::pair<bool, std::string> isHeartRateHealthy(int heartRate)

{
    if ((heartRate >= HR_LOWER_LIMIT_ATHLETE && heartRate < HR_UPPER_LIMIT_ATHLETE) ||
        (heartRate >= HR_LOWER_LIMIT_ADULT && heartRate <= HR_UPPER_LIMIT_ADULT))
        return {true, "Heart rate is within the normal range."};
    else if (heartRate < HR_LOWER_LIMIT_ATHLETE)
        return {false, "Heart rate is below the normal range. Potential bradycardia."};
    else
        return {false, "Heart rate is above the normal range. Potential tachycardia."};
}

std::pair<bool, std::string> isBloodPressureHealthy(std::pair<int, int> bp)

{
    int systolic = bp.first;
    int diastolic = bp.second;

    if (systolic < BP_SYSTOLIC_NORMAL && diastolic < BP_DIASTOLIC_NORMAL)
        return {true, "Blood pressure is within the normal range."};
    else if (systolic >= BP_SYSTOLIC_NORMAL && diastolic >= BP_DIASTOLIC_NORMAL)
        return {false, "Both Systolic and Diastolic Too High"};
    else if (systolic >= BP_SYSTOLIC_NORMAL)
        return {false, "Systolic Too High"};
    else
        return {false, "Diastolic Too High"};
}

std::pair<bool, std::string> isGlucoseLevelHealthy(int glucoseLevel)

{
    if (glucoseLevel >= 70 && glucoseLevel <= GLUCOSE_NORMAL_UPPER_LIMIT)
        return {true, "Glucose level is within the normal range."};
    else if (glucoseLevel < 70)
        return {false, "Glucose level is too low."};
    else
        return {false, "Glucose level is too high."};
}

// Function to generate random patient profiles
std::vector<PatientProfile> generatePatientProfiles(int numPatients)

{
    std::vector<PatientProfile> profiles;

    for (int i = 0; i < numPatients; i++)

    {
        PatientProfile profile;
        profile.name = "Patient " + std::to_string(i + 1);
        profile.age = rand() % 60 + 20;  // Age between 20 to 80 for simplicity
        profile.gender = (rand() % 2 == 0) ? "Male" : "Female";

        // Randomly assign health issues
        if (rand() % 5 == 0)  // 20% chance for a health issue
            profile.healthIssues.push_back("Cardiac Problems");

        if (rand() % 10 == 0)  // 10% chance for another health issue
            profile.healthIssues.push_back("Diabetes");

        profiles.push_back(profile);
    }

    return profiles;
}

MainPPO::MainPPO(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPPO)
    , isDarkMode(false)  // Initialize isDarkMode to false

{
    ui->setupUi(this);
    ui->themeSwitchButton->setIconSize(QSize(40, 40));  // Initial icon size
    ui->textEdit->setAcceptRichText(true);

    this->setWindowTitle("MedGen");
    this->setWindowIcon(QIcon("C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/images/medgen.png"));

    connect(ui->themeSwitchButton, &QPushButton::clicked, this, &MainPPO::switchTheme);
    connect(ui->analyzeDataButton, &QPushButton::clicked, this, &MainPPO::on_analyzeDataButton_clicked);

    connect(ui->actionCalculateAverage, &QAction::triggered, this, &MainPPO::calculateAverageValues);
    connect(ui->actionCalculateMaxMin, &QAction::triggered, this, &MainPPO::calculateMaxMinValues);
    connect(ui->actionHealthOverview, &QAction::triggered, this, &MainPPO::healthOverview);

    connect(ui->actionStandardDeviation, &QAction::triggered, this, &MainPPO::StandardDeviation);
    connect(ui->actionVariance, &QAction::triggered, this, &MainPPO::Variance);

    srand(time(0));

    updateThemeButtonIcon();

    QMessageBox::information(this, "Welcome to MedGen", "Hello! Welcome to MedGen. If you want to use this application correctly you must first generate data and save it to CSV.");

    defaultDirectory = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

MainPPO::~MainPPO()

{
    delete ui;
}

QString MainPPO::loadStyleSheet(const QString &styleSheetFile)

{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (!file.isOpen())

    {
        qDebug() << "Failed to open stylesheet:" << styleSheetFile;
        return "";
    }

    QString styleSheet = QLatin1String(file.readAll());
    return styleSheet;
}

void MainPPO::on_generateDataButton_clicked()

{
    // Read the values from the spin boxes
    int NUM_PATIENTS = ui->numPatientsSpinBox->value();
    int MEASUREMENTS_PER_PATIENT = ui->numMeasurementsSpinBox->value();

    // Generate the patient profiles
    std::vector<PatientProfile> profiles = generatePatientProfiles(NUM_PATIENTS);

    QString displayText;

    for (int j = 0; j < NUM_PATIENTS; j++)

    {
        displayText += QString("Patient %1:<br><br>").arg(j + 1);

        for (int i = 0; i < MEASUREMENTS_PER_PATIENT; i++)

        {
            int heartRate = mockHeartRate();
            std::pair<int, int> bloodPressure = mockBloodPressure();
            int glucoseLevel = mockGlucoseLevel();

            // Inside the loop generate the display text:
            auto heartRateCheck = isHeartRateHealthy(heartRate);
            auto bpCheck = isBloodPressureHealthy(bloodPressure);
            auto glucoseCheck = isGlucoseLevelHealthy(glucoseLevel);

            QString heartColor = heartRateCheck.first ? "black" : "red";
            QString bpColor = bpCheck.first ? "black" : "red";
            QString glucoseColor = glucoseCheck.first ? "black" : "red";

            displayText += QString("Measurement %1:<br>").arg(i + 1);

            displayText += QString("<span style=\"color:%1;\">Heart Rate: %2 BPM - %3 %4</span><br>")
                               .arg(heartColor)
                               .arg(heartRate)
                               .arg(heartRateCheck.first ? "" : "")
                               .arg(QString::fromStdString(heartRateCheck.second));

            displayText += QString("<span style=\"color:%1;\">Blood Pressure: %2/%3 mmHg - %4 %5</span><br>")
                               .arg(bpColor)
                               .arg(bloodPressure.first)
                               .arg(bloodPressure.second)
                               .arg(bpCheck.first ? "" : "")
                               .arg(QString::fromStdString(bpCheck.second));

            displayText += QString("<span style=\"color:%1;\">Glucose Level: %2 mg/dL - %3 %4</span><br><br>")
                               .arg(glucoseColor)
                               .arg(glucoseLevel)
                               .arg(glucoseCheck.first ? "" : "")
                               .arg(QString::fromStdString(glucoseCheck.second));
        }
    }

    // Display the data in the TextEdit widget
    ui->textEdit->setHtml(displayText);

    // Define the path for the CSV file
    QString csvFilePath = "generated_data.csv";

    // Open the file for writing
    QFile file(csvFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))

    {
        QTextStream out(&file);

        // Write the CSV header
        out << "Patient Name,Age,Gender,Measurement Number,Heart Rate,Systolic BP,Diastolic BP,Glucose Level\n";

        for (int j = 0; j < NUM_PATIENTS; j++)

        {
            for (int i = 0; i < MEASUREMENTS_PER_PATIENT; i++)

            {
                int heartRate = mockHeartRate();
                std::pair<int, int> bloodPressure = mockBloodPressure();
                int glucoseLevel = mockGlucoseLevel();

                // Adjusted the format to match the header
                out << QString("%1,%2,%3,%4,%5,%6,%7,%8\n")
                           .arg(profiles[j].name.c_str())
                           .arg(profiles[j].age)
                           .arg(profiles[j].gender.c_str())
                           .arg(i + 1)
                           .arg(heartRate)
                           .arg(bloodPressure.first)
                           .arg(bloodPressure.second)
                           .arg(glucoseLevel);
            }
        }

        file.close();
    }
}

void MainPPO::on_saveToCSVButton_clicked()

{
    // Get the values from the spin boxes
    int NUM_PATIENTS = ui->numPatientsSpinBox->value();
    int MEASUREMENTS_PER_PATIENT = ui->numMeasurementsSpinBox->value();

    // Get the path and append the filename to it
    QString filePath = defaultDirectory + "/health_data.csv";

    std::ofstream file(filePath.toStdString(), std::ios::app);

    // Check if file is empty (i.e., it's a new file)
    if (file.tellp() == 0)

    {
        file << "Patient ID,Gender,Age\n";
        file << "Patient ID,Measurement,Heart Rate,Systolic BP,Diastolic BP,Glucose Level\n";
    }

    // Generate random patient profiles
    std::vector<PatientProfile> profiles = generatePatientProfiles(NUM_PATIENTS);

    for (int j = 0; j < NUM_PATIENTS; j++)

    {
        // Write gender and age from the randomly generated patient profiles to the CSV file
        file << j + 1 << ","
             << profiles[j].gender << ","
             << profiles[j].age << "\n";

        // Write the measurements
        for (int i = 0; i < MEASUREMENTS_PER_PATIENT; i++)

        {
            int heartRate = mockHeartRate();
            std::pair<int, int> bloodPressure = mockBloodPressure();
            int glucoseLevel = mockGlucoseLevel();

            file << j + 1 << ","
                 << i + 1 << ","
                 << heartRate << ","
                 << bloodPressure.first << ","
                 << bloodPressure.second << ","
                 << glucoseLevel << "\n";
        }
    }

    file.close();

    QMessageBox::information(this, "Info", "Data saved to health_data.csv on your computer!");

    // The function to prepare data for machine learning
    prepareDataForMachineLearning();
}

int safe_stoi(const std::string& str, bool& success)

{
    try

    {
        success = true;
        return std::stoi(str);
    } catch (std::exception& e)

    {
        success = false;
        return 0;
    }

}

void MainPPO::on_LoadData_clicked()

{
    QString filePath = QFileDialog::getOpenFileName(this, "Open CSV File", defaultDirectory, "CSV Files (*.csv)");
    if (filePath.isEmpty())

    {
        return;  // User canceled the file dialog
    }

    std::ifstream file(filePath.toStdString());
    if (!file.is_open())

    {
        QMessageBox::warning(this, "Error", "Failed to open the selected file.");
        return;
    }

    std::map<int, std::vector<QString>> patientMeasurements;
    std::string line;

    // Skip the two header lines
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line))

    {
        std::stringstream ss(line);
        std::string value;
        bool success = false;

        // Parse Patient ID
        std::getline(ss, value, ',');
        int patientID = safe_stoi(value, success);
        if (!success) continue;

        // Parse Measurement Number
        std::getline(ss, value, ',');
        int measurementNumber = safe_stoi(value, success);
        if (!success) continue;

        // Parse Heart Rate
        std::getline(ss, value, ',');
        int heartRate = safe_stoi(value, success);
        if (!success) continue;

        // Parse Systolic Blood Pressure
        std::getline(ss, value, ',');
        int systolicBP = safe_stoi(value, success);
        if (!success) continue;

        // Parse Diastolic Blood Pressure
        std::getline(ss, value, ',');
        int diastolicBP = safe_stoi(value, success);
        if (!success) continue;

        // Parse Glucose Level
        std::getline(ss, value, ',');
        int glucoseLevel = safe_stoi(value, success);
        if (!success) continue;

        // Check healthiness
        auto heartRateCheck = isHeartRateHealthy(heartRate);
        auto bpCheck = isBloodPressureHealthy({systolicBP, diastolicBP});
        auto glucoseCheck = isGlucoseLevelHealthy(glucoseLevel);

        // Determine colors based on healthiness
        QString heartColor = heartRateCheck.first ? "black" : "red";
        QString bpColor = bpCheck.first ? "black" : "red";
        QString glucoseColor = glucoseCheck.first ? "black" : "red";

        // Construct the display text for each measurement
        QString measurementText = QString("Measurement %1:<br>").arg(measurementNumber);
        measurementText += QString("<span style=\"color:%1;\">Heart Rate: %2 BPM - %3</span><br>")
                               .arg(heartColor)
                               .arg(heartRate)
                               .arg(heartRateCheck.second.c_str());
        measurementText += QString("<span style=\"color:%1;\">Blood Pressure: %2/%3 mmHg - %4</span><br>")
                               .arg(bpColor)
                               .arg(systolicBP)
                               .arg(diastolicBP)
                               .arg(bpCheck.second.c_str());
        measurementText += QString("<span style=\"color:%1;\">Glucose Level: %2 mg/dL - %3</span><br><br>")
                               .arg(glucoseColor)
                               .arg(glucoseLevel)
                               .arg(glucoseCheck.second.c_str());

        patientMeasurements[patientID].push_back(measurementText);
    }

    file.close();

    // Construct the final display text
    QString displayText;
    for (const auto& [patientID, measurements] : patientMeasurements)

    {
        displayText += QString("Patient %1:<br>").arg(patientID);
        for (const QString& measurementText : measurements)

        {
            displayText += measurementText;
        }
    }

    // Display the loaded data in the TextEdit widget
    ui->textEdit->setHtml(displayText);
}

void MainPPO::on_analyzeDataButton_clicked()

{
    // Path to the Python executable
    QString pythonExe = "D:/Python/python.exe";

    // Path to the Python script
    QString pythonScript = "C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/data_analysis.py";

    // Path to the CSV file
    QString csvFilePath = defaultDirectory + "/health_data.csv";

    // Run the Python script using QProcess
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, [=]()

            {
                qDebug() << process->readAllStandardOutput();
            });

    connect(process, &QProcess::readyReadStandardError, [=]()

            {
                qDebug() << process->readAllStandardError();
            });

    connect(process, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred), [=](QProcess::ProcessError error)

            {
                qDebug() << "Error occurred:" << error;
            });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus)

            {
                if(exitStatus == QProcess::CrashExit)

                {
                    qDebug() << "Python script crashed!";
                } else

                {
                    qDebug() << "Python script finished with exit code:" << exitCode;
                }

                process->deleteLater();
            });

    process->setWorkingDirectory(QFileInfo(csvFilePath).absoluteDir().absolutePath());
    process->start(pythonExe, QStringList() << pythonScript << csvFilePath);
}

// Calculate average values for heart rate, blood pressure, and glucose level
void MainPPO::calculateAverageValues()

{
    std::ifstream file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString() + "/health_data.csv");
    if (!file.is_open())

    {
        QMessageBox::warning(this, "Error", "Unable to open health_data.csv");
        return;
    }

    std::string line;
    int totalHeartRate = 0, totalSystolicBP = 0, totalDiastolicBP = 0, totalGlucoseLevel = 0;
    int count = 0;

    std::getline(file, line);  // Skip initial header line
    while (std::getline(file, line))

    {
        std::stringstream ss(line);
        std::string patientID, measurement;

        std::getline(ss, patientID, ',');
        std::getline(ss, measurement, ',');

        // Check if the line contains measurement data
        if (isdigit(measurement[0]))

        {
            std::string value;

            try {
                std::getline(ss, value, ',');  // Heart Rate
                totalHeartRate += std::stoi(value);

                std::getline(ss, value, ',');  // Systolic BP
                totalSystolicBP += std::stoi(value);

                std::getline(ss, value, ',');  // Diastolic BP
                totalDiastolicBP += std::stoi(value);

                std::getline(ss, value, ',');  // Glucose Level
                totalGlucoseLevel += std::stoi(value);

                count++;
            }

            catch (const std::exception& e)

            {
                QMessageBox::warning(this, "Error", QString("Invalid data format in file. Problematic line: %1").arg(QString::fromStdString(line)));
                return;
            }
        }
    }

    file.close();

    if (count == 0)

    {
        QMessageBox::warning(this, "Error", "No measurement data available to calculate averages.");
        return;
    }

    QString message = QString("Average Heart Rate: %1 BPM\nAverage Systolic BP: %2 mmHg\nAverage Diastolic BP: %3 mmHg\nAverage Glucose Level: %4 mg/dL")
                          .arg(totalHeartRate / count)
                          .arg(totalSystolicBP / count)
                          .arg(totalDiastolicBP / count)
                          .arg(totalGlucoseLevel / count);

    QMessageBox::information(this, "Average Values", message);
}

// Calculate max and min values for heart rate, blood pressure, and glucose level
void MainPPO::calculateMaxMinValues()

{
    std::ifstream file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString() + "/health_data.csv");
    if (!file.is_open())

    {
        QMessageBox::warning(this, "Error", "Unable to open health_data.csv");
        return;
    }

    std::string line;

    int maxHeartRate = std::numeric_limits<int>::min(), minHeartRate = std::numeric_limits<int>::max();
    int maxSystolicBP = std::numeric_limits<int>::min(), minSystolicBP = std::numeric_limits<int>::max();
    int maxDiastolicBP = std::numeric_limits<int>::min(), minDiastolicBP = std::numeric_limits<int>::max();
    int maxGlucoseLevel = std::numeric_limits<int>::min(), minGlucoseLevel = std::numeric_limits<int>::max();

    std::getline(file, line);  // Skip initial header line
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string patientID, measurement;

        std::getline(ss, patientID, ',');
        std::getline(ss, measurement, ',');

        // Check if the line contains measurement data
        if (isdigit(measurement[0]))

        {
            std::string value;

            try

            {
                std::getline(ss, value, ',');  // Heart Rate
                int heartRate = std::stoi(value);
                maxHeartRate = std::max(maxHeartRate, heartRate);
                minHeartRate = std::min(minHeartRate, heartRate);

                std::getline(ss, value, ',');  // Systolic BP
                int systolicBP = std::stoi(value);
                maxSystolicBP = std::max(maxSystolicBP, systolicBP);
                minSystolicBP = std::min(minSystolicBP, systolicBP);

                std::getline(ss, value, ',');  // Diastolic BP
                int diastolicBP = std::stoi(value);
                maxDiastolicBP = std::max(maxDiastolicBP, diastolicBP);
                minDiastolicBP = std::min(minDiastolicBP, diastolicBP);

                std::getline(ss, value, ',');  // Glucose Level
                int glucoseLevel = std::stoi(value);
                maxGlucoseLevel = std::max(maxGlucoseLevel, glucoseLevel);
                minGlucoseLevel = std::min(minGlucoseLevel, glucoseLevel);
            } catch (const std::exception& e)

            {
                QMessageBox::warning(this, "Error", QString("Invalid data format in file. Problematic line: %1").arg(QString::fromStdString(line)));
                return;
            }
        }
    }

    file.close();

    QString message = QString("Max Heart Rate: %1 BPM\nMin Heart Rate: %2 BPM\nMax Systolic BP: %3 mmHg\nMin Systolic BP: %4 mmHg\nMax Diastolic BP: %5 mmHg\nMin Diastolic BP: %6 mmHg\nMax Glucose Level: %7 mg/dL\nMin Glucose Level: %8 mg/dL")
                          .arg(maxHeartRate)
                          .arg(minHeartRate)
                          .arg(maxSystolicBP)
                          .arg(minSystolicBP)
                          .arg(maxDiastolicBP)
                          .arg(minDiastolicBP)
                          .arg(maxGlucoseLevel)
                          .arg(minGlucoseLevel);

    QMessageBox::information(this, "Max/Min Values", message);
}

// Provide a health overview based on the data
void MainPPO::healthOverview()

{
    std::ifstream file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString() + "/health_data.csv");
    if (!file.is_open())

    {
        QMessageBox::warning(this, "Error", "Unable to open health_data.csv");
        return;
    }

    std::string line;
    int unhealthyHeartRateCount = 0, unhealthyBPCount = 0, unhealthyGlucoseCount = 0;

    std::getline(file, line);  // Skip initial header line
    while (std::getline(file, line))

    {
        std::stringstream ss(line);
        std::string patientID, measurement;

        std::getline(ss, patientID, ',');
        std::getline(ss, measurement, ',');

        // Check if the line contains measurement data
        if (isdigit(measurement[0]))

        {
            std::string value;

            try

            {
                std::getline(ss, value, ',');  // Heart Rate
                int heartRate = std::stoi(value);
                if (!isHeartRateHealthy(heartRate).first)

                {
                    unhealthyHeartRateCount++;
                }

                std::getline(ss, value, ',');  // Systolic BP
                int systolicBP = std::stoi(value);
                std::getline(ss, value, ',');  // Diastolic BP
                int diastolicBP = std::stoi(value);
                if (!isBloodPressureHealthy({systolicBP, diastolicBP}).first)

                {
                    unhealthyBPCount++;
                }

                std::getline(ss, value, ',');  // Glucose Level
                int glucoseLevel = std::stoi(value);
                if (!isGlucoseLevelHealthy(glucoseLevel).first)

                {
                    unhealthyGlucoseCount++;
                }

            }

            catch (const std::exception& e)

            {
                QMessageBox::warning(this, "Error", QString("Invalid data format in file. Problematic line: %1").arg(QString::fromStdString(line)));
                return;
            }
        }
    }

    file.close();

    QString message = QString("Number of Unhealthy Heart Rate Readings: %1\nNumber of Unhealthy Blood Pressure Readings: %2\nNumber of Unhealthy Glucose Level Readings: %3")
                          .arg(unhealthyHeartRateCount)
                          .arg(unhealthyBPCount)
                          .arg(unhealthyGlucoseCount);

    QMessageBox::information(this, "Health Overview", message);
}


double calculateVariance(const std::vector<int>& values)

{
    if (values.empty()) return 0.0;
    double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    double variance = std::accumulate(values.begin(), values.end(), 0.0,
                                      [mean](double acc, int val) { return acc + (val - mean) * (val - mean); });
    return variance / values.size();
}

double calculateStandardDeviation(const std::vector<int>& values)

{
    return std::sqrt(calculateVariance(values));
}

void MainPPO::StandardDeviation()

{
    qDebug() << "Entering StandardDeviation function";

    QString filePath = defaultDirectory + "/health_data.csv";
    std::ifstream file(filePath.toStdString());
    if (!file.is_open()) {
        QMessageBox::critical(this, "Error", "Unable to open the file.");
        return;
    }

    std::string line;
    std::getline(file, line); // Skip first header line
    std::getline(file, line); // Skip second header line

    std::vector<int> heartRates, systolicBPs, diastolicBPs, glucoseLevels;

    // Now start reading the actual data, which starts from the third line
    while (std::getline(file, line))

    {
        std::stringstream ss(line);
        std::string value;

        // Skip the Patient ID and Measurement columns, which are the first two columns
        std::getline(ss, value, ','); // Patient ID
        std::getline(ss, value, ','); // Measurement

        try

        {
            // Now read the numeric values
            std::getline(ss, value, ','); // Heart Rate
            heartRates.push_back(std::stoi(value));
            std::getline(ss, value, ','); // Systolic BP
            systolicBPs.push_back(std::stoi(value));
            std::getline(ss, value, ','); // Diastolic BP
            diastolicBPs.push_back(std::stoi(value));
            std::getline(ss, value, ','); // Glucose Level
            glucoseLevels.push_back(std::stoi(value));
        } catch (const std::invalid_argument& e)

        {
            QMessageBox::warning(this, "Parse Error", "Invalid argument encountered when parsing data.");
            file.close();
            return;
        } catch (const std::out_of_range& e)

        {
            QMessageBox::warning(this, "Parse Error", "Value out of range encountered when parsing data.");
            file.close();
            return;
        }
    }

    file.close();

    QString stdDevMessage = QString("Standard Deviation - Heart Rate: %1, Systolic BP: %2, Diastolic BP: %3, Glucose Level: %4")
                                .arg(calculateStandardDeviation(heartRates))
                                .arg(calculateStandardDeviation(systolicBPs))
                                .arg(calculateStandardDeviation(diastolicBPs))
                                .arg(calculateStandardDeviation(glucoseLevels));

    QMessageBox::information(this, "Standard Deviation of Measurements", stdDevMessage);
}

void MainPPO::Variance()

{
    qDebug() << "Entering Variance function";

    QString filePath = defaultDirectory + "/health_data.csv";
    std::ifstream file(filePath.toStdString());
    if (!file.is_open())

    {
        QMessageBox::critical(this, "Error", "Unable to open the file.");
        return;
    }

    std::string line;
    // Skip the two header lines
    std::getline(file, line);
    std::getline(file, line);

    std::vector<int> heartRates, systolicBPs, diastolicBPs, glucoseLevels;

    while (std::getline(file, line))

    {
        std::stringstream ss(line);
        std::string value;

        // Skip Patient ID and Measurement columns
        std::getline(ss, value, ',');
        std::getline(ss, value, ',');

        try

        {
            // Heart Rate
            std::getline(ss, value, ',');
            heartRates.push_back(std::stoi(value));
            // Systolic BP
            std::getline(ss, value, ',');
            systolicBPs.push_back(std::stoi(value));
            // Diastolic BP
            std::getline(ss, value, ',');
            diastolicBPs.push_back(std::stoi(value));
            // Glucose Level
            std::getline(ss, value, ',');
            glucoseLevels.push_back(std::stoi(value));
        } catch (const std::invalid_argument& e)

        {
            QMessageBox::warning(this, "Parse Error", "Invalid argument encountered when parsing data.");
            file.close();
            return;
        } catch (const std::out_of_range& e)

        {
            QMessageBox::warning(this, "Parse Error", "Value out of range encountered when parsing data.");
            file.close();
            return;
        }
    }
    file.close();

    QString varianceMessage = QString("Variance - Heart Rate: %1, Systolic BP: %2, Diastolic BP: %3, Glucose Level: %4")
                                  .arg(calculateVariance(heartRates))
                                  .arg(calculateVariance(systolicBPs))
                                  .arg(calculateVariance(diastolicBPs))
                                  .arg(calculateVariance(glucoseLevels));

    QMessageBox::information(this, "Variance of Measurements", varianceMessage);
    qDebug() << "Exiting Variance function";
}

void MainPPO::on_actionExit_triggered()

{
    QMessageBox::information(this, "Goodbye", "Thank you for using MedGen application. Have a great day!");
    qApp->quit();
}

void MainPPO::selectDefaultDirectory()

{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Default Directory"), defaultDirectory);
    if (!dir.isEmpty())

    {
        defaultDirectory = dir;
        QMessageBox::information(this, "Info", "Default Directory set to: " + defaultDirectory);
    }
}

void MainPPO::updateThemeButtonIcon()

{
    if (isDarkMode)

    {
        ui->themeSwitchButton->setIcon(QIcon(":/darkmode_icon.png"));
    }

    else

    {
        ui->themeSwitchButton->setIcon(QIcon(":/lightmode_icon.png"));
    }
}

void MainPPO::on_actionSet_Default_Directory_triggered()

{
    selectDefaultDirectory();
}

void MainPPO::switchTheme()

{
    if (isDarkMode)

    {
        // Switch to light mode
        qApp->setStyleSheet(loadStyleSheet("C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/theme/lightmode.qss"));
        ui->themeSwitchButton->setIcon(QIcon("C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/images/lightmode_icon.png"));
        //ui->themeSwitchButton->setIconSize(QSize(40, 40));  // Set the icon size to 40x40 pixels (adjust)
        ui->themeSwitchButton->setText("");  // Remove the button text

        isDarkMode = false;

    }

    else

    {
        // Switch to dark mode
        qApp->setStyleSheet(loadStyleSheet("C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/theme/darkmode.qss"));
        ui->themeSwitchButton->setIcon(QIcon("C:/Users/tymek/OneDrive/Pulpit/Studia/Programowanie/C++/Projekt na PPO/ProjektPPO/images/darkmode_icon.png"));
        //ui->themeSwitchButton->setIconSize(QSize(40, 40));  // Set the icon size to 40x40 pixels (adjust)
        ui->themeSwitchButton->setText("");  // Remove the button text

        isDarkMode = true;
    }

    qDebug() << "Current theme mode (after switch):" << (isDarkMode ? "Dark" : "Light");
}

void MainPPO::prepareDataForMachineLearning()

{
    // Use the default directory to locate the health_data.csv
    QString inputFilePath = defaultDirectory + "/health_data.csv";

    // Open the input file
    std::ifstream inputFile(inputFilePath.toStdString());
    if (!inputFile.is_open())

    {
        QMessageBox::warning(this, "Error", "Failed to open the input file.");
        return;
    }

    // Create the output file path for machine learning data
    QString outputFilePath = defaultDirectory + "/machine_learning_data.csv";

    // Open the output file
    std::ofstream outputFile(outputFilePath.toStdString());
    if (!outputFile.is_open())

    {
        QMessageBox::warning(this, "Error", "Failed to open the output file for writing.");
        inputFile.close();  // Make sure to close the input file before returning
        return;
    }

    std::string line;

    // Skip the two header lines in the input file
    std::getline(inputFile, line);
    std::getline(inputFile, line);

    // Write the header to the output file
    outputFile << "Patient ID,Measurement,Heart Rate,Systolic BP,Diastolic BP,Glucose Level,Heart Rate Label,Blood Pressure Label,Glucose Label\n";

    while (std::getline(inputFile, line))

    {
        std::stringstream ss(line);
        std::string value;
        bool success = false;

        // Parse the CSV values
        std::getline(ss, value, ','); // Patient ID
        int patientID = safe_stoi(value, success);
        if (!success) continue;

        std::getline(ss, value, ','); // Measurement Number
        int measurementNumber = safe_stoi(value, success);
        if (!success) continue;

        std::getline(ss, value, ','); // Heart Rate
        int heartRate = safe_stoi(value, success);
        if (!success) continue;

        std::getline(ss, value, ','); // Systolic Blood Pressure
        int systolicBP = safe_stoi(value, success);
        if (!success) continue;

        std::getline(ss, value, ','); // Diastolic Blood Pressure
        int diastolicBP = safe_stoi(value, success);
        if (!success) continue;

        std::getline(ss, value, ','); // Glucose Level
        int glucoseLevel = safe_stoi(value, success);
        if (!success) continue;

        // Check the healthiness of each measurement and assign labels
        int heartRateLabel = isHeartRateHealthy(heartRate).first ? 0 : 1;
        int bloodPressureLabel = isBloodPressureHealthy(std::make_pair(systolicBP, diastolicBP)).first ? 0 : 1;
        int glucoseLabel = isGlucoseLevelHealthy(glucoseLevel).first ? 0 : 1;

        // Write the data and labels to the output file
        outputFile << patientID << ","
                   << measurementNumber << ","
                   << heartRate << ","
                   << systolicBP << ","
                   << diastolicBP << ","
                   << glucoseLevel << ","
                   << heartRateLabel << ","
                   << bloodPressureLabel << ","
                   << glucoseLabel << "\n";
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    QMessageBox::information(this, "Success", "The machine learning data file has been created at: " + outputFilePath);
}
