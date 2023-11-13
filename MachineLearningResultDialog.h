// MachineLearningResultDialog.h

#ifndef MACHINELEARNINGRESULTDIALOG_H
#define MACHINELEARNINGRESULTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>

class MachineLearningResultDialog : public QDialog {
    Q_OBJECT

public:
    explicit MachineLearningResultDialog(QWidget *parent = nullptr) : QDialog(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        resultTextEdit = new QTextEdit(this);
        resultTextEdit->setReadOnly(true);
        layout->addWidget(resultTextEdit);
    }

    void setResultText(const QString &text) {
        resultTextEdit->setText(text);
    }

private:
    QTextEdit *resultTextEdit;
};

#endif // MACHINELEARNINGRESULTDIALOG_H
