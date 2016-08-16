#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    QSize size((double)qApp->desktop()->width() / 1.5, (double)qApp->desktop()->width() / fieldWidth * fieldHeight / 1.5);
    setMinimumSize(size);
    setMaximumSize(size);
    move(qApp->desktop()->rect().center() - rect().center());

    qsrand(QTime::currentTime().msec());

    startTimer(16);

    setMouseTracking(true);

    digitColors[0] = QColor(65, 79, 188);
    digitColors[1] = QColor(31, 102, 4);
    digitColors[2] = QColor(169, 7, 7);
    digitColors[3] = QColor(2, 0, 130);
    digitColors[4] = QColor(123, 0, 0);
    digitColors[5] = QColor(3, 124, 125);
    digitColors[6] = QColor(175, 3, 6);
    digitColors[7] = QColor(165, 10, 9);

    field.resize(fieldWidth);

    for (int i = 0; i < fieldWidth; i++)
        field[i].resize(fieldHeight);

    randomize();
}

Widget::~Widget() {
}

void Widget::timerEvent(QTimerEvent *) {
    update();
}

void Widget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Escape:
        qApp->quit();
        break;

    case Qt::Key_R:
        randomize();
        break;
    }
}

void Widget::mousePressEvent(QMouseEvent *) {
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    mousePos = e->pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *) {
}

void Widget::leaveEvent(QEvent *) {
    mousePos = QPoint();
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(rect(), Qt::lightGray);

    p.setFont(QFont("Impact", 22));

    for (int i = 0; i < fieldWidth; i++)
        for (int j = 0; j < fieldHeight; j++)
            drawDigit(p, i, j, sum(i, j));

    const double cellSize = (double)width() / fieldWidth;

    p.setPen(Qt::gray);

    for (int i = 0; i < fieldWidth - 1; i++)
        p.drawLine((i + 1) * cellSize, 0, (i + 1) * cellSize, height());

    for (int j = 0; j < fieldHeight - 1; j++)
        p.drawLine(0, (j + 1) * cellSize, width(), (j + 1) * cellSize);
}

void Widget::drawDigit(QPainter &p, int i, int j, int digit) {
    const double cellSize = (double)width() / fieldWidth;

    if (!mousePos.isNull())
        if (qAbs((i + 0.5) * cellSize - mousePos.x()) < cellSize / 2 && qAbs((j + 0.5) * cellSize - mousePos.y()) < cellSize / 2)
            p.fillRect(i * cellSize, j * cellSize, cellSize, cellSize, QColor(Qt::lightGray).lighter(110));

    if (digit > 0) {
        p.setPen(QPen(digitColors[digit - 1]));
        p.drawText(QRect(i * cellSize, j * cellSize, cellSize, cellSize), Qt::AlignCenter, QString::number(digit));
    }
}

void Widget::randomize() {
    for (int i = 0; i < fieldWidth; i++)
        field[i].fill(false);

    for (int m = 0; m < mines; m++) {
        int i, j;

        do {
            i = qrand() % fieldWidth;
            j = qrand() % fieldHeight;
        } while (field[i][j]);

        field[i][j] = true;
    }
}

int Widget::sum(int i, int j) {
    int s = 0;

    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++) {
            if ((di == 0 && dj == 0) || (di == -1 && i == 0) || (di == 1 && i == fieldWidth - 1) || (dj == -1 && j == 0) || (dj == 1 && j == fieldHeight - 1))
                continue;

            s += field[i + di][j + dj];
        }

    return s;
}
