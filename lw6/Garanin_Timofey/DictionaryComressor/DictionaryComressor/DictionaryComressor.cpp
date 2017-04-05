#include "stdafx.h"
#include "IOManager.h"
#include "Compressor.h"
#include "Application.h"

using namespace std;

int main(int argc, char *argv[])
{
	CApplication app(new CIOManager("ds.txt", "out.txt"));
	app.ProcessFile();
    return 0;
}

