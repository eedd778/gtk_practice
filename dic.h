#include <map>
#include <string>
using namespace std;

class dic
{
public:
  dic()
  {
    strint.clear();
    intstr.clear();
  }

  void findword(string temp)
  {
    siter = strint.find(temp);
  }

  int getdigital()
  {
    return siter->second;
  }

  bool s_end()
  {
    return (siter == strint.end()) ? true : false;
  }

  void encode(string temp, int i)
  {
    strint[temp] = i;
  }

  void decode(string temp, int i)
  {
    intstr[i] = temp;
  }

  int getsize()
  {
    return strint.size();
  }

private:
  map<string, int> strint;
  map<string, int>::iterator siter;
  map<int, string> intstr;
};