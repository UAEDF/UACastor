void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string trees_in[5];
trees_in[0] = "PMT_test_2012_old_group1.root"; // measurements 1 to 41
trees_in[1] = "PMT_test_2012_old_group2.root"; // measurements 59 to 121
trees_in[2] = "PMT_test_2012_old_group3.root"; // measurements 122 to 148
trees_in[3] = "PMT_test_2012_new_group1.root"; // measurements 42 to 58
trees_in[4] = "PMT_test_2012_new_group2.root"; // measurements 149 onwards

int ini_file = 3;
int end_file = 3;

read_tree(trees_in, ini_file, end_file);
}
