#include "DiskUsageWidget.h"
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>

DiskUsageWidget::DiskUsageWidget(QWidget *parent)
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

void DiskUsageWidget::setDiskUsage(qreal used_disk, qreal total_disk)
{
    series->clear();

    qreal free = total_disk - used_disk;
    QPieSlice *usedSlice = series->append("Used", used_disk);
    QPieSlice *freeSlice = series->append("Free", free);

    usedSlice->setBrush(Qt::red);
    freeSlice->setBrush(Qt::green);

    // Установите метки для сегментов
    usedSlice->setLabel(QString("Used: %1 GB").arg(used_disk));
    freeSlice->setLabel(QString("Free: %1 GB").arg(free));
    
    // Включите отображение меток
    usedSlice->setLabelVisible(true);
    freeSlice->setLabelVisible(true);

    chartView->chart()->setTitle(QString("Disk Usage: Total %1 GB").arg(total_disk)); // Установите заголовок диаграммы
    
    chartView->chart()->update();
}