
#ifndef _FRAGVIEW_LABEL_H_
#define _FRAGVIEW_LABEL_H_ 1
#include"Widget.h"

/**
 *
 */
class FVDECLSPEC Label: public Widget { 
public:
	Label(void);

	void setText(std::string &text);

private:
	void* bar;
};

#endif