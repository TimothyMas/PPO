import pandas as pd
import matplotlib.pyplot as plt
import math

def analyze_data(csv_file):
    # Load the CSV data into a pandas DataFrame using the second row as header
    df = pd.read_csv(csv_file, header=1)

    # Drop rows with NaN values
    df = df.dropna()

    # Unique patients
    patients = df['Patient ID'].unique()

    # Determine the number of rows and columns for the subplots
    num_patients = len(patients)
    num_cols = 3  # You can adjust this value if needed
    num_rows = math.ceil(num_patients / num_cols)

    # Plotting for each measurement type
    measurements = [
        ('Heart Rate', 'BPM', 'darkred'),
        ('BP', 'mmHg', [('Systolic BP', 'green'), ('Diastolic BP', 'red')]),
        ('Glucose Level', 'mg/dL', 'purple')
    ]

    for measurement, unit, details in measurements:
        fig, axs = plt.subplots(num_rows, num_cols, figsize=(20, 15))
        fig.suptitle(f'{measurement} Distribution for Each Patient', fontsize=20, y=1.05)

        for i, patient in enumerate(patients):
            row = i // num_cols
            col = i % num_cols

            if measurement == 'BP':
                # Split the subplot into two for Systolic and Diastolic BP
                ax1 = axs[row, col].twinx()
                ax1.hist(df[df['Patient ID'] == patient][details[1][0]], bins=20, color=details[1][1], edgecolor='black', alpha=0.5, label=details[1][0])
                ax1.set_ylabel(details[1][0], fontsize=14)
                ax1.legend(loc="upper left", fontsize=12)

                axs[row, col].hist(df[df['Patient ID'] == patient][details[0][0]], bins=20, color=details[0][1], edgecolor='black', alpha=0.5, label=details[0][0])
                axs[row, col].legend(loc="upper right", fontsize=12)
            else:
                axs[row, col].hist(df[df['Patient ID'] == patient][measurement], bins=20, color=details, edgecolor='black', label=measurement)
                axs[row, col].legend(loc="upper right", fontsize=12)

            axs[row, col].set_title(f'Patient {patient}', fontsize=16)
            axs[row, col].set_xlabel(f'{measurement} ({unit})', fontsize=14)
            axs[row, col].set_ylabel('Frequency', fontsize=14)
            axs[row, col].grid(True, which='both', linestyle='--', linewidth=0.5)

        plt.tight_layout()
        plt.subplots_adjust(top=0.95, hspace=0.3)
        #plt.savefig(f"{measurement.replace(' ', '_').lower()}_distribution.png")
        plt.show()

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        csv_file_path = sys.argv[1]
        analyze_data(csv_file_path)
    else:
        print("Please provide the path to the CSV file as an argument.")
