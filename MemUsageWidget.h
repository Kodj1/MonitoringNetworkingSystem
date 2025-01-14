#ifndef MEMUSAGEWIDGET_H
#define MEMUSAGEWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class MemUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemUsageWidget(QWidget *parent = nullptr);
    void setMemUsage(double usage);

private:
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    int time;
};

#endif // MEMUSAGEWIDGET_H