#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <QApplication>
#include "LibreBridge.hpp"
#include "Misc.hpp"
#include "Game.hpp"
#include "gui/Common.hpp"
#include "gui/MainWindow.hpp"
#include "gui/Table1SockClient.hpp"
#include "gui/Table2SockClient.hpp"
#include "gui/Table3SockClient.hpp"
#include "gui/Table4SockClient.hpp"
#include "gui/ChatSockClient.hpp"
#include <QtCore/QCoreApplication>
#include <QObject>
#include <unistd.h>

using namespace std;

Options options;

QString lastMessageParsed = "   ";
QString lastCardPlayedMessage ="  ";

QString WebAddress="ws://192.168.1.3";
bool PracticePlay=false;
bool PositionNorth = false;
bool PositionEast = false;
bool PositionSouth = false;
bool PositionWest = false;
bool NorthSeated = false;
bool EastSeated = false;
bool SouthSeated = false;
bool WestSeated = false;
bool iAmSeated = false;
bool Table1=false;
bool Table2=false;
bool Table3=false;
bool Table4=false;

bool showWelcomeWindow = true;
bool showPlayWindow= false;
int sessionStartDeal =20;
int cumPointsNS = 0;
int cumPointsEW =0;
QString T1North="";

int main(int argc, char *argv[])
{
	initializeOptions();
	options.useGui = (argc <= 1);


	if(options.useGui)
	{
        ChatSockClient *socketchat = ChatSockClient::instance();
        socketchat->onConnect(QUrl(QString(WebAddress+":8010")));



       Table1SockClient *socket = Table1SockClient::instance();
       socket->onConnect(QUrl(QString(WebAddress+":8001")));
       Table2SockClient *socket2 = Table2SockClient::instance();
       socket2->onConnect(QUrl(QString(WebAddress+":8002")));
       Table3SockClient *socket3 = Table3SockClient::instance();
       socket3->onConnect(QUrl(QString(WebAddress+":8003")));
       Table4SockClient *socket4 = Table4SockClient::instance();
       socket4->onConnect(QUrl(QString(WebAddress+":8004")));


		if(!DEBUG_COUT) cout.setstate(ios_base::failbit); // ignore console output
        QApplication libreBridgeGUI(argc, argv);

          MainWindow mainWindow;
       // WelcomeWindow welcomeWindow;



     //   qDebug() << "LibreBridgeGUI";
        return libreBridgeGUI.exec();
	}

	for(uint8_t i=1; i<argc; i++)
	{
		if(!strcmp(argv[i], "-C"))
		{
			generateScoringChart();
			return 0;
		}
		else if(!strcmp(argv[i], "-PN") && i+1<argc) options.playerTypes[North] = argv[++i];
		else if(!strcmp(argv[i], "-PE") && i+1<argc) options.playerTypes[East] = argv[++i];
		else if(!strcmp(argv[i], "-PS") && i+1<argc) options.playerTypes[South] = argv[++i];
		else if(!strcmp(argv[i], "-PW") && i+1<argc) options.playerTypes[West] = argv[++i];
        else if(!strcmp(argv[i], "-S") && i+1<argc) options.seed = atol(argv[++i]);
		else
		{
			//TODO display command line help
			cout << "\nLibreBridge version " << to_string(VERSION_MAJOR) << "." << to_string(VERSION_MINOR) << "." << to_string(VERSION_BUILD) << "\n\n";
			return 0;
		}
	}
 // qDebug() << "Game";
	Game game;
	return 0;
}
