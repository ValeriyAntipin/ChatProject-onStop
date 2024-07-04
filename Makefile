# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++11

# Исходные файлы
SRCS = User.cpp Message.cpp Chat.cpp TCPclient.cpp TCPServer.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемые файлы
TARGETS = TCPclient TCPServer

# Правило по умолчанию
all: $(TARGETS)

# Создание исполняемого файла TCPclient
TCPclient: User.o Message.o Chat.o TCPclient.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Создание исполняемого файла TCPserver
TCPServer: User.o Message.o Chat.o TCPServer.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции исходных файлов
%.o: %.
