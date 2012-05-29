void run_create_tree()
{
  gROOT -> Reset();
  //gROOT -> ProcessLine(".L LeakageSubtractor.C++");
  gROOT -> ProcessLine(".L create_tree.C++");

string files_in[50];

files_in[0] = "../data/cpt_sf_CA1579_2012_05_12_15_32_59_mod.cpt";
files_in[1] = "../data/cpt_sf_CA1579_2012_05_13_09_56_20_mod.cpt";
files_in[2] = "../data/cpt_sf_CA1579_2012_05_14_08_02_23_mod.cpt";
files_in[3] = "../data/cpt_sf_CA1842_2012_05_14_11_09_39_mod.cpt";
files_in[4] = "../data/cpt_sf_CA1842_2012_05_14_13_41_55_mod.cpt";
files_in[5] = "../data/cpt_sf_CA1842_2012_05_14_17_08_20_mod.cpt";
files_in[6] = "../data/cpt_sf_CA1592_2012_05_15_08_54_52_mod.cpt";
files_in[7] = "../data/cpt_sf_CA1592_2012_05_15_12_02_58_mod.cpt";
files_in[8] = "../data/cpt_sf_CA0327_2012_05_15_15_20_10_mod.cpt";
files_in[9] = "../data/cpt_sf_CA1680_2012_05_16_07_55_12_mod.cpt";
files_in[10] = "../data/cpt_sf_CA0558_2012_05_16_17_14_48_mod.cpt";
files_in[11] = "../data/cpt_sf_CA0812_2012_05_17_09_56_21_mod.cpt";
files_in[12] = "../data/cpt_sf_CA1954_2012_05_17_15_57_58_mod.cpt";
files_in[13] = "../data/cpt_sf_CA1321_2012_05_18_01_04_36_mod.cpt";
files_in[14] = "../data/cpt_sf_CA1537_2012_05_18_09_53_11_mod.cpt";
files_in[15] = "../data/cpt_sf_CA0886_2012_05_18_14_30_24_mod.cpt";
files_in[16] = "../data/cpt_sf_CA0857_2012_05_18_23_13_00_mod.cpt";
files_in[17] = "../data/cpt_sf_CA1832_2012_05_19_08_57_38_mod.cpt";
files_in[18] = "../data/cpt_sf_CA3399_2012_05_19_14_04_26_mod.cpt";
files_in[19] = "../data/cpt_sf_CA0540_2012_05_19_22_29_01_mod.cpt";
files_in[20] = "../data/cpt_sf_CA0683_2012_05_20_12_41_46_mod.cpt";
files_in[21] = "../data/cpt_sf_CA1620_2012_05_20_15_58_54_mod.cpt";
files_in[22] = "../data/cpt_sf_CA1829_2012_05_20_21_04_16_mod.cpt";
files_in[23] = "../data/cpt_sf_CA3362_2012_05_20_09_24_04_mod.cpt";
files_in[24] = "../data/cpt_sf_CA1617_2012_05_21_00_24_41_mod.cpt";
files_in[25] = "../data/cpt_sf_CA1431_2012_05_21_08_55_15_mod.cpt";
files_in[26] = "../data/cpt_sf_CA1549_2012_05_21_12_33_16_mod.cpt";
files_in[27] = "../data/cpt_sf_CA0948_2012_05_21_15_43_16_mod.cpt";
files_in[28] = "../data/cpt_sf_CA1200_2012_05_21_20_34_38_mod.cpt";
files_in[29] = "../data/cpt_sf_CA3236_2012_05_22_00_41_35_mod.cpt";
files_in[30] = "../data/cpt_sf_CA0742_2012_05_22_08_13_03_mod.cpt";
files_in[31] = "../data/cpt_sf_CA0574_2012_05_22_11_37_58_mod.cpt";
files_in[32] = "../data/cpt_sf_CA0829_2012_05_22_15_04_27_mod.cpt";
files_in[33] = "../data/cpt_sf_CA0715_2012_05_22_19_14_07_mod.cpt";
files_in[34] = "../data/cpt_sf_CA0715_2012_05_23_01_15_27_mod.cpt";
files_in[35] = "../data/cpt_sf_CA1263_2012_05_23_08_02_05_mod.cpt";
files_in[36] = "../data/cpt_sf_CA3386_2012_05_23_11_31_26_mod.cpt";
files_in[37] = "../data/cpt_sf_CA0625_2012_05_23_15_50_52_mod.cpt";
files_in[38] = "../data/cpt_sf_CA1593_2012_05_23_18_47_30_mod.cpt";
files_in[39] = "../data/cpt_sf_CA0892_2012_05_24_08_51_55_mod.cpt";
files_in[40] = "../data/cpt_sf_CA1620_2012_05_24_14_49_03_mod.cpt";
files_in[41] = "../data/cpt_sf_BA0274_2012_05_25_17_52_57_mod.cpt";
files_in[42] = "../data/cpt_sf_BA0311_2012_05_28_19_34_55_mod.cpt";
files_in[43] = "../data/cpt_sf_BA0265_2012_05_29_07_45_47_mod.cpt";
files_in[44] = "../data/cpt_sf_BA0264_2012_05_29_11_11_00_mod.cpt";
files_in[45] = "../data/cpt_sf_BA0263_2012_05_29_14_21_05_mod.cpt";
files_in[46] = "../data/cpt_sf_BA0263_2012_05_29_15_33_18_mod.cpt";
files_in[47] = "../data/.cpt";
files_in[48] = "../data/.cpt";
files_in[49] = "../data/.cpt";

int n_files = 47;


  string tree_out = "PMT_test_2012.root";

  create_tree(files_in, n_files, tree_out);
}
