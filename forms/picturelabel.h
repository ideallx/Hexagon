#ifndef PICTURELABEL_H
#define PICTURELABEL_H

#include <QLabel>

class PictureLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PictureLabel(QWidget *parent = 0);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    
signals:
    void clicked(void);

public slots:
    
};

#endif // PICTURELABEL_H
