#include "CpuUsageWidget.h"
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>

CpuUsageWidget::CpuUsageWidget(QWidget *parent)
    : QWidget(parent),
      series(new QPieSeries()),
      chartView(new QChartView(new QChart()))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    chartView->chart()->addSeries(series);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 300);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void CpuUsageWidget::setCpuUsage(qreal used_cpu, qreal total_cpu)
{
    series->clear();

    qreal free = total_cpu - used_cpu;
    QPieSlice *usedSlice = series->append("Used", used_cpu);
    QPieSlice *freeSlice = series->append("Free", free);

    usedSlice->setBrush(Qt::red);
    freeSlice->setBrush(Qt::green);

    usedSlice->setLabel(QString("Used: %1 %").arg(used_cpu));
    freeSlice->setLabel(QString("Free: %1 %").arg(free));
    
    // Включите отображение меток
    usedSlice->setLabelVisible(true);
    freeSlice->setLabelVisible(true);

    chartView->chart()->setTitle("Cpu Usage:"); // Установите заголовок диаграммы
    
    chartView->chart()->update();
}