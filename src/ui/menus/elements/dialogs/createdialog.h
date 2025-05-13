#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H
#include <qdialog.h>
#include <QLineEdit>

namespace PIPKA::UI {

class CreateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateDialog(QWidget *parent = nullptr);
    int widthValue() const { return widthInput->text().toInt();}
    int heightValue() const { return heightInput->text().toInt();}

private:
    QLineEdit *widthInput;
    QLineEdit *heightInput;

};

}

#endif //CREATEDIALOG_H
