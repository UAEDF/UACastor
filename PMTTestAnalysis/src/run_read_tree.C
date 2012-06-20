void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string tree_in = "PMT_test_2012_old_group1.root";

read_tree(tree_in);
}
