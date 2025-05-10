#pragma once

class SimpleClass
{
public:
	SimpleClass(int k);
	int get_val() const;
	void reset_val(int k);

private:
	int k_;
};

void shapes_examples();

void smart_pointers();
void unique_pointers();
void shared_pointers();

void option_info_examples();
void cpp03_examples();
void cpp11_examples();
