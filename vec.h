#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <math.h>
#include <pthread.h>
#include </home/eedd778/gladetest/dic.h>
using namespace std;
struct filename
{
  vector<int> a;
  vector<double> result;
  char *name;
};

struct matrix
{
  vector<int> b;
};

int max(int a, int b)
{
  return a > b ? a : b;
}

class vec
{
public:
  vec()
  {
    open.clear();
  }

  void push(filename obj)
  {
    open.push_back(obj);
  }

  int getsize()
  {
    return open.size();
  }

  int getfilesize(int i)
  {
    return open[i].a.size();
  }

  char *getname(int i)
  {
    return open[i].name;
  }

  void readfile(int i, dic &dirc)
  {
    int j = dirc.getsize();
    string temp;
    fstream file;
    file.open(open[i].name);
    while (!file.eof())
    {
      file >> temp;
      dirc.findword(temp);
      if (dirc.s_end())
      {
        dirc.encode(temp, j);
        dirc.decode(temp, j);
        j++;
        dirc.findword(temp);
      }
      open[i].a.push_back(dirc.getdigital());
    }
  }

  void putzero(int i)
  {
    open[i].result.push_back(0);
  }

  bool empty()
  {
    return open.empty();
  }

  void setname(int i)
  {
    string str = open[i].name;
    string::size_type idx = str.rfind('/', str.length());
    str = str.substr(idx + 1, str.length());
    strcpy(open[i].name, str.c_str());
  }

  void print()
  {
    for (int i = 0; i < open.size(); i++)
    {
      cout << open[i].name << ":[";
      for (int j = 0; j < open[i].result.size(); j++)
      {
        cout << "\'" << open[i].result[j] << "'"
             << ",";
      }
      cout << "]" << endl;
    }
  }

  void dolcs(int x, int y)
  {
    vector<matrix> lcs;
    int m = open[x].a.size();
    int n = open[y].a.size();
    lcs.resize(m + 1);
    for (int i = 0; i < lcs.size(); i++)
      lcs[i].b.resize(n + 1);
    for (int j = 0; j <= n; j++)
      lcs[0].b[j] = 0;
    for (int i = 0; i <= m; i++)
      lcs[i].b[0] = 0;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        lcs[i + 1].b[j + 1] = lcs[i].b[j];
        if (open[x].a[i] == open[y].a[j])
          lcs[i + 1].b[j + 1]++;
        else
          lcs[i + 1].b[j + 1] = max(lcs[i].b[j + 1], lcs[i + 1].b[j]);
      }
    }
    double z = (double)lcs[m].b[n];
    double total1 = (double)open[x].a.size();
    double total2 = (double)open[y].a.size();
    open[x].result.push_back(ceil(z / total1 * 100));
    open[y].result.push_back(ceil(z / total2 * 100));
    //cout << open[x].name << " compare to " << open[y].name << " " << z << endl;
  }

  void writeresult()
  {
    fstream out;
    out.open("/home/eedd778/gladetest/result.html", ios::out); //output data
    out << "<!DOCTYPE html>\n"
        << "<html style=\"height: 100%\">" << endl
        << "  <head>" << endl
        << "    <meta charset=\"utf-8\">" << endl
        << "  </head>" << endl
        << "  <body style=\"height: 100%; margin: 0\">" << endl
        << "  <div id=\"container\" style=\"height: 100%\"></div>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts/echarts.min.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts-gl/echarts-gl.min.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts-stat/ecStat.min.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts/extension/dataTool.min.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts/map/js/china.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts/map/js/world.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://api.map.baidu.com/api?v=2.0&ak=ZUONbpqGBsYGXNIYHicvbAbM\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/echarts/extension/bmap.min.js\"></script>" << endl
        << "    <script type=\"text/javascript\" src=\"http://echarts.baidu.com/gallery/vendors/simplex.js\"></script>" << endl
        << "    <script type=\"text/javascript\">" << endl;
    out << "var dom = document.getElementById(\"container\");" << endl
        << "var myChart = echarts.init(dom);" << endl
        << "var app = {};" << endl
        << "option = null;" << endl
        << "dataMap = {};" << endl
        << "function dataFormatter(obj) {" << endl
        << "  var pList = [";
    for (int i = 0; i < open.size() - 1; i++)
      out << "\'" << open[i].name << "\',";
    out << "\'" << open[open.size() - 1].name << "\'"
        << "];" << endl
        << "  var temp;" << endl
        << "  for (var month = 1; month <= " << open.size() << "; month++) {" << endl
        << "    temp = obj[month.toString()];" << endl
        << "    obj[month + 'sum'] = temp[0];" << endl
        << "    for (var i = 1, len = temp.length; i < len; i++) {" << endl
        << "      obj[month.toString()][i] = {" << endl
        << "        name : pList[i]," << endl
        << "        value : temp[i]}}" << endl
        << "    }" << endl
        << "  return obj;}" << endl;
    out << "dataMap.dataMonth = dataFormatter({" << endl;
    for (int i = 0; i < open.size() - 1; i++)
    {
      out << "  \'" << i + 1 << "\':[";
      for (int j = 0; j < open[i].result.size() - 1; j++)
      {
        out << open[i].result[j] << ",";
      }
      out << open[i].result[open[i].result.size() - 1] << "]," << endl;
    }
    out << "  \'" << open.size() << "\':[";
    for (int j = 0; j < open[open.size() - 1].result.size() - 1; j++)
    {
      out << open[open.size() - 1].result[j] << ",";
    }
    out << open[open.size() - 1].result[open[open.size() - 1].result.size() - 1] << "]});" << endl
        << "option = {" << endl
        << "  baseOption: {" << endl
        << "    timeline: {" << endl
        << "      y:'top'," << endl
        << "      axisType: 'category'," << endl
        << "      autoPlay: false," << endl
        << "      controlStyle:{show:false}," << endl
        << "      tooltip:{formatter:'{b}'}," << endl
        << "      show:true," << endl
        << "      data: [";
    for (int i = 0; i < open.size() - 1; i++)
      out << "\'" << open[i].name << "\',";
    out << "\'" << open[open.size() - 1].name << "\'"
        << "]}," << endl
        << "    title: {" << endl
        << "      text: '資料比對結果'}," << endl
        << "toolbox:{feature:{saveAsImage:{}}},"
        << "    calculable : true," << endl
        << "    tooltip:{formatter:'和{b}比對{c}％相似'}," << endl
        << "    xAxis: [ {" << endl
        << "      name : \"檔案名\"," << endl
        << "      type:'category'," << endl
        << "      show:false," << endl
        << "      axisLabel:{'interval':0}," << endl
        << "      data: [";
    for (int i = 0; i < open.size() - 1; i++)
      out << "\'" << open[i].name << "\',";
    out << "\'" << open[open.size() - 1].name << "\'"
        << "]," << endl
        << "      splitLine: {show: false}}]," << endl
        << "    yAxis: [ {" << endl
        << "      type: 'value'," << endl
        << "      max : 100 }]," << endl
        << "    series: [{ type: 'bar'},]}," << endl
        << " options: [ " << endl;
    for (int i = 0; i < open.size() - 1; i++)
    {
      out << "  {title:{subtext:'" << open[i].name << "'},series: [" << endl;
      out << "    {data: dataMap.dataMonth['" << i + 1 << "']}] }," << endl;
    }
    out << "  {title:{subtext:'" << open[open.size() - 1].name << "'},series: [" << endl;
    out << "    {data: dataMap.dataMonth['" << open.size() << "']}] } ]};" << endl;
    out << "if (option && typeof option === \"object\") " << endl
        << "{myChart.setOption(option, true);}" << endl;
    out << "    </script>" << endl
        << "  </body>" << endl
        << "</html>";
  }

private:
  vector<filename>
      open;
};