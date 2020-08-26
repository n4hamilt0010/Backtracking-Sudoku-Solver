#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backtracking_solver.h"
#include <unistd.h>
#include <cstdbool>
#include <stdlib.h>

sudoku::matrix matx;

#define DIM 9
#define BOX_DIM 3

struct coordinate{
  int row;
  int column;
};

const struct coordinate GRID_FULL = {DIM, DIM};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    matx.new_puzzle();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            QTableWidgetItem* Cell = ui->table->item(i, j);
            QString str = "";
            str += '0' + matx.read(i, j);
            const QString cstr = str;
            QFont font;
            font.setBold(true);
            if (matx.read(i, j))
            {
                Cell->setText(cstr);
                Cell->setFont(font);
                QColor c(122,122,235);
                Cell->setBackgroundColor(c);
            } else{
                Cell->setText("");
            }
        }
    }
    ui->label->setText("sudoku!!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_table_cellClicked(int row, int column)
{
    Row = row;
    Column = column;
    QString str = "";
    str += '0' + row;
    str += ',';
    str += '0' + column;
    const QString cstr = str;
    ui->label->setText(cstr);
}

void MainWindow::click__on_pb(int num)
{
    QTableWidgetItem* Cell = ui->table->item(Row, Column);
    matx.write(Row, Column, num);
    QString str = "";
    str += '0' + matx.read(Row, Column);
    const QString cstr = str;
    Cell->setText(cstr);
    if (matx.you_win())
    {
        ui->label->setText("you win!!");
    }
}

void MainWindow::on_pb00_1_clicked()
{
   click__on_pb(1);
}

void MainWindow::on_pb00_2_clicked()
{
    click__on_pb(2);
}

void MainWindow::on_pb00_3_clicked()
{
    click__on_pb(3);
}

void MainWindow::on_pb00_4_clicked()
{
    click__on_pb(4);
}

void MainWindow::on_pb00_5_clicked()
{
    click__on_pb(5);
}

void MainWindow::on_pb00_6_clicked()
{
    click__on_pb(6);
}

void MainWindow::on_pb00_7_clicked()
{
    click__on_pb(7);
}

void MainWindow::on_pb00_8_clicked()
{
    click__on_pb(8);
}

void MainWindow::on_pb00_9_clicked()
{
    click__on_pb(9);
}

bool MainWindow::sudoku_solver_wrapper(int curr_row, int curr_column){
  assert(matx.obj);
  assert(curr_row >= 0);
  assert(curr_row < DIM);
  assert(curr_column >= 0);
  assert(curr_column < DIM);

  struct coordinate empty_posn = get_empty_posn(matx.obj, curr_row, curr_column);

  if(coordinates_equal(empty_posn, GRID_FULL)){
    return true;
  }

  const int row = empty_posn.row;
  const int col = empty_posn.column;
  for(int num = 1; num <= DIM; ++num){
    if(is_valid(matx.obj, row, col, num)){
      matx.obj[row][col] = num;
      QTableWidgetItem* Cell = ui->table->item(row, col);
      Cell->setForeground(QBrush(QColor(Qt::red)));
      QString str = "";
      str += '0' + matx.read(row,col);
      const QString cstr = str;
      Cell->setText(cstr);
      QFont font;
      font.setBold(true);
      Cell->setFont(font);
      repaint();
      //show();
      //usleep(100);
      if(sudoku_solver_wrapper(row, col)){
        return true;
      }
      matx.obj[row][col] = 0;
      str = "";
      const QString cstr_2 = str;
      Cell->setText(cstr_2);
      repaint();
      //show();
      //usleep(100000);
    }
  }
  return false;
}

void MainWindow::on_New_Board_clicked(){
    matx.new_puzzle();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            QTableWidgetItem* Cell = ui->table->item(i, j);
            Cell->setForeground(QBrush(QColor(Qt::black)));
            QFont font;
            font.setBold(true);
            Cell->setFont(font);
            QString str = "";
            str += '0' + matx.read(i, j);
            const QString cstr = str;
            if (matx.read(i, j))
            {
                Cell->setText(cstr);
                QColor c(122,122,235);
                Cell->setBackgroundColor(c);
            }
            else
            {
                Cell->setText("");
                QColor c(255,255,255);
                Cell->setBackgroundColor(c);
            }
        }
    }
}

void MainWindow::on_solve_clicked()
{
    matx.init();
    sudoku_solver_wrapper(0, 0);
    /*for (int i = 0; i < 9; ++i)
	{
        for (int j = 0; j < 9; ++j)
		{
			QTableWidgetItem* Cell = ui->table->item(i, j);
			QString str = "";
            str += '0' + matx.read(i,j);
			const QString cstr = str;
			Cell->setText(cstr);
            show();
		}
    }*/
}

void MainWindow::on_pushButton_clicked()
{
    matx.reset();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            QTableWidgetItem* Cell = ui->table->item(i, j);
            QString str = "";
            if(matx.read(i, j)){
                str += '0' + matx.read(i, j);
                const QString cstr = str;
                Cell->setText(cstr);
            } else{
                Cell->setText("");
            }
        }
    }
}
