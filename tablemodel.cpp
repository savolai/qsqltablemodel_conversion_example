#include "tablemodel.h"
#include <QDebug>
#include <QSqlField>
#include <QSqlRecord>

TableModel::TableModel(QObject *parent, QSqlDatabase db)
    :    QSqlTableModel(parent,db)

{

}


bool TableModel::setData(const QModelIndex &index, QVariant &value, int role){

    double dValue=value.toDouble();
    double baseValue=dValue*2;

    bool success=QSqlTableModel::setData(index,QVariant(baseValue),role);
    emit dataChanged(index,index);
    return success;

}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QVariant value=QSqlTableModel::data(index,role);
    double dValue=value.toDouble();
    double userValue=dValue/2;
    return QVariant(userValue);

}



