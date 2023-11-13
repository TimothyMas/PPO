import pandas as pd
from sklearn.model_selection import train_test_split, RandomizedSearchCV, StratifiedKFold, cross_val_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, roc_auc_score
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import randint
import sys

def save_confusion_matrix(cm, class_names, filename='confusion_matrix.png', figsize=(10, 7), fontsize=14):
    """Saves a confusion matrix as returned by sklearn.metrics.confusion_matrix as a heatmap."""
    df_cm = pd.DataFrame(cm, index=class_names, columns=class_names)
    fig = plt.figure(figsize=figsize)
    try:
        heatmap = sns.heatmap(df_cm, annot=True, fmt="d", cmap='viridis', cbar_kws={'label': 'Scale'})
    except ValueError:
        raise ValueError("Confusion matrix values must be integers.")
    heatmap.yaxis.set_ticklabels(heatmap.yaxis.get_ticklabels(), rotation=0, ha='right', fontsize=fontsize)
    heatmap.xaxis.set_ticklabels(heatmap.xaxis.get_ticklabels(), rotation=0, ha='right', fontsize=fontsize)
    plt.ylabel('True label')
    plt.xlabel('Predicted label')

    # Save the confusion matrix to a file
    plt.savefig(filename)
    plt.close(fig)

def machine_learning(csv_file):
    # Load the CSV data into a pandas DataFrame
    data = pd.read_csv(csv_file)

    # Prepare the feature matrix (X) and the target vector (y)
    X = data[['Heart Rate', 'Systolic BP', 'Diastolic BP', 'Glucose Level']]
    y = data['Heart Rate Label']  # Replace with your target column

    # Scaling the features
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    # Initialize the classifier
    clf = RandomForestClassifier(random_state=42)

    # Define a parameter grid to search over
    param_dist = {
        'n_estimators': randint(100, 500),
        'max_depth': randint(3, 10),
        'min_samples_split': randint(2, 11),
        'min_samples_leaf': randint(1, 5),
        'max_features': ['sqrt', 'log2'],
        'bootstrap': [True, False]
    }

    # Stratified K-Fold for cross-validation
    strat_k_fold = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)

    # Run randomized search
    random_search = RandomizedSearchCV(
        clf, param_distributions=param_dist, n_iter=100, cv=strat_k_fold,
        scoring='roc_auc', n_jobs=-1, random_state=42, verbose=2
    )

    # Fit the randomized search model
    random_search.fit(X_scaled, y)

    # Best model
    best_clf = random_search.best_estimator_

    # Perform cross-validation
    cross_val_scores = cross_val_score(best_clf, X_scaled, y, cv=strat_k_fold, scoring='roc_auc')

    # Print out the cross-validation scores
    print(f'Cross-validated ROC AUC scores: {cross_val_scores}')
    print(f'Mean ROC AUC score: {cross_val_scores.mean()}')

    # Split the data for evaluation
    X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, stratify=y, test_size=0.2, random_state=42)

    # Train and evaluate the best model
    best_clf.fit(X_train, y_train)
    y_pred = best_clf.predict(X_test)
    y_pred_proba = best_clf.predict_proba(X_test)[:, 1]

    # Compute ROC AUC
    roc_auc = roc_auc_score(y_test, y_pred_proba)

    # Generate the classification report
    print(classification_report(y_test, y_pred))

    # Compute and print the confusion matrix
    cm = confusion_matrix(y_test, y_pred)
    class_names = ['Healthy', 'Unhealthy']
    save_confusion_matrix(cm, class_names, filename='confusion_matrix.png')

    # Print ROC AUC
    print(f'ROC AUC: {roc_auc}')

if __name__ == "__main__":
    if len(sys.argv) > 1:
        csv_file_path = sys.argv[1]
        machine_learning(csv_file_path)
    else:
        print("Please provide the path to the CSV file as an argument.")
