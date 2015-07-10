#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QRadioButton>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>
#include "tablemodel.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect to db
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
        QMessageBox::critical(0, "Opening database failed",
            "Opening database failed. It really did.", QMessageBox::Close);
    }

    // connect model to db table table1
    TableModel *model=new TableModel(this,db);
    model->setTable("table1");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    // add new record

    QSqlRecord record;
    QSqlField field0("radio", QVariant::Int);
    field0.setValue(QVariant(QVariant::Int));

    int fieldnumber=0;
    record.insert(fieldnumber,field0);

    int id=-1;
    QSqlError error;

    if(model->insertRecord(model->rowCount(),record)){
        if(model->submitAll()){
            id=record.value("id").toInt();
        }else{
            error=model->lastError();
            qDebug()<<error.text();

        }

    }else{
        error=model->lastError();
        qDebug()<<error.text();
    }

    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->toLast();


    mapper->addMapping(ui->lineEdit,model->fieldIndex("text"));





}

MainWindow::~MainWindow()
{
    delete ui;
}
