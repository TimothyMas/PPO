#ifndef PATIENTPROFILE_H
#define PATIENTPROFILE_H

#include <string>
#include <vector>

struct PatientProfile

{
    int id; // Add an ID for each patient profile
    int age;
    std::string gender;
    std::vector<std::string> healthIssues;
    std::string name;

    struct Measurement

    {
        int id;
        int heartRate;
        std::pair<int, int> bloodPressure;
        int glucoseLevel;
        // Add more attributes here if needed
    };

    std::vector<Measurement> measurements;
};

#endif // PATIENTPROFILE_H
