void run_create_tree()
{
  gROOT -> Reset();
  //gROOT -> ProcessLine(".L LeakageSubtractor.C++");
  gROOT -> ProcessLine(".L create_tree.C++");

string files_in[160];

files_in[0] = "../data/cpt_sf_CA1579_2012_05_12_15_32_59_mod.cpt"; //good
files_in[1] = "../data/cpt_sf_CA1579_2012_05_13_09_56_20_mod.cpt"; //good
files_in[2] = "../data/cpt_sf_CA1579_2012_05_14_08_02_23_mod.cpt"; //good
files_in[3] = "../data/cpt_sf_CA1842_2012_05_14_11_09_39_mod.cpt"; //good
files_in[4] = "../data/cpt_sf_CA1842_2012_05_14_13_41_55_mod.cpt"; //good
files_in[5] = "../data/cpt_sf_CA1842_2012_05_14_17_08_20_mod.cpt"; //bad - 3 bad fits - very big value for cathode!
files_in[6] = "../data/cpt_sf_CA1592_2012_05_15_08_54_52_mod.cpt"; //warning - except one of the fits
files_in[7] = "../data/cpt_sf_CA1592_2012_05_15_12_02_58_mod.cpt"; //good
files_in[8] = "../data/cpt_sf_CA0327_2012_05_15_15_20_10_mod.cpt"; //good
files_in[9] = "../data/cpt_sf_CA1680_2012_05_16_07_55_12_mod.cpt"; //good
files_in[10] = "../data/cpt_sf_CA0558_2012_05_16_17_14_48_mod.cpt"; //good
files_in[11] = "../data/cpt_sf_CA0812_2012_05_17_09_56_21_mod.cpt"; //warning - qe plot is empty
files_in[12] = "../data/cpt_sf_CA1954_2012_05_17_15_57_58_mod.cpt"; //good
files_in[13] = "../data/cpt_sf_CA1321_2012_05_18_01_04_36_mod.cpt"; //good
files_in[14] = "../data/cpt_sf_CA1537_2012_05_18_09_53_11_mod.cpt"; //good
files_in[15] = "../data/cpt_sf_CA0886_2012_05_18_14_30_24_mod.cpt"; //good
files_in[16] = "../data/cpt_sf_CA0857_2012_05_18_23_13_00_mod.cpt"; //good
files_in[17] = "../data/cpt_sf_CA1832_2012_05_19_08_57_38_mod.cpt"; //good
files_in[18] = "../data/cpt_sf_CA3399_2012_05_19_14_04_26_mod.cpt"; //good
files_in[19] = "../data/cpt_sf_CA0540_2012_05_19_22_29_01_mod.cpt"; //good
files_in[20] = "../data/cpt_sf_CA0683_2012_05_20_12_41_46_mod.cpt"; //good
files_in[21] = "../data/cpt_sf_CA1620_2012_05_20_15_58_54_mod.cpt"; //good
files_in[22] = "../data/cpt_sf_CA1829_2012_05_20_21_04_16_mod.cpt"; //good
files_in[23] = "../data/cpt_sf_CA3362_2012_05_20_09_24_04_mod.cpt"; //good
files_in[24] = "../data/cpt_sf_CA1617_2012_05_21_00_24_41_mod.cpt"; //good
files_in[25] = "../data/cpt_sf_CA1431_2012_05_21_08_55_15_mod.cpt"; //bad - 2 bad fits
files_in[26] = "../data/cpt_sf_CA1549_2012_05_21_12_33_16_mod.cpt"; //good
files_in[27] = "../data/cpt_sf_CA0948_2012_05_21_15_43_16_mod.cpt"; //good
files_in[28] = "../data/cpt_sf_CA1200_2012_05_21_20_34_38_mod.cpt"; //good
files_in[29] = "../data/cpt_sf_CA3236_2012_05_22_00_41_35_mod.cpt"; //warning - strange plot on the fitting at 800V
files_in[30] = "../data/cpt_sf_CA0742_2012_05_22_08_13_03_mod.cpt"; //good
files_in[31] = "../data/cpt_sf_CA0574_2012_05_22_11_37_58_mod.cpt"; //good
files_in[32] = "../data/cpt_sf_CA0829_2012_05_22_15_04_27_mod.cpt"; //good
files_in[33] = "../data/cpt_sf_CA0715_2012_05_22_19_14_07_mod.cpt"; //warning - imcomplete measurement
files_in[34] = "../data/cpt_sf_CA0715_2012_05_23_01_15_27_mod.cpt"; //good
files_in[35] = "../data/cpt_sf_CA1263_2012_05_23_08_02_05_mod.cpt"; //good
files_in[36] = "../data/cpt_sf_CA3386_2012_05_23_11_31_26_mod.cpt"; //good
files_in[37] = "../data/cpt_sf_CA0625_2012_05_23_15_50_52_mod.cpt"; //good
files_in[38] = "../data/cpt_sf_CA1593_2012_05_23_18_47_30_mod.cpt"; //bad - all plots and values look strange
files_in[39] = "../data/cpt_sf_CA0892_2012_05_24_08_51_55_mod.cpt"; //warning - 1 bad fit
files_in[40] = "../data/cpt_sf_CA1620_2012_05_24_14_49_03_mod.cpt"; //warning - fit for 1600V failed!
files_in[41] = "../data/cpt_sf_BA0274_2012_05_25_17_52_57_mod.cpt"; //bad - 4 bad fits - i need to update the code and rerun from this onwards
files_in[42] = "../data/cpt_sf_BA0311_2012_05_28_19_34_55_mod.cpt"; //bad - 4 bad fits
files_in[43] = "../data/cpt_sf_BA0265_2012_05_29_07_45_47_mod.cpt"; //good
files_in[44] = "../data/cpt_sf_BA0264_2012_05_29_11_11_00_mod.cpt"; //warning - 2 bad fits
files_in[45] = "../data/cpt_sf_BA0263_2012_05_29_14_21_05_mod.cpt";
files_in[46] = "../data/cpt_sf_BA0263_2012_05_29_15_33_18_mod.cpt";
files_in[47] = "../data/cpt_sf_BA0279_2012_05_29_18_45_43_mod.cpt";
files_in[48] = "../data/cpt_sf_BA0287_2012_05_29_21_53_31_mod.cpt";
files_in[49] = "../data/cpt_sf_BA0288_2012_05_30_07_22_29_mod.cpt";
files_in[50] = "../data/cpt_sf_BA0291_2012_05_30_10_34_08_mod.cpt";
files_in[51] = "../data/cpt_sf_BA0297_2012_05_30_13_44_58_mod.cpt"; 
files_in[52] = "../data/cpt_sf_BA0300_2012_05_30_16_53_26_mod.cpt"; 
files_in[53] = "../data/cpt_sf_BA0303_2012_05_30_20_05_08_mod.cpt"; 
files_in[54] = "../data/cpt_sf_BA0304_2012_05_31_07_42_35_mod.cpt";
files_in[55] = "../data/cpt_sf_BA0305_2012_05_31_11_01_55_mod.cpt";
files_in[56] = "../data/cpt_sf_BA0307_2012_05_31_14_13_08_mod.cpt";
files_in[57] = "../data/cpt_sf_BA0309_2012_05_31_17_22_32_mod.cpt";
files_in[58] = "../data/cpt_sf_CA1495_2012_06_01_09_17_42_mod.cpt";
files_in[59] = "../data/cpt_sf_CA1759_2012_06_01_11_54_02_mod.cpt";
files_in[60] = "../data/cpt_sf_CA1141_2012_06_01_14_29_11_mod.cpt";
files_in[61] = "../data/cpt_sf_CA1984_2012_06_01_17_04_50_mod.cpt";
files_in[62] = "../data/cpt_sf_CA0811_2012_06_01_19_12_41_mod.cpt";
files_in[63] = "../data/cpt_sf_CA1538_2012_06_01_21_26_21_mod.cpt"; //here
files_in[64] = "../data/cpt_sf_CA1161_2012_06_01_23_34_54_mod.cpt";
files_in[65] = "../data/cpt_sf_CA0793_2012_06_02_01_44_25_mod.cpt";
files_in[66] = "../data/cpt_sf_CA1316_2012_06_02_07_24_28_mod.cpt";
files_in[67] = "../data/cpt_sf_CA0979_2012_06_02_09_33_29_mod.cpt";
files_in[68] = "../data/cpt_sf_CA1844_2012_06_02_11_47_37_mod.cpt";
files_in[69] = "../data/cpt_sf_CA1131_2012_06_02_14_49_38_mod.cpt";
files_in[70] = "../data/cpt_sf_CA3184_2012_06_02_17_04_14_mod.cpt";
files_in[71] = "../data/cpt_sf_CA1634_2012_06_02_19_19_23_mod.cpt";
files_in[72] = "../data/cpt_sf_CA0354_2012_06_02_23_05_47_mod.cpt";
files_in[73] = "../data/cpt_sf_CA0292_2012_06_03_08_33_57_mod.cpt";
files_in[74] = "../data/cpt_sf_CA0792_2012_06_03_10_43_05_mod.cpt";
files_in[75] = "../data/cpt_sf_CA1327_2012_06_03_12_51_29_mod.cpt";
files_in[76] = "../data/cpt_sf_CA0535_2012_06_03_18_15_14_mod.cpt";
files_in[77] = "../data/cpt_sf_CA2623_2012_06_04_07_59_17_mod.cpt";
files_in[78] = "../data/cpt_sf_CA0126_2012_06_04_10_20_54_mod.cpt";
files_in[79] = "../data/cpt_sf_CA0640_2012_06_04_12_32_34_mod.cpt";
files_in[80] = "../data/cpt_sf_CA1438_2012_06_04_14_45_14_mod.cpt";
files_in[81] = "../data/cpt_sf_CA0723_2012_06_04_17_27_45_mod.cpt";
files_in[82] = "../data/cpt_sf_CA1410_2012_06_04_19_39_45_mod.cpt";
files_in[83] = "../data/cpt_sf_CA0885_2012_06_05_07_56_19_mod.cpt";
files_in[84] = "../data/cpt_sf_CA1434_2012_06_05_10_13_42_mod.cpt";
files_in[85] = "../data/cpt_sf_CA1524_2012_06_05_12_26_43_mod.cpt";
files_in[86] = "../data/cpt_sf_CA0315_2012_06_05_14_40_19_mod.cpt";
files_in[87] = "../data/cpt_sf_CA2044_2012_06_05_16_54_01_mod.cpt";
files_in[88] = "../data/cpt_sf_CA1228_2012_06_05_19_07_32_mod.cpt";
files_in[89] = "../data/cpt_sf_CA1387_2012_06_06_09_11_08_mod.cpt";
files_in[90] = "../data/cpt_sf_CA0045_2012_06_06_16_02_43_mod.cpt";
files_in[91] = "../data/cpt_sf_CA0018_2012_06_06_18_36_34_mod.cpt";
files_in[92] = "../data/cpt_sf_CA1350_2012_06_06_21_25_43_mod.cpt";
files_in[93] = "../data/cpt_sf_CA1170_2012_06_06_23_40_08_mod.cpt";
files_in[94] = "../data/cpt_sf_CA1931_2012_06_07_10_35_51_mod.cpt";
files_in[95] = "../data/cpt_sf_CA1795_2012_06_07_12_48_58_mod.cpt";
files_in[96] = "../data/cpt_sf_CA0843_2012_06_07_15_01_25_mod.cpt";
files_in[97] = "../data/cpt_sf_CA1328_2012_06_07_17_27_52_mod.cpt";
files_in[98] = "../data/cpt_sf_CA1442_2012_06_07_19_48_36_mod.cpt";
files_in[99] = "../data/cpt_sf_CA2023_2012_06_07_22_07_57_mod.cpt";
files_in[100] = "../data/cpt_sf_CA2022_2012_06_08_08_47_51_mod.cpt";
files_in[101] = "../data/cpt_sf_CA0790_2012_06_08_11_43_28_mod.cpt";
files_in[102] = "../data/cpt_sf_CA0143_2012_06_08_14_38_33_mod.cpt";
files_in[103] = "../data/cpt_sf_CA2034_2012_06_08_17_04_40_mod.cpt";
files_in[104] = "../data/cpt_sf_CA2018_2012_06_08_19_20_36_mod.cpt";
files_in[105] = "../data/cpt_sf_CA0977_2012_06_09_08_17_46_mod.cpt";
files_in[106] = "../data/cpt_sf_CA0708_2012_06_09_10_38_02_mod.cpt";
files_in[107] = "../data/cpt_sf_CA0072_2012_06_09_12_55_18_mod.cpt";
files_in[108] = "../data/cpt_sf_CA1513_2012_06_09_15_13_00_mod.cpt";
files_in[109] = "../data/cpt_sf_CA0299_2012_06_09_17_32_42_mod.cpt";
files_in[110] = "../data/cpt_sf_CA0584_2012_06_09_19_53_51_mod.cpt";
files_in[111] = "../data/cpt_sf_CA1325_2012_06_09_22_15_03_mod.cpt";
files_in[112] = "../data/cpt_sf_CA1450_2012_06_10_08_57_43_mod.cpt";
files_in[113] = "../data/cpt_sf_CA1870_2012_06_10_11_13_47_mod.cpt";
files_in[114] = "../data/cpt_sf_CA2060_2012_06_10_13_28_37_mod.cpt";
files_in[115] = "../data/cpt_sf_CA1509_2012_06_10_16_30_32_mod.cpt";
files_in[116] = "../data/cpt_sf_CA0796_2012_06_10_18_47_33_mod.cpt";
files_in[117] = "../data/cpt_sf_CA1655_2012_06_10_21_05_01_mod.cpt";
files_in[118] = "../data/cpt_sf_CA1525_2012_06_11_13_14_35_mod.cpt";
files_in[119] = "../data/cpt_sf_CA1966_2012_06_11_15_41_20_mod.cpt";
files_in[120] = "../data/cpt_sf_CA2046_2012_06_11_17_55_50_mod.cpt";
files_in[121] = "../data/cpt_sf_CA1530_2012_06_15_15_53_26_mod.cpt";
files_in[122] = "../data/cpt_sf_CA1501_2012_06_15_18_14_36_mod.cpt";
files_in[123] = "../data/cpt_sf_CA1979_2012_06_15_20_31_36_mod.cpt";
files_in[124] = "../data/cpt_sf_CA1808_2012_06_15_22_45_25_mod.cpt";
files_in[125] = "../data/cpt_sf_CA1760_2012_06_16_15_42_12_mod.cpt";
files_in[126] = "../data/cpt_sf_CA1691_2012_06_16_18_02_08_mod.cpt";
files_in[127] = "../data/cpt_sf_CA0696_2012_06_16_20_16_32_mod.cpt";
files_in[128] = "../data/cpt_sf_CA1377_2012_06_16_22_43_15_mod.cpt";
files_in[129] = "../data/cpt_sf_CA0084_2012_06_17_09_40_26_mod.cpt";
files_in[130] = "../data/cpt_sf_CA1992_2012_06_17_12_00_21_mod.cpt";
files_in[131] = "../data/cpt_sf_CA1432_2012_06_17_14_14_03_mod.cpt";
files_in[132] = "../data/cpt_sf_CA1577_2012_06_17_16_27_55_mod.cpt";
files_in[133] = "../data/cpt_sf_CA1657_2012_06_17_18_43_45_mod.cpt";
files_in[134] = "../data/cpt_sf_CA0787_2012_06_17_20_57_17_mod.cpt";
files_in[135] = "../data/cpt_sf_CA1591_2012_06_18_08_48_35_mod.cpt";
files_in[136] = "../data/cpt_sf_CA0847_2012_06_18_11_02_20_mod.cpt";
files_in[137] = "../data/cpt_sf_CA1300_2012_06_18_13_15_36_mod.cpt";
files_in[138] = "../data/cpt_sf_CA1884_2012_06_18_15_51_11_mod.cpt";
files_in[139] = "../data/cpt_sf_CA0930_2012_06_18_18_30_23_mod.cpt";
files_in[140] = "../data/cpt_sf_CA1161_2012_06_18_22_04_38_mod.cpt";
files_in[141] = "../data/cpt_sf_CA0656_2012_06_19_08_46_10_mod.cpt"; //need to add sec. and mod.
files_in[142] = "../data/cpt_sf_CA1273_2012_06_19_18_05_03_mod.cpt"; //need to add sec. and mod.
files_in[143] = "../data/cpt_sf_CA1828_2012_06_20_09_24_37_mod.cpt"; //need to add sec. and mod.
files_in[144] = "../data/cpt_sf_CA1828_2012_06_20_11_28_10_mod.cpt"; //need to add sec. and mod.
files_in[145] = "../data/cpt_sf_CA1760_2012_06_20_13_59_43_mod.cpt";
files_in[146] = "../data/cpt_sf_CA0292_2012_06_20_16_39_13_mod.cpt";
files_in[147] = "../data/cpt_sf_CA0792_2012_06_20_21_08_24_mod.cpt";
files_in[148] = "../data/cpt_sf_BA0169_2012_06_21_10_06_04_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[149] = "../data/cpt_sf_BA0170_2012_06_21_14_15_29_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[150] = "../data/cpt_sf_BA0314_2012_06_21_17_09_11_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[151] = "../data/cpt_sf_BA0316_2012_06_21_22_01_15_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[152] = "../data/cpt_sf_BA0317_2012_06_22_08_10_48_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[153] = "../data/cpt_sf_BA0318_2012_06_22_11_01_45_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[154] = "../data/.cpt";
files_in[155] = "../data/.cpt";
files_in[156] = "../data/.cpt";
files_in[157] = "../data/.cpt";
files_in[158] = "../data/.cpt";
files_in[159] = "../data/.cpt";

int ini_file = 122;
int end_file = 148;


  string tree_out = "PMT_test_2012_old_group3.root";

  create_tree(files_in, ini_file, end_file, tree_out);
}
