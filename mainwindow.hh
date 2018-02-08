#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void calculate_bodymassindex();
    void reset_values();
    void update_gender_male();
    void update_gender_female();
    void update_interpretation();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HH
