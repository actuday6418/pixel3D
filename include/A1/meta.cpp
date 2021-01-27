#include "meta.h"

Meta::Meta(std::string *s): Vbox(Gtk::ORIENTATION_VERTICAL),
	label("1. Drop your OBJ file with triangulated mesh below.\n2. Use S and R for scaling and rotation with (X,Y,Z) for choosing an axis.\n3. LShift reverses the transform.\n4. O and P pressed together toggle perspective / orthographic mode.\n5. K and L control the field of view / zoom.\n6. Scroll to transform depth (Z axis)\n\n\n\n\n\n\n\n\n\n\n\n\n",true),
	frame("USAGE"),
	button("Go!"),
	strp(s)
{
	set_border_width(10);
	add(Vbox);

	button.signal_clicked().connect(sigc::mem_fun(*this,&Meta::on_button_clicked));	
	frame.add(label);

	entry.set_max_length(50);
	entry.set_text("");
	entry.set_margin_right(10);

	Hbox.set_margin_top(10);
	Hbox.pack_start(entry);
	Hbox.pack_start(button);

	Vbox.pack_start(frame);
	Vbox.pack_start(Hbox);

	show_all_children();
}

Meta::~Meta()
{
}

void Meta::on_button_clicked()
{
	*strp = entry.get_text();
	close();
}
