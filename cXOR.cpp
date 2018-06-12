/*
	Name: Cripto XOR
	Author: Erick Oliveira
	Date: 06/11/18
	Description: Cryptographic Project
*/

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

#define cls system("cls")
#define pause system("pause")
#define SetColorGreen system("color 0a")
#define exit exit(0)
#define del_pw system("del password.dat")
#define del_tx system("del text.dat")
#define MAX_ENT 10000
#define MAX_PSW 256
#define send_enc system("python mail.py")
#define send_dec system("python mail2.py")
#define MAX_DST 250

void menu();
void encode();
void decode();
void destroy();
string to_bin(char chr);

int main(void)
{
	SetConsoleTitle("Cripto XOR");
	SetColorGreen;
	menu();
}

void menu()
{
	int op;
	cout << "\t Cripto XOR by Cripto S.a\n\n";
	cout << " 1 - Encode\n 2 - Decode\n 3 - Exit\n\n Option: ";
	cin >> op;

	switch(op)
	{
		case 1:
			cls;
			encode();
			break;
		case 2:
			cls;
			decode();
			break;
		case 3:
			exit;
		default:
			cls;
			menu();
	}
}

void destroy()
{
	del_pw;
	del_tx;
}

string to_bin(char chr)
{
	int i, tam;
	char buff[32];
	
	itoa(chr,buff,2);
	tam = strlen(buff);
	string response = "";
	if (tam < 8) for (i = 0; i < 8-tam; i++) response += '0';
	for (i = 0; i < tam; i++) response += buff[i];
	
	return response;
}

void encode()
{
	int i, j;
	string ent, pass;
	
	fflush(stdin);
	cout << "Enter your password:\n\n";
	getline(cin, pass);
	cls;
	cout << "Enter your text:\n\n";
	getline(cin, ent);
	
	FILE *tx = fopen("text.dat", "a");
	FILE *pw = fopen("password.dat", "a");
	if (!pw or !tx) exit;
	string aux;
	
	for (i = 0; i < pass.length(); i++)
	{
		aux = to_bin(pass[i]);
		for (j = 0; j < aux.length(); j++) fprintf(pw, "%c", aux[j]);
	}
	
	for (i = 0; i < ent.length(); i++)
	{
		aux = to_bin(ent[i]);
		for (j = 0; j < aux.length(); j++) fprintf(tx, "%c", aux[j]);
	}
	
	float mult;
	float a = 8*ent.length();
	float b = 8*pass.length();
	bool consider;
	
	if (a > b)
	{
		mult = a/b;
		consider = true;
	}
	else
	{
		mult = b/a;
		consider = false;
	}
	mult = ceil(mult);
	
	if (mult != 1)
	{
		mult--;
		if (a > b)
		{
			while (mult--)
			{
				for (i = 0; i < pass.length(); i++)
				{
					aux = to_bin(pass[i]);
					for (j = 0; j < aux.length(); j++) fprintf(pw, "%c", aux[j]);
				}
			}
		}
		else
		{
			while (mult--)
			{
				for (i = 0; i < ent.length(); i++)
				{
					aux = to_bin(ent[i]);
					for (j = 0; j < aux.length(); j++) fprintf(tx, "%c", aux[j]);
				}
			}	
		}
	}
	fprintf(pw, "\n");
	fprintf(tx, "\n");
	
	fclose(pw);
	fclose(tx);
	
	FILE *open_pw = fopen("password.dat", "r");
	FILE *open_tx = fopen("text.dat", "r");
	if (!open_tx or !open_pw) exit;
	
	char *text = (char *) malloc(sizeof(char) * MAX_ENT * 8);
	char *pswd = (char *) malloc(sizeof(char) * MAX_PSW * 8);
	char *out = (char *) malloc(sizeof(char) * MAX_ENT * 8);
	if (!text or !pswd or !out) exit;
	
	fscanf(open_tx, " %[^\n]s", text);
	fscanf(open_pw, " %[^\n]s", pswd);
	int cont = 0;
	
	if (consider == true)
	{
		for (i = 0; i < strlen(text); i++)
		{
			if (text[i] == '0' and pswd[i] == '0') out[cont] = '0';
			else if (text[i] == '0' and pswd[i] == '1') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '0') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '1') out[cont] = '0';
			cont++;
		}
	}
	else
	{		
		for (i = 0; i < strlen(pswd); i++)
		{
			if (text[i] == '0' and pswd[i] == '0') out[cont] = '0';
			else if (text[i] == '0' and pswd[i] == '1') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '0') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '1') out[cont] = '0';
			cont++;
		}
	}
	fclose(open_tx);
	fclose(open_pw);
	
	cls;
	cout << "Encoded text:\n\n";
	for (i = 0; i < cont; i++) cout << out[i];
	cout << endl << endl << endl;
	destroy();
	
	int op2;
	cout << " 1 - Save in a .txt file\n 2 - Send to my e-mail\n 3 - Return to menu\n 4 - Exit\n\n";
	cout << " Option: ";
	cin >> op2;
	
	if (op2 == 2)
	{
		FILE *exp = fopen("config.py", "w");
		if(!exp) exit;
		
		char *dst = (char *) malloc(sizeof(char) * MAX_DST);
		if (!dst) exit;
		
		cout << "\n\nDestinatination Address: ";
		scanf(" %[^\n]s", dst);
		
		string address = ""; //Edit the source address here (gmail)
	    string pass = ""; //Edit the source address password here (gmail)
	    char chr = '"';
	    
		fprintf(exp, "EMAIL_ADDRESS = %c", chr);
		int i;
		for (i = 0; i < address.length(); i++) fprintf(exp, "%c", address[i]);
		fprintf(exp, "%c\n", chr);
		fprintf(exp, "PASSWORD = %c", chr);
		for (i = 0; i < pass.length(); i++) fprintf(exp, "%c", pass[i]);
		fprintf(exp, "%c\n", chr);
		fprintf(exp, "EMAIL_DEST = %c", chr);
		for (i = 0; i < strlen(dst); i++) fprintf(exp, "%c", dst[i]);
		fprintf(exp, "%c\n", chr);
		fprintf(exp, "MSGE = %c", chr);
		for (i = 0; i < strlen(out); i++) fprintf(exp, "%c", out[i]);
		fprintf(exp, "%c", chr);
		fclose(exp);
		cout << "\n\nSending...  ";
		send_enc;
	}
	else if (op2 == 1)
	{
		FILE *output = fopen("output.txt", "w");
		if(!output) exit;	
		for (i = 0; i < strlen(out); i++) fprintf(output, "%c", out[i]);
		fclose(output);
	}
	else if (op2 == 3)
	{
		cls;
		menu();
	}
	else if (op2 == 4)
	{
		exit;
	}
	
	cout << endl << endl;
	pause;
	cls;
	menu();	
}

void decode()
{
	int i, j;
	string ent, pass;
	
	fflush(stdin);
	cout << "Enter your password:\n\n";
	getline(cin, pass);
	cls;
	cout << "Enter your text:\n\n";
	getline(cin, ent);
	
	FILE *tx = fopen("text.dat", "a");
	FILE *pw = fopen("password.dat", "a");
	if (!pw or !tx) exit;
	string aux;
	
	for (i = 0; i < pass.length(); i++)
	{
		aux = to_bin(pass[i]);
		for (j = 0; j < aux.length(); j++) fprintf(pw, "%c", aux[j]);
	}
	
	for (i = 0; i < ent.length(); i++) fprintf(tx, "%c", ent[i]);

	float mult;
	float a = ent.length();
	float b = 8*pass.length();
	bool consider;
	
	if (a > b)
	{
		mult = a/b;
		consider = true;
	}
	else
	{
		mult = b/a;
		consider = false;
	}
	mult = ceil(mult);
	
	if (mult != 1)
	{
		mult--;
		if (a > b)
		{
			while (mult--)
			{
				for (i = 0; i < pass.length(); i++)
				{
					aux = to_bin(pass[i]);
					for (j = 0; j < aux.length(); j++) fprintf(pw, "%c", aux[j]);
				}
			}
		}
		else
		{
			while (mult--)
			{
				for (i = 0; i < ent.length(); i++) fprintf(tx, "%c", ent[i]);
			}	
		}
	}
	fprintf(pw, "\n");
	fprintf(tx, "\n");
	
	fclose(pw);
	fclose(tx);
	
	FILE *open_pw = fopen("password.dat", "r");
	FILE *open_tx = fopen("text.dat", "r");
	if (!open_tx or !open_pw) exit;
	
	char *text = (char *) malloc(sizeof(char) * MAX_ENT * 8);
	char *pswd = (char *) malloc(sizeof(char) * MAX_PSW * 8);
	char *out = (char *) malloc(sizeof(char) * MAX_ENT * 8);
	if (!text or !pswd or !out) exit;
	
	fscanf(open_tx, " %[^\n]s", text);
	fscanf(open_pw, " %[^\n]s", pswd);
	int cont = 0;
	
	if (consider == true)
	{
		for (i = 0; i < strlen(text); i++)
		{
			if (text[i] == '0' and pswd[i] == '0') out[cont] = '0';
			else if (text[i] == '0' and pswd[i] == '1') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '0') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '1') out[cont] = '0';
			cont++;
		}
	}
	else
	{		
		for (i = 0; i < strlen(pswd); i++)
		{
			if (text[i] == '0' and pswd[i] == '0') out[cont] = '0';
			else if (text[i] == '0' and pswd[i] == '1') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '0') out[cont] = '1';
			else if (text[i] == '1' and pswd[i] == '1') out[cont] = '0';
			cont++;
		}
	}
	fclose(open_tx);
	fclose(open_pw);
	destroy();
	
	cls;
	cout << "Decoded text:\n\n";
	string chr;
	char chr2[7], c;
	cont = 0;
	
	for (i = 0; i < strlen(out); i+=8)
	{
		chr.clear();
		chr += out[i];
		chr += out[i + 1];
		chr += out[i + 2];
		chr += out[i + 3];
		chr += out[i + 4];
		chr += out[i + 5];
		chr += out[i + 6];
		chr += out[i + 7];
		for (j = 0; j <= 7; j++) chr2[j] = chr[j];
		
		c = strtol(chr2, 0 ,2);
		out[cont] = c;
		cont++;
		printf("%c", c);
	}
	
    int op2;
	cout << " \n\n\n 1 - Save in a .txt file\n 2 - Send to my e-mail\n 3 - Return to menu\n 4 - Exit\n\n";
	cout << " Option: ";
	cin >> op2;
	
	if (op2 == 2)
	{
		FILE *exp = fopen("config.py", "w");
		if(!exp) exit;
		
		char *dst = (char *) malloc(sizeof(char) * MAX_DST);
		if (!dst) exit;
		
		cout << "\n\nDestinatination Address: ";
		scanf(" %[^\n]s", dst);
		
		string address = ""; //Edit the source address here (gmail)
	    string pass = ""; //Edit the source address password here (gmail)
	    char chr_aux = '"';
	    
		fprintf(exp, "EMAIL_ADDRESS = %c", chr_aux);
		int i;
		for (i = 0; i < address.length(); i++) fprintf(exp, "%c", address[i]);
		fprintf(exp, "%c\n", chr_aux);
		fprintf(exp, "PASSWORD = %c", chr_aux);
		for (i = 0; i < pass.length(); i++) fprintf(exp, "%c", pass[i]);
		fprintf(exp, "%c\n", chr_aux);
		fprintf(exp, "EMAIL_DEST = %c", chr_aux);
		for (i = 0; i < strlen(dst); i++) fprintf(exp, "%c", dst[i]);
		fprintf(exp, "%c\n", chr_aux);
		fprintf(exp, "MSGE = %c", chr_aux);
		for (i = 0; i < cont; i++) fprintf(exp, "%c", out[i]);
		fprintf(exp, "%c", chr_aux);
		fclose(exp);
		cout << "\n\nSending...  ";
		send_dec;
	}
	else if (op2 == 1)
	{
		FILE *output = fopen("output.txt", "w");
		if(!output) exit;	
		for (i = 0; i < cont; i++) fprintf(output, "%c", out[i]);
		fclose(output);
	}
	else if (op2 == 3)
	{
		cls;
		menu();
	}
	else if (op2 == 4)
	{
		exit;
	}
	
	cout << endl << endl;
	pause;
	cls;
	menu();	
}
