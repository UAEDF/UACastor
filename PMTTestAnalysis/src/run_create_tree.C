void run_create_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L LeakageSubtractor.C++");
gROOT -> ProcessLine(".L create_tree.C++");

string files_in[8];
files_in[0] = "../data/cpt_sf_CA1579_2012_05_12_15_32_59_mod.cpt";
files_in[1] = "../data/cpt_sf_CA1579_2012_05_13_09_56_20_mod.cpt";
files_in[2] = "../data/cpt_sf_CA1579_2012_05_14_08_02_23_mod.cpt";
files_in[3] = "../data/cpt_sf_CA1842_2012_05_14_11_09_39_mod.cpt";
files_in[4] = "../data/cpt_sf_CA1842_2012_05_14_13_41_55_mod.cpt";
files_in[5] = "../data/cpt_sf_CA1842_2012_05_14_17_08_20_mod.cpt";
files_in[6] = "../data/cpt_sf_CA1592_2012_05_15_08_54_52_mod.cpt";
files_in[7] = "../data/cpt_sf_CA1592_2012_05_15_12_02_58_mod.cpt";

int n_files = 8;

string tree_out = "test_tree.root";

create_tree(files_in, n_files, tree_out);
}
