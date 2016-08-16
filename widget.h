#pragma once
#include <QtWidgets>

class Widget : public QWidget {
    Q_OBJECT

    const int fieldWidth = 30;
    const int fieldHeight = 16;
    const int mines = 99;

    QColor digitColors[8];

    QVector<QVector<bool>> field;

    QPoint mousePos;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void timerEvent(QTimerEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    void drawDigit(QPainter &p, int i, int j, int digit);
    void randomize();
    int sum(int i, int j);
};
