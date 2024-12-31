// widget.cpp
#include "videowidget.h"
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    this->setFixedSize(500, 300);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_videoWidget = new QVideoWidget(this);
    m_videoWidget->resize(500, 260);
    m_player->setAudioOutput(m_audioOutput);
    m_player->setVideoOutput(m_videoWidget);

    m_player->setSource(QUrl("qrc:/xcm/nailong.mp4"));
    m_player->play();
}

Widget::~Widget()
{

}
