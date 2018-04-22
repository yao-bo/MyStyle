#ifndef DEMO_H
#define DEMO_H

#include <QWidget>
#include <QDialog>
#include <QPalette>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QTableWidget>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QProgressBar>
#include <QDial>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollBar>
#include <QTimer>

class Demo : public QDialog
{
    Q_OBJECT
public:
    Demo(QWidget *parent = 0);
    ~Demo();
private slots:
    void changeStyle(const QString &styleName);
    void changePalette();
    void advanceProgressBar();
private:
    void createTopLeftGroupBox();
    void createTopRightGroupBox();
    void createBottomLeftTabWidget();
    void createBottomRightGroupBox();
    void createProgressBar();

    QPalette originalPalette;
    QLabel *styleLabel;
    QComboBox *styleComboBox;
    QCheckBox *useStylePaletteCheckBox;
    QCheckBox *disableWidgetsCheckBox;

    QGroupBox *topLeftGroupBox;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QCheckBox *checkBox;

    QGroupBox *topRightGroupBox;
    QPushButton *defaultPushButton;
    QPushButton *togglePushButton;
    QPushButton *flatPushButton;

    QTabWidget *bottomLeftTabWidget;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;

    QGroupBox *bottomRightGroupBox;
    QLineEdit *lineEdit;
    QSpinBox *spinBox;
    QDateTimeEdit *dateTimeEdit;
    QSlider *slider;
    QScrollBar *scrollBar;
    QDial *dial;

    QProgressBar *progressBar;

};

#endif // DEMO_H
