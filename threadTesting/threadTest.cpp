#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include "program.h"

using namespace std;

vector<Program> scripts;

void call_from_thread(int x) {
	system( ( "./scripts/"+scripts[x].name ).c_str() );
}

void loadScripts() {
	vector<string> names;
	names.push_back("testScript1.sh");
	names.push_back("testScript2.sh");
	names.push_back("testScript3.sh");
	names.push_back("testScript4.sh");

	for(int i = 0; i < names.size(); i++) {
		Program p;
		p.name = names[i];
		scripts.push_back(p);
	}
}

int main() {
	loadScripts();

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
