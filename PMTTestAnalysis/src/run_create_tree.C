void run_create_tree()
{
  gROOT -> Reset();
  //gROOT -> ProcessLine(".L LeakageSubtractor.C++");
  gROOT -> ProcessLine(".L create_tree.C++");

string files_in[330];

//PMT_test_2012_old_group1.root 
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

//PMT_test_2012_new_group1.root
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

//PMT_test_2012_old_group2.root
files_in[58] = "../data/cpt_sf_CA1495_2012_06_01_09_17_42_mod.cpt";
files_in[59] = "../data/cpt_sf_CA1759_2012_06_01_11_54_02_mod.cpt";
files_in[60] = "../data/cpt_sf_CA1141_2012_06_01_14_29_11_mod.cpt";
files_in[61] = "../data/cpt_sf_CA1984_2012_06_01_17_04_50_mod.cpt";
files_in[62] = "../data/cpt_sf_CA0811_2012_06_01_19_12_41_mod.cpt";
files_in[63] = "../data/cpt_sf_CA1538_2012_06_01_21_26_21_mod.cpt";
files_in[64] = "../data/cpt_sf_CA1161_2012_06_01_23_34_54_mod.cpt";
files_in[65] = "../data/cpt_sf_CA0793_2012_06_02_01_44_25_mod.cpt";

//PMT_test_2012_old_group3.root
files_in[66] = "../data/cpt_sf_CA1316_2012_06_02_07_24_28_mod.cpt";
files_in[67] = "../data/cpt_sf_CA0979_2012_06_02_09_33_29_mod.cpt";
files_in[68] = "../data/cpt_sf_CA1844_2012_06_02_11_47_37_mod.cpt";
files_in[69] = "../data/cpt_sf_CA1131_2012_06_02_14_49_38_mod.cpt";
files_in[70] = "../data/cpt_sf_CA3184_2012_06_02_17_04_14_mod.cpt";
files_in[71] = "../data/cpt_sf_CA1634_2012_06_02_19_19_23_mod.cpt";
files_in[72] = "../data/cpt_sf_CA0354_2012_06_02_23_05_47_mod.cpt";
files_in[73] = "../data/cpt_sf_CA0292_2012_06_03_08_33_57_mod.cpt";

//PMT_test_2012_old_group4.root
files_in[74] = "../data/cpt_sf_CA0792_2012_06_03_10_43_05_mod.cpt";
files_in[75] = "../data/cpt_sf_CA1327_2012_06_03_12_51_29_mod.cpt";
files_in[76] = "../data/cpt_sf_CA0535_2012_06_03_18_15_14_mod.cpt";
files_in[77] = "../data/cpt_sf_CA2623_2012_06_04_07_59_17_mod.cpt";
files_in[78] = "../data/cpt_sf_CA0126_2012_06_04_10_20_54_mod.cpt";
files_in[79] = "../data/cpt_sf_CA0640_2012_06_04_12_32_34_mod.cpt";
files_in[80] = "../data/cpt_sf_CA1438_2012_06_04_14_45_14_mod.cpt";
files_in[81] = "../data/cpt_sf_CA0723_2012_06_04_17_27_45_mod.cpt";

//PMT_test_2012_old_group5.root
files_in[82] = "../data/cpt_sf_CA1410_2012_06_04_19_39_45_mod.cpt";
files_in[83] = "../data/cpt_sf_CA0885_2012_06_05_07_56_19_mod.cpt";
files_in[84] = "../data/cpt_sf_CA1434_2012_06_05_10_13_42_mod.cpt";
files_in[85] = "../data/cpt_sf_CA1524_2012_06_05_12_26_43_mod.cpt";
files_in[86] = "../data/cpt_sf_CA0315_2012_06_05_14_40_19_mod.cpt";
files_in[87] = "../data/cpt_sf_CA2044_2012_06_05_16_54_01_mod.cpt";
files_in[88] = "../data/cpt_sf_CA1228_2012_06_05_19_07_32_mod.cpt";
files_in[89] = "../data/cpt_sf_CA1387_2012_06_06_09_11_08_mod.cpt";
files_in[90] = "../data/cpt_sf_CA0045_2012_06_06_16_02_43_mod.cpt";

//PMT_test_2012_old_group6a.root  //most be re-checked
files_in[91] = "../data/cpt_sf_CA0018_2012_06_06_18_36_34_mod.cpt";
files_in[92] = "../data/cpt_sf_CA1350_2012_06_06_21_25_43_mod.cpt";
files_in[93] = "../data/cpt_sf_CA1170_2012_06_06_23_40_08_mod.cpt";
files_in[94] = "../data/cpt_sf_CA0326_2012_06_07_08_21_07_mod.cpt";
files_in[95] = "../data/cpt_sf_CA1931_2012_06_07_10_35_51_mod.cpt";
files_in[96] = "../data/cpt_sf_CA1795_2012_06_07_12_48_58_mod.cpt";
files_in[97] = "../data/cpt_sf_CA0843_2012_06_07_15_01_25_mod.cpt";
files_in[98] = "../data/cpt_sf_CA1328_2012_06_07_17_27_52_mod.cpt";
files_in[99] = "../data/cpt_sf_CA1442_2012_06_07_19_48_36_mod.cpt";
files_in[100] = "../data/cpt_sf_CA2023_2012_06_07_22_07_57_mod.cpt";

//PMT_test_2012_old_group6b.root  //most me rerrunned
files_in[101] = "../data/cpt_sf_CA2022_2012_06_08_08_47_51_mod.cpt";
files_in[102] = "../data/cpt_sf_CA0790_2012_06_08_11_43_28_mod.cpt";
files_in[103] = "../data/cpt_sf_CA0143_2012_06_08_14_38_33_mod.cpt";
files_in[104] = "../data/cpt_sf_CA2034_2012_06_08_17_04_40_mod.cpt";
files_in[105] = "../data/cpt_sf_CA2018_2012_06_08_19_20_36_mod.cpt";
files_in[106] = "../data/cpt_sf_CA0977_2012_06_09_08_17_46_mod.cpt";
files_in[107] = "../data/cpt_sf_CA0708_2012_06_09_10_38_02_mod.cpt";
files_in[108] = "../data/cpt_sf_CA0072_2012_06_09_12_55_18_mod.cpt"; //
files_in[109] = "../data/cpt_sf_CA1513_2012_06_09_15_13_00_mod.cpt";
files_in[110] = "../data/cpt_sf_CA0299_2012_06_09_17_32_42_mod.cpt";

//PMT_test_2012_old_group8.root  //most be re-checked
files_in[111] = "../data/cpt_sf_CA0584_2012_06_09_19_53_51_mod.cpt";
files_in[112] = "../data/cpt_sf_CA1325_2012_06_09_22_15_03_mod.cpt";
files_in[113] = "../data/cpt_sf_CA1450_2012_06_10_08_57_43_mod.cpt";
files_in[114] = "../data/cpt_sf_CA1870_2012_06_10_11_13_47_mod.cpt";
files_in[115] = "../data/cpt_sf_CA2060_2012_06_10_13_28_37_mod.cpt";
files_in[116] = "../data/cpt_sf_CA1509_2012_06_10_16_30_32_mod.cpt";
files_in[117] = "../data/cpt_sf_CA0796_2012_06_10_18_47_33_mod.cpt";
files_in[118] = "../data/cpt_sf_CA1655_2012_06_10_21_05_01_mod.cpt";
files_in[119] = "../data/cpt_sf_CA1525_2012_06_11_13_14_35_mod.cpt";
files_in[120] = "../data/cpt_sf_CA1966_2012_06_11_15_41_20_mod.cpt";
files_in[121] = "../data/cpt_sf_CA2046_2012_06_11_17_55_50_mod.cpt";

//PMT_test_2012_old_group9.root //most be re-checked
files_in[122] = "../data/cpt_sf_CA1530_2012_06_15_15_53_26_mod.cpt";
files_in[123] = "../data/cpt_sf_CA1501_2012_06_15_18_14_36_mod.cpt";
files_in[124] = "../data/cpt_sf_CA1979_2012_06_15_20_31_36_mod.cpt";
files_in[125] = "../data/cpt_sf_CA1808_2012_06_15_22_45_25_mod.cpt";
files_in[126] = "../data/cpt_sf_CA1760_2012_06_16_15_42_12_mod.cpt";
files_in[127] = "../data/cpt_sf_CA1691_2012_06_16_18_02_08_mod.cpt";
files_in[128] = "../data/cpt_sf_CA0696_2012_06_16_20_16_32_mod.cpt";

//PMT_test_2012_old_group10.root //most be re-checked
files_in[129] = "../data/cpt_sf_CA1377_2012_06_16_22_43_15_mod.cpt";
files_in[130] = "../data/cpt_sf_CA0084_2012_06_17_09_40_26_mod.cpt";
files_in[131] = "../data/cpt_sf_CA1992_2012_06_17_12_00_21_mod.cpt";
files_in[132] = "../data/cpt_sf_CA1432_2012_06_17_14_14_03_mod.cpt";
files_in[133] = "../data/cpt_sf_CA1577_2012_06_17_16_27_55_mod.cpt";
files_in[134] = "../data/cpt_sf_CA1657_2012_06_17_18_43_45_mod.cpt";

//PMT_test_2012_old_group11.root
files_in[135] = "../data/cpt_sf_CA0787_2012_06_17_20_57_17_mod.cpt";
files_in[136] = "../data/cpt_sf_CA1591_2012_06_18_08_48_35_mod.cpt";
files_in[137] = "../data/cpt_sf_CA0847_2012_06_18_11_02_20_mod.cpt";
files_in[138] = "../data/cpt_sf_CA1300_2012_06_18_13_15_36_mod.cpt";
files_in[139] = "../data/cpt_sf_CA1884_2012_06_18_15_51_11_mod.cpt";
files_in[140] = "../data/cpt_sf_CA0930_2012_06_18_18_30_23_mod.cpt";
files_in[141] = "../data/cpt_sf_CA1161_2012_06_18_22_04_38_mod.cpt";
files_in[142] = "../data/cpt_sf_CA0656_2012_06_19_08_46_10_mod.cpt";
files_in[143] = "../data/cpt_sf_CA1273_2012_06_19_18_05_03_mod.cpt";
files_in[144] = "../data/cpt_sf_CA1828_2012_06_20_09_24_37_mod.cpt"; 
files_in[145] = "../data/cpt_sf_CA1828_2012_06_20_11_28_10_mod.cpt";
files_in[146] = "../data/cpt_sf_CA1760_2012_06_20_13_59_43_mod.cpt";
files_in[147] = "../data/cpt_sf_CA0292_2012_06_20_16_39_13_mod.cpt";
files_in[148] = "../data/cpt_sf_CA0792_2012_06_20_21_08_24_mod.cpt";

//PMT_test_2012_new_group2.root
files_in[149] = "../data/cpt_sf_BA0169_2012_06_21_10_06_04_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[150] = "../data/cpt_sf_BA0170_2012_06_21_14_15_29_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[151] = "../data/cpt_sf_BA0314_2012_06_21_17_09_11_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[152] = "../data/cpt_sf_BA0316_2012_06_21_22_01_15_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[153] = "../data/cpt_sf_BA0317_2012_06_22_08_10_48_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[154] = "../data/cpt_sf_BA0318_2012_06_22_11_01_45_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[155] = "../data/cpt_sf_BA0319_2012_06_22_14_26_24_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[156] = "../data/cpt_sf_BA0321_2012_06_22_14_39_03_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[157] = "../data/cpt_sf_BA0322_2012_06_22_17_33_18_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[158] = "../data/cpt_sf_BA0324_2012_06_23_08_28_31_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[159] = "../data/cpt_sf_BA0326_2012_06_23_11_22_49_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[160] = "../data/cpt_sf_BA0327_2012_06_23_14_22_19_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[161] = "../data/cpt_sf_BA0329_2012_06_23_17_12_36_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;

//PMT_test_2012_new_group3.root
files_in[162] = "../data/cpt_sf_BA0336_2012_06_24_08_54_41_mod.cpt";//if you are not happy: repeat analysis with chi2 threshold = 100 or 200;
files_in[163] = "../data/cpt_sf_BA0337_2012_06_24_11_46_54_mod.cpt";
files_in[164] = "../data/cpt_sf_BA0339_2012_06_24_14_40_03_mod.cpt";
files_in[165] = "../data/cpt_sf_BA0342_2012_06_24_18_31_58_mod.cpt";
files_in[166] = "../data/cpt_sf_BA0349_2012_06_25_07_47_18_mod.cpt";
files_in[167] = "../data/cpt_sf_BA0351_2012_06_25_11_01_43_mod.cpt";
files_in[168] = "../data/cpt_sf_BA0352_2012_06_25_14_06_07_mod.cpt";
files_in[169] = "../data/cpt_sf_BA0353_2012_06_25_16_58_05_mod.cpt";
files_in[170] = "../data/cpt_sf_BA0354_2012_06_26_07_32_34_mod.cpt";
files_in[171] = "../data/cpt_sf_BA0355_2012_06_26_10_34_28_mod.cpt";
files_in[172] = "../data/cpt_sf_BA0359_2012_06_26_17_53_21_mod.cpt";
files_in[173] = "../data/cpt_sf_BA0360_2012_06_27_07_55_51_mod.cpt";

//PMT_test_2012_testpmt.root
files_in[174] = "../data/cpt_sf_CA2000_2012_06_27_10_57_09_mod.cpt";
files_in[175] = "../data/cpt_sf_CA2000_2012_07_07_13_56_22_mod.cpt";

//PMT_test_2012_new_group4.root
files_in[176] = "../data/cpt_sf_BA0361_2012_06_27_13_15_01_mod.cpt";
files_in[177] = "../data/cpt_sf_BA0364_2012_06_27_16_05_19_mod.cpt";
files_in[178] = "../data/cpt_sf_BA0373_2012_07_06_18_38_37_mod.cpt";
files_in[179] = "../data/cpt_sf_BA0374_2012_07_07_09_28_32_mod.cpt";
files_in[180] = "../data/cpt_sf_BA0374_2012_07_07_17_05_00_mod.cpt";
files_in[181] = "../data/cpt_sf_BA0373_2012_07_08_08_56_42_mod.cpt";
files_in[182] = "../data/cpt_sf_BA0336_2012_07_08_11_49_23_mod.cpt";
files_in[183] = "../data/cpt_sf_BA0351_2012_07_08_14_47_05_mod.cpt";
files_in[184] = "../data/cpt_sf_BA0329_2012_07_08_17_52_15_mod.cpt";
files_in[185] = "../data/cpt_sf_BA0326_2012_07_09_07_43_46_mod.cpt";

//PMT_test_2012_old_group12.root //most be re-checked
files_in[186] = "../data/cpt_sf_CA1601_2012_07_09_10_47_10_mod.cpt";
files_in[187] = "../data/cpt_sf_CA0040_2012_07_09_14_58_02_mod.cpt";
files_in[188] = "../data/cpt_sf_CA2123_2012_07_09_17_14_56_mod.cpt";
files_in[189] = "../data/cpt_sf_CA1095_2012_07_09_19_28_01_mod.cpt";
files_in[190] = "../data/cpt_sf_CA0808_2012_07_10_08_00_22_mod.cpt";
files_in[191] = "../data/cpt_sf_CA1469_2012_07_10_13_17_39_mod.cpt";
files_in[192] = "../data/cpt_sf_CA1951_2012_07_10_15_38_44_mod.cpt";
files_in[193] = "../data/cpt_sf_CA0791_2012_07_10_18_03_42_mod.cpt";

//PMT_test_2012_old_group13.root //most be re-checked
files_in[194] = "../data/cpt_sf_CA0055_2012_07_11_08_04_34_mod.cpt";
files_in[195] = "../data/cpt_sf_CA2045_2012_07_11_10_23_40_mod.cpt";
files_in[196] = "../data/cpt_sf_CA1636_2012_07_11_12_36_59_mod.cpt";
files_in[197] = "../data/cpt_sf_CA1576_2012_07_11_15_02_19_mod.cpt";
files_in[198] = "../data/cpt_sf_CA2020_2012_07_11_17_24_26_mod.cpt";
files_in[199] = "../data/cpt_sf_CA0745_2012_07_11_19_40_51_mod.cpt";
files_in[200] = "../data/cpt_sf_CA0675_2012_07_12_08_08_38_mod.cpt";

//PMT_test_2012_old_group14.root  //most be re-checked
files_in[201] = "../data/cpt_sf_CA1229_2012_07_12_10_44_08_mod.cpt";
files_in[202] = "../data/cpt_sf_CA0749_2012_07_12_12_59_13_mod.cpt";
files_in[203] = "../data/cpt_sf_CA0422_2012_07_12_15_33_05_mod.cpt";
files_in[204] = "../data/cpt_sf_CA2057_2012_07_12_17_47_19_mod.cpt";
files_in[205] = "../data/cpt_sf_CA3400_2012_07_13_08_04_24_mod.cpt";
files_in[206] = "../data/cpt_sf_CA1527_2012_07_13_10_41_11_mod.cpt";
files_in[207] = "../data/cpt_sf_CA0400_2012_07_13_13_16_09_mod.cpt";
files_in[208] = "../data/cpt_sf_CA1016_2012_07_13_15_31_33_mod.cpt";
files_in[209] = "../data/cpt_sf_CA1548_2012_07_13_17_49_23_mod.cpt";
files_in[210] = "../data/cpt_sf_CA1852_2012_07_14_09_16_50_mod.cpt";
files_in[211] = "../data/cpt_sf_CA0267_2012_07_14_11_32_12_mod.cpt";
files_in[212] = "../data/cpt_sf_CA2115_2012_07_14_13_50_31_mod.cpt";
files_in[213] = "../data/cpt_sf_CA1881_2012_07_14_16_04_18_mod.cpt";

//PMT_test_2012_old_group15.root  //most be re-checked
files_in[214] = "../data/cpt_sf_CA1363_2012_07_14_18_24_32_mod.cpt";
files_in[215] = "../data/cpt_sf_CA1468_2012_07_15_09_17_12_mod.cpt";
files_in[216] = "../data/cpt_sf_CA1143_2012_07_15_11_48_47_mod.cpt";
files_in[217] = "../data/cpt_sf_CA2051_2012_07_15_14_03_09_mod.cpt";
files_in[218] = "../data/cpt_sf_CA0907_2012_07_15_16_17_52_mod.cpt";
files_in[219] = "../data/cpt_sf_CA1953_2012_07_16_08_16_40_mod.cpt";
files_in[220] = "../data/cpt_sf_CA0780_2012_07_16_11_10_29_mod.cpt";
files_in[221] = "../data/cpt_sf_CA0932_2012_07_16_13_51_10_mod.cpt";
files_in[222] = "../data/cpt_sf_CA1010_2012_07_16_16_07_25_mod.cpt";
files_in[223] = "../data/cpt_sf_CA0031_2012_07_16_18_38_41_mod.cpt";
files_in[224] = "../data/cpt_sf_CA1594_2012_07_17_08_05_40_mod.cpt";
files_in[225] = "../data/cpt_sf_CA0043_2012_07_17_10_37_23_mod.cpt";
files_in[226] = "../data/cpt_sf_CA1444_2012_07_17_17_35_35_mod.cpt";
files_in[227] = "../data/cpt_sf_CA1490_2012_07_17_20_03_21_mod.cpt";

//PMT_test_2012_old_group16.root
files_in[228] = "../data/cpt_sf_CA1790_2012_07_20_14_21_21_mod.cpt";
files_in[229] = "../data/cpt_sf_CA3400_2012_07_20_16_44_18_mod.cpt";
files_in[230] = "../data/cpt_sf_CA1538_2012_07_20_18_59_28_mod.cpt";
files_in[231] = "../data/cpt_sf_CA0043_2012_07_21_09_30_20_mod.cpt";
files_in[232] = "../data/cpt_sf_CA0327_2012_07_21_11_53_40_mod.cpt";
files_in[233] = "../data/cpt_sf_CA1760_2012_07_21_14_19_17_mod.cpt";
files_in[234] = "../data/cpt_sf_CA2034_2012_07_21_16_36_42_mod.cpt";
files_in[235] = "../data/cpt_sf_CA0084_2012_07_22_10_01_27_mod.cpt";
files_in[236] = "../data/cpt_sf_CA1680_2012_07_22_12_17_15_mod.cpt";
files_in[237] = "../data/cpt_sf_CA1620_2012_07_22_14_36_01_mod.cpt";
files_in[238] = "../data/cpt_sf_CA1842_2012_07_22_16_57_12_mod.cpt";
files_in[239] = "../data/cpt_sf_CA0808_2012_07_23_08_06_23_mod.cpt";
files_in[240] = "../data/cpt_sf_CA1676_2012_07_27_11_48_58_mod.cpt";

//PMT_test_2012_new_group5.root
files_in[241] = "../data/cpt_sf_BA0182_2012_07_30_10_38_09_mod.cpt";
files_in[242] = "../data/cpt_sf_BA0184_2012_07_30_15_02_42_mod.cpt";
files_in[243] = "../data/cpt_sf_BA0367_2012_07_30_18_36_17_mod.cpt";
files_in[244] = "../data/cpt_sf_BA0372_2012_07_31_13_20_48_mod.cpt";
files_in[245] = "../data/cpt_sf_BA0377_2012_07_31_16_36_36_mod.cpt";
files_in[246] = "../data/cpt_sf_BA0379_2012_07_31_19_28_59_mod.cpt";
files_in[247] = "../data/cpt_sf_BA0381_2012_08_01_10_46_25_mod.cpt";
files_in[248] = "../data/cpt_sf_BA0384_2012_08_01_13_40_38_mod.cpt";
files_in[249] = "../data/cpt_sf_BA0386_2012_08_02_11_22_36_mod.cpt";
files_in[250] = "../data/cpt_sf_BA0387_2012_08_02_14_18_11_mod.cpt";
files_in[251] = "../data/cpt_sf_BA0388_2012_08_02_18_37_13_mod.cpt";
files_in[252] = "../data/cpt_sf_BA0390_2012_08_03_10_37_48_mod.cpt";

//PMT_test_2012_new_group6.root
files_in[253] = "../data/cpt_sf_BA0391_2012_08_03_13_35_57_mod.cpt";
files_in[254] = "../data/cpt_sf_BA0392_2012_08_03_17_20_56_mod.cpt";
files_in[255] = "../data/cpt_sf_BA0393_2012_08_06_11_29_31_mod.cpt";
files_in[256] = "../data/cpt_sf_BA0396_2012_08_06_14_22_42_mod.cpt";
files_in[257] = "../data/cpt_sf_BA0397_2012_08_06_17_22_13_mod.cpt";
files_in[258] = "../data/cpt_sf_BA0398_2012_08_07_11_04_21_mod.cpt";
files_in[259] = "../data/cpt_sf_BA0400_2012_08_07_13_57_45_mod.cpt";
files_in[260] = "../data/cpt_sf_BA0401_2012_08_07_18_29_35_mod.cpt";

//PMT_test_2012_new_group7.root
files_in[261] = "../data/cpt_sf_BA0376_2012_08_15_11_13_28_mod.cpt";
files_in[262] = "../data/cpt_sf_BA0402_2012_08_15_14_04_31_mod.cpt";
files_in[263] = "../data/cpt_sf_BA0403_2012_08_15_16_58_53_mod.cpt";
files_in[264] = "../data/cpt_sf_BA0404_2012_08_16_10_33_17_mod.cpt";
files_in[265] = "../data/cpt_sf_BA0405_2012_08_16_13_27_58_mod.cpt";
files_in[266] = "../data/cpt_sf_BA0407_2012_08_16_16_20_37_mod.cpt";
files_in[267] = "../data/cpt_sf_BA0408_2012_08_16_20_24_22_mod.cpt";
files_in[268] = "../data/cpt_sf_BA0409_2012_08_17_09_42_26_mod.cpt";

//PMT_test_2012_new_group8.root
files_in[269] = "../data/cpt_sf_BA0411_2012_08_17_17_47_32_mod.cpt";
files_in[270] = "../data/cpt_sf_BA0413_2012_08_18_15_36_31_mod.cpt";
files_in[271] = "../data/cpt_sf_BA0422_2012_08_18_18_38_29_mod.cpt";
files_in[272] = "../data/cpt_sf_BA0425_2012_08_18_21_57_29_mod.cpt";
files_in[273] = "../data/cpt_sf_BA0426_2012_08_19_00_34_39_mod.cpt";
files_in[274] = "../data/cpt_sf_BA0425_2012_08_19_12_30_02_mod.cpt";
files_in[275] = "../data/cpt_sf_BA0427_2012_08_19_15_26_13_mod.cpt";
files_in[276] = "../data/cpt_sf_BA0428_2012_08_19_18_29_19_mod.cpt";

//PMT_test_2012_new_group9.root
files_in[277] = "../data/cpt_sf_BA0431_2012_08_19_21_27_59_mod.cpt";
files_in[278] = "../data/cpt_sf_BA0433_2012_08_20_11_23_15_mod.cpt";
files_in[279] = "../data/cpt_sf_BA0435_2012_08_20_14_15_56_mod.cpt";
files_in[280] = "../data/cpt_sf_BA0437_2012_08_20_17_12_54_mod.cpt";
files_in[281] = "../data/cpt_sf_BA0438_2012_08_20_20_04_17_mod.cpt";
files_in[282] = "../data/cpt_sf_BA0386_2012_08_21_11_26_01_mod.cpt";
files_in[283] = "../data/cpt_sf_BA0392_2012_08_21_14_24_07_mod.cpt";
files_in[284] = "../data/cpt_sf_BA0393_2012_08_21_20_19_18_mod.cpt";
files_in[285] = "../data/cpt_sf_BA0411_2012_08_22_10_38_55_mod.cpt";
files_in[286] = "../data/cpt_sf_BA0425_2012_08_22_16_35_33_mod.cpt";

//PMT_test_2012_new_group10.root
files_in[287] = "../data/cpt_sf_BA0433_2012_08_22_19_27_25_mod.cpt";
files_in[288] = "../data/cpt_sf_BA0437_2012_08_23_10_28_54_mod.cpt";
files_in[289] = "../data/cpt_sf_BA0438_2012_08_23_13_26_21_mod.cpt";
files_in[290] = "../data/cpt_sf_BA0427_2012_08_24_18_17_16_mod.cpt";
files_in[291] = "../data/cpt_sf_BA0420_2012_08_27_13_45_51_mod.cpt";
files_in[292] = "../data/cpt_sf_BA0430_2012_08_27_16_46_38_mod.cpt";
files_in[293] = "../data/cpt_sf_BA0434_2012_08_27_19_42_31_mod.cpt";
files_in[294] = "../data/cpt_sf_BA0439_2012_08_28_11_21_16_mod.cpt";
files_in[295] = "../data/cpt_sf_BA0440_2012_08_28_14_23_57_mod.cpt";
files_in[296] = "../data/cpt_sf_BA0441_2012_08_28_17_14_47_mod.cpt";

//PMT_test_2012_new_group11.root
files_in[297] = "../data/cpt_sf_BA0443_2012_08_29_08_20_10_mod.cpt";
files_in[298] = "../data/cpt_sf_BA0444_2012_08_29_11_11_32_mod.cpt";
files_in[299] = "../data/cpt_sf_BA0444_2012_08_29_14_18_40_mod.cpt";
files_in[300] = "../data/cpt_sf_BA0445_2012_08_29_17_24_05_mod.cpt";
files_in[301] = "../data/cpt_sf_BA0446_2012_08_30_11_17_37_mod.cpt";
files_in[302] = "../data/cpt_sf_BA0447_2012_08_30_14_32_42_mod.cpt";
files_in[303] = "../data/cpt_sf_BA0448_2012_08_30_17_47_37_mod.cpt";
files_in[304] = "../data/cpt_sf_BA0449_2012_08_31_08_17_27_mod.cpt";
files_in[305] = "../data/cpt_sf_BA0451_2012_08_31_11_08_11_mod.cpt";
files_in[306] = "../data/cpt_sf_BA0451_2012_08_31_13_31_01_mod.cpt";

//PMT_test_2012_new_group12.root
files_in[307] = "../data/cpt_sf_BA0452_2012_08_31_16_23_42_mod.cpt";
files_in[308] = "../data/cpt_sf_BA0453_2012_09_03_08_06_24_mod.cpt";
files_in[309] = "../data/cpt_sf_BA0454_2012_09_03_10_57_49_mod.cpt";
files_in[310] = "../data/cpt_sf_BA0455_2012_09_03_13_50_48_mod.cpt";
files_in[311] = "../data/cpt_sf_BA0456_2012_09_03_16_41_13_mod.cpt";
files_in[312] = "../data/cpt_sf_BA0457_2012_09_04_08_36_28_mod.cpt";
files_in[313] = "../data/cpt_sf_BA0458_2012_09_04_11_30_08_mod.cpt";
files_in[314] = "../data/cpt_sf_BA0460_2012_09_04_14_19_26_mod.cpt";
files_in[315] = "../data/cpt_sf_BA0461_2012_09_04_17_10_22_mod.cpt";
files_in[316] = "../data/cpt_sf_BA0466_2012_09_05_07_14_28_mod.cpt";
files_in[317] = "../data/cpt_sf_BA0472_2012_09_05_10_05_10_mod.cpt";

//PMT_test_2012_new_group13.root
files_in[318] = "../data/cpt_sf_BA0278_2012_09_19_10_01_24_mod.cpt";
files_in[319] = "../data/cpt_sf_BA0172_2012_09_19_12_51_52_mod.cpt";
files_in[320] = "../data/cpt_sf_BA0267_2012_09_19_15_41_09_mod.cpt";
files_in[321] = "../data/cpt_sf_BA0275_2012_09_19_18_31_09_mod.cpt";
files_in[322] = "../data/cpt_sf_BA0277_2012_09_20_12_04_13_mod.cpt";
files_in[323] = "../data/cpt_sf_BA0319_2012_09_20_19_17_50_mod.cpt";

//PMT_test_2012_old_fix.root
files_in[324] = "../data/cpt_sf_*_mod.cpt";

 int ini_file = 112;  // +1 wrt file 
 int end_file = 122;


  string tree_out = "PMT_test_2012_old_group6c.root";

  create_tree(files_in, ini_file, end_file, tree_out);
}
