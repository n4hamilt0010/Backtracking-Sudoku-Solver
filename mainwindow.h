#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include "include.h"

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
    void on_pb00_1_clicked();
    void on_pb00_2_clicked();
    void on_pb00_3_clicked();
    void on_pb00_4_clicked();
    void on_pb00_5_clicked();
    void on_pb00_6_clicked();
    void on_pb00_7_clicked();
    void on_pb00_8_clicked();
    void on_pb00_9_clicked();
    void on_table_cellClicked(int row, int column);

    void on_solve_clicked();

    bool sudoku_solver_wrapper(int curr_row, int curr_col);

    void on_New_Board_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int Column, Row;
    void click__on_pb(int num);
};

#endif // MAINWINDOW_H
