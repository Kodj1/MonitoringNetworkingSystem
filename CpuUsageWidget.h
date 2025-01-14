#ifndef CPUUSAGEWIDGET_H
#define CPUUSAGEWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class CpuUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CpuUsageWidget(QWidget *parent = nullptr);
    void setCpuUsage(qreal usage);

private:
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    int time;
};

#endif // CPUUSAGEWIDGET_H