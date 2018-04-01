#include <iostream>
#include <fstream>
using namespace std;

int main()
{

ofstream  outfile("xiaogongwei.vim",ios::out);
for(int i = 0;i < 100;i++)
{
    cout << "xiaogongwei123" << endl;
    cout << "xiaogongwei123" << endl;
    outfile << "xiaogongwei123" << endl;
    outfile << "xiaogongwei123" << endl; 
    outfile << "xiaogongwei123" << endl;
}

outfile.close();

return 0;
}
