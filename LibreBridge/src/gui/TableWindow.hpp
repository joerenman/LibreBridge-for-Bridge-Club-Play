#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>
#include <QObject>
#include <QDialog>
class QPushButton;
class QComboBox;
class QGroupBox;
class QLabel;



class TableWindow : public QDialog
{
    Q_OBJECT

public:
    

explicit TableWindow(QWidget *parent = Q_NULLPTR);
     QPushButton *practiceButton;
     QPushButton *seatStatusButton;
public  slots:
     void T1NChanged(int index);
     void T1EChanged(int index);
     void T1SChanged(int index);
     void T1WChanged(int index);
     void T2NChanged(int index);
     void T2EChanged(int index);
     void T2SChanged(int index);
     void T2WChanged(int index);
     void T3NChanged(int index);
     void T3EChanged(int index);
     void T3SChanged(int index);
     void T3WChanged(int index);
     void T4NChanged(int index);
     void T4EChanged(int index);
     void T4SChanged(int index);
     void T4WChanged(int index);
     void seatingStatusChanged(QString);
     void provideSeatingStatus();
     void requestSeatingStatus();
     void startPracticeGame();
     void hideChatWindow();
      void PlayGame();

signals:
     void openPlayWindow();
     void changeChatWindow();
private:
    QGroupBox *table1;
    QLabel *t1Label;
    QComboBox *T1NBox;
    QComboBox *T1EBox;
    QComboBox *T1SBox;
    QComboBox *T1WBox;

    QGroupBox *table2;
    QLabel *t2Label;
    QComboBox *T2NBox;
    QComboBox *T2EBox;
    QComboBox *T2SBox;
    QComboBox *T2WBox;
    QGroupBox *table3;
    QLabel *t3Label;
    QComboBox *T3NBox;
    QComboBox *T3EBox;
    QComboBox *T3SBox;
    QComboBox *T3WBox;
    QGroupBox *table4;
    QLabel *t4Label;
    QComboBox *T4NBox;
    QComboBox *T4EBox;
    QComboBox *T4SBox;
    QComboBox *T4WBox;


    QWidget *centralWidget;


};
#endif // TABLEWINDOW_H
