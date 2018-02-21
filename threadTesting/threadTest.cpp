#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<string> scripts;

void call_from_thread(int x) {
	system( ( "./"+scripts[x] ).c_str() );
}

int main() {
	scripts.push_back("testScript1.sh");
	scripts.push_back("testScript2.sh");
	scripts.push_back("testScript3.sh");
	scripts.push_back("testScript4.sh");
	vector<thread> th;

	for(int i = 0; i < scripts.size(); i++) {
		th.push_back(thread(call_from_thread, i));
	}

	cout << "main" << endl;

	for(auto &t : th) {
		t.join();
	}
	return 0;
}
