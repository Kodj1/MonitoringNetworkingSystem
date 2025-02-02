#ifndef MEMUSAGEWIDGET_H
#define MEMUSAGEWIDGET_H

#include <QWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>


QT_CHARTS_USE_NAMESPACE

class MemUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemUsageWidget(QWidget *parent = nullptr);
    void setMemUsage(qreal used_mem, qreal total_mem);

private:
    QPieSeries *series;
    QChartView *chartView;
};

#endif