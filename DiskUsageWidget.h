#ifndef DISKUSAGEWIDGET_H
#define DISKUSAGEWIDGET_H

#include <QWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class DiskUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiskUsageWidget(QWidget *parent = nullptr);
    void setDiskUsage(qreal used, qreal total);

private:
    QPieSeries *series;
    QChartView *chartView;
};

#endif 