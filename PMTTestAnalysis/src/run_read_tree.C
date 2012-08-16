void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string trees_in[15];

//old pmts
trees_in[0] = "PMT_test_2012_old_group1.root"; // measurements 1 to 41 - done
trees_in[1] = "PMT_test_2012_old_group2.root"; // measurements 59 to 121 - done
trees_in[2] = "PMT_test_2012_old_group3.root"; // measurements 122 to 148 - done
trees_in[3] = "PMT_test_2012_old_group4.root"; // measurements 186 to 200 - done
trees_in[4] = "PMT_test_2012_old_group5.root"; // measurements 201 to 227 - done
trees_in[5] = "PMT_test_2012_old_group6.root"; // measurements 228 to 240 - done

//new pmts
trees_in[6]  = "PMT_test_2012_new_group1.root"; // measurements 42 to 58 - done
trees_in[7]  = "PMT_test_2012_new_group2.root"; // measurements 149 to 161 - done
trees_in[8]  = "PMT_test_2012_new_group3.root"; // measurements 162 to 173 - done
trees_in[9]  = "PMT_test_2012_new_group4.root"; // measurements 176 to 185 - done
trees_in[10] = "PMT_test_2012_new_group5.root"; // measurements 241 to 252 - done
trees_in[11] = "PMT_test_2012_new_group6.root"; // measurements 253 to 260 - (incomplete)

//test pmt
trees_in[12] = "PMT_test_2012_testpmt.root"; // measurement 174 to 175 - done

int ini_file = 1;
int end_file = 13;

read_tree(trees_in, ini_file, end_file);
}
