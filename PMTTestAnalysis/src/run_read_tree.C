void run_read_tree()
{
gROOT -> Reset();
gROOT -> ProcessLine(".L read_tree.C++");

string tree_in = "test_tree.root";

read_tree(tree_in);
}
