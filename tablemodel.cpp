#include "tablemodel.h"
#include <QDebug>
#include <QSqlField>
#include <QSqlRecord>

TableModel::TableModel(QObject *parent, QSqlDatabase db)
    :    QSqlTableModel(parent,db)

{

}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role){

    double dValue=value.toDouble();
    bool success;
    if(role==Qt::EditRole){
        double baseValue=dValue*2;
        success=QSqlTableModel::setData(index,QVariant(baseValue),role);
    }else{
        success=QSqlTableModel::setData(index,value,role);

    }
    emit dataChanged(index,index);
    return success;


}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QVariant value=QSqlTableModel::data(index,role);
    double dValue=value.toDouble();
    double userValue=dValue;
    if(role==Qt::EditRole){
        userValue=dValue/2;
        return QVariant(userValue);
    }
    return QSqlTableModel::data(index,role);

}



