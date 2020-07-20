#include"Windows/Label.h"
#include<QLabel>

Label::Label(void){
	QLabel* label = new QLabel("");
	label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	label->setText("first line\nsecond line");
	label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
}

void Label::setText(std::string &text)
{

}