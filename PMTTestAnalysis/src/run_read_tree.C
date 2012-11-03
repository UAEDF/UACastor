void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string trees_in[30];

//old pmts
trees_in[0]  = "PMT_test_2012_old_group1.root";  // measurements 1 to 41 - done
trees_in[1]  = "PMT_test_2012_old_group2.root";  // measurements 59 to 66 - done
trees_in[2]  = "PMT_test_2012_old_group3.root";  // measurements 67 to 74 - done
trees_in[3]  = "PMT_test_2012_old_group4.root";  // measurements 75 to 82 - done
trees_in[4]  = "PMT_test_2012_old_group5.root";  // measurements 83 to 91 - done
trees_in[5]  = "PMT_test_2012_old_group6.root";  // measurements 92 to 101 - done
trees_in[6]  = "PMT_test_2012_old_group7.root";  // measurements 102 to 111 - done
trees_in[7]  = "PMT_test_2012_old_group8.root";  // measurements 112 to 122 - done
trees_in[8]  = "PMT_test_2012_old_group9.root";  // measurements 123 to 129 - done
trees_in[9]  = "PMT_test_2012_old_group10.root"; // measurements 130 to 135 - done
trees_in[10] = "PMT_test_2012_old_group11.root"; // measurements 136 to 149 - done
trees_in[11] = "PMT_test_2012_old_group12.root"; // measurements 187 to 194 - done
trees_in[12] = "PMT_test_2012_old_group13.root"; // measurements 195 to 201 - done
trees_in[13] = "PMT_test_2012_old_group14.root"; // measurements 202 to 214 - done
trees_in[14] = "PMT_test_2012_old_group15.root"; // measurements 215 to 228 - done
trees_in[15] = "PMT_test_2012_old_group16.root"; // measurements 229 to 241 - done

//new pmts
trees_in[16] = "PMT_test_2012_new_group1.root";  // measurements 42 to 58 - done
trees_in[17] = "PMT_test_2012_new_group2.root";  // measurements 150 to 162 - done
trees_in[18] = "PMT_test_2012_new_group3.root";  // measurements 163 to 174 - done
trees_in[19] = "PMT_test_2012_new_group4.root";  // measurements 177 to 186 - done
trees_in[20] = "PMT_test_2012_new_group5.root";  // measurements 242 to 253 - done
trees_in[21] = "PMT_test_2012_new_group6.root";  // measurements 254 to 261 - done
trees_in[22] = "PMT_test_2012_new_group7.root";  // measurements 262 to 269 - done
trees_in[23] = "PMT_test_2012_new_group8.root";  // measurements 270 to 277 - done
trees_in[24] = "PMT_test_2012_new_group9.root";  // measurements 278 to 287 - done
trees_in[25] = "PMT_test_2012_new_group10.root"; // measurements 288 to 297 - done
trees_in[26] = "PMT_test_2012_new_group11.root"; // measurements 298 to 307 - done
trees_in[27] = "PMT_test_2012_new_group12.root"; // measurements 308 to 318 - done
trees_in[28] = "PMT_test_2012_new_group13.root"; // measurements 319 to 324 - done

//test pmt
trees_in[29] = "PMT_test_2012_testpmt.root";     // measurement 175 to 176 - done

int ini_file = 1;
int end_file = 30;

read_tree(trees_in, ini_file, end_file);
}
