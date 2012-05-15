void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string tree_in = "test_tree.root";

Read_tree(tree_in);
}
