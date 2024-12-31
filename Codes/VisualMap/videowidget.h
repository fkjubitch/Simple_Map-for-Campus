#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    QMediaPlayer* m_player = nullptr;
    QAudioOutput* m_audioOutput = nullptr;
    QVideoWidget* m_videoWidget = nullptr;
};


#endif // VIDEOWIDGET_H
