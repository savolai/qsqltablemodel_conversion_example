#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

signals:

public slots:

};

#endif // TABLEMODEL_H
