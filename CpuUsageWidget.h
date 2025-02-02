#ifndef CPUUSAGEWIDGET_H
#define CPUUSAGEWIDGET_H

#include <QWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class CpuUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CpuUsageWidget(QWidget *parent = nullptr);
    void setCpuUsage(qreal used_cpu, qreal total_cpu);

private:
    QPieSeries *series;
    QChartView *chartView;
};

#endif