# MedGen

## Overview
The Health Data Analysis application is a powerful tool designed to assist medical professionals and health data analysts in understanding and interpreting health metrics. Utilizing the robust capabilities of the C++ language and the Qt framework, along with advanced machine learning techniques provided by Python's scikit-learn library, this app offers insightful data analysis, predictive modeling, and clear visualizations.

## Features
- **Data Generation**: Simulate patient health data including heart rate, blood pressure, and glucose levels.
- **CSV Export**: Export generated data to CSV files for easy sharing and further analysis.
- **Health Data Overview**: View an organized summary of patient health data directly in the UI.
- **Machine Learning Integration**: Leverage machine learning to identify patterns and predict health outcomes.
- **Data Visualization**: Generate confusion matrices and other charts to visualize the analysis results.
- **Cross-validation**: Validate the machine learning model's performance with Stratified K-Fold cross-validation.

## Installation
To get started with the Health Data Analysis app, clone this repository to your local machine using the following command:

Ensure you have the following prerequisites installed:
- Qt (5.15 or later recommended)
- Python (3.8 or later recommended)
- Required Python libraries: `pandas`, `scikit-learn`, `matplotlib`, `seaborn`

## Usage
After installing the necessary dependencies, compile the application using Qt Creator or your preferred C++ IDE.

Run the application, and use the GUI to generate new patient data, save to CSV, or perform data analysis. For machine learning features, ensure the Python environment is correctly set up with all dependencies installed.

## Machine Learning Pipeline
The app incorporates a sophisticated machine learning pipeline that includes:

- Data preprocessing with scaling and normalization
- Hyperparameter tuning with RandomizedSearchCV
- Model evaluation with ROC AUC and confusion matrices

## Contributing
Contributions to the Health Data Analysis app are welcome! Please feel free to submit pull requests or open issues to suggest enhancements or report bugs.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE) file for details.

## Contact
For any questions or comments, please feel free to reach out to the repository owner.

---

**Note**: This application is intended for educational and research purposes and should not be used as a substitute for professional medical advice, diagnosis, or treatment.
