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
    chartView->setMinimumSize(600, 300);  // Установите минимальные размеры для chartView
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);  // Уберите отступы, чтобы график занимал все пространство
    setLayout(layout);
}

void DiskUsageWidget::setDiskUsage(qreal used, qreal total)
{
    series->clear();

    qreal free = total - used;
    QPieSlice *usedSlice = series->append("Used", used);
    QPieSlice *freeSlice = series->append("Free", free);

    usedSlice->setBrush(Qt::red);
    freeSlice->setBrush(Qt::green);

    chartView->chart()->update();
}