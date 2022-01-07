#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


string Clipboard() {

	 HANDLE clip(0);
	 char* buff;

	OpenClipboard(NULL);

	if (IsClipboardFormatAvailable(CF_TEXT)) clip = GetClipboardData(CF_TEXT);
	else if (IsClipboardFormatAvailable(CF_UNICODETEXT)) clip = GetClipboardData(CF_UNICODETEXT);

	CloseClipboard();

	buff = (char*)clip;
	return buff;
}


string vector_to_fen(vector<string> board[]){
	string fen="";
	for (int i = 0; i < 8; i++) {
		int zeros = 0;
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == "0")zeros++;
			else {
				if (zeros > 0) {
					fen += to_string(zeros);
					zeros = 0;
				}
				if (board[i][j][0] == 'b')fen += board[i][j][1];
				else fen += board[i][j][1] - 32;
			}
		}
		if (zeros > 0) {
			fen += to_string(zeros);
		}
		fen += "/";
	}
	return fen;
}

int main()
{
	cout << "Welcome at chess.com cheats!\n";

	vector<string> board[8];
	for (int i = 0; i < 8; i++)board[i].resize(8,"0");

	string s = Clipboard();

	int pos = s.find("piece");
	cout << "Parsing...\n";

	char side;
	if (s.find("<text x=\"0.75\" y=\"90.75\" font-size=\"2.8\" class=\"coordinate-dark\">1</text>") != string::npos) side = 'w';
	else side = 'b';

	while (pos != string::npos) {
		string piece="";
		piece += s[pos + 6]; 
		piece += s[pos + 7];

		int x = (int)s[pos + 16]-48;
		int y = (int)s[pos + 17]-48;

		board[8-y][x-1] = piece;

		s = s.substr(pos + 5, 4096);
		pos = s.find("piece");
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Parsing to fen...\n";
	string fen = vector_to_fen(board);
	cout << fen << endl;
	cout << "\n Opening cheats at lichess";
	string cmd = "start https://lichess.org/analysis/fromPosition/" + fen + "_";
	cmd += side;
	system(cmd.c_str());

}

