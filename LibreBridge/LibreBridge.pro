VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_BUILD = 0
DEBUG_COUT = 1

DEFINES +=	"VERSION_MAJOR=$$VERSION_MAJOR"\
			"VERSION_MINOR=$$VERSION_MINOR"\
			"VERSION_BUILD=$$VERSION_BUILD"\
			"DEBUG_COUT=$$DEBUG_COUT"

TEMPLATE = app
TARGET = LibreBridge
INCLUDEPATH += .

QT = core gui
QT += network
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 

RESOURCES     = LibreBridge.qrc

CONFIG += debug
CONFIG += warn_on
CONFIG += c++14

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -fPIC -Wno-c++11-narrowing
#QMAKE_CXX = g++

# Input
HEADERS +=	src/AIPlayer.hpp \
			src/Bid.hpp \
			src/Card.hpp \
			src/Contract.hpp \
			src/Game.hpp \
			src/HumanPlayer.hpp \
			src/LibreBridge.hpp \
			src/Misc.hpp \
			src/Player.hpp \
			src/AIPlayers/AI_Random.hpp \
			src/gui/BidButton.hpp \
			src/gui/BidWindow.hpp \
			src/gui/CardLayout.hpp \
			src/gui/CardWidget.hpp \
			src/gui/ContractWindow.hpp \
			src/gui/DealOverWindow.hpp \
			src/gui/PlayedCardsLayout.hpp \
			src/gui/PlayWindow.hpp \
                        src/gui/MainWindow.hpp \
			src/gui/DealSelectionWindow.hpp \
			src/gui/SeedValidator.hpp \
			src/gui/PauseClickGrabber.hpp \
                        src/gui/Common.hpp \
                        src/gui/ChatWindow.hpp \
                        src/gui/Table1SockClient.hpp \
                        src/gui/Table2SockClient.hpp \
                        src/gui/Table3SockClient.hpp \
                        src/gui/Table4SockClient.hpp \
                        src/gui/ChatSockClient.hpp \
                        src/gui/TableWindow.hpp \


			
SOURCES +=	src/AIPlayer.cpp \
			src/Bid.cpp \
			src/Card.cpp \
			src/Contract.cpp \
			src/Game.cpp \
			src/HumanPlayer.cpp \
			src/LibreBridge.cpp \
			src/Misc.cpp \
			src/Player.cpp \
			src/AIPlayers/AI_Random.cpp \
			src/gui/BidButton.cpp \
			src/gui/BidWindow.cpp \
			src/gui/CardLayout.cpp \
			src/gui/CardWidget.cpp \
			src/gui/ContractWindow.cpp \
			src/gui/DealOverWindow.cpp \
			src/gui/PlayedCardsLayout.cpp \
			src/gui/PlayWindow.cpp \
                        src/gui/MainWindow.cpp \
			src/gui/DealSelectionWindow.cpp \
			src/gui/SeedValidator.cpp \
			src/gui/PauseClickGrabber.cpp \
                        src/gui/Common.cpp \
                        src/gui/ChatWindow.cpp \
                        src/gui/Table1SockClient.cpp \
                        src/gui/Table2SockClient.cpp \
                        src/gui/Table3SockClient.cpp \
                        src/gui/Table4SockClient.cpp \
                        src/gui/ChatSockClient.cpp \
                        src/gui/TableWindow.cpp \
  #                      qrc_LibreBridge.cpp
