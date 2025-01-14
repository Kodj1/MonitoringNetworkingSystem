#include "MemUsageWidget.h"
#include <QVBoxLayout>

MemUsageWidget::MemUsageWidget(QWidget *parent)
    : QWidget(parent),
      chart(new QChart()),
      series(new QLineSeries()),
      chartView(new QChartView(chart)),
      axisX(new QValueAxis()),
      axisY(new QValueAxis()),
      time(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    chart->addSeries(series);
    chart->setTitle("Memory Usage");

    axisX->setLabelFormat("%i");
    axisX->setTitleText("Time");
    axisX->setRange(0, 100);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setRange(0, 100);
    axisY->setTitleText("Usage (%)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800, 600);  // Установите минимальные размеры для chartView
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);  // Уберите отступы, чтобы график занимал все пространство
    setLayout(layout);
}

void MemUsageWidget::setMemUsage(double usage)
{
    // Add new point to series
    series->append(time++, usage);

    // Keep only recent 100 points
    if (series->count() > 100) {
        series->removePoints(0, series->count() - 100);
    }

    axisX->setRange(time - 100, time);
}