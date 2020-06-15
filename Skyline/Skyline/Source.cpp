#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct node {
	int number, cor, length;
	string newface;
} Node;

void sort(vector<node> & a);
void percolDwn(vector<node> &a, int i, int n);

template <class Comparable>
class Mpqueue
{
	vector<int> dimension;
	vector<Comparable> allData;
	int size;
public:
	Mpqueue();
	//~Mpqueue();
	void createHeap(vector<Comparable>);
	void insert(const Comparable &value, int label);
	bool isEmpty();
	Comparable getMax();
	Comparable Remove(int label);
	void percolateDwn(int p);
	int loc(int l);
	bool isempty();
};

template <class Comparable>
Mpqueue<Comparable>::Mpqueue() { size = 0; }

template <class Comparable>
void Mpqueue<Comparable>::createHeap(vector<Comparable> add)
{
	allData = add;
	size = add.size()-1;
	for (int j = size/2; j > 0; j--)
		percolateDwn(j);
}

template <class Comparable>
void Mpqueue<Comparable>::insert(const Comparable &addTo, int s) {

	if (allData.size() == 0){
		allData.push_back(addTo);
	}
	allData.push_back(addTo);
	int way = size + 1;
	size++;
	for (; way > 1 && addTo < allData[way / 2]; way = way/2){
		allData[way] = allData[way / 2];
	}
		
	allData[way] = addTo;
	if (dimension.size() < s + 1) {
		dimension.resize(s + 1);
	}
	Comparable t;
	for (int i = 1; i <= size; i++) {
		t = allData[i];
		dimension[t] = i;
	}
}

template <class Comparable>
bool Mpqueue<Comparable>::isEmpty() {
	if (size == 0){
		return true;

	}
	return false;
}

template <class Comparable>
Comparable Mpqueue<Comparable>::getMax() {
	if (size == 0) {
		return 0;
	}
	else
	{
		int c = size / 2 + 1;
		Comparable m = allData[c];
		for (; c<size; c++) {
			if (m <= allData[c + 1]) {
				m = allData[c + 1];
			}
		}
		return m;
	}
}

template <class Comparable>
Comparable Mpqueue<Comparable>::Remove(int s)
{
	Comparable ty = allData[s];

	allData[s] = allData[size];
	percolateDwn(s);

	size--;
	allData.resize(size + 1);
	Comparable tem;
	for (int k = 1; k <= size; k++)
	{
		tem = allData[k];
		dimension[tem] = k;
	}
	return ty;
}

template <class Comparable>
void Mpqueue<Comparable>::percolateDwn(int dwn)
{
	int lastadded;
	Comparable tmp = allData[dwn];

	for (; dwn * 2 <= size; dwn = lastadded)
	{
		lastadded = dwn * 2;
		if (lastadded != size &&  allData[lastadded + 1] < allData[lastadded])
			lastadded++;
		if (allData[lastadded] < tmp)
			allData[dwn] = allData[lastadded];
		else {
			break;
		}
	}
	allData[dwn] = tmp;
}

template <class Comparable>
int Mpqueue<Comparable>::loc(int l) {
	return dimension[l];
}

template <class Comparable>
bool Mpqueue<Comparable>::isempty() {
	if (size == 0)
		return true;
	return false;
}

inline int nFace(int e)
{
	return 2 * e + 1;
}

int main()
{
	int number, x, y;
	Mpqueue<int> myq;
	ifstream input;
	string str;
	input.open("input.txt");
	if (input.fail()) {
		cout << "Error! input file can not be opened" << endl;
		system("pause");
		return 0;
	}
	getline(input, str);
	istringstream stream(str);
	stream >> number;
	vector<node> vec(number * 2 + 1);
	int f = 1, q = 1;
	while (!input.eof())
	{
		getline(input, str);
		istringstream istr(str);
		istr >> x;
		vec[f].number = q;
		vec[f].cor = x;
		vec[f].newface = "Left";
		istr >> y >> x;
		vec[f].length = y;
		vec[f + 1].number = q;
		vec[f + 1].cor = x;
		vec[f + 1].newface = "Right";
		vec[f + 1].length = y;
		f = f + 2;
		q++;
	}

	sort(vec);

	for (int i = vec.size(); i>1; i--) {
		vec[i-1] = vec[i-2];
	}

	if (vec[1].cor != 0) {
		cout << 0 << " " << 0 << endl;
	}

	int big = -1;
	for (int i = 1; i<vec.size(); i++)
	{
		if (vec[i].newface == "Left")
		{
			myq.insert(vec[i].length, vec[i].length);
			if (myq.isEmpty())
			{
				cout << vec[i].cor << " " << 0 << endl;
				big = 0;
			}
			else if (myq.getMax()>big)
			{
				cout << vec[i].cor << " " << vec[i].length << endl;
				big = myq.getMax();
			}
		}
		else
		{
			myq.Remove(myq.loc(vec[i].length));
			big = myq.getMax();
			if (myq.isEmpty())
			{
				cout << vec[i].cor << " " << 0 << endl;
				big = 0;
			}
			else if (vec[i].length >= big)
			{
				cout << vec[i].cor << " " << vec[i].length << endl;
				big = myq.getMax();
			}
		}
	}
	return 0;
}

void percolDwn(vector<node> &a, int i, int n)
{
	int newDown;
	int tmp, build, len;
	string newface;
	build = a[i].number;
	newface = a[i].newface;
	len = a[i].length;

	for (tmp = a[i].cor; nFace(i) < n; i = newDown)
	{
		newDown = nFace(i);
		if (newDown != n - 1 && a[newDown].cor < a[newDown + 1].cor)
			newDown++;
		if (a[newDown].cor > tmp)
			a[i] = a[newDown];
		else {
			break;
		}
	}
	a[i].cor = tmp;
	a[i].number = build;
	a[i].newface = newface;
	a[i].length = len;
}

void sort(vector<node> & a)
{
	for (int v = a.size() / 2; v > 0; v--) {
		percolDwn(a, v, a.size());
	}
	for (int h = a.size() - 1; h >0; h--) {
		swap(a[0], a[h]);
		percolDwn(a, 0, h);
	}
}