#include "MemUsageWidget.h"
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>

MemUsageWidget::MemUsageWidget(QWidget *parent)
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

void MemUsageWidget::setMemUsage(qreal used_mem, qreal total_mem)
{
    series->clear();

    qreal free = total_mem - used_mem;
    QPieSlice *usedSlice = series->append("Used", used_mem);
    QPieSlice *freeSlice = series->append("Free", free);

    usedSlice->setBrush(Qt::red);
    freeSlice->setBrush(Qt::green);

    // Установите метки для сегментов
    usedSlice->setLabel(QString("Used: %1 %").arg(used_mem));
    freeSlice->setLabel(QString("Free: %1 %").arg(free));
    
    // Включите отображение меток
    usedSlice->setLabelVisible(true);
    freeSlice->setLabelVisible(true);

    chartView->chart()->setTitle(QString("Memory Usage:").arg(total_mem)); // Установите заголовок диаграммы
    
    chartView->chart()->update();
}