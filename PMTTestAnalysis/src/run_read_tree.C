void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string trees_in[9];

//old pmts
trees_in[0] = "PMT_test_2012_old_group1.root"; // measurements 1 to 41
trees_in[1] = "PMT_test_2012_old_group2.root"; // measurements 59 to 121
trees_in[2] = "PMT_test_2012_old_group3.root"; // measurements 122 to 148  must be re-analysed because 4 pmts were unknown
trees_in[3] = "PMT_test_2012_old_group4.root"; // measurement 174
trees_in[4] = "PMT_test_2012_old_group5.root"; // measurements 177 to 190 
trees_in[5] = "PMT_test_2012_old_group6.root"; // measurements 191 to 217

//new pmts
trees_in[6] = "PMT_test_2012_new_group1.root"; // measurements 42 to 58
trees_in[7] = "PMT_test_2012_new_group2.root"; // measurements 149 to 173 re-run to update
trees_in[8] = "PMT_test_2012_new_group3.root"; // measurements 175 to 176

int ini_file = 1;
int end_file = 9;

read_tree(trees_in, ini_file, end_file);
}
