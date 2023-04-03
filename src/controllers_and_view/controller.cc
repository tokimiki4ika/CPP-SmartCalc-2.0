#include "controller.h"
#include "ui_view.h"

using namespace s21;

Controller::Controller(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Controller) {
  ui->setupUi(this);
  connect(ui->button0, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button1, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button2, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button3, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button4, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button5, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button6, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button7, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button8, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->button9, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonDOT, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->buttonPLUS, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonMINUS, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonMUL, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonDIV, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonMOD, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonPOW, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->buttonBRACKET_OPEN, SIGNAL(clicked()), this,
          SLOT(AnyButtonClick()));
  connect(ui->buttonBRACKET_CLOSE, SIGNAL(clicked()), this,
          SLOT(AnyButtonClick()));

  connect(ui->buttonLOG, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonLN, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonSQRT, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonSIN, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonASIN, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonCOS, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonACOS, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonTAN, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonATAN, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));

  connect(ui->buttonE, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
  connect(ui->buttonX, SIGNAL(clicked()), this, SLOT(AnyButtonClick()));
}

void Controller::AnyButtonClick() {
  data.PushBack(((QPushButton *)sender())->text().toStdString().back());
  ui->expressionLabel->setText(QString::fromStdString(data.ToString()));
}

Controller::~Controller() { delete ui; }

void Controller::on_buttonGraph_clicked() {
  if (data.IsValid()) {
      QLineSeries *series = new QLineSeries();
      int xAxisSize = ui->spinBox_X_AXIS->value(),
      yAxisSize = ui->spinBox_Y_AXIS->value();
      double increment = xAxisSize / 10000.;
      double result;
      for (double i = -xAxisSize; i < xAxisSize; i += increment) {
        if (!data.SolveEquation(&result, i)) {
          *series << QPointF(i, result);
        }
      }

    GraphPlot graph(series, xAxisSize, yAxisSize);
    graph.exec();
    on_buttonC_clicked();
  } else {
    data.Clear();
    ui->expressionLabel->setText("Ошибка");
  }
}

void Controller::on_buttonC_clicked() {
  data.Clear();
  ui->expressionLabel->setText(QString::fromStdString(data.ToString()));
}

void Controller::on_buttonCE_clicked() {
  if (!data.Empty()) {
    data.PopBack();
    ui->expressionLabel->setText(QString::fromStdString(data.ToString()));
  }
}

void Controller::on_buttonPI_clicked() {
  data.PushBack('p');
  ui->expressionLabel->setText(QString::fromStdString(data.ToString()));
}

void Controller::on_buttonRES_clicked() {
  double result = 0;
  Model::CalculationError error =
      data.SolveEquation(&result, ui->doubleSpinBoxX->value());
  if (!error) {
    data.AddNewExp(QString::number(result, 'f', 7).toStdString());
    ui->expressionLabel->setText(QString::fromStdString(data.ToString()));
  } else {
    data.Clear();
    QString error_text;
    switch (error) {
      case Model::WRONG_EXP:
        error_text = "Не правильное уравнение";
        break;
      case Model::LOG_MINUS:
      case Model::LN_MINUS:
        error_text = "Нет логарифма от отрицательного числа";
        break;
      case Model::SQRT_MINUS:
        error_text = "Нет корня от отрицательного числа";
        break;
      case Model::ASIN_RANGE:
        error_text = "Арксинус есть только в пределах от -1 до 1";
        break;
      case Model::ACOS_RANGE:
        error_text = "Арккосинус есть только в пределах от -1 до 1";
        break;
      case Model::DIV_ZERO:
        error_text = "Деление на ноль, невозможно";
        break;
      default:
        break;
    }
    ui->expressionLabel->setText(error_text);
  }
}

void Controller::on_openCreditCalc_clicked()
{
    CreditCalc credit;
    credit.exec();
}


void Controller::on_openDebitCalc_clicked()
{
    DebitCalc debit;
    debit.exec();
}

