#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;
//namespace fs = std::filesystem;
int n, g;
vector<vector<double>> marks(n);
vector<int> clasters(g);
vector<int> typical(g);

const char* string_to_css(string str) {
    char* writable = new char[str.size() + 1];
    copy(str.begin(), str.end(), writable);
    writable[str.size()] = '\0';
    return writable;
}

double distance(int i, int j) {
    double s = (marks[i][0] - marks[j][0]) * (marks[i][0] - marks[j][0]);
    for (int x = 1; x < marks[i].size(); x++) {
        if (marks[i][x] == -1) continue;
        if (marks[j][x] == -1) continue;
        s += (marks[i][x] - marks[j][x]) * (marks[i][x] - marks[j][x]);
      //  if (x == 202) {
    ////        cout << endl;
    //    }
       // s = sqrt(s);
    }
    return sqrt(s);
}

double distance(int i, int j, vector<vector<double>> marks) {
    double s = (marks[i][0] - marks[j][0]) * (marks[i][0] - marks[j][0]);
    for (int x = 1; x < marks[i].size(); x++) {
        if (marks[i][x] == -1) continue;
        if (marks[j][x] == -1) continue;
        s += (marks[i][x] - marks[j][x]) * (marks[i][x] - marks[j][x]);
        //  if (x == 202) {
      ////        cout << endl;
      //    }
         // s = sqrt(s);
    }
    return sqrt(s);
}

vector<double> load_image(const char* path) {
   // path = "C:\\Users\\suzer\\Documents\\SP\\mnist_png-master\\unpackaged_decoded\\0.-transformed.txt";

    fstream s (path, ios_base::in);

    vector<double> ans;
  //  cout << (string)path << endl;
    double a, b, c;
    while (s >> a >> b >> c) {
        if (a != 0) {
            a = 1;
        }
        if (c != 0) {
            c = 1;
        }
        if (b != 0) {
            b = 1;
        }
        ans.push_back(a);
        ans.push_back(b);
        ans.push_back(c);
    }

    //fclose(f);
    s.close();

    return ans;
}

vector<vector<double>> load_images() {
    string mainpath = "C:\\Users\\suzer\\Documents\\SP\\mnist_png-master\\unpackaged_decoded\\";
    vector<vector<double>> ans;
    
    for (int i = 0; i < 10000; i++) {
       // cout << mainpath + to_string(i) + ".-tranformed.txt";
        ans.push_back(load_image(string_to_css(mainpath + to_string(i) + ".-transformed.txt")));
        if (i % 1000 == 0) cout << "CHECK" << endl;
        //cout << (ans[0] == ans[i]) << endl;
    }
    return ans;
}





void claster() {
    n = 10000;
    g = 10;
    marks = load_images();
    typical.assign(g, 0);
    clasters.assign(n, 0);
  //  for (int i = 0; i < n; i++) {
    vector<int> hint = {3, 2, 1, 18, 4, 8, 11, 0, 61, 7};
    for (int i = 0; i < 10; i++) {
        clasters[hint[i]] = i;
        typical[i] = hint[i];
    }

   // }
    int s;
    cin >> s;
    for (int step = 0; step < s; step++) {
        cout << "Processing step " << step << endl;
        for (int id = 0; id < n; id++) {
       //     cout << "Number " << id << endl;
            if (find(typical.begin(), typical.end(), id) != typical.end()) {
       //         cout << "Is a typical element" << endl;
                continue;
            }
            double minv = 2e9;
            int minid = -1;
            for (int i = 0; i < g; i++) {
                double t = distance(id, typical[i]);
      //          cout << "Claster " << i << endl;
      //          cout << "Typical " << typical[i] << endl;
          //      cout << "Distance " << t << endl;
                if (minv > t) {
                    minid = i;
                    minv = t;
                }
            }
            clasters[id] = minid;
       //     cout << "Declared claster " << minid << endl;
        }
 //       cout << "Current clasters " << endl;
        for (int i = 0; i < n; i++) {
    //        cout << "Vertex " << i << endl;
    //        cout << "Claster " << clasters[i] << endl;
        }

   //     cout << "Recalculating clasters" << endl;
        for (int c = 0; c < g; c++) {
   //         cout << "Claster " << c << endl;
            vector<double> sum(marks[0].size());
            int cnt = 0;
            for (int id = 0; id < n; id++) {
                if (clasters[id] != c) continue;
                cnt++;
                for (int i = 0; i < marks[id].size(); i++) {
                    sum[i] += marks[id][i];
                }
            }
            for (int i = 0; i < g; i++) {
                sum[i] /= (double)cnt;
            }
        //    cout << "Sum" << endl;
           // for (int el : sum) cout << el << " ";
         //   cout << endl;

            double minv = 2e9;
            int minid = -1;
            marks.push_back(sum);
            for (int id = 0; id < n; id++) {
                if (clasters[id] != c) continue;
                double t = distance(n, id);
   //             cout << "Vertex " << id << endl;
  //              cout << "Distance " << t << endl;
                if (minv > t) {
                    minv = t;
                    minid = id;
                }

            }
            marks.pop_back();
   //         cout << "Assigned typical " << minid << endl;
            typical[c] = minid;
        }
    }
    cout << "Clasterisation complete" << endl;
    system("copy NUL clasterdata.txt");
    for (int i = 0; i < n; i++) {
        cout << clasters[i] << " ";

    }
    fstream f("clasterdata.txt", ios_base::out);

    for (int i = 0; i < 10; i++) {
        f << typical[i] << " ";
    }
    f.close();
    cout << "Claster data saved" << endl;
}

void getchar(vector<double> loaded_image, vector<vector<double>> marks) {
    typical.assign(10, 0);
    fstream f("clasterdata.txt", ios_base::in);
    for (int i = 0; i < 10; i++) {
        f >> typical[i];
    }
    f.close();

    marks.push_back(loaded_image);
    int minv = 2e9;
    int minid = -1;
    for (int i = 0; i < 10; i++) {
        double t = distance(n, typical[i], marks);
        if (minv > t) {
            minv = t;
            minid = i;
        }
    }
    cout << "Probable character " << minid << endl;
   
}

int main() {
    string a;
    cin >> a;
    if (a == "0") {
        claster();
    }
    else {
        getchar(load_image(string_to_css(a)), load_images());
    }
    
}