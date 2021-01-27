#ifndef META_H
#define META_H

#include<gtkmm.h>
class Meta : public Gtk::Window
{
		//Signal handlers:
		void on_button_clicked();

		//Member widgets:
		std::string *strp;
		Gtk::Box Vbox;
		Gtk::Entry entry;
		Gtk::Frame frame;
		Gtk::Label label;
		Gtk::Button button;
		Gtk::Box Hbox;

	public:
		Meta(std::string *);
		virtual ~Meta();
};
#endif
